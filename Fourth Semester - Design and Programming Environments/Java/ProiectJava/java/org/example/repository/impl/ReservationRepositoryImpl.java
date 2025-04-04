package org.example.repository.impl;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.exception.RepositoryException;
import org.example.modul.Reservation;
import org.example.modul.Trip;
import org.example.modul.validator.Validator;
import org.example.repository.interfaces.ReservationRepository;
import org.example.repository.utils.JdbcUtils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Properties;

public class ReservationRepositoryImpl implements ReservationRepository {
    protected JdbcUtils jdbcUtils;
    protected Validator<Reservation> validator;
    protected static final Logger logger = LogManager.getLogger();

    public ReservationRepositoryImpl(Properties properties, Validator<Reservation> validator) {
        logger.info("Initializing ReservationDatabaseRepository with properties: {}", properties);

        this.jdbcUtils = new JdbcUtils(properties);
        this.validator = validator;
    }

    private Reservation getReservationFromSet(ResultSet result) throws SQLException {
        Integer id = result.getInt("id");
        Integer numberOfReservedSeats = result.getInt("numberOfReservedSeats");

        String nameClient = result.getString("clientName");
        String contactClient = result.getString("clientContact");

        Integer tripId = result.getInt("tripId");
        String destination = result.getString("destination");
        String transportCompany = result.getString("transportCompany");
        String departure = result.getString("departureDate");
        Double price = result.getDouble("price");
        Integer numberOfAvailableSeats = result.getInt("numberOfAvailableSeats");
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
        LocalDateTime departureDate = LocalDateTime.parse(departure, formatter);
        Trip trip = new Trip(destination, transportCompany, departureDate, price, numberOfAvailableSeats);
        trip.setId(tripId);

        Reservation reservation = new Reservation(trip, nameClient, contactClient, numberOfReservedSeats);
        reservation.setId(id);
        return reservation;
    }

    @Override
    public Optional<Reservation> findOne(Integer id) {
        //how manage if trip, client or reservation is null/

        logger.traceEntry("finding reservation with id {}", id);

        Connection connection = jdbcUtils.getConnection();

        String sql = "select " +
                "r.id as id, r.numberOfReservedSeats as numberOfReservedSeats, " +
                "r.clientName AS clientName, r.clientContact AS clientContact, " +
                "t.id as tripId, t.destination as destination, t.transportCompany as transportCompany, " +
                "t.departureDate AS departureDate, t.price AS price, t.numberOfAvailableSeats as numberOfAvailableSeats " +
                "from reservation r " +
                "inner join trip t on t.id = r.tripId " +
                "where r.id = ?";
        Reservation reservation = null;
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setInt(1, id);
            try (ResultSet result = preparedStatement.executeQuery()) {
                if (result.next()) {
                    reservation = getReservationFromSet(result);
                    logger.trace("Found reservation: {}", reservation);
                } else {
                    logger.warn("No reservation found with id {}", id);
                }
            }
        } catch (SQLException exception) {
            logger.error(exception);
        }

        logger.traceExit();
        return Optional.ofNullable(reservation);
    }

    @Override
    public Iterable<Reservation> findAll() {
        logger.traceEntry();

        Connection connection = jdbcUtils.getConnection();
        List<Reservation> reservations = new ArrayList<>();

        String sql = "select " +
                "r.id as id, r.numberOfReservedSeats as numberOfReservedSeats, " +
                "r.clientName AS clientName, r.clientContact AS clientContact, " +
                "t.id as tripId, t.destination as destination, t.transportCompany as transportCompany, " +
                "t.departureDate AS departureDate, t.price AS price, t.numberOfAvailableSeats as numberOfAvailableSeats " +
                "from reservation r " +
                "inner join trip t on t.id = r.tripId ";
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            try (ResultSet result = preparedStatement.executeQuery()) {
                while (result.next()) {
                    Reservation reservation = getReservationFromSet(result);
                    if (reservation != null) {
                        reservations.add(reservation);
                    }
                }
            }
        } catch (SQLException exception) {
            logger.error(exception);
        }

        logger.traceExit("Found reservations: {}", reservations);
        return reservations;
    }

    @Override
    public Optional<Reservation> save(Reservation entity) {
        logger.traceEntry("saving reservation {}", entity);

        validator.validate(entity);

        Connection connection = jdbcUtils.getConnection();

        try (PreparedStatement preparedStatement = connection.prepareStatement("insert into reservation (tripId, clientName, clientContact, numberOfReservedSeats) values (?, ?, ?, ?)")) {
            preparedStatement.setInt(1, entity.getTrip().getId());
            preparedStatement.setString(2, entity.getClientName());
            preparedStatement.setString(3, entity.getClientContact());
            preparedStatement.setInt(4, entity.getNumberOfReservedSeats());
            int result = preparedStatement.executeUpdate();
            if (result == 0) {
                logger.warn("Failed to save reservation {}", entity);
            } else {
                Optional<Reservation> reservationF = findReservation(entity.getTrip().getId(), entity.getClientName(), entity.getClientContact(), entity.getNumberOfReservedSeats());
                entity.setId(reservationF.get().getId());
                logger.trace("Successfully saved reservation {}", entity);
            }
        } catch (SQLException exception) {
            logger.error(exception);
            throw new RepositoryException("Error saving reservation in database", exception);
        }

        logger.traceExit();
        return Optional.of(entity);
    }

    @Override
    public Optional<Reservation> delete(Integer integer) {
        logger.traceEntry("deleting reservation with id {}", integer);

        if (integer == null || integer < 0) {
            throw new IllegalArgumentException("Reservation id is null or negative");
        }
        Optional<Reservation> reservation = findOne(integer);
        if (reservation.isEmpty()) {
            throw new RepositoryException("This reservation doesn't exists");
        }

        Connection connection = jdbcUtils.getConnection();

        try (PreparedStatement preparedStatement = connection.prepareStatement("delete from reservation where id = ?")) {
            preparedStatement.setInt(1, integer);

            int result = preparedStatement.executeUpdate();
            if (result == 0) {
                logger.warn("Failed to delete reservation {}", reservation);
            } else {
                logger.trace("Successfully deleted reservation {}", reservation);
            }
        } catch (SQLException exception) {
            logger.error(exception);
            throw new RepositoryException("Error deleting reservation in database", exception);
        }

        logger.traceExit();
        return reservation;
    }

    @Override
    public Optional<Reservation> update(Reservation reservation) {
        logger.traceEntry("updating reservation {}", reservation);

        validator.validate(reservation);

        Connection connection = jdbcUtils.getConnection();

        try (PreparedStatement preparedStatement = connection.prepareStatement("update reservation set tripId = ?, " +
                "clientName = ?, clientName = ?, numberOfReservedSeats = ? where id = ?")) {
            preparedStatement.setInt(1, reservation.getTrip().getId());
            preparedStatement.setString(2, reservation.getClientName());
            preparedStatement.setString(3, reservation.getClientContact());
            preparedStatement.setInt(4, reservation.getNumberOfReservedSeats());
            preparedStatement.setInt(5, reservation.getId());
            int result = preparedStatement.executeUpdate();

            if (result == 0) {
                logger.warn("Failed to update reservation {}", reservation);
            } else {
                logger.trace("Successfully updated reservation {}", reservation);
            }
        } catch (SQLException exception) {
            logger.error(exception);
            throw new RepositoryException("Error updating reservation in database", exception);
        }

        logger.traceExit();
        return Optional.of(reservation);
    }

    @Override
    public Optional<Reservation> findReservation(Integer tripId, String nameClient, String contactClient, Integer numberOfReservedSeats) {
        logger.trace("Finding reservation with tripId {}, clientName {}, contactClient {}, numberOfReservedSeats {}",
                tripId, nameClient, contactClient, numberOfReservedSeats);

        String sql = "SELECT " +
                "r.id AS id, r.numberOfReservedSeats AS numberOfReservedSeats, " +
                "r.clientName AS clientName, r.clientContact AS clientContact, " +
                "t.id AS tripId, t.destination AS destination, t.transportCompany AS transportCompany, " +
                "t.departureDate AS departureDate, t.price AS price, t.numberOfAvailableSeats AS numberOfAvailableSeats " +
                "FROM reservation r " +
                "INNER JOIN trip t ON t.id = r.tripId " +
                "WHERE r.tripId = ? AND r.clientName = ? AND r.clientContact = ? AND r.numberOfReservedSeats = ?";

        try (Connection connection = jdbcUtils.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setInt(1, tripId);
            preparedStatement.setString(2, nameClient);
            preparedStatement.setString(3, contactClient);
            preparedStatement.setInt(4, numberOfReservedSeats);

            try (ResultSet result = preparedStatement.executeQuery()) {
                if (result.next()) {
                    Reservation reservation = getReservationFromSet(result);
                    logger.trace("Found reservation: {}", reservation);
                    return Optional.of(reservation);
                } else {
                    logger.warn("No reservation found with tripId {}, clientName {}, contactClient {}, numberOfReservedSeats {}",
                            tripId, nameClient, contactClient, numberOfReservedSeats);
                }
            }
        } catch (SQLException e) {
            logger.error("Database error: ", e);
        }

        logger.traceExit();
        return Optional.empty();
    }

    @Override
    public Iterable<Reservation> findReservationsByTrip(Integer tripId) {
        logger.trace("Finding reservations with tripId {}", tripId);

        Connection connection = jdbcUtils.getConnection();
        List<Reservation> reservations = new ArrayList<>();

        String sql = "select " +
                "r.id as id, r.numberOfReservedSeats as numberOfReservedSeats, " +
                "r.clientName AS clientName, r.clientContact AS clientContact, " +
                "t.id as tripId, t.destination as destination, t.transportCompany as transportCompany, " +
                "t.departureDate AS departureDate, t.price AS price, t.numberOfAvailableSeats as numberOfAvailableSeats " +
                "from reservation r " +
                "inner join trip t on t.id = r.tripId " +
                "where r.tripId = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setInt(1, tripId);
            try (ResultSet result = preparedStatement.executeQuery()) {
                while (result.next()) {
                    Reservation reservation = getReservationFromSet(result);
                    if (reservation != null) {
                        reservations.add(reservation);
                    }
                }
            }
        } catch (SQLException exception) {
            logger.error(exception);
        }

        logger.traceExit("Found reservations: {}", reservations);
        return reservations;
    }

    @Override
    public Iterable<Reservation> findReservationsByClient(String clientName) {
        logger.trace("Finding reservations with clientName {}", clientName);

        Connection connection = jdbcUtils.getConnection();

        List<Reservation> reservations = new ArrayList<>();
        String sql = "select " +
                "r.id as id, r.numberOfReservedSeats as numberOfReservedSeats, " +
                "r.clientName AS clientName, r.clientContact AS clientContact, " +
                "t.id as tripId, t.destination as destination, t.transportCompany as transportCompany, " +
                "t.departureDate AS departureDate, t.price AS price, t.numberOfAvailableSeats as numberOfAvailableSeats " +
                "from reservation r " +
                "inner join trip t on t.id = r.tripId " +
                "where r.clientName = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, clientName);
            try (ResultSet result = preparedStatement.executeQuery()) {
                while (result.next()) {
                    Reservation reservation = getReservationFromSet(result);
                    reservations.add(reservation);
                }
            }
        } catch (SQLException exception) {
            logger.error(exception);
        }

        logger.traceExit("Found reservations: {}", reservations);
        return reservations;
    }

}

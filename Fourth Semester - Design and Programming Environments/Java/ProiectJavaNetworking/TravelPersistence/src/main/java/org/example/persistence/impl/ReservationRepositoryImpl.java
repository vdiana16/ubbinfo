package org.example.persistence.impl;



import org.example.model.Reservation;
import org.example.model.Tour;
import org.example.model.validator.Validator;
import org.example.persistence.interfaces.ReservationRepository;
import org.example.persistence.utils.JdbcUtils;
import org.example.persistence.utils.RepositoryException;

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

    public ReservationRepositoryImpl(Properties properties, Validator<Reservation> validator) {
        this.jdbcUtils = new JdbcUtils(properties);
        this.validator = validator;
    }

    private Reservation getReservationFromSet(ResultSet result) throws SQLException {
        Integer id = result.getInt("id");
        Integer numberOfReservedSeats = result.getInt("numberOfReservedSeats");

        String nameClient = result.getString("clientName");
        String contactClient = result.getString("clientContact");

        Integer tourId = result.getInt("tourId");
        String destination = result.getString("destination");
        String transportCompany = result.getString("transportCompany");
        String departure = result.getString("departureDate");
        Double price = result.getDouble("price");
        Integer numberOfAvailableSeats = result.getInt("numberOfAvailableSeats");
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
        LocalDateTime departureDate = LocalDateTime.parse(departure, formatter);
        Tour tour = new Tour(destination, transportCompany, departureDate, price, numberOfAvailableSeats);
        tour.setId(tourId);

        Reservation reservation = new Reservation(tour, nameClient, contactClient, numberOfReservedSeats);
        reservation.setId(id);
        return reservation;
    }

    @Override
    public Optional<Reservation> findOne(Integer id) {
        Connection connection = jdbcUtils.getConnection();

        String sql = "select " +
                "r.id as id, r.numberOfReservedSeats as numberOfReservedSeats, " +
                "r.clientName AS clientName, r.clientContact AS clientContact, " +
                "t.id as tourId, t.destination as destination, t.transportCompany as transportCompany, " +
                "t.departureDate AS departureDate, t.price AS price, t.numberOfAvailableSeats as numberOfAvailableSeats " +
                "from reservation r " +
                "inner join tour t on t.id = r.tourId " +
                "where r.id = ?";
        Reservation reservation = null;
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setInt(1, id);
            try (ResultSet result = preparedStatement.executeQuery()) {
                if (result.next()) {
                    reservation = getReservationFromSet(result);
                }
            }
        } catch (SQLException exception) {
            throw new RepositoryException("Error getting connection", exception);
        }

        return Optional.ofNullable(reservation);
    }

    @Override
    public Iterable<Reservation> findAll() {
        Connection connection = jdbcUtils.getConnection();
        List<Reservation> reservations = new ArrayList<>();

        String sql = "select " +
                "r.id as id, r.numberOfReservedSeats as numberOfReservedSeats, " +
                "r.clientName AS clientName, r.clientContact AS clientContact, " +
                "t.id as tourId, t.destination as destination, t.transportCompany as transportCompany, " +
                "t.departureDate AS departureDate, t.price AS price, t.numberOfAvailableSeats as numberOfAvailableSeats " +
                "from reservation r " +
                "inner join tour t on t.id = r.tourId ";
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
            throw new RepositoryException("Error getting connection", exception);
        }

        return reservations;
    }

    @Override
    public Optional<Reservation> save(Reservation entity) {
        validator.validate(entity);

        Connection connection = jdbcUtils.getConnection();

        try (PreparedStatement preparedStatement = connection.prepareStatement("insert into reservation (tourId, clientName, clientContact, numberOfReservedSeats) values (?, ?, ?, ?)")) {
            preparedStatement.setInt(1, entity.getTour().getId());
            preparedStatement.setString(2, entity.getClientName());
            preparedStatement.setString(3, entity.getClientContact());
            preparedStatement.setInt(4, entity.getNumberOfReservedSeats());
            int result = preparedStatement.executeUpdate();
            Optional<Reservation> reservationF = findReservation(entity.getTour().getId(), entity.getClientName(), entity.getClientContact(), entity.getNumberOfReservedSeats());
            entity.setId(reservationF.get().getId());
        } catch (SQLException exception) {
            throw new RepositoryException("Error saving reservation in database", exception);
        }

        return Optional.of(entity);
    }

    @Override
    public Optional<Reservation> delete(Integer integer) {
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
        } catch (SQLException exception) {
            throw new RepositoryException("Error deleting reservation in database", exception);
        }

        return reservation;
    }

    @Override
    public Optional<Reservation> update(Reservation reservation) {
        validator.validate(reservation);

        Connection connection = jdbcUtils.getConnection();

        try (PreparedStatement preparedStatement = connection.prepareStatement("update reservation set tourId = ?, " +
                "clientName = ?, clientName = ?, numberOfReservedSeats = ? where id = ?")) {
            preparedStatement.setInt(1, reservation.getTour().getId());
            preparedStatement.setString(2, reservation.getClientName());
            preparedStatement.setString(3, reservation.getClientContact());
            preparedStatement.setInt(4, reservation.getNumberOfReservedSeats());
            preparedStatement.setInt(5, reservation.getId());
            int result = preparedStatement.executeUpdate();
        } catch (SQLException exception) {
            throw new RepositoryException("Error updating reservation in database", exception);
        }

        return Optional.of(reservation);
    }

    @Override
    public Optional<Reservation> findReservation(Integer tourId, String nameClient, String contactClient, Integer numberOfReservedSeats) {
        String sql = "SELECT " +
                "r.id AS id, r.numberOfReservedSeats AS numberOfReservedSeats, " +
                "r.clientName AS clientName, r.clientContact AS clientContact, " +
                "t.id AS tourId, t.destination AS destination, t.transportCompany AS transportCompany, " +
                "t.departureDate AS departureDate, t.price AS price, t.numberOfAvailableSeats AS numberOfAvailableSeats " +
                "FROM reservation r " +
                "INNER JOIN tour t ON t.id = r.tourId " +
                "WHERE r.tourId = ? AND r.clientName = ? AND r.clientContact = ? AND r.numberOfReservedSeats = ?";

        try (Connection connection = jdbcUtils.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setInt(1, tourId);
            preparedStatement.setString(2, nameClient);
            preparedStatement.setString(3, contactClient);
            preparedStatement.setInt(4, numberOfReservedSeats);

            try (ResultSet result = preparedStatement.executeQuery()) {
                if (result.next()) {
                    Reservation reservation = getReservationFromSet(result);
                    return Optional.of(reservation);
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException("Error finding reservation in database", e);
        }

        return Optional.empty();
    }

    @Override
    public Iterable<Reservation> findReservationsByTour(Integer tourId) {
        Connection connection = jdbcUtils.getConnection();
        List<Reservation> reservations = new ArrayList<>();

        String sql = "select " +
                "r.id as id, r.numberOfReservedSeats as numberOfReservedSeats, " +
                "r.clientName AS clientName, r.clientContact AS clientContact, " +
                "t.id as tourId, t.destination as destination, t.transportCompany as transportCompany, " +
                "t.departureDate AS departureDate, t.price AS price, t.numberOfAvailableSeats as numberOfAvailableSeats " +
                "from reservation r " +
                "inner join tour t on t.id = r.tourId " +
                "where r.tourId = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setInt(1, tourId);
            try (ResultSet result = preparedStatement.executeQuery()) {
                while (result.next()) {
                    Reservation reservation = getReservationFromSet(result);
                    if (reservation != null) {
                        reservations.add(reservation);
                    }
                }
            }
        } catch (SQLException exception) {
            throw new RepositoryException("Error getting connection", exception);
        }

        return reservations;
    }

    @Override
    public Iterable<Reservation> findReservationsByClient(String clientName) {
        Connection connection = jdbcUtils.getConnection();

        List<Reservation> reservations = new ArrayList<>();
        String sql = "select " +
                "r.id as id, r.numberOfReservedSeats as numberOfReservedSeats, " +
                "r.clientName AS clientName, r.clientContact AS clientContact, " +
                "t.id as tourId, t.destination as destination, t.transportCompany as transportCompany, " +
                "t.departureDate AS departureDate, t.price AS price, t.numberOfAvailableSeats as numberOfAvailableSeats " +
                "from reservation r " +
                "inner join tour t on t.id = r.tourId " +
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
            throw new RepositoryException("Error getting connection", exception);
        }

        return reservations;
    }

}

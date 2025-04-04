package org.example.repository.impl;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.exception.RepositoryException;
import org.example.modul.Trip;
import org.example.modul.validator.Validator;
import org.example.repository.interfaces.TripRepository;
import org.example.repository.utils.JdbcUtils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;

public class TripRepositoryImpl implements TripRepository {
    protected JdbcUtils jdbcUtils;
    protected Validator<Trip> validator;
    private static final Logger logger = LogManager.getLogger();

    public TripRepositoryImpl(Properties properties, Validator<Trip> validator) {
        logger.info("Initializing TripDatabaseRepository with properties: {}", properties);

        this.jdbcUtils = new JdbcUtils(properties);
        this.validator = validator;
    }

    private Trip getTripFromSet(ResultSet result) throws SQLException {
        Integer id = result.getInt("id");
        String destination = result.getString("destination");
        String transportCompany = result.getString("transportCompany");
        String departure = result.getString("departureDate");
        Double price = result.getDouble("price");
        Integer numberOfAvailableSeats = result.getInt("numberOfAvailableSeats");

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
        LocalDateTime departureTime = LocalDateTime.parse(departure, formatter);

        Trip trip = new Trip(destination, transportCompany, departureTime, price, numberOfAvailableSeats);
        trip.setId(id);
        return trip;
    }

    @Override
    public Iterable<Trip> findAll() {
        logger.trace("Finding all trips");

        Connection connection = jdbcUtils.getConnection();

        List<Trip> trips = new ArrayList<>();
        try(PreparedStatement preparedStatement = connection.prepareStatement("select * from trip")){
            try(ResultSet result = preparedStatement.executeQuery()){
                while (result.next()){
                    Trip trip = getTripFromSet(result);
                    trips.add(trip);
                }
            }
        } catch (Exception e) {
            logger.error(e);
            System.out.println("Error getting connection "+e);
        }

        logger.traceExit("Found trips: {}", trips);
        return trips;
    }

    @Override
    public Optional<Trip> findOne(Integer id) {
        logger.trace("Finding trip with id {}", id);

        Connection connection = jdbcUtils.getConnection();

        Trip trip = null;
        try(PreparedStatement preparedStatement = connection.prepareStatement("select * from trip where id = ?")){
            preparedStatement.setInt(1, id);
            try(ResultSet result = preparedStatement.executeQuery()){
                if (result.next()){
                    trip = getTripFromSet(result);
                    logger.traceExit("Found trip: {}", trip);
                }
                else {
                    logger.warn("No trip found with id {}", id);
                }
            }
        } catch (SQLException e) {
            logger.error(e);
        }

        logger.traceExit();
        return Optional.ofNullable(trip);
    }

    @Override
    public Optional<Trip> save(Trip entity) {
        logger.trace("Saving trip {}", entity);

        validator.validate(entity);

        Connection connection = jdbcUtils.getConnection();

        try(PreparedStatement preparedStatement = connection.prepareStatement("insert into trip (destination, transportCompany, departureDate, price, numberOfAvailableSeats) values (?, ?, ?, ?, ?)")){
            preparedStatement.setString(1, entity.getDestination());
            preparedStatement.setString(2, entity.getTransportCompany());
            preparedStatement.setString(3, entity.getDepartureDate().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm")));
            preparedStatement.setDouble(4, entity.getPrice());
            preparedStatement.setInt(5, entity.getNumberOfAvailableSeats());
            int result = preparedStatement.executeUpdate();
            if(result == 0) {
                logger.warn("Failed to save trip {}", entity);
            }
            else {
                Optional<Trip> trip = findTrip(entity.getDestination(), entity.getTransportCompany(),
                        entity.getDepartureDate(), entity.getPrice(), entity.getNumberOfAvailableSeats());
                entity.setId(trip.get().getId());
                logger.trace("Successfully saved trip {}", entity);
            }
        } catch (SQLException exception) {
            logger.error(exception);
            throw new RepositoryException("Error saving trip in database", exception);
        }

        logger.traceExit();
        return Optional.of(entity);
    }

    @Override
    public Optional<Trip> delete(Integer id) {
        logger.trace("Deleting trip with id {}", id);

        Connection connection = jdbcUtils.getConnection();

        Optional<Trip> trip = findOne(id);
        if(trip.isEmpty()) {
            throw new RepositoryException("This trip doesn't exists");
        }

        try(PreparedStatement preparedStatement = connection.prepareStatement("delete from trip where id = ?")){
            preparedStatement.setInt(1, id);

            int result = preparedStatement.executeUpdate();
            if(result == 0) {
                logger.warn("Failed to delete trip {}", trip);
            }
            else {
                logger.trace("Successfully deleted trip {}", trip);
            }
        } catch (SQLException e) {
            logger.error(e);
            throw new RepositoryException("Error deleting trip in database", e);
        }

        logger.traceExit();
        return trip;
    }

    @Override
    public Optional<Trip> update(Trip entity) {
        logger.trace("Updating trip {}", entity);

        validator.validate(entity);

        Connection connection = jdbcUtils.getConnection();

        try(PreparedStatement preparedStatement = connection.prepareStatement("update trip set destination = ?, " +
                "transportCompany = ?, departureDate = ?, price = ?, numberOfAvailableSeats = ? where id = ?")){
            preparedStatement.setString(1, entity.getDestination());
            preparedStatement.setString(2, entity.getTransportCompany());
            preparedStatement.setString(3, entity.getDepartureDate().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm")));
            preparedStatement.setDouble(4, entity.getPrice());
            preparedStatement.setInt(5, entity.getNumberOfAvailableSeats());
            preparedStatement.setInt(6, entity.getId());

            int result = preparedStatement.executeUpdate();
            if(result == 0) {
                logger.warn("Failed to update trip {}", entity);
            }
            else {
                logger.trace("Successfully updated trip {}", entity);
            }
        } catch (SQLException e) {
            logger.error(e);
            throw new RepositoryException("Error updating trip in database", e);
        }

        logger.traceExit();
        return Optional.of(entity);
    }

    @Override
    public Optional<Trip> findTrip(String destination, String transportCompany, LocalDateTime departureDate, Double price, Integer numberOfAvailableSeats) {
        logger.trace("Finding trip with destination {}, transportCompany {}, departureDate {}, price {}, numberOfAvailableSeats {}", destination, transportCompany, departureDate, price, numberOfAvailableSeats);

        Connection connection = jdbcUtils.getConnection();

        Trip trip = null;
        try(PreparedStatement preparedStatement = connection.prepareStatement("select * from trip where destination = ? " +
                "and transportCompany = ? and departureDate = ? and price = ? and numberOfAvailableSeats = ?")){
            preparedStatement.setString(1, destination);
            preparedStatement.setString(2, transportCompany);
            preparedStatement.setString(3, departureDate.format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm")));
            preparedStatement.setDouble(4, price);
            preparedStatement.setInt(5, numberOfAvailableSeats);
            try(ResultSet result = preparedStatement.executeQuery()){
                if (result.next()){
                    trip = getTripFromSet(result);
                    logger.trace("Found trip: {}", trip);
                }
                else {
                    logger.warn("No trip found with destination {}, transportCompany {}, departureDate {}, price {}, numberOfAvailableSeats {}", destination, transportCompany, departureDate, price, numberOfAvailableSeats);
                }
            }
        } catch (SQLException e) {
            logger.error(e);
        }

        logger.traceExit();
        return Optional.ofNullable(trip);
    }

    @Override
    public Iterable<Trip> findTripsByDestination(String destination) {
        logger.trace("Finding trips with destination {}", destination);

        Connection connection = jdbcUtils.getConnection();

        List<Trip> trips = new ArrayList<>();
        try(PreparedStatement preparedStatement = connection.prepareStatement("select * from trip where destination = ?")){
            preparedStatement.setString(1, destination);
            try(ResultSet result = preparedStatement.executeQuery()){
                while (result.next()){
                    Trip trip = getTripFromSet(result);
                    trips.add(trip);
                }
            }
        } catch (SQLException e) {
            logger.error(e);
        }

        logger.traceExit("Found trips: {}", trips);
        return trips;
    }

    @Override
    public Optional<Trip> updateSeats(Integer id, Integer numberOfReservedSeats) {
        logger.trace("Updating trip with id {}", id);

        Connection connection = jdbcUtils.getConnection();

        Optional<Trip> trip = findOne(id);
        if(trip.isEmpty()) {
            throw new RepositoryException("This trip doesn't exists");
        }

        try(PreparedStatement preparedStatement = connection.prepareStatement("update trip set numberOfAvailableSeats = ? where id = ?")){
            Integer numberOfAvailableSeats = trip.get().getNumberOfAvailableSeats() - numberOfReservedSeats;
            preparedStatement.setInt(1, numberOfAvailableSeats);
            preparedStatement.setInt(2, id);

            int result = preparedStatement.executeUpdate();
            if(result == 0) {
                logger.warn("Failed to update trip {}", trip);
            }
            else {
                logger.trace("Successfully updated trip {}", trip);
            }
        } catch (SQLException e) {
            logger.error(e);
            throw new RepositoryException("Error updating trip in database", e);
        }

        logger.traceExit();
        return trip;
    }
}

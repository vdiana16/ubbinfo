package org.example.persistence.impl;


import org.example.model.Tour;
import org.example.model.validator.Validator;
import org.example.persistence.interfaces.TourRepository;
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

public class TourRepositoryImpl implements TourRepository {
    protected JdbcUtils jdbcUtils;
    protected Validator<Tour> validator;

    public TourRepositoryImpl(Properties properties, Validator<Tour> validator) {
        this.jdbcUtils = new JdbcUtils(properties);
        this.validator = validator;
    }

    private Tour getTourFromStatement(ResultSet result) throws SQLException {
        Integer id = result.getInt("id");
        String destination = result.getString("destination");
        String transportCompany = result.getString("transportCompany");
        String departure = result.getString("departureDate");
        Double price = result.getDouble("price");
        Integer numberOfAvailableSeats = result.getInt("numberOfAvailableSeats");

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
        LocalDateTime departureTime = LocalDateTime.parse(departure, formatter);

        Tour tour = new Tour(destination, transportCompany, departureTime, price, numberOfAvailableSeats);
        tour.setId(id);
        return tour;
    }

    @Override
    public Iterable<Tour> findAll() {
        Connection connection = jdbcUtils.getConnection();

        List<Tour> tours = new ArrayList<>();
        try(PreparedStatement preparedStatement = connection.prepareStatement("select * from tour")){
            try(ResultSet result = preparedStatement.executeQuery()){
                while (result.next()){
                    Tour tour = getTourFromStatement(result);
                    tours.add(tour);
                }
            }
        } catch (Exception e) {
            throw new RepositoryException("Error getting tours from database", e);
        }

        return tours;
    }

    @Override
    public Optional<Tour> findOne(Integer id) {
        Connection connection = jdbcUtils.getConnection();

        Tour tour = null;
        try(PreparedStatement preparedStatement = connection.prepareStatement("select * from tour where id = ?")){
            preparedStatement.setInt(1, id);
            try(ResultSet result = preparedStatement.executeQuery()){
                if (result.next()) {
                    tour = getTourFromStatement(result);
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException("Error getting tour from database", e);
        }

        return Optional.ofNullable(tour);
    }

    @Override
    public Optional<Tour> save(Tour entity) {
        validator.validate(entity);

        Connection connection = jdbcUtils.getConnection();

        try(PreparedStatement preparedStatement = connection.prepareStatement("insert into tour (destination, transportCompany, departureDate, price, numberOfAvailableSeats) values (?, ?, ?, ?, ?)")){
            preparedStatement.setString(1, entity.getDestination());
            preparedStatement.setString(2, entity.getTransportCompany());
            preparedStatement.setString(3, entity.getDepartureDate().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm")));
            preparedStatement.setDouble(4, entity.getPrice());
            preparedStatement.setInt(5, entity.getNumberOfAvailableSeats());
            int result = preparedStatement.executeUpdate();
            Optional<Tour> tour = findTour(entity.getDestination(), entity.getTransportCompany(),
                        entity.getDepartureDate(), entity.getPrice(), entity.getNumberOfAvailableSeats());
            entity.setId(tour.get().getId());
        } catch (SQLException exception) {
            throw new RepositoryException("Error saving tour in database", exception);
        }

        return Optional.of(entity);
    }

    @Override
    public Optional<Tour> delete(Integer id) {
        Connection connection = jdbcUtils.getConnection();

        Optional<Tour> tour = findOne(id);
        if(tour.isEmpty()) {
            throw new RepositoryException("This tour doesn't exists");
        }

        try(PreparedStatement preparedStatement = connection.prepareStatement("delete from tour where id = ?")){
            preparedStatement.setInt(1, id);

            int result = preparedStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException("Error deleting tour in database", e);
        }

        return tour;
    }

    @Override
    public Optional<Tour> update(Tour entity) {
        validator.validate(entity);

        Connection connection = jdbcUtils.getConnection();

        try(PreparedStatement preparedStatement = connection.prepareStatement("update tour set destination = ?, " +
                "transportCompany = ?, departureDate = ?, price = ?, numberOfAvailableSeats = ? where id = ?")){
            preparedStatement.setString(1, entity.getDestination());
            preparedStatement.setString(2, entity.getTransportCompany());
            preparedStatement.setString(3, entity.getDepartureDate().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm")));
            preparedStatement.setDouble(4, entity.getPrice());
            preparedStatement.setInt(5, entity.getNumberOfAvailableSeats());
            preparedStatement.setInt(6, entity.getId());

            int result = preparedStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException("Error updating tour in database", e);
        }

        return Optional.of(entity);
    }

    @Override
    public Optional<Tour> findTour(String destination, String transportCompany, LocalDateTime departureDate, Double price, Integer numberOfAvailableSeats) {
        Connection connection = jdbcUtils.getConnection();

        Tour tour = null;
        try(PreparedStatement preparedStatement = connection.prepareStatement("select * from tour where destination = ? " +
                "and transportCompany = ? and departureDate = ? and price = ? and numberOfAvailableSeats = ?")){
            preparedStatement.setString(1, destination);
            preparedStatement.setString(2, transportCompany);
            preparedStatement.setString(3, departureDate.format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm")));
            preparedStatement.setDouble(4, price);
            preparedStatement.setInt(5, numberOfAvailableSeats);
            try(ResultSet result = preparedStatement.executeQuery()){
                if (result.next()) {
                    tour = getTourFromStatement(result);
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException("Error getting tour from database", e);
        }

        return Optional.ofNullable(tour);
    }

    @Override
    public Iterable<Tour> findToursByDestination(String destination) {
        Connection connection = jdbcUtils.getConnection();

        List<Tour> tours = new ArrayList<>();
        try(PreparedStatement preparedStatement = connection.prepareStatement("select * from tour where destination = ?")){
            preparedStatement.setString(1, destination);
            try(ResultSet result = preparedStatement.executeQuery()){
                while (result.next()){
                    Tour tour = getTourFromStatement(result);
                    tours.add(tour);
                }
            }
        } catch (SQLException e) {
            throw new RepositoryException("Error getting tours from database", e);
        }

        return tours;
    }

    @Override
    public Optional<Tour> updateSeats(Integer id, Integer numberOfReservedSeats) {
        Connection connection = jdbcUtils.getConnection();

        Optional<Tour> tour = findOne(id);
        if(tour.isEmpty()) {
            throw new RepositoryException("This tour doesn't exists");
        }

        try(PreparedStatement preparedStatement = connection.prepareStatement("update tour set numberOfAvailableSeats = ? where id = ?")){
            Integer numberOfAvailableSeats = tour.get().getNumberOfAvailableSeats() - numberOfReservedSeats;
            preparedStatement.setInt(1, numberOfAvailableSeats);
            preparedStatement.setInt(2, id);

            int result = preparedStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException("Error updating tour in database", e);
        }

        return tour;
    }
}

package org.example.socialnetwork.repository.database.util;


import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class DataBaseAccess {
    private Connection connection;
    private String url;
    private String user;
    private String password;

    public DataBaseAccess(String url, String user, String password) {
        this.url = url;
        this.user = user;
        this.password = password;
    }

    public void createConnection() throws SQLException {
        connection = DriverManager.getConnection(url, user, password);
    }

    public PreparedStatement createStatement(String statement) throws SQLException {
        return connection.prepareStatement(statement);
    }

    public void closeConnection() throws SQLException {
        connection.close();
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getUser() {
        return user;
    }

    public void setUser(String user) {
        this.user = user;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}

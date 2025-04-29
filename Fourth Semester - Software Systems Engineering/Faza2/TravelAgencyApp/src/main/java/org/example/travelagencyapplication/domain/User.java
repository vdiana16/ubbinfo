package org.example.travelagencyapplication.domain;

import jakarta.persistence.*;


@Entity
@Table(name = "users")
public class User extends Identifiable<Integer> {
    private String name;
    private String username;
    private String password;
    private String agencyName;

    @Enumerated(EnumType.STRING)
    private Status status;

    public User() {
    }

    public User(String name, String username, String password, String agencyName, Status status) {
        this.name = name;
        this.username = username;
        this.password = password;
        this.agencyName = agencyName;
        this.status = status;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getAgencyName() {
        return agencyName;
    }

    public void setAgencyName(String agencyName) {
        this.agencyName = agencyName;
    }

    public Status getStatus() {
        return status;
    }

    public void setStatus(Status status) {
        this.status = status;
    }

}
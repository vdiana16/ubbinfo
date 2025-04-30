package org.example.model;

import java.util.Objects;

public class Agent extends Entity<Integer> {
    private String name;
    private String username;
    private String password;

    public Agent(String agentName, String username, String password) {
        this.name = agentName;
        this.username = username;
        this.password = password;
    }

    public String getName() { return name; }

    public void setName(String name) { this.name = name;}

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

    @Override
    public String toString() {
        return "Agent{" +
                "name='" + name + '\'' +
                ", username='" + username + '\'' +
                ", password='" + password + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if(!(obj instanceof Agent agent)) {
            return false;
        }
        return getName().equals(agent.getName()) && getUsername().equals(agent.getUsername()) && getPassword().equals(agent.getPassword());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getName(), getUsername(), getPassword());
    }
}

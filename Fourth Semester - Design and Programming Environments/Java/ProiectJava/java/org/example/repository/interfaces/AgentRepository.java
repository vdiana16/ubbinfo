package org.example.repository.interfaces;

import org.example.modul.Agent;
import org.example.repository.Repository;

import java.util.Optional;

public interface AgentRepository extends Repository<Integer, Agent> {
    Optional<Agent> findByUsername(String username, String password);
}
package org.example.persistence.interfaces;


import org.example.model.Agent;
import org.example.persistence.Repository;

import java.util.Optional;

public interface AgentRepository extends Repository<Integer, Agent> {
    Optional<Agent> findByUsername(String username, String password);
}
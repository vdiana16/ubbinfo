package org.example.modul.validator;


import org.example.exception.ValidationException;
import org.example.modul.Agent;

public class AgentValidator implements Validator<Agent> {
    @Override
    public void validate(Agent entity) throws ValidationException {
        if (entity == null) {
            throw new IllegalArgumentException("Agency is null");
        }
        if (entity.getName() == null || entity.getName().isEmpty()) {
            throw new ValidationException("Agency name is null or empty");
        }
        if (entity.getUsername() == null || entity.getUsername().isEmpty()){
            throw new ValidationException("Agency username is null or empty");
        }
        if (entity.getPassword() == null || entity.getPassword().isEmpty()){
            throw new ValidationException("Agency password is null or empty");
        }
    }
}
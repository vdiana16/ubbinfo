package org.example.socialnetwork.domain.validators;


import org.example.socialnetwork.exceptions.ValidationException;

/**
 * Interface for a generic Validator that defines a contract for validating entities.
 * @param <T> the entity to be validated
 */
public interface Validator<T> {
    /**
     * Validates the given entity.
     * @param entity - the entity to be validated
     * @throws ValidationException - if the entity is found to be invalid
     */
    void validate(T entity) throws ValidationException;
}

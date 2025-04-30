package org.example.model.validator;


public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}

package org.example.modul.validator;

import org.example.exception.ValidationException;

public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}

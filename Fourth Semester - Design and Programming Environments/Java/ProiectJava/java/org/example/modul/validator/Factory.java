package org.example.modul.validator;

public interface Factory {
    default Validator createValidator(ValidatorStrategy strategy) {
        return null;
    }
}

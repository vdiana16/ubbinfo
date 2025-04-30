package org.example.model.validator;

public interface Factory {
    default Validator createValidator(ValidatorStrategy strategy) {
        return null;
    }
}

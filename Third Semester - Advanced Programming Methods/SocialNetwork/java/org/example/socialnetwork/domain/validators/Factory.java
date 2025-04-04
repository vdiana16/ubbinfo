package org.example.socialnetwork.domain.validators;


/**
 * Interface for a Validator Factory that creates Validator instance based on specified startegy.
 */
public interface Factory {
    /**
     * Creates a validator based on the specified validation strategy
     *
     * @param strategy - the validation strategy to determine which validator to create
     * @return an instance of Validator corresponding to the provided strategy
     */
    default Validator createValidator(ValidatorStrategy strategy) {
        return null;
    }
}


package domain.validators;

/**
 * Interface for a Validator Factory that creates Validator instance based on specified startegy.
 */
public interface FactoryV {
    /**
     * Creates a validator based on the specified validation strategy
     * @param strategy - the validation strategy to determine which validator to create
     * @return an instance of Validator corresponding to the provided strategy
     */
    Validator createValidator(ValidatorStrategy strategy);
}

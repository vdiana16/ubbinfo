package org.example.socialnetwork.domain.validators;


import org.example.socialnetwork.exceptions.ValidationException;

/**
 * the singletom factory class for creating validators based on specified validation strategy
 */
public class ValidatorFactory implements Factory {
    private static ValidatorFactory instance = null; //the single instance of the factory

    //Private constructor to prevent instantiation from outeside the class.
    private ValidatorFactory() {}

    /**
     * Getter for the single instance of the Factory
     * @return instance
     */
    public static ValidatorFactory getInstance() {
        if (instance == null) {
            instance = new ValidatorFactory();
        }
        return instance;
    }

    @Override
    public Validator createValidator(ValidatorStrategy strategy) {
        switch (strategy) {
            case User -> {
                return new UserValidator();
            }
            case Friendship -> {
                return new FriendshipValidator();
            }
            default -> throw new ValidationException("Invalid strategy");
        }

    }
}

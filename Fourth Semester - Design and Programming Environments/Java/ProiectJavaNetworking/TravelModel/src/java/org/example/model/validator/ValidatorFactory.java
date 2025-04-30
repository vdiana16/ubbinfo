package org.example.model.validator;


public class ValidatorFactory implements Factory {
    private static ValidatorFactory instance = null;

    private ValidatorFactory() {
    }

    public static ValidatorFactory getInstance() {
        if (instance == null) {
            instance = new ValidatorFactory();
        }
        return instance;
    }

    @Override
    public Validator createValidator(ValidatorStrategy strategy) {
        switch (strategy) {
            case TOUR:
                return new TourValidator();
            case RESERVATION:
                return new ReservationValidator();
            case AGENT:
                return new AgentValidator();
            default:
                return null;
        }
    }
}


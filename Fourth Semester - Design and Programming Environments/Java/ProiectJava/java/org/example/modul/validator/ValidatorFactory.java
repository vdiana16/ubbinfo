package org.example.modul.validator;

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
            case TRIP:
                return new TripValidator();
            case RESERVATION:
                return new ReservationValidator();
            case AGENCY:
                return new AgentValidator();
            default:
                return null;
        }
    }
}


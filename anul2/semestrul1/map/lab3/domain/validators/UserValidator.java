package domain.validators;

import domain.User;
import exceptions.ValidationException;

/**
 * Validator for User entities.
 * This class checks if the User objects meets the specified validation rules.
 */
public class UserValidator implements Validator<User> {
    @Override
    public void validate(User entity) throws ValidationException {
        String erori = "";
        if(entity.getFirstName().equals("")) {
            erori += "The First Name cannot be null!\n";
        }
        if(entity.getLastName().equals("")) {
            erori += "The Last Name cannot be null!\n";
        }
        if(erori.isEmpty()) {
            return;
        }
        throw new ValidationException(erori);
    }
}

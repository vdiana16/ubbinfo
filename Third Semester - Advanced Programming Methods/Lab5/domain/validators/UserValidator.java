package org.example.domain.validators;


import org.example.domain.User;
import org.example.exceptions.ValidationException;

/**
 * Validator for User entities.
 * This class checks if the User objects meets the specified validation rules.
 */
public class UserValidator implements Validator<User> {
    @Override
    public void validate(User entity) throws ValidationException {
        String erori = "";
        if(entity.getFirstName().isEmpty()) {
            erori += "The First Name cannot be null!\n";
        }
        if(entity.getLastName().isEmpty()) {
            erori += "The Last Name cannot be null!\n";
        }
        if(erori.isEmpty()) {
            return;
        }
        throw new ValidationException(erori);
    }
}

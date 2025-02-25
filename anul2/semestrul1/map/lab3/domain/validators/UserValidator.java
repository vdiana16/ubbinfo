package domain.validators;

import domain.Friendship;
import exceptions.ValidationException;

/**
 * Validator for Friendship entities.
 * This class checks if the Friendship meet the specified validation rules.
 */
public class FriendshipValidator implements Validator<Friendship> {
    @Override
    public void validate(Friendship entity) throws ValidationException {
        String erori = "";
        if(entity.getUser1() == null || entity.getUser2() == null) {
            erori += "The User cannot be null!\n";
        }
        if(erori.isEmpty()) {
            return;
        }
        throw new ValidationException(erori);
    }
}

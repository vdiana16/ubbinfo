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
        if(entity.getData() == null) {
            erori += "The date cannot be null!\n";
        }
        if(entity.getId().getFirst() == null || entity.getId().getSecond() == null) {
            erori += "The ids cannot be null!\n";
        }
        if(entity.getId().getFirst() == entity.getId().getSecond()) {
            erori += "The ids cannot be identical!\n";
        }
        if(erori.isEmpty()) {
            return;
        }
        throw new ValidationException(erori);
    }
}

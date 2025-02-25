package org.example.socialnetwork.exceptions;

/**
 * Custom exceptions class for repository related errors.
 */
public class RepositoryException extends RuntimeException {
    /**
     * Default constructor
     */
    public RepositoryException() {
    }

    /**
     * Constructor for RepositoryException with a detail message.
     * @param message - the detail message which can be retrieved later by the getMessage() method
     */
    public RepositoryException(String message) {
        super(message);
    }

    /**
     * Constructor for RepositoryException with a detail message and a cause.
     * @param message - the detail message
     * @param cause - the cause (which is saved for later retrieval by the getCause() method)
     */
    public RepositoryException(String message, Throwable cause) {
        super(message, cause);
    }

    /**
     * Constructor for RepositoryException with a cause.
     * @param cause - the cause (which is saved for later retrieval by the getCause() method)
     */
    public RepositoryException(Throwable cause) {
        super(cause);
    }

    /**
     * Constructor for RepositoryException with a detail message, cause, suppression enabled or disabled,
     * and whether the stack trace should be writable.
     * @param message - the detail message
     * @param cause - the cause (which is saved for later retrieval by the getCause() method)
     * @param enableSuppression - whether suppression is enabled or disabled
     * @param writableStackTrace - whether the stack trace should be writable
     */
    public RepositoryException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}


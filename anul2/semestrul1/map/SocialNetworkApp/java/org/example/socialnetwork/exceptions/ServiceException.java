package org.example.socialnetwork.exceptions;

/**
 * Custom exceptions class for service related errors.
 */
public class ServiceException extends RuntimeException {
    /**
     * Default constructor
     */
    public ServiceException() {
    }

    /**
     * Constructor for ServiceException with a detail message.
     * @param message - the detail message which can be retrieved later by the getMessage() method
     */
    public ServiceException(String message) {
        super(message);
    }

    /**
     * Constructor for ServiceException with a detail message and a cause.
     * @param message - the detail message
     * @param cause - the cause (which is saved for later retrieval by the getCause() method)
     */
    public ServiceException(String message, Throwable cause) {
        super(message, cause);
    }

    /**
     * Constructor for ServiceException with a cause.
     * @param cause - the cause (which is saved for later retrieval by the getCause() method)
     */
    public ServiceException(Throwable cause) {
        super(cause);
    }

    /**
     * Constructor for ServiceException with a detail message, cause, suppression enabled or disabled,
     * and whether the stack trace should be writable.
     * @param message - the detail message
     * @param cause - the cause (which is saved for later retrieval by the getCause() method)
     * @param enableSuppression - whether suppression is enabled or disabled
     * @param writableStackTrace - whether the stack trace should be writable
     */
    public ServiceException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}


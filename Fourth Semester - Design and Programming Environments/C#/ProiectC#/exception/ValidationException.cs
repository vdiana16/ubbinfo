﻿namespace TravelAgency.exception;

public class ValidationException : Exception
{
    public ValidationException() { }
    
    public ValidationException(string message) : base(message) { }
    
    public ValidationException(string message, Exception cause) : base(message, cause) { }
}
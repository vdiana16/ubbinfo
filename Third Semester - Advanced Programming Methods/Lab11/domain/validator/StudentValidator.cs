using lab11.exception;

namespace lab11.domain.validator;

public class StudentValidator : IValidator<Student>
{
    public bool ValidateName(string name)
    {
        if (string.IsNullOrEmpty(name))
            throw new ValidationException("Team name cannot be empty");
        return true;
    }

    public bool ValidateSchool(string school)
    {
        if (string.IsNullOrEmpty(school))
            throw new ValidationException("School name cannot be empty");
        return true;
    }
    
    public virtual bool Validate(Student student)
    {
        var error = new List<string>();

        try
        {
            ValidateName(student.Name);
        }
        catch (ValidationException e)
        {
            error.Add(e.Message);
        }

        try
        {
            ValidateSchool(student.School);
        }
        catch (ValidationException e)
        {
            error.Add(e.Message);
        }

        if (error.Count != 0)
        {
            error.Insert(0, "Student is invalid!");
            throw new ValidationException(string.Join("\n", error));
        }
        return true;
    }
}
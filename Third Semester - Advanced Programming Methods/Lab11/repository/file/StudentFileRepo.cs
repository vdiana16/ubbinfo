using lab11.domain;

namespace lab11.repository.file;

public class StudentFileRepo : InFileRepository<int, Student>
{
    public StudentFileRepo(string filePath) : base(filePath, LineToStudent, StudentToLine)
    {
        
    }

    public static Student LineToStudent(string line)
    {
        var fields = line.Split(",");
        return new Student
        {
            Id = int.Parse(fields[0]),
            Name = fields[1],
            School = fields[2]
        };
    }

    public static string StudentToLine(Student student)
    {
        return $"{student.Id},{student.Name},{student.School}";
    }
}
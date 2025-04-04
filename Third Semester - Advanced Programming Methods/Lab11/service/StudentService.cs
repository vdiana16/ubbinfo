using lab11.domain;
using lab11.domain.validator;
using lab11.repository;
using lab11.utils;

namespace lab11.service;

public class StudentService
{
    private readonly IRepository<int, Student> _studentRepository;
    private static readonly IValidator<Student> _studentValidator = new StudentValidator();

    public StudentService(){}
    
    public StudentService(IRepository<int, Student> studentRepository)
    {
        _studentRepository = studentRepository;
    }

    public Student? Add(Student student)
    {
        _studentValidator.Validate(student);
        student.Id = Util.GenerateId(GetAll());
        return _studentRepository.Add(student);
    }

    public Student? Update(Student student)
    {
        _studentValidator.Validate(student);
        return _studentRepository.Update(student);
    }

    public Student? Delete(int id)
    {
        return _studentRepository.Delete(id);
    }

    public Student? Get(int id)
    {
        return _studentRepository.Get(id);
    }

    public IEnumerable<Student> GetAll()
    {
        return _studentRepository.GetAll();
    }
}
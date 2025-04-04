namespace lab11.domain;

public class Student : Entity<int>
{
    public string Name { get; set; }
    public string School { get; set; }

    public Student() { }

    public Student(string name, string school)
    {
        Name = name;
        School = school;
    }

    public override string ToString()
    {
        return base.Id.ToString() + " " + Name + " " + School;
    }
}
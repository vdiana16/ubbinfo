using lab11.domain;

namespace lab11.utils;

public class Util
{
    public static int GenerateId(IEnumerable<Entity<int>> entities)
    {
        return !entities.Any() ? 1 : entities.Max(x => x.Id) + 1;
    }
    
}
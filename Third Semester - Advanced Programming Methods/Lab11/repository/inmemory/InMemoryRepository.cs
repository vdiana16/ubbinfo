using lab11.domain;

namespace lab11.repository.inmemory;

public class InMemoryRepository<ID, E> : IRepository<ID, E> where E : Entity<ID>
{
    protected Dictionary<ID, E?> Entities = new Dictionary<ID, E?>();

    public virtual E? Add(E? entity)
    {
        ArgumentNullException.ThrowIfNull(entity);
        return Entities.TryAdd(entity.Id, entity) ? entity : default;
    }

    public virtual E? Delete(ID id)
    {
        ArgumentNullException.ThrowIfNull(id);
        Entities.Remove(id, out E? entity);
        return entity;
    }

    public virtual E? Update(E? entity)
    {
        ArgumentNullException.ThrowIfNull(entity);
        if (!Entities.TryGetValue(entity.Id, out var update))
        {
            return default;
        }
        return update;
    }

    public virtual E? Get(ID id)
    {
       ArgumentNullException.ThrowIfNull(id);
       return Entities.GetValueOrDefault(id);
    }

    public virtual IEnumerable<E> GetAll()
    {
        return Entities.Values;
    }
}
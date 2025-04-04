using lab11.domain;

namespace lab11.repository;

public interface IRepository<ID, E> where E : Entity<ID>
{
    public E? Add(E? entity);
    
    public E? Delete(ID id);
    
    public E? Update(E? entity);
    
    public E? Get(ID id);
    
    public IEnumerable<E> GetAll();
}
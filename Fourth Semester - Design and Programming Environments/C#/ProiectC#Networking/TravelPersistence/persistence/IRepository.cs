using TravelModel.model;

namespace TravelPersistence.persistence;


/// <summary>
/// CRUD operations repository interface
/// </summary>
/// <typeparam name="ID">Type of the entity ID</typeparam>
/// <typeparam name="E">Type of entities saved in the repository</typeparam>

public interface IRepository<ID, E> where E : Entity<ID>
{
    /// <summary>
    /// Finds an entity by its ID.
    /// </summary>
    /// <param name="id">The ID of the entity to be returned. Must not be null.</param>
    /// <returns>An optional entity encapsulated in a nullable type.</returns>
    /// <exception cref="ArgumentException">Thrown if ID is null.</exception>
    E? FindOne(ID id);

    /// <summary>
    /// Retrieves all entities.
    /// </summary>
    /// <returns>An enumerable collection of entities.</returns>
    IEnumerable<E> FindAll();

    /// <summary>
    /// Saves an entity.
    /// </summary>
    /// <param name="entity">The entity to save. Must not be null.</param>
    /// <returns>Null if the entity was saved, otherwise returns the existing entity if the ID already exists.</returns>
    /// <exception cref="ValidationException">Thrown if the entity is not valid.</exception>
    /// <exception cref="ArgumentException">Thrown if the entity is null.</exception>
    E? Save(E entity);

    /// <summary>
    /// Removes the entity with the specified ID.
    /// </summary>
    /// <param name="id">The ID of the entity to remove. Must not be null.</param>
    /// <returns>Null if no entity was found, otherwise returns the removed entity.</returns>
    /// <exception cref="ArgumentException">Thrown if ID is null.</exception>
    E? Delete(ID id);

    /// <summary>
    /// Updates an entity.
    /// </summary>
    /// <param name="entity">The entity to update. Must not be null.</param>
    /// <returns>Null if the entity was updated, otherwise returns the entity if the ID does not exist.</returns>
    /// <exception cref="ValidationException">Thrown if the entity is not valid.</exception>
    /// <exception cref="ArgumentException">Thrown if the entity is null.</exception>
    E? Update(E entity);
}
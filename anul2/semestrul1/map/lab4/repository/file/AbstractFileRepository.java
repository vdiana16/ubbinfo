package repository.file;

import domain.Entity;
import exceptions.ValidationException;
import domain.validators.Validator;
import repository.inmemory.InMemoryRepository;

import java.io.*;
import java.util.Optional;

/**
 * Abstract base class for file based repositories that handle persistence
 * of entities to a file
 * @param <ID> - type of the entity's identifier
 * @param <E> - type of the entity, which extends the Entity class
 */
public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {
    private final String fileName; // the name of the file where entities are stored

    /**
     * Constructor for AbstractFileRepository
     * @param validator - the validator used to validate entities
     * @param fileName - the name of the file where entities are stored
     */
    public AbstractFileRepository(Validator<E> validator, String fileName) {
        super(validator);
        this.fileName = fileName;
        loadData();
    }

    /**
     * Loads data from the specified file into the repository.
     */
    private void loadData() {
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            String linie;
            while ((linie = br.readLine()) != null) {
                E e = createEntity(linie);
                super.save(e);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Abstract method to create an entity from a line of texte.
     * @param line -  the line of text representing an entity
     * @return an instance of the entity
     */
    public abstract E createEntity(String line);

    /**
     * Abstract method to save an entity as a string representation.
     * @param entity - the entity to be saved
     * @return the string representation of the entity
     */
    public abstract String saveEntity(E entity);

    @Override
    public Optional<E> findOne(ID id) {
        loadData();
        return super.findOne(id);
    }

    @Override
    public Iterable<E> findAll() {
        loadData();
        return super.findAll();
    }

    @Override
    public Optional<E> save(E entity) throws ValidationException {
        Optional<E> savedEntity = super.save(entity);
        if (savedEntity.isEmpty()) {
            writeToFile();
        }
        return savedEntity;
    }

    @Override
    public Optional<E> delete(ID id) {
        Optional<E> deletedEntity = super.delete(id);
        if (deletedEntity.isPresent()){
            writeToFile();
        }
        return deletedEntity;
    }

    @Override
    public Optional<E> update(E entity) {
        Optional<E> updatedEntity = super.update(entity);
        if (updatedEntity.isEmpty()) {
            writeToFile();
        }
        return updatedEntity;
    }

    private void writeToFile() {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            for (E entity : entities.values()) {
                String ent = saveEntity(entity);
                writer.write(ent);
                writer.newLine();
            }
        }catch (IOException e) {
            throw new RuntimeException(e);
        }

    }
}

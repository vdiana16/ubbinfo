package repository.file;

import domain.Entity;
import exceptions.ValidationException;
import domain.validators.Validator;
import repository.memory.InMemoryRepository;

import java.io.*;

/**
 * Abstract base class for file based repositories that handle persistence
 * of entities to a file
 * @param <ID> - type of the entity's identifier
 * @param <E> - type of the entity, which extends the Entity class
 */
public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {
    private String fileName; // the name of the file where entities are stored

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
    public E findOne(ID id) {
        loadData();
        return super.findOne(id);
    }

    @Override
    public Iterable<E> findAll() {
        loadData();
        return super.findAll();
    }

    @Override
    public E save(E entity) throws ValidationException {
        E e = super.save(entity);
        if (e == null) {
            writeToFile();
        }
        return e;
    }

    @Override
    public E delete(ID id) {
        E e = super.delete(id);
        if (e != null) {
            writeToFile();
        }
        return e;
    }

    @Override
    public E update(E entity) {
        E e = super.update(entity);
        if (e == null) {
            writeToFile();
        }
        return e;
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

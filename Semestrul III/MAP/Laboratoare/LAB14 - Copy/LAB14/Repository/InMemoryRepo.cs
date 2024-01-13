using LAB14.Domain;

namespace LAB14.Repository;

public class InMemoryRepo<Id,E> : IRepository<Id, E>
    where E : Entity<Id>
{
    private Dictionary<Id, E> entities;

    public InMemoryRepo()
    {
        entities = new Dictionary<Id, E>();
    }

    public IEnumerable<E> FindAll() => entities.Values;


    public E FindOne(Id id)
    {
        return entities[id];
    }

    public E Save(E entity)
    {
        entities[entity.Id] = entity;
        // entities.Add(entity.Id,entity);
        return entity;
    }

    public bool Delete(Id id)
    {
        return entities.Remove(id);
    }
}
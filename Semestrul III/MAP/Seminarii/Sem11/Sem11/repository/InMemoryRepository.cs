using System.ComponentModel;
using sem11.domain;

namespace sem11.repository;

public class InMemoryRepository<TID, TE> : IRepository<TID, TE> where TE: Entity<TID>
{
    private IDictionary<TID, TE> _dictionary = new Dictionary<TID, TE>();
        
    public TE FindOne(TID id)
    {

        throw new NotImplementedException();
    }

    public IEnumerable<TE> FindAll()
    {
        return _dictionary.Values;
    }

    public TE Save(TE entity)
    {
        try
        {
            _dictionary.Add(entity.Id, entity);
        }
        catch (ArgumentException e)
        {
            return entity;
        }

        return default(TE);

    }

    public TE Delete(TID id)
    {
        throw new NotImplementedException();
    }

    public TE Update(TE entity)
    {
        throw new NotImplementedException();
    }
}
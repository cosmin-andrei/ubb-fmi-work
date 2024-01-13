using LAB14.Domain;

namespace LAB14.Repository;

public interface IRepository <TId, TE> where TE : Entity<TId>
{
    IEnumerable<TE> FindAll();
}
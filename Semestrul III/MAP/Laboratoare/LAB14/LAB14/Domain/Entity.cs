namespace LAB14.Domain
{
    public class Entity<TId>
    {
        public TId Id { get; set; }

        
        public Entity(){ }
        public Entity(TId id)
        {
            this.Id = id;
        }
        
    }
}
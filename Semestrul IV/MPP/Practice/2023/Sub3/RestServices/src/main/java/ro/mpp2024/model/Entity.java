package ro.mpp2024.model;


public interface Entity<ID> {
    void setId(ID id);
    ID getId();
}

package ro.mpp2024.model;

import java.io.Serializable;

public interface Entity <ID> extends Serializable {
    void setId(ID id);
    ID getId();
}

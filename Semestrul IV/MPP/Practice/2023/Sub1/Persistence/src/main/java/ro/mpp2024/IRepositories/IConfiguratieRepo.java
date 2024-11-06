package ro.mpp2024.IRepositories;

import ro.mpp2024.Configuratie;
import ro.mpp2024.IRepository;

public interface IConfiguratieRepo extends IRepository<Long, Configuratie> {
    Integer getSize();
}

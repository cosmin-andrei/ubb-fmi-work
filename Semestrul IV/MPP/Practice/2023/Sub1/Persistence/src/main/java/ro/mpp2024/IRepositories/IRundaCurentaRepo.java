package ro.mpp2024.IRepositories;

import ro.mpp2024.IRepository;
import ro.mpp2024.Jucator;
import ro.mpp2024.RundaCurenta;

public interface IRundaCurentaRepo extends IRepository<Long, RundaCurenta> {
    void deleteByJucator(Jucator jucator);
}

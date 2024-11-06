package ro.mpp2024.repository.interfaces;

import ro.mpp2024.model.Cuvant;
import ro.mpp2024.repository.Repository;

import java.util.List;

public interface CuvantRepoInterface extends Repository<String, Cuvant> {
    List<Cuvant> generateWords(int n);
}

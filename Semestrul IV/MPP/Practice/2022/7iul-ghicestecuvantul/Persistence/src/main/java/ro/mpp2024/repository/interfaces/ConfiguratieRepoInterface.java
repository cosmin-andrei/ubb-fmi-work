package ro.mpp2024.repository.interfaces;

import ro.mpp2024.model.Configuratie;
import ro.mpp2024.repository.Repository;

import java.util.Optional;

public interface ConfiguratieRepoInterface extends Repository<Long, Configuratie> {
   Optional<Configuratie> findByPlayer(String id);
}

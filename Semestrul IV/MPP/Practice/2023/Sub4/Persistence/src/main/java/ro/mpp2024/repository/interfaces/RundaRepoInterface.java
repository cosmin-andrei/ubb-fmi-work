package ro.mpp2024.repository.interfaces;

import ro.mpp2024.model.Runda;
import ro.mpp2024.repository.Repository;

import java.util.List;

public interface RundaRepoInterface extends Repository<Long, Runda> {
    List<Runda> findByPlayer(String player);
}

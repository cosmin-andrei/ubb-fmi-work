package ro.mpp2024.controller;

import lombok.AllArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import ro.mpp2024.model.Runda;
import ro.mpp2024.repository.interfaces.RundaRepoInterface;

import java.util.Collections;
import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("runda")
@AllArgsConstructor
public class Controller {

    private static final String template = "Hello, %s!";

    @Autowired
    private RundaRepoInterface repo;

    @RequestMapping("/greeting")
    public String greeting(@RequestParam(value = "name", defaultValue = "World") String name) {
        return String.format(template, name);
    }

    @RequestMapping(method = RequestMethod.GET)
    public List<Runda> getAll() {
        System.out.println("Get all causes ...");
        return (List<Runda>) repo.findAll();
    }

    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public ResponseEntity<?> getById(@PathVariable Long id) {
        System.out.println("Get by id " + id);
        return repo.findOne(id).map(ResponseEntity::ok).orElseGet(() -> ResponseEntity.notFound().build());
    }

    @RequestMapping(method = RequestMethod.POST)
    public Runda create(@RequestBody Runda runda) {
        System.out.println("Create " + runda);
        return repo.save(runda).orElse(null);
    }

    @RequestMapping(value = "/{id}", method = RequestMethod.PUT)
    public Runda update(@PathVariable Long id, @RequestBody Runda runda) {
        System.out.println("Update " + runda);
        runda.setId(id);
        Optional<Runda> result = repo.update(runda);
        return result.orElse(null);
    }

    @RequestMapping(value = "/{id}", method = RequestMethod.DELETE)
    public ResponseEntity<?> delete(@PathVariable Long id) {
        System.out.println("Delete " + id);
        Optional<Runda> result = repo.delete(id);
        if (result.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok().build();
    }

    @RequestMapping(value = "/games/{username}", method = RequestMethod.GET)
    public List<Runda> getByPlayer(@PathVariable String username) {
        List<Runda> runda = (List<Runda>) repo.findByPlayer(username);
        runda.sort((r1, r2) -> r2.getDurata() - r1.getDurata());
        return runda;
    }

    @ExceptionHandler(Exception.class)
    @ResponseStatus(HttpStatus.BAD_REQUEST)
    public String causeError(Exception e) {
        return e.getMessage();
    }
}





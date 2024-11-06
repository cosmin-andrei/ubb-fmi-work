package computershop;

import model.ComputerRepairRequest;
import model.RequestStatus;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import repository.ComputerRepairRequestRepository;

import java.util.Collection;

@RestController
@RequestMapping("computershop/computer-repair-requests")
public class ComputerRepairRequestRestController {
    @Autowired
    private ComputerRepairRequestRepository  crrRepository;


    @GetMapping("/test")
    public  String test(@RequestParam(value="name", defaultValue="Hello") String name) {
        return name.toUpperCase();
    }



    @PostMapping
    public ComputerRepairRequest create(@RequestBody ComputerRepairRequest crrRequest){
        System.out.println("Creating computerRepairRequest");
        return crrRepository.add(crrRequest);

    }

    /*@RequestMapping(method = RequestMethod.GET)
    public Collection<ComputerRepairRequest> getAll(){
        System.out.println("Getting computerRepairRequests");
        Collection<ComputerRepairRequest> all=crrRepository.getAll();
        return all;

    }*/

    @GetMapping
    public Collection<ComputerRepairRequest> filterByStatus(@RequestParam (value="status", required=false)RequestStatus status){
        Collection<ComputerRepairRequest> all;
        if (status!=null){
             System.out.println("Getting computerRepairRequests by status "+status);
            all=crrRepository.filterByStatus(status);
        }else
            all=crrRepository.getAll();

        return all;

    }

    @GetMapping("/{id}")
    public ResponseEntity<?> getById(@PathVariable Integer id){
        System.out.println("Get by id "+id);
        ComputerRepairRequest request=crrRepository.findById(id);
        if (request==null)
            return new ResponseEntity<String>("Entity not found", HttpStatus.NOT_FOUND);
        else
            return new ResponseEntity<ComputerRepairRequest>(request, HttpStatus.OK);
    }
}

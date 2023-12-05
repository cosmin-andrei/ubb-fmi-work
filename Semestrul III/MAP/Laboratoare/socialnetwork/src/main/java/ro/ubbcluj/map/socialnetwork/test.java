package ro.ubbcluj.map.socialnetwork;

import ro.ubbcluj.map.socialnetwork.domain.CererePrietenie;
import ro.ubbcluj.map.socialnetwork.domain.Tuple;
import ro.ubbcluj.map.socialnetwork.domain.validators.CerereValidator;
import ro.ubbcluj.map.socialnetwork.domain.validators.PrietenieValidator;
import ro.ubbcluj.map.socialnetwork.domain.validators.UtilizatorValidator;
import ro.ubbcluj.map.socialnetwork.repository.CerereDBRepository;
import ro.ubbcluj.map.socialnetwork.repository.PrietenieDBRepository;
import ro.ubbcluj.map.socialnetwork.repository.UserDBRepository;
import ro.ubbcluj.map.socialnetwork.service.CerereService;

public class test {

    public void Test() {
        CererePrietenie cererePrietenie = new CererePrietenie();
        cererePrietenie.setId(new Tuple<>(5L,6L));
        cererePrietenie.setStatus("PENDING");

        final String url = "jdbc:postgresql://localhost:5432/socialnetwork";
        final String username = "postgres";
        final String password = "2003";
        CerereValidator cerereValidator = new CerereValidator();
        PrietenieValidator prietenieValidator = new PrietenieValidator();
        CerereDBRepository cerereDBRepository = new CerereDBRepository(cerereValidator, url, username, password);
        PrietenieDBRepository prietenieDBRepository = new PrietenieDBRepository(prietenieValidator, url, username, password);
        UtilizatorValidator utilizatorValidator = new UtilizatorValidator();
        UserDBRepository userDBRepository = new UserDBRepository(utilizatorValidator, url, username, password);
        CerereService cerereService = new CerereService(prietenieDBRepository, userDBRepository, cerereDBRepository);

//        try {
//            cerereService.addCerere(cererePrietenie);
//        } catch (SQLException e) {
//            throw new RuntimeException(e);
//        }




    }

}

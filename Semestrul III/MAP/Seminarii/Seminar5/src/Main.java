import repository.RegizorDBRepository;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {

        String url = "jdbc:postgresql://localhost:5432/seminar5";
        String username = "postgres";
        String password = "2003";

        RegizorDBRepository regizorDBRepository = new RegizorDBRepository(url, username, password);
        regizorDBRepository.findAll().forEach(System.out::println);

    }
}
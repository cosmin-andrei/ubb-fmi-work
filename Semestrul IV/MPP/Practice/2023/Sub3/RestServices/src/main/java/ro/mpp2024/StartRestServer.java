package ro.mpp2024;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

//@ComponentScan("ro.mpp2024.client")

@SpringBootApplication
public class StartRestServer {
    public static void main(String[] args) {
        SpringApplication.run(StartRestServer.class, args);
    }
}
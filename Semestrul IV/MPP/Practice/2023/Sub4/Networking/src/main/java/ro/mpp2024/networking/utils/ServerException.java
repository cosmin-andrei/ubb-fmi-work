package ro.mpp2024.networking.utils;


public class ServerException extends Exception{
    public ServerException() {
        super();
    }

    public ServerException(String message) {
        super(message);
    }

    public ServerException(String message, Throwable cause) {
        super(message, cause);    
    }
}

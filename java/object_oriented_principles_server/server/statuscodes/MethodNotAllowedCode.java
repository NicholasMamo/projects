package server.statuscodes;

/**
 *
 * @author memonick
 * @date Dec 1, 2015
 */
public class MethodNotAllowedCode extends StatusCode {
    
    public MethodNotAllowedCode() {
        super("405 Method Not Allowed", "Some other method than GET was supplied.");
    }

}

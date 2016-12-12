package server.statuscodes;

/**
 *
 * @author memonick
 * @date Dec 1, 2015
 */
public class InternalServerErrorCode extends StatusCode {
    
    public InternalServerErrorCode() {
        super("500 Internal Server Error", "Generic (unknown) server error");
    }

}

package server.statuscodes;

/**
 *
 * @author memonick
 * @date Dec 1, 2015
 */
public class UnsupportedMediaTypeCode extends StatusCode {
    
    public UnsupportedMediaTypeCode() {
        super("415 Unsupported Media Type", "User requested an existing but unsupported file (e.g. .jpg binary file)");
    }

}

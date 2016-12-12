package quiz.exceptions;

/**
 *
 * @author memonick
 * @date Nov 30, 2015
 */
public class InvalidInputException extends Exception {
    
    /**
     * An exception that indicates that the input was not of the required form
     * @param input The input that flagged this Exception
     */
    public InvalidInputException(String input) {
        super("Invalid Input: " + input);
    }

}

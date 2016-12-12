package quiz.exceptions;

/**
 *
 * @author memonick
 * @date Nov 30, 2015
 */
public class TooManyAnswersException extends Exception {
    
    /**
     * An exception that indicates that the Question already has met its answer limit
     */
    public TooManyAnswersException() {
        super("The question already has enough answers");
    }

}

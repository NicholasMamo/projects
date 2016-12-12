package quiz.exceptions;

/**
 *
 * @author memonick
 * @date Nov 30, 2015
 */
public class AnswerOutOfBoundsException extends Exception {
    
    /**
     * An exception that indicates that the index given does not refer to an answer
     * @param answer The index that flagged this Exception
     */
    public AnswerOutOfBoundsException(int answer) {
        super("Index " + answer + " is not part of the answer set");
    }

}

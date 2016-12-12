package quiz.exceptions;

/**
 *
 * @author memonick
 * @date Nov 30, 2015
 */
public class UnknownQuestionTypeException extends Exception {
    
    /**
     * An exception that indicates that the Question type was not recognized by the Parser
     * @param type The Question type that flagged this Exception
     */
    public UnknownQuestionTypeException(String type) {
        super(type + " is not a recognized question type");
    }

}

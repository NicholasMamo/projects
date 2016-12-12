package quiz.exceptions;

/**
 *
 * @author memonick
 * @date Nov 30, 2015
 */
public class UnknownCommandException extends Exception {
    
    /**
     * An exception that indicates that the command was not recognized by the Parser
     * @param answer The command that flagged this Exception
     */
    public UnknownCommandException(String answer) {
        super(answer + " is not a recognized command");
    }

}

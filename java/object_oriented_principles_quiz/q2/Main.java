package q2;

import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import parser.Parser;
import quiz.exceptions.*;
import quiz.questions.*;
import quiz.quizmaster.QuizMaster;

/**
 * @author memonick
 */

public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try {
            QuizMaster quizMaster;
            if (args.length > 0) {
                ArrayList<Question> questions = Parser.parseFile(args[0]);
                quizMaster = new QuizMaster(questions);
                if (args.length > 1) {
                    quizMaster.setIncorrectAnswerMultiplier(args[1]);
                }
            } else {
                ArrayList<Question> questions = Parser.parseFile("sample.txt");
                quizMaster = new QuizMaster(questions);
            }
            quizMaster.run();
            System.out.println("Final Score: " + quizMaster.getScore());
        } catch (UnknownCommandException | UnknownQuestionTypeException exception) {
            System.out.println(exception);
        }
    }
    
}

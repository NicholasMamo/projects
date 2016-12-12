package quiz.questions;

import java.util.ArrayList;
import quiz.exceptions.*;

/**
 *
 * @author memonick
 * @date Nov 30, 2015
 */
public class MultiAnswerQuestion extends Question {
    
    /**
     * Initialize the MultiAnswerQuestion with an empty name
     */
    public MultiAnswerQuestion() {
        this("");
    }
    
    /**
     * Initialize the MultiAnswerQuestion with the given text
     * @param question The String representation of the Question
     */
    public MultiAnswerQuestion(String question) {
        this.setQuestion(question);
        this.points = 2;
        this.choices = new ArrayList<>();
        this.answers = new ArrayList<>();
    }
    
    /**
     * Initialize the MultiAnswerQuestion with the given text and choices
     * @param question The String representation of the Question
     * @param choices The set of choices that the user must choose from
     */
    public MultiAnswerQuestion(String question, ArrayList<String> choices) {
        this.setQuestion(question);
        this.points = 2;
        this.choices = new ArrayList<>();
        this.answers = new ArrayList<>();
    }
    
    /**
     * Initialize the MultiAnswerQuestion with the given text and choices
     * @param question The String representation of the Question
     * @param choices The set of choices that the user must choose from
     * @param answers The indices of the correct answers to the MultiAnswerQuestion
     */
    public MultiAnswerQuestion(String question, ArrayList<String> choices, ArrayList<Integer> answers) {
        this.setQuestion(question);
        this.points = 2;
        this.choices = new ArrayList<>();
        this.answers = new ArrayList<>();
    }
    
    /**
     * Add an index of a correct answer to the MultiAnswerQuestion
     * @param answer The index of a correct answer to the MultiAnswerQuestion
     * @throws AnswerOutOfBoundsException An AnswerOutOfBoundsException is thrown if the answer cannot be accepted because its index is not in the answer set 
     */
    @Override
    public void addAnswer(int answer) throws AnswerOutOfBoundsException {
        if (answer >= 0 && answer < this.getNumberofChoices()) {
            this.answers.add(answer);
        } else {
            throw new AnswerOutOfBoundsException(answer);
        }
    }
    
    /**
     * Get the list of indices of the correct answers to the MultiAnswerQuestion
     * @return The list of correct indices of the correct answers to the MultiAnswerQuestion
     */
    public ArrayList<Integer> getAnswers() {
        return this.answers;
    }

    /**
     * Checks whether the given answer is correct or not
     * @param answer The answer to be tested
     * @return A boolean indicating whether the given answer is correct or not
     * @throws InvalidInputException An InvalidInputException is thrown whenever the given string is empty
     */
    @Override
    public boolean isCorrect(String answer) throws InvalidInputException {
        try {
            int start = 0;
            int delimeter = answer.indexOf(",", start) + 1;
            answer = answer.replace(" ", ""); // remove any whitespaces, leaving just commas as delimeters
            ArrayList<Integer> answerSet = new ArrayList<>();
            if (!answer.isEmpty()) { // if an answer was provided
                // go through each answer in the String, except for the last
                while (answer.indexOf(",", start) > 0) {
                    int index = Integer.parseInt(answer.substring(start, answer.indexOf(",", start))); // parse the integer
                    answerSet.add(index - 1); // subtract 1 from the integer retrieved to obtain the index of the answer and add it as a proposed answer
                    start = delimeter;
                    delimeter = answer.indexOf(",", start) + 1;
                }
                // finally, retrieve the last answer in the set
                if (start > 0) {
                    int index = Integer.parseInt(answer.substring(start));
                    answerSet.add(index - 1);
                }
                
                // if the user's answer set is contained in the answer set of the Question, and the answer set of the Question is contained in the user's answer set, then by definition of equality, the two sets are the same
                return (answerSet.containsAll(this.answers) && this.answers.containsAll(answerSet));
            } else {
                throw new InvalidInputException(answer); // if the input was incorrect in any way, throw an exception that indicates this
            }
        } catch (NumberFormatException numberFormat) {
            throw new InvalidInputException(answer); // if parsing the string failed because something other than a number was found, throw an exception that indicates that the input was correct
        }
    }

}

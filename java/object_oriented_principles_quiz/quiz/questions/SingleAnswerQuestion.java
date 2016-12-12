package quiz.questions;

import java.util.ArrayList;
import quiz.exceptions.*;

/**
 *
 * @author memonick
 * @date Nov 30, 2015
 */
public class SingleAnswerQuestion extends Question {
    
    /**
     * Initialize the SingleAnswerQuestion with an empty name
     */
    public SingleAnswerQuestion() {
        this("");
    }
    
    /**
     * Initialize the SingleAnswerQuestion with the given text
     * @param question The String representation of the Question
     */
    public SingleAnswerQuestion(String question) {
        this.setQuestion(question);
        this.points = 1;
        this.choices = new ArrayList<>();
        this.answers = new ArrayList<>();
    }
    
    /**
     * Initialize the SingleAnswerQuestion with the given text and choices
     * @param question The String representation of the Question
     * @param choices The set of choices that the user must choose from
     */
    public SingleAnswerQuestion(String question, ArrayList<String> choices) {
        this.setQuestion(question);
        this.points = 1;
        this.choices = choices;
        this.answers = new ArrayList<>();
    }
    
    /**
     * Initialize the SingleAnswerQuestion with the given text and choices
     * @param question The String representation of the Question
     * @param choices The set of choices that the user must choose from
     * @param answer The index of the correct answer to the SingleAnswerQuestion
     */
    public SingleAnswerQuestion(String question, ArrayList<String> choices, int answer) {
        this.setQuestion(question);
        this.points = 2;
        this.choices = choices;
        this.answers = new ArrayList<>();
        answers.add(answer);
    }
    
    /**
     * Set the index of the answer to the SingleAnswerQuestion
     * @param answer The correct index of the answer to the SingleAnswerQuestion
     * @throws AnswerOutOfBoundsException An AnswerOutOfBoundsException is thrown if the answer cannot be accepted because its index is not in the answer set 
     * @throws TooManyAnswersException A TooManyAnswersException is thrown if the SingleAnswerQuestion already has an answer
     */
    @Override
    public void addAnswer(int answer) throws AnswerOutOfBoundsException, TooManyAnswersException {
        if (answer >= 0 && answer < this.getNumberofChoices()) { // if the index provided is within the bounds of the ArrayList of answers
            if (this.answers.size() > 0) { // if there is already an answer
                throw new TooManyAnswersException(); // throw an exception that indicates this
            } else { // if there is no answer
                this.answers.add(answer); // add the answer
            }
        } else { // if the index is not within the bounds
            throw new AnswerOutOfBoundsException(answer); // throw an exception that indicates this
        }
    }
    
    /**
     * Checks whether the given answer is correct or not
     * @param answer The answer to be tested
     * @return A boolean indicating whether the given answer is correct or not
     * @throws InvalidInputException An InvalidInputException is thrown whenever the given input is incorrect
     */
    @Override
    public boolean isCorrect(String answer) throws InvalidInputException {
        try {
            int index = Integer.parseInt(answer) - 1; // transform the answer into an index
            return this.answers.get(0) == index; // if the answer stored is the same as the given index, then the answer is correct, so return true, else return false
        } catch (NumberFormatException numberFormat) { // if there was an error parsing the given answer
            throw new InvalidInputException(answer); // the input must be invalid, so throw an exception that indicates this
        }
    }

}

package quiz.questions;

import java.util.ArrayList;
import quiz.exceptions.*;

/**
 *
 * @author memonick
 * @date Nov 30, 2015
 */
public abstract class Question {
    
    protected String question = "";
    protected int points;    
    protected ArrayList<String> choices;
    protected ArrayList<Integer> answers;
    
    /**
     * Initialize the Question with the given text
     * @param question The String representation of the Question
     */
    /*public Question(String question) {
        this.question = question;
    }*/
    
    /**
     * Set the text of the Question to the one given
     * @param question The String representation of the Question
     */
    public void setQuestion(String question) {
        this.question = question;
    }
    
    /**
     * Add a choice to the list of choices that the user must choose from
     * @param choice The choice to add to the MultiAnswerQuestion
     */
    public void addChoice(String choice) {
        this.choices.add(choice);
    }
    
    /**
     * Get the list of choices that the user must choose from
     * @return The list of choices that the user must choose from
     */
    public ArrayList<String> getChoices() {
        return this.choices;
    }
    
    /**
     * Get the number of choices that the user must choose from
     * @return The number of choices that the user must choose from
     */
    public int getNumberofChoices() {
        return this.choices.size();
    }
    
    /**
     * Set the value in points of a Question
     * @param points The new value of getting a Question right
     */
    public void setPoints(int points) {
        this.points = points;
    }
    
    /**
     * Get the value in points of a Question
     * @return The value of getting a Question right
     */
    public int getPoints() {
        return this.points;
    }
    
    /**
     * Checks whether the given answer is correct or not
     * @param answer The answer to be tested
     * @return A boolean indicating whether the given answer is correct or not
     * @throws InvalidInputException An InvalidInputException is thrown whenever the given input is incorrect
     */
    abstract boolean isCorrect(String answer) throws InvalidInputException;
    
    /**
     * Add an index of a correct answer to the Question
     * @param index The index of a correct answer to the Question
     * @throws AnswerOutOfBoundsException An AnswerOutOfBoundsException is thrown if the answer cannot be accepted because its index is not in the answer set
     * @throws TooManyAnswersException A TooManyAnswersException is thrown if the Question already has an answer
     */
    abstract void addAnswer(int index) throws AnswerOutOfBoundsException, TooManyAnswersException;
    
    /**
     * Add a list of indices of correct answers to the Question
     * @param indices The indices of the correct answers to the Question
     * @throws AnswerOutOfBoundsException An AnswerOutOfBoundsException is thrown if the answer cannot be accepted because its index is not in the answer set
     * @throws TooManyAnswersException A TooManyAnswersException is thrown if the Question already has an answer
     */
    public void addAnswers(ArrayList<Integer> indices) throws AnswerOutOfBoundsException, TooManyAnswersException {
        for(int index : indices) {
            this.addAnswer(index);
        }
    }
    
    /**
     * Get the text of the Question
     * @return The String representation of the Question
     */
    public String getQuestion() {
        return this.question;
    }
    
    /**
     * Output the text of the Question and every answer choice
     * @return A string comprising the text of the Question and every answer choice
     */
    @Override
    public String toString() {
        String s = this.question + "\n";
        int count = 1;
        for (String choice : this.choices) {
            s += "\t" + count++ + ". " + choice + "\n";
        }
        return s;
    }

}

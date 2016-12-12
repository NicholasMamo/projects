package quiz.quizmaster;

import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;
import quiz.exceptions.*;
import quiz.questions.*;

/**
 *
 * @author memonick
 * @date Nov 30, 2015
 */

public class QuizMaster {
    
    private int incorrectAnswerMultiplier, correctAnswerMultiplier;
    private int score = 0;
    private ArrayList<Question> questions;
    
    /**
     * Initialize the QuizMaster with the default multiplier values and an empty set of Question instances
     */
    public QuizMaster() {
        this.questions = new ArrayList<>();
        this.incorrectAnswerMultiplier = 0;
        this.correctAnswerMultiplier = 1;
    }
    
    /**
     * Initialize the QuizMaster with the given quiz questions and the default multiplier values
     * @param questions The quiz questions
     */
    public QuizMaster(ArrayList<Question> questions) {
        this.questions = questions;
        this.incorrectAnswerMultiplier = 0;
        this.correctAnswerMultiplier = 1;
    }
    
    /**
     * Initialize the QuizMaster with the given multiplier for incorrect answers and the default multiplier for correct answers
     * @param questions The quiz questions
     * @param incorrectAnswerMultiplier The point multiplier for incorrect answers
     */
    public QuizMaster(ArrayList<Question> questions, int incorrectAnswerMultiplier) {
        this.questions = questions;
        this.incorrectAnswerMultiplier = incorrectAnswerMultiplier;
        this.correctAnswerMultiplier = 1;
    }
    
    /**
     * Initialize the QuizMaster with the given multipliers for incorrect and correct answers
     * @param questions The quiz questions
     * @param incorrectAnswerMultiplier The point multiplier for incorrect answers
     * @param correctAnswerMultiplier The point multiplier for correct answers
     */
    public QuizMaster(ArrayList<Question> questions, int incorrectAnswerMultiplier, int correctAnswerMultiplier) {
        this.questions = questions;
        this.incorrectAnswerMultiplier = incorrectAnswerMultiplier;
        this.correctAnswerMultiplier = correctAnswerMultiplier;
    }
    
    /**
     * Set the point multiplier for incorrect answers to the given one
     * @param mode The string indicating the mode for the multiplier for incorrect answers
     */
    public void setIncorrectAnswerMultiplier(String mode) {
        switch (mode) {
            case "StraightForwardGrading":
                this.incorrectAnswerMultiplier = 0;
                break;
            case "NegativeMarkingScheme":
                this.incorrectAnswerMultiplier = -1;
                break;
            default:
                this.incorrectAnswerMultiplier = 0;
                break;
        }
    }
    
    /**
     * Get the point multiplier for incorrect answers
     * @return The point multiplier for incorrect answers
     */
    public int getIncorrectAnswerMultiplier() {
        return this.incorrectAnswerMultiplier;
    }
    
    /**
     * Set the point multiplier for correct answers to the given one
     * @param correctAnswerMultiplier The point multiplier for correct answers
     */
    public void setCorrectAnswerMultiplier(int correctAnswerMultiplier) {
        this.correctAnswerMultiplier = correctAnswerMultiplier;
    }
    
    /**
     * Get the point multiplier for correct answers
     * @return The point multiplier for correct answers
     */
    public int getCorrectAnswerMultiplier() {
        return this.correctAnswerMultiplier;
    }
    
    /**
     * Add a Question to the list of quiz questions
     * @param question The new Question to be added to the quiz
     */
    public void addQuestion(Question question) {
        this.questions.add(question);
    }
    
    /**
     * Get the list of Question instances making up the quiz
     * @return The list of Question instances making up the quiz
     */
    public ArrayList<Question> getQuestions() {
        return this.questions;
    }
    
    /**
     * Get the score of the quiz
     * @return The score of the quiz
     */
    public int getScore() {
        return this.score;
    }
    
    /**
     * Increment the score by the correct answer multiplier
     * @param score The score of the Question
     */
    private void incrementScore(int score) {
        this.score += score * this.correctAnswerMultiplier;
    }
    
    /**
     * Decrement the score by the incorrect answer multiplier
     * @param score The score of the Question
     */
    private void decrementScore(int score) {
        this.score += score * this.incorrectAnswerMultiplier;
    }
    
    /**
     * Go through each Question and conduct the quiz
     */
    public void run() {
        Scanner keyboard = new Scanner(System.in);
        for(Question question : this.questions) { // for each Question
            boolean accepted = false;
            System.out.println(question); // display the Question
            if (question instanceof TruthQuestion) { // if this is a TruthQuestion
                do {
                    System.out.print("Answer (T or F): "); // display its information request tag
                    String answer = keyboard.nextLine(); // fetch the input
                    try {
                        if (((TruthQuestion)question).isCorrect(answer)) { // if the answer is correct
                            this.incrementScore(((TruthQuestion)question).getPoints()); // increment the score by the point value of the TruthQuestion
                            System.out.println("Correct Answer!"); // inform the user
                        } else { // if the answer is incorrect
                            this.decrementScore(((TruthQuestion)question).getPoints()); // decrement the score by the point value of the TruthQuestion
                            System.out.println("Incorrect Answer!"); // inform the user
                        }
                        accepted = true; // flag the boolean indicating that an answer was accepted
                    } catch (InvalidInputException invalidInput) {} // if the input was flagged as invalid, do nothing, forcing the loop to repeat
                } while (!accepted); // repeat until an answer is accpeted
            } else if (question instanceof SingleAnswerQuestion) { // if this is a SingleAnswerQestion
                do {
                    System.out.print("Answer: "); // display its information request tag
                    String answer = keyboard.nextLine(); // fetch the input
                    try {
                        if (((SingleAnswerQuestion)question).isCorrect(answer)) { // if the answer is correct
                            this.incrementScore(((SingleAnswerQuestion)question).getPoints()); // increment the score by the point value of the SingleAnswerQuestion
                            System.out.println("Correct Answer!"); // inform the user
                        } else { // if the answer is incorrect
                            this.decrementScore(((SingleAnswerQuestion)question).getPoints()); // decrement the score by the point value of the SingleAnswerQuestion
                            System.out.println("Incorrect Answer!"); // inform the user
                        }
                        accepted = true; // flag the boolean indicating that an answer was accepted
                    } catch (InvalidInputException invalidInput) {} // if the input was flagged as invalid, do nothing, forcing the loop to repeat
                } while (!accepted); // repeat until an answer is accpeted
            } else if (question instanceof MultiAnswerQuestion) { // if this is a MultiAnswerQestion
                do {
                    System.out.print("Answers (separated by a comma): "); // display its information request tag
                    String answer = keyboard.nextLine(); // fetch the input
                    try {
                        if (((MultiAnswerQuestion)question).isCorrect(answer)) { // if the answer is correct
                            this.incrementScore(((MultiAnswerQuestion)question).getPoints()); // increment the score by the point value of the MultiAnswerQuestion
                            System.out.println("Correct Answer!"); // inform the user
                        } else { // if the answer is incorrect
                            this.decrementScore(((MultiAnswerQuestion)question).getPoints()); // decrement the score by the point value of the MultiAnswerQuestion
                            System.out.println("Incorrect Answer!"); // inform the user
                        }
                        accepted = true; // flag the boolean indicating that an answer was accepted
                    } catch (InvalidInputException invalidInput) {} // if the input was flagged as invalid, do nothing, forcing the loop to repeat
                } while (!accepted);
            }
        }
    }

}

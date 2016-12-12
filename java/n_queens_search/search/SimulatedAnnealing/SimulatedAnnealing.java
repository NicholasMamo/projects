package search.SimulatedAnnealing;

import chessboard.Chessboard;
import chessboard.Queen;
import java.util.ArrayList;
import java.util.Random;

/**
 *
 * @author memonick
 * @date Mar 5, 2016
 */
public abstract class SimulatedAnnealing {
    
    /**
     * The initial temperature
     */
    public static double initialTemperature = 2000;
    
    /**
     * The cooling rate
     */
    public static double coolingRate = 0.998;
    
    /**
     * The temperature below which it is acceptable to stop
     */
    public static double stopTemperature = 1;
    
    /**
     * Search for a better solution to the Chessboard instance
     * @param c the Chessboard instance for which a solution will be sought
     * @return a Chessboard instance after searching is complete (whether optimal or not)
     */
    public static Chessboard search(Chessboard c) {
        double temperature = initialTemperature;
        Chessboard chessboard = c.clone();
        int fitness = SimulatedAnnealing.getFitness(chessboard);
        
        do {
            Chessboard step = SimulatedAnnealing.makeMove(chessboard);
            temperature *= coolingRate;
            int newFitness = SimulatedAnnealing.getFitness(step);
            if (newFitness <= fitness) {
                chessboard = step;
                fitness = newFitness;
            } else { // newFitness > fitness
                if (SimulatedAnnealing.accept(fitness, newFitness, temperature)) {
                    chessboard = step;
                    fitness = newFitness;                    
                }
            }
        } while (temperature > stopTemperature);
        
        return chessboard;
    }
    
    /**
     * Calculate the fitness of the given Chessboard configuration
     * @param chessboard the Chessboard instance whose fitness will be calculated
     * @return the fitness of the given Chessboard configuration
     */
    private static int getFitness(Chessboard chessboard) {
        return chessboard.getCollisions();
    }

    /**
     * Make a move on the Chessboard provided
     * @param c the Chessboard on which to make a move
     * @return a new Chessboard following a random move
     */
    private static Chessboard makeMove(Chessboard c) {
        Chessboard chessboard = c.clone();
        ArrayList<Queen> queens = chessboard.getQueens();
        Random random = new Random();
        
        int r = random.nextInt(queens.size());
        Queen queen = queens.get(r); // pick a random Queen
        
        ArrayList<Queen> moveSet = chessboard.getMoveSet(queen, 1);
        if (moveSet.size() > 0) {
            r = random.nextInt(moveSet.size());
            chessboard.moveQueen(queen, moveSet.get(r));
            return chessboard;
        } else {
            return c;
        }
    }

    /**
     * Check whether the given proposal may be accepted or not
     * @param fitness the current best fitness
     * @param newFitness the proposed fitness
     * @param temperature the current temperature
     * @return a boolean indicating whether the new candidate should be accepted (true), or not (false)
     */
    private static boolean accept(int fitness, int newFitness, double temperature) {
        Random random = new Random();
        
        if (newFitness < fitness) {
            return true;
        } else if (temperature == 0) {
            return false;
        }
        
        double probability = Math.exp(-(newFitness - fitness) / temperature);
        
        return random.nextDouble() < probability;
    }
    
    /**
     * Print the setup of the SA
     */
    public static void printSetup() {
        System.out.println("SA Method:");
        System.out.println("\tinitial temperature: " + initialTemperature);
        System.out.println("\tcooling rate: " + coolingRate);
        System.out.println("\tstopping temperature: " + stopTemperature);
    }    

}

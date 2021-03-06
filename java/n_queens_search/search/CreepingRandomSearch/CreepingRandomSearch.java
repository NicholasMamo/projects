package search.CreepingRandomSearch;

import chessboard.Chessboard;
import static chessboard.Piece.*;
import chessboard.Queen;
import java.util.ArrayList;
import java.util.Random;

/**
 *
 * @author memonick
 * @date Mar 2, 2016
 */
public abstract class CreepingRandomSearch {
    
    /**
     * a value that indicates after how many steps the algorithm should give up if the fitness value remains unchanged
     */
    public static int stagnation = 100;
    
    /**
     * a value between 0 and 1 used in conjunction with what local steps to accept
     * 0 - accept nothing, except if it's better
     * 1 - accept anything
     */
    public static double localThreshold = 1f;
    
    /**
     * a value between 0 and 1 used in conjunction with what global steps to accept
     * 0 - accept nothing, except if it's better
     * 1 - accept anything
     */
    public static double globalThreshold = 1f;
    
    /**
     * the ratio of local steps to global steps
     */
    public static double ratio = 1/1000.0;
    
    /**
     * the number of successive global steps that may fail before giving up
     */
    public static int globalSteps = 10;
    
    /**
     * the maximum number of rounds that may pass before giving up
     */
    public static double maxRounds = 1000000;
    
    /**
     * the number of steps since the last global step
     */
    private static double step = 0;
    
    /**
     * Search for a better solution to the Chessboard instance
     * @param c the Chessboard instance for which a solution will be sought
     * @return a Chessboard instance after searching is complete (whether optimal or not)
     */
    public static Chessboard search(Chessboard c) {
        Chessboard chessboard = c.clone();
        boolean stepPerformed = true;
        
        int steps = 0;
        int fitness = CreepingRandomSearch.getFitness(chessboard);
        int rounds = 0;
        
        while (chessboard.getCollisions() > 0 && stepPerformed && steps < stagnation && rounds++ < maxRounds) {
            stepPerformed = CreepingRandomSearch.localStep(chessboard);
            step += ratio;
            if (step >= 1) {
                step = 0;
                CreepingRandomSearch.globalStep(chessboard);
            }
            
            if (CreepingRandomSearch.getFitness(chessboard) != fitness) {
                fitness = CreepingRandomSearch.getFitness(chessboard);
                steps = 0;
            } else {
                steps++;
            }
            
        }
        
        //System.out.println("Search completed in " + count + " steps\n");        
        
        return chessboard;
    }
    
    /**
     * Perform a local step on the given Chessboard instance
     * @param chessboard the Chessboard instance on which to perform a local step
     * @return a boolean indicating whether a local step was performed (true), or not (false)
     */
    private static boolean localStep(Chessboard chessboard) {
        if (performStep(chessboard, 1)) {
            return true;
        } else {
            return (performStep(chessboard, 2));
        }
    }
    
    /**
     * Try to perform a step on the given Chessboard
     * @param chessboard the Chessboard instance on which to attempt to perform a step
     * @param step the step size
     * @return a boolean indicating whether a step was performed (true), or not (false)
     */
    private static boolean performStep(Chessboard chessboard, int step) {
        ArrayList<Queen> queens = (ArrayList<Queen>) chessboard.getQueens().clone(); // get a list of Queen instances on the Chessboard
        int fitness = CreepingRandomSearch.getFitness(chessboard); // calculate the fitness of the Chessboard
        
        Random random = new Random();
        
        for(Queen queen : queens) { // for each Queen instance
            ArrayList<Queen> moveSet = chessboard.getMoveSet(queen, step); // get the move set for the Queen instance
            int size = moveSet.size();
            for (int i = 0 ; i < size; i++) {
                int index = random.nextInt(moveSet.size());
                Queen candidate = moveSet.get(index);
                chessboard.moveQueen(queen, candidate); // make the move
                if (CreepingRandomSearch.getFitness(chessboard) - fitness <= localThreshold ) { // if the move was better overall
                    return true; // then the local step is performed
                } else {
                    chessboard.moveQueen(candidate, queen); // else, revert the move and keep searching
                    moveSet.remove(index);
                }
            }
        }
        
        return false;
    }
    
    /**
     * Perform a global step on the given Chessboard instance
     * @param chessboard the Chessboard instance on which to perform a global step
     */
    private static Chessboard globalStep(Chessboard chessboard) {
        int steps = 0;
        int fitness = CreepingRandomSearch.getFitness(chessboard);
        int length = chessboard.getLength();
        Chessboard c;
        
        do {
            c = new Chessboard(length);
            c.randomize();
        } while (CreepingRandomSearch.getFitness(c)  - fitness <= globalThreshold && ++steps < CreepingRandomSearch.globalSteps);
        
        return (CreepingRandomSearch.getFitness(c) - fitness <= globalThreshold ? chessboard : c);
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
     * Calculate the fitness of the given Queen
     * @param queen the Queen whose fitness will be calculated
     * @return the fitness of the given queen
     */
    private static int getFitness(Queen queen) {
        return queen.getCollisions();
    }
    
    /**
     * Calculate the neighboring move set for the Queen instances in the given Chessboard
     * @param chessboard the Chessboard instance containing Queen instances
     * @param step the step size from each Queen to every neighbor
     * @return an ArrayList of Queen instances that the Creeping Random Search may move to next
     */
    private static ArrayList<Queen> getMoveSet(Chessboard chessboard, int step) {
        ArrayList<Queen> moveSet = new ArrayList<>();
        
        ArrayList<Queen> queens = chessboard.getQueens();
        int length = chessboard.getLength();
        
        for (Queen queen : queens) {
            moveSet.addAll(chessboard.getMoveSet(queen, step));
        }
        
        return moveSet;
    }
    
    /**
     * Print the setup of the CRS
     */
    public static void printSetup() {
        System.out.println("CRS Method:");
        System.out.println("\tstagnation: " + stagnation);
        System.out.println("\tlocal threshold: " + localThreshold);
        System.out.println("\tglobal threshold: " + globalThreshold);
        System.out.println("\tratio of global steps to local steps: " + ratio);
        System.out.println("\tmaximum global steps: " + globalSteps);
        System.out.println("\tmaximum number of rounds: " + maxRounds);
    }

}

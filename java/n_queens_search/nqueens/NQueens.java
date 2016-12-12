package nqueens;

import java.util.Scanner;

import chessboard.Chessboard;
import search.CreepingRandomSearch.CreepingRandomSearch;
import search.GeneticAlgorithm.GeneticAlgorithm;
import search.SimulatedAnnealing.SimulatedAnnealing;

/**
 *
 * @author memonick
 * @date Mar 2, 2016
 */
public class NQueens {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Chessboard chessboard;
        int chessboardSize; // Chessboard configuration
        System.out.println("Chessboard Size/Number of Queens: ");
        chessboardSize = getInteger(2);
        chessboard = new Chessboard(chessboardSize);
        chessboard.randomize();
        
        getConfigurations();
        
        chessboard.printSetup();
        CreepingRandomSearch.printSetup();
        SimulatedAnnealing.printSetup();
        GeneticAlgorithm.printSetup();
        
        System.out.println("Results:");
        System.out.println("\tOriginal: " + chessboard.getCollisions());
        Chessboard CRSChessboard = CreepingRandomSearch.search(chessboard);
        System.out.println("\tCRS: " + CRSChessboard.getCollisions());
        Chessboard SAChessboard = SimulatedAnnealing.search(chessboard);
        System.out.println("\tSA: " + SAChessboard.getCollisions());
        Chessboard GAChessboard = GeneticAlgorithm.search(chessboard);
        System.out.println("\tGA: " + GAChessboard.getCollisions());
    }
    
    /**
     * Get an integer in the given range
     * @param lowerThreshold the lower range of the integer
     * @return a integer value in the given range
     */
    public static int getInteger(int lowerThreshold) {
        Scanner keyboard = new Scanner(System.in);
        int i;
        do {
            System.out.print("\tEnter a number bigger than, or equal to " + lowerThreshold + ": ");
            i = keyboard.nextInt();
        } while(i < lowerThreshold);
        return i;
    }
    
    /**
     * Get a double in the given range
     * @param lowerThreshold the lower range of the double
     * @param upperThreshold the upper range of the double
     * @return a double value in the given range
     */
    public static double getDouble(double lowerThreshold, double upperThreshold) {
        Scanner keyboard = new Scanner(System.in);
        double r;
        do {
            System.out.print("\tEnter a number between " + lowerThreshold + " and " + upperThreshold + ": ");
            r = keyboard.nextDouble();
        } while(r < lowerThreshold || r > upperThreshold);
        return r;
    }
    
    /**
     * Get a double greater than, or equal to the given value
     * @param lowerThreshold the upper range of the double
     * @return a double greater than, or equal to the given value
     */
    public static double getDoubleWithLowerBound(double lowerThreshold) {
        Scanner keyboard = new Scanner(System.in);
        double r;
        do {
            System.out.print("\tEnter a number bigger than, or equal to " + lowerThreshold + ": ");
            r = keyboard.nextDouble();
        } while(r < lowerThreshold);
        return r;
    }
    
    /**
     * Get a double less than, or equal to the given value
     * @param upperThreshold the upper range of the double
     * @return a double less than, or equal to the given value
     */
    public static double getDoubleWithUpperBound(double upperThreshold) {
        Scanner keyboard = new Scanner(System.in);
        double r;
        do {
            System.out.print("\tEnter a number less than, or equal to " + upperThreshold + ": ");
            r = keyboard.nextDouble();
        } while(r > upperThreshold);
        return r;
    }
    
    /**
     * Get a boolean response (yes/no)
     * @return a boolean indicating whether the response is yes (true), or no (false)
     */
    public static boolean getBooleanResponse() {
        Scanner keyboard = new Scanner(System.in);
        char c;
        do {
            System.out.print("\ty/n: ");
            c = keyboard.next().charAt(0);
        } while(c != 'y' && c != 'n');
        return (c == 'y');
    }

    /**
     * Get the configurations for the CRS, SA and GA searches
     */
    private static void getConfigurations() {
        System.out.println("Would you like to alter the default configurations?");
        if (getBooleanResponse()) {

            System.out.println("Would you like to alter the CRS configuration?");
            if (getBooleanResponse()) {
                int stagnation, globalSteps, maxRounds; // CRS configuration
                double localThreshold, globalThreshold, ratio; // CRS configuration
                System.out.println("CRS");
                System.out.println("Stagnation (number of consecutive steps with roughly the same fitness before giving up):");
                stagnation = getInteger(0);
                System.out.println("Threshold for the local steps to accept:");
                localThreshold = getInteger(0);
                System.out.println("Threshold for the global steps to accept:");
                globalThreshold = getInteger(0);
                System.out.println("Number of local steps before a global step:");
                ratio = 1.0/getInteger(1);
                System.out.println("Number of global steps to try before giving up:");
                globalSteps = getInteger(1);
                System.out.println("Maximum number of rounds to try before giving up:");
                maxRounds = getInteger(1);

                CreepingRandomSearch.stagnation = stagnation;
                CreepingRandomSearch.globalSteps = globalSteps;
                CreepingRandomSearch.localThreshold = localThreshold;
                CreepingRandomSearch.globalThreshold = globalThreshold;
                CreepingRandomSearch.ratio = ratio;
                CreepingRandomSearch.maxRounds = maxRounds;
            }

            System.out.println("Would you like to alter the SA configuration?");
            if (getBooleanResponse()) {
                double initialTemperature, coolingRate, stopTemperature;
                System.out.println("SA");
                System.out.println("Initial temperature:");
                initialTemperature = getDoubleWithLowerBound(1);
                System.out.println("Cooling rate:");
                coolingRate = getDouble(0, 1);
                System.out.println("Stopping temperature:");
                stopTemperature = getDoubleWithUpperBound(initialTemperature);

                SimulatedAnnealing.initialTemperature = initialTemperature;
                SimulatedAnnealing.coolingRate = coolingRate;
                SimulatedAnnealing.stopTemperature = stopTemperature;
            }

            System.out.println("Would you like to alter the GA configuration?");
            if (getBooleanResponse()) {
                int chromosomeCount, rounds; // GA configuration
                double mutationRate, averageThreshold; // GA configuration
                System.out.println("GA");
                System.out.println("Chromosome count:");
                chromosomeCount = getInteger(2);
                System.out.println("Rounds:");
                rounds = getInteger(0);
                System.out.println("Mutation rate:");
                mutationRate = getDouble(0, 1);
                System.out.println("Average threshold:");
                averageThreshold = getDouble(0, 1);

                GeneticAlgorithm.chromosomeCount = chromosomeCount;
                GeneticAlgorithm.rounds = rounds;
                GeneticAlgorithm.mutationRate = mutationRate;
                GeneticAlgorithm.averageThreshold = averageThreshold;
            }
        }
    }
    
}

package search.GeneticAlgorithm;

import chessboard.Chessboard;

/**
 *
 * @author memonick
 * @date Mar 5, 2016
 */
public class Chromosome {
    
    /**
     * The Chessboard instance belonging to this Chromosome
     */
    private Chessboard chessboard;
    
    /**
     * The fitness of this Chromosome
     */
    private double fitness = 0;
    
    /**
     * Initialize the Chromosome with the given Chessboard instance
     * @param chessboard the Chessboard instance of this Chromosome
     */
    public Chromosome (Chessboard chessboard) {
        this.chessboard = chessboard;
    }
    
    /**
     * Set the Chessboard of this Chromosome to the one given
     * @param chessboard the new Chessboard of this Chromosome
     */
    public void setChessboard(Chessboard chessboard) {
        this.chessboard = chessboard;
    }
    
    /**
     * Get the Chessboard belonging to this Chromosome
     * @return the Chessboard belonging to this Chromosome
     */
    public Chessboard getChessboard() {
        return this.chessboard;
    }
    
    /**
     * Set the fitness of this Chromosome to the one given
     * @param fitness the new fitness of this Chromosome
     */
    public void setFitness(double fitness) {
        this.fitness = fitness;
    }
    
    /**
     * Get the fitness of this Chromosome
     * @return the fitness of this Chromosome
     */
    public double getFitness() {
        return this.fitness;
    }
    
    
}

package chessboard;

import static chessboard.Piece.*;
import java.util.ArrayList;

import java.util.Random;

/**
 *
 * @author memonick
 * @date Mar 2, 2016
 */
public class Chessboard {
    
    /**
     * The length of the Chessboard
     */
    private int length;
    
    /**
     * The representation of the Chessboard
     */
    private Piece[][] chessboard;
    
    /**
     * The ArrayList of Queen instances on the Chessboard
     */
    private ArrayList<Queen> queens = new ArrayList<>();
    
    /**
     * Create the Chessboard with the given length
     * @param length the length of the Chessboard
     */
    public Chessboard(int length) {
        this.length = length;
        this.reset();
    }
    
    /**
     * Set the length of the Chessboard
     * @param length the new length of the Chessboard
     */
    public void setLength(int length) {
        this.length = length;
    }
    
    /**
     * Get the length of the Chessboard
     * @return the length of the Chessboard
     */
    public int getLength() {
        return this.length;
    }
    
    /**
     * Get the list of Queens on the Chessboard
     * @return the list of Queens on the Chessboard
     */
    public ArrayList<Queen> getQueens() {
        return this.queens;
    }
    
    /**
     * Get the chess Piece at the given row and column
     * @param row the row in which the Piece lies
     * @param column the column in which the Piece lies
     * @return the Piece, if any, that is in the given coordinate
     */
    public Piece get(int row, int column) {
        if (row >= 0 && row < length && column >= 0 && column < length) { // if the coordinate does lie on the chessboard
            return chessboard[row][column]; // return the Piece at that coordinate
        } else {
            return OTHER; // else return the default value
        }
    }
    
    /**
     * Check whether the given coordinate is empty or not
     * @param row the row in which the coordinate to be checked lies
     * @param column the column in which the coordinate to be checked lies
     * @return a boolean indicating whether the given coordinate is empty (true), or not (false)
     */
    public boolean isEmpty(int row, int column) {
        return chessboard[row][column] == EMPTY;
    }
    
    /**
     * Add a new Queen to the Chessboard at the specified coordinates
     * @param x the x-coordinate of the Queen
     * @param y the y-coordinate of the Queen
     */
    public void addQueen(int x, int y) {
        Queen queen = new Queen(x, y);
        this.addQueen(queen);
    }
    
    /**
     * Add the specified Queen to the Chessboard
     * @param queen the Queen to add to the Chessboard
     */
    public void addQueen(Queen queen) {
        if (this.chessboard[queen.getX()][queen.getY()] == EMPTY) {
            this.queens.add(queen);
            this.chessboard[queen.getX()][queen.getY()] = QUEEN;
        } else {
            Random random = new Random();
            int x = random.nextInt(length);
            int y = random.nextInt(length);
            while(chessboard[x][y] != EMPTY) { // if the position on the Chessboard is not empty
                x = random.nextInt(length); // randomize x
                y = random.nextInt(length); // randomize y
            }
            this.addQueen(x, y);
        }
        this.calculateCollisions();
    }
    
    /**
     * Add the specified list of Queen instances to the Chessboard
     * @param queens the Queen instances to add to the Chessboard
     */
    public void addQueens(ArrayList<Queen> queens) {
        for(Queen queen : queens ) {
            this.addQueen(queen);
        }
    }
    
    /**
     * Remove the given Queen instance from the Chessboard
     * @param queen the Queen instance to remove from the Chessboard
     * @return a boolean indicating whether the given Queen instance was removed (true) or not (false)
     */
    public boolean removeQueen(Queen queen) {
        if (this.chessboard[queen.getX()][queen.getY()] == QUEEN) {
            boolean found = false;
            
            for (int i = 0; i < this.queens.size(); i++) {
                if (this.queens.get(i).getX() == queen.getX() && this.queens.get(i).getY() == queen.getY()) {
                    this.queens.remove(i);
                    found = true;
                }
            }
            
            if (found) {
                this.chessboard[queen.getX()][queen.getY()] = EMPTY;
                return true;
            }
        }
        return false;
    }
    
    /**
     * Move the given Queen instance to a new position
     * @param queen the Queen instance to move
     * @param newQueen the new Queen instance to move to
     * @return a boolean indicating whether the given Queen instance was moved (true) or not (false)
     */
    public boolean moveQueen(Queen queen, Queen newQueen) {
        if (this.chessboard[newQueen.getX()][newQueen.getY()] == EMPTY) {
            if (this.removeQueen(queen)) {
                this.addQueen(newQueen);
                this.calculateCollisions();
                return true;
            }
        }
        return false;
    }
    
    /**
     * Get the total number of collisions in the Chessboard
     * @return the total number of collisions in the Chessboard
     */
    public int getCollisions() {
        int collisions = 0;
        for (Queen queen : queens) {
            collisions += queen.getCollisions();
        }
        return collisions;
    }
    
    /**
     * Reset the Chessboard
     */
    public void reset() {
        this.queens.clear();
        chessboard = new Piece[length][length];
        for (int row = 0; row < length; row++) {
            for (int column = 0; column < length; column++) {
                chessboard[row][column] = EMPTY;
            }
        }
    }
    
    /**
     * Insert queens into the Chessboard equal to its length, such that each column has exactly one queen
     */
    public void randomizeByColumn() {
        this.randomize(this.length);
    }
    
    /**
     * Insert the given number of queens into the Chessboard, such that each column has no more than one queen
     * @param queens the number of queens to insert into the Chessboard
     */
    public void randomizeByColumn(int queens) {
        if (queens < length * length) { // only insert the queens if there is enough space for them
            Random random = new Random();
            for (int i = 0; i < queens; i++) {
                for (int x = 0; x < queens; x++) {
                    int y = random.nextInt(length);
                    this.addQueen(x, y);
                }
            }
        }
        this.calculateCollisions();
    }
    
    /**
     * Insert queens into the Chessboard equal to its length
     */
    public void randomize() {
        this.randomize(this.length);
    }
    
    /**
     * Insert the given number of queens into the Chessboard
     * @param queens the number of queens to insert into the Chessboard
     */
    public void randomize(int queens) {
        if (queens < length * length) { // only insert the queens if there is enough space for them
            Random random = new Random();
            for (int i = 0; i < queens; i++) {
                int x = random.nextInt(length);
                int y = random.nextInt(length);
                while(chessboard[x][y] != EMPTY) { // if the position on the Chessboard is not empty
                    x = random.nextInt(length); // randomize x
                    y = random.nextInt(length); // randomize y
                }
                this.addQueen(x, y);
            }
        }
        this.calculateCollisions();
    }
    
    /**
     * Calculate the number of possible collisions of each Queen
     */
    public void calculateCollisions() {
        this.resetCollisions();
        for (int i = 0; i < queens.size(); i++) {
            for (int j = i + 1; j < queens.size(); j++) {
                if (queens.get(i) != queens.get(j)) {
                    if (queens.get(i).onCollisionCourse(queens.get(j))) {
                        queens.get(i).addCollision();
                        queens.get(j).addCollision();
                    }
                }
            }
        }
    }
    
    /**
     * Reset the number of collisions of each Queen
     */
    public void resetCollisions() {
        for(Queen queen : queens) {
            queen.setCollisions(0);
        }
    }
    
    /**
     * Get the move set of the given Queen
     * @param queen the Queen whose move set will be calculated
     * @param step the maximum number of steps that may be performed
     * @return a list of moves that the Queen may perform
     */
    public ArrayList<Queen> getMoveSet(Queen queen, int step) {
        ArrayList<Queen> moveSet = new ArrayList<>();
        if (step == 1) {
            moveSet.addAll(this.getMoveSet(queen));
        } else if (step == 2) {
            ArrayList<Queen> tempMoveSet = new ArrayList<>();
            tempMoveSet.addAll(this.getMoveSet(queen));
            for(Queen other : tempMoveSet) {
                moveSet.addAll(this.getMoveSet(other, 1));
            }
        }
        return moveSet;
    }
    
     /**
     * Get the move set of the given Queen
     * @param queen the Queen whose move set will be calculated
     * @return a list of moves that the Queen may perform
     */
    private ArrayList<Queen> getMoveSet(Queen queen) {
        ArrayList<Queen> moveSet = new ArrayList<>();
        
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if (x != 0 || y != 0) {
                    moveSet.addAll(this.getMoves(queen, x, y));
                }
            }
        }        
        
        return moveSet;
    }
    
     /**
     * Get all the possible moves of the given Queen
     * @param queen the Queen whose move set will be calculated
     * @param xDirection the x-direction to move towards
     * @param yDirection the y-direction to move towards
     * @return a list of moves that the Queen may perform
     */
    private ArrayList<Queen> getMoves(Queen queen, int xDirection, int yDirection) {
        ArrayList<Queen> moveSet = new ArrayList<>();
        
        int row = 1;
        int column = 1;
        int x = queen.getX();
        int y = queen.getY();
        
        while (x - xDirection * row >= 0 && x - xDirection * row < this.length &&
                y - yDirection * column >= 0 && y - yDirection * column < this.length &&
                this.get(x - xDirection * row, y - yDirection * column) == EMPTY) {
            moveSet.add(new Queen(x - xDirection * row, y - yDirection * column));
            row++;
            column++;
        }
        
        return moveSet;
    }
    
    /**
     * Get the Chebyshev distance between the two Queen instances provided
     * @param queen1 the first Queen instance to be used in computing Chebyshev distance
     * @param queen2 the second Queen instance to be used in computing Chebyshev distance
     * @return the Chebyshev distance between the two Queen instances provided
     */
    private static int chebyshev(Queen queen1, Queen queen2) {
        return Math.max(Math.abs(queen1.getX() - queen2.getX()), Math.abs(queen1.getY() - queen2.getY()));
    }
    
    /**
     * Print the setup of the Chessboard
     */
    public void printSetup() {
        System.out.println("Instance name: " + length + "-queens (random)");
    }
    
    /**
     * Clone the current Chessboard and return the clone
     * @return a clone of the current Chessboard
     */
    @Override
    public Chessboard clone() {
        Chessboard clone = new Chessboard(length);
        for(Queen queen : queens) {
            clone.addQueen(queen.getX(), queen.getY());
        }
        return clone;
    }
    
    /**
     * Get the String representation of the Chessboard
     * @return the String representation of the Chessboard
     */
    @Override
    public String toString() {
        String s = "";
        s += "Collisions: " + this.getCollisions() + "\n";
        s += "   ";
        for (int row = 0; row < length; row++) {
            s += " " + (row + 1) + "  ";
        }
        s += "\n";
        for (int row = 0; row < length; row++) {
            s += (row + 1) + " |";
            for (int column = 0; column < length; column++) {
                s += " " + chessboard[row][column] + " |";
            }
            s += "\n";
        }
        return s;
    }
    
}

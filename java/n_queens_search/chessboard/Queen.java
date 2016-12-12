package chessboard;

/**
 *
 * @author memonick
 * @date Mar 2, 2016
 */
public class Queen {

    private int x, y, collisions;
    
    /**
     * Initialize the Coordinate with the given x- and y-components
     * @param x the x-component of the Coordinate
     * @param y the y-component of the Coordinate
     */
    public Queen(int x, int y) {
        this.x = x;
        this.y = y;
        this.collisions = 0;
    }
    
    /**
     * Set the x-component of the Queen
     * @param x the x-component of the Queen
     */
    public void setX(int x) {
        this.x = x;
    }
    
    /**
     * Get the x-component of the Queen
     * @return the x-component of the Queen
     */
    public int getX() {
        return this.x;
    }
    
    /**
     * Set the y-component of the Queen
     * @param y the y-component of the Queen
     */
    public void setY(int y) {
        this.y = y;
    }
    
    /**
     * Get the y-component of the Queen
     * @return the y-component of the Queen
     */
    public int getY() {
        return this.y;
    }
    
    /**
     * Add a collision to this Queen
     */
    public void addCollision() {
        this.collisions++;
    }
    
    /**
     * Set the number of collisions of this Queen to the given number
     * @param n the number of collisions of this Queen
     */
    public void setCollisions(int n) {
        this.collisions = n;
    }
    
    /**
     * Get the number of collisions that this Queen may have
     * @return the number of collisions that this Queen may have
     */
    public int getCollisions() {
        return this.collisions;
    }
    
    /**
     * Check if this Queen may collide with another Queen
     * @param other the other Queen with which to check the collision course
     * @return a boolean indicating whether this queen may collide with another queen
     */
    public boolean onCollisionCourse(Queen other) {
        if (this.x == other.getX()) { // horizontally the same
            return true;
        } else if (this.y == other.getY()) { // vertically the same
            return true;
        } else if (Math.abs(this.y - other.getY()) == Math.abs(this.x - other.getX())) {
            return true;
        } else {
            return false;
        }
    }
    
    /**
     * Check whether the given Object is the same as this one or not
     * @param object The Object to be used in comparison
     * @return a boolean indicating whether this Queen and the given Object are the same or not
     */
    @Override
    public boolean equals(Object object) {
        if (object instanceof Queen) {
            return ((Queen) object).getX() == this.x && ((Queen) object).getY() == this.y;
        } else {
            return false;
        }
    }

    @Override
    public int hashCode() {
        int hash = 3;
        hash = 43 * hash + this.x;
        hash = 43 * hash + this.y;
        return hash;
    }
    
    /**
     * Get the String representation of the Queen
     * @return the String representation of the Queen
     */
    @Override
    public String toString() {
        return "(" + (this.x + 1) + ", " + (this.y + 1) + ") - " + this.collisions + " collisions";
    }
    
}
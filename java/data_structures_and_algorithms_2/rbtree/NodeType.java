package rbtree;

/**
 * An Enum of all possible Node states
 * @author memonick
 */
public enum NodeType {
    
    BLACK, RED, NIL;
    
    /**
     * Get the textual representation of the NodeType
     * @return the textual representation of the NodeType
     */
    @Override
    public String toString() {
        switch(this) {
            case BLACK: return "B";
            case RED: return "R";
            case NIL: return "N";
            default: return "O";
        }
    }
    
}

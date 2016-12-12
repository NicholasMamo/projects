package chessboard;

/**
 *
 * @author memonick
 * @date Mar 2, 2016
 */
public enum Piece {
    
    EMPTY, QUEEN, OTHER;
    
    @Override
    public String toString() {
        switch (this){
            case EMPTY: return " ";
            case QUEEN: return "Q";
            case OTHER: return "O";
            default: return "";
        }
    }

}

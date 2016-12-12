package graph;

/**
 *
 * @author memonick
 * @date Nov 19, 2015
 */
public class Edge {
    
    private Node source, destination;
    private boolean polarity;
    
    /**
     * Initialize the Edge instance with the given source, destination and polarity
     * @param source The source Node of the Edge
     * @param destination The destination Node of the Edge
     * @param polarity The polarity of the Edge (true is positive, false is negative)
     */
    public Edge(Node source, Node destination, boolean polarity) {
        this.source = source;
        this.destination = destination;
        this.polarity = polarity;
    }
    
    /**
     * Set the polarity of the Edge
     * @param polarity A boolean indicating the polarity of the Edge, whether positive (true) or negative (false)
     */
    public void setPositive(boolean polarity) {
        this.polarity = polarity;
    }
    
    /**
     * Get the polarity of the Edge
     * @return A boolean indicating whether the Edge is positive (true) or negative (false)
     */
    public boolean isPositive() {
        return this.polarity;
    }
    
    /**
     * Set the source Node of the Edge
     * @param source The new source Node of the Edge
     */
    public void setSource(Node source) {
        this.source = source;
    }
    
    /**
     * Get the source Node of the Edge
     * @return The source Node of the Edge
     */
    public Node getSource() {
        return source;
    }
    
    /**
     * Set the destination Node of the Edge
     * @param destination The new destination Node of the Edge
     */
    public void setDestination(Node destination) {
        this.destination = destination;
    }
    
    /**
     * Get the destination Node of the Edge
     * @return The destination Node of the Edge
     */
    public Node getDestination() {
        return destination;
    }
    
    @Override
    public String toString() {
        String s = "";
        s += source;
        s += isPositive() ? " IS-A " : " IS-NOT-A ";
        s += destination;
        return s;
    }

}

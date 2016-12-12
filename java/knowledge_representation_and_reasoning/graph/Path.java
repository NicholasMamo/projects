package graph;

import java.util.ArrayList;

/**
 *
 * @author memonick
 * @date Nov 19, 2015
 */

public class Path {
    
    private ArrayList<Edge> edges = new ArrayList<>();
    
    /**
     * Add the given Edge to the head of the Path
     * @param edge The Edge to be added to the Path
     */
    public void append(Edge edge) {
        edges.add(0, edge);
    }
    
    /**
     * Get the length, or size, of the Path
     * @return The number of Edge instances making up the Path
     */
    public int size() {
        return edges.size();
    }
    
    /**
     * Get the list of Edge instances making up the Path
     * @return The list of Edge instances making up the Path
     */
    public ArrayList<Edge> getEdges() {
        return edges;
    }
    
    /**
     * Get the Edge instance at the given index
     * @param i The index of the Edge to be retrieved
     * @return The Edge instance at the given index
     */
    public Edge getEdge(int i) {
        return edges.get(i);
    }
    
    @Override
    public String toString() {
        String s = "";
        if (size() > 0) {
            s += edges.get(0).getSource();
            for (Edge edge : edges) {
                s += (edge.isPositive() ? " IS-A " : " IS-NOT-A ") + edge.getDestination();
            }
        }
        return s;
    }
    
}

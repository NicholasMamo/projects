package graph;

import java.util.ArrayList;

/**
 *
 * @author memonick
 * @date Nov 19, 2015
 */
public class Graph {
    
    protected ArrayList<Node> nodes = new ArrayList<>();
    
    public Graph() {}
    
    /**
     * Checks whether the given Node is a member of the Graph or not
     * @param n The Node to be sought in the Graph
     * @return A boolean indicating whether the Node is a member of the Graph (true) or not (false)
     */
    protected boolean inGraph(Node n) {
        return nodes.contains(n);
    }
    
    /**
     * Print all the Node instances in the Graph
     */
    public void printNodes() {
        for (Node node : nodes) {
            System.out.println(node);
            for (Edge edge : node.getEdges()) {
                System.out.println("\t" + edge);
            }
        }
    }
    
}

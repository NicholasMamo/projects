package graph;

import java.util.ArrayList;

/**
 *
 * @author memonick
 * @date Nov 19, 2015
 */
public class Node {
    
    private ArrayList<Edge> edges = new ArrayList<>();
    private String name;
    
    /**
     * Initialize the Node with the given name
     * @param name 
     */
    public Node(String name) {
        this.name = name;
    }
    
    /**
     * Add an Edge to the Node, starting from this Node, destined to the given Node with the given polarity
     * @param node The destination Node from the current Node
     * @param positive A boolean indicating whether the Edge has a positive polarity (true) or not (false)
     */
    public void addEdge(Node node, boolean positive) {
        Edge e = new Edge(this, node, positive);
        edges.add(e);
    }
    
    /**
     * Get the name of the Node
     * @return The name of the Node
     */
    public String getName() {
        return name;
    }
    
    /**
     * Set the name of the Node
     * @param name The name of the Node
     */
    public void setName(String name) {
        this.name = name;
    }
    
    /**
     * Get the list of Edge instances that connect this Node to other Node instances
     * @return The list of Edge instances that connect this Node to other Node instances
     */
    public ArrayList<Edge> getEdges() {
        return edges;
    }
    
    /**
     * Get a list of Path instances, if any, that connect this Node to the given Node with the given polarity
     * @param n The Node at which all the Path instances should end
     * @return A list of Path instances, if any, that connect this Node to the given Node with the given polarity
     */
    public ArrayList<Path> getPathTo(Node n) {
        ArrayList<Path> paths = new ArrayList<>();
        for(Edge edge : edges) {
            if (edge.getDestination().equals(n)) { // if the destination is the same as the desired node
                Path path = new Path();
                path.append(edge);
                paths.add(path);
            } else if (edge.isPositive()) { // if this is not a negative path
                if (edge.getDestination().hasPathTo(n)) { // and a path exists from the next edge to the desired node
                    ArrayList<Path> edgePaths = edge.getDestination().getPathTo(n);
                    for (Path path : edgePaths) {
                        path.append(edge);
                    }
                    paths.addAll(edgePaths);
                }
            }
        }
        return paths;
    }
    
    /**
     * Get a list of Path instances, if any, that connect this Node to the given Node with the given polarity
     * @param n The Node at which all the Path instances should end
     * @param positivePolarity A boolean indicating whether the Path should be a positive one (true) or a negative one (false)
     * @return A list of Path instances, if any, that connect this Node to the given Node with the given polarity
     */
    public ArrayList<Path> getPathTo(Node n, boolean positivePolarity) {
        ArrayList<Path> paths = new ArrayList<>();
        for(Edge edge : edges) {
            if (edge.getDestination().equals(n)) { // if the destination is the same as the desired node
                if (edge.isPositive() == positivePolarity) { // and if the polarity is the same, add the path
                    Path path = new Path();
                    path.append(edge);
                    paths.add(path);
                }
            } else if (edge.isPositive()) { // if this is not a negative path
                if (edge.getDestination().hasPathTo(n, positivePolarity)) { // and a path exists from the next edge to the desired node
                    ArrayList<Path> edgePaths = edge.getDestination().getPathTo(n, positivePolarity);
                    for (Path path : edgePaths) {
                        path.append(edge);
                    }
                    paths.addAll(edgePaths);
                }
            }
        }
        return paths;
    }
    
    /**
     * Check whether this Node has a Path with the given polarity to the given Node
     * @param n The Node at which the Path should end
     * @param positivePolarity A boolean indicating the desired polarity of the Path, whether positive (true), or negative (false)
     * @return A boolean indicating whether this Node has a Path with the given polarity to the given Node (true), or not (false)
     */
    public boolean hasPathTo(Node n, boolean positivePolarity) {
        for(Edge edge : edges) {
            if (edge.getDestination().equals(n)) { // if the destination is the same as the desired node
                if (edge.isPositive() == positivePolarity) { // and if the polarity is the same, then a path exists
                    return true;
                }
            } else if (edge.isPositive()) { // if this is not a negative path
               if (edge.getDestination().hasPathTo(n, positivePolarity)) { // and a path exists to the desired node
                   return true;
               }
            }
        }
        return false;
    }
    
    /**
     * Check whether this Node has a Path (irrespective of its polarity) to the given Node
     * @param n The Node at which the Path should end
     * @return A boolean indicating whether this Node has a Path (irrespective of its polarity) to the given Node (true), or not (false)
     */
    public boolean hasPathTo(Node n) {
        for(Edge edge : edges) {
            if (edge.getDestination().equals(n) || edge.getDestination().hasPathTo(n)) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * 
     * @param n The Node Object that will be compared to this Node. Comparison is done through the name of the Node
     * @return A boolean indicating whether the two Node Object instances are the same (true) or not (false) in terms of their name
     */
    @Override
    public boolean equals(Object n) {
        if (n instanceof Node) {
            return ((Node) n).getName().equals(this.name);
        } else {
            return false;
        }
    }
    
    @Override
    public String toString() {
        String s = this.getName();
        return s;
    }

}

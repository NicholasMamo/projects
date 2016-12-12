package assignment;

import graph.*;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.net.URISyntaxException;
import java.util.ArrayList;

/**
 *
 * @author memonick
 * @date Nov 19, 2015
 */
public class InheritanceNetwork extends Graph {

    /**
     * Load the inheritance network from the File indicated by the provided filename
     * @param filename The filename of the File from which the input will be read
     * @return A boolean indicating whether the File could be opened or not
     */
    public InheritanceNetwork(String filename) {
        super();
        String filePath = "";
        File file = new File("");
        try {
            file = new File(InheritanceNetwork.class.getProtectionDomain().getCodeSource().getLocation().toURI().getPath());
            String absolutePath = file.getAbsolutePath();
            if(absolutePath.contains("Assignment.jar")) {
                absolutePath = absolutePath.replace("Assignment.jar", "");
                filePath = absolutePath + File.separator + ".." + File.separator;
            } else {
                filePath = absolutePath + File.separator + ".." + File.separator + ".." + File.separator;
            }
        } catch (URISyntaxException uri) {
            uri.printStackTrace();
        }
        try (BufferedReader br = new BufferedReader(new FileReader(filePath + "input/" + filename))) {
            String line;
            while ((line = br.readLine()) != null) {
               addInheritance(line);
            }
        } catch (IOException io) {
            System.out.println("The file could not be opened");
        }
    }
    
    /**
     * Parse the given line of text and add it to the inheritance network
     * @param line The line that will be interpreted and fed into the inheritance network
     */
    private void addInheritance(String line) {
        int index;
        Node subconcept, superconcept;
        if ((index = line.indexOf("IS-A")) > -1) {
            subconcept = new Node(line.substring(0, index - 1));
            superconcept = new Node(line.substring(index + ("IS-A").length() + 1));
            // check if subconcept exists already
            if (!inGraph(subconcept)) { // if it doesn't exist, add it
                nodes.add(subconcept);
            } else { // else retrieve it from the Graph
                subconcept = nodes.get(nodes.indexOf(subconcept));
            }
            
            // check if superconcept exists already
            if (!inGraph(superconcept)) {// if it doesn't exist, add it
                nodes.add(superconcept);
            } else { // else retrieve it from the Graph
                superconcept = nodes.get(nodes.indexOf(superconcept));
            }
            subconcept.addEdge(superconcept, true);
        } else if ((index = line.indexOf("IS-NOT-A")) > -1) {
            subconcept = new Node(line.substring(0, index - 1));
            superconcept = new Node(line.substring(index + ("IS-NOT-A").length() + 1));
            // check if subconcept exists already
            if (!inGraph(subconcept)) { // if it doesn't exist, add it
                nodes.add(subconcept);
            } else {
                subconcept = nodes.get(nodes.indexOf(subconcept)); // else retrieve it from the Graph
            }
            
            // check if superconcept exists already
            if (!inGraph(superconcept)) {// if it doesn't exist, add it
                nodes.add(superconcept);
            } else {
                superconcept = nodes.get(nodes.indexOf(superconcept)); // else retrieve it from the Graph
            }
            subconcept.addEdge(superconcept, false);
        }
    }
    
    /**
     * Find all the possible Path instances that satisfy the given query
     * @param query The query to be executed
     * @return A list of Path instances that satisfy the given query
     */
    public ArrayList<Path> query(String query) {
        Node subconcept, superconcept;
        ArrayList<Path> paths = new ArrayList<>();
        boolean positivePolarity;
        
        // check if the query is valid and assign the superconcept
        superconcept = extractSuperConcept(query);
        
        // if the query was validated, get the subconcept and get the actual nodes from the list
        if (!superconcept.getName().equals("")) {
            subconcept = extractSubConcept(query);
            positivePolarity = extractPositivePolarity(query);
            if (inGraph(subconcept) && inGraph(superconcept)) {
                subconcept = nodes.get(nodes.indexOf(subconcept));
                superconcept = nodes.get(nodes.indexOf(superconcept));
            }

            if (subconcept.hasPathTo(superconcept)) {
                paths = subconcept.getPathTo(superconcept);
            } else {
                System.out.println("A path does not exist");
            }

            return paths;
        } else {
            return paths;
        }
    }
    
    /**
     * Extract the shortest Path instance(s) from the given list
     * @param paths The list of Path instances that will be searched for the shortest instances
     * @return A list containing the shortest Path instance(s)
     */
    public ArrayList<Path> getShortestPath(ArrayList<Path> paths) {
        int min = Integer.MAX_VALUE;
        ArrayList<Path> shortestPaths = new ArrayList<>();
        for (int i = 0; i < paths.size(); i++) {
            if (paths.get(i).size() < min) {
                min = paths.get(i).size();
                shortestPaths.clear();
                shortestPaths.add(paths.get(i));
            } else if (paths.get(i).size() == min) {
                shortestPaths.add(paths.get(i));
            }
        }
        return shortestPaths;
    }
    
    /**
     * Extract all the Path instances that satisfy the Inferential Distance algorithm
     * @param paths The list of Path instances that will be checked with the Inferential Distance algorithm
     * @return A list comprising all the Path instances that satisfy the Inferential Distance algorithm
     */
    public ArrayList<Path> getInferentialPath(ArrayList<Path> paths) {
        ArrayList<Path> inferentialPaths = new ArrayList<>();
        for (Path path : paths) { // for each path in the list
            if (!isPreempted(path) && !isRedundant(path)) {
                inferentialPaths.add(path);
            }
        }
        return inferentialPaths;
    }
    
    /**
     * Checks whether any part of the given Path is preempted by another edge
     * @param path The Path to be checked
     * @return A boolean indicating whether the given Path is preempted (true) or not (false)
     */
    private boolean isPreempted(Path path) {
        // for each Edge in the Path
        for (int i = 0; i < path.size(); i++) {
            Edge edge = path.getEdge(i);
            // get the source Node
            Node source = edge.getSource();
            
            // for each subsequent Node in the Path
            for (int j = i + 1; j < path.size(); j++) {
                // get all the Node instances connected to the current source Node
                ArrayList<Edge> sourceEdges = source.getEdges();
                // for each Edge from the source Node
                for (Edge sourceEdge : sourceEdges) {
                    // if there is an Edge from the sourceNode to a destination Node and it is of a different polarity, then there is an Edge that preempts this path
                    if (sourceEdge.getDestination().equals(path.getEdge(j).getDestination()) && 
                            (sourceEdge.isPositive() != path.getEdge(j).isPositive())) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    /**
     * Checks whether any part of the given Path is redundant
     * @param path The Path to be checked
     * @return A boolean indicating whether the given Path is redundant (true) or not (false)
     */
    private boolean isRedundant(Path path) {
        for (Edge edge : path.getEdges()) {
            /*
             * if there is more than one Path from each Edge source Node to the destination Node (with the same polarity)
             *  then assuming that duplicate Edge instances are not allowed, the other one must be more complex
             */
            if (edge.getSource().getPathTo(edge.getDestination(), edge.isPositive()).size() > 1) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * Extract the super concept from the given query
     * @param query The query to be analyzed
     * @return The super concept Node extracted from the given query
     */
    private Node extractSuperConcept(String query) {
        if (query.contains("IS-A")) {
            int index = query.indexOf("IS-A");
            return new Node(query.substring(index + ("IS-A").length() + 1));
        } else if (query.contains("IS-NOT-A")) {
            int index = query.indexOf("IS-NOT-A");
            return new Node(query.substring(index + ("IS-NOT-A").length() + 1));
        } else {
            return new Node("");
        }
    }
    
    /**
     * Extract the sub concept from the given query
     * @param query The query to be analyzed
     * @return The sub concept Node extracted from the given query
     */
    private Node extractSubConcept(String query) {
        if (query.contains("IS-A")) {
            int index = query.indexOf("IS-A");
            return new Node(query.substring(0, index - 1));
        } else if (query.contains("IS-NOT-A")) {
            int index = query.indexOf("IS-NOT-A");
            return new Node(query.substring(0, index - 1));
        } else {
            return new Node("");
        }
    }
    
    /**
     * Extract the polarity of the given query
     * @param query The query to be analyzed
     * @return A boolean indicating whether the query is a positive one (true) or not (false)
     */
    private boolean extractPositivePolarity(String query) {
        if (query.contains("IS-A")) {
            return true;
        } else if (query.contains("IS-NOT-A")) {
            return false;
        } else {
            return false;
        }
    }
    
}

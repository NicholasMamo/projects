package assignment;

import graph.Path;
import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author memonick
 * @date Nov 19, 2015
 */
public class Assignment {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        InheritanceNetwork network;
        final String defaultString = "elephant.txt";
        if (args.length > 0) {
            network = new InheritanceNetwork(args[0]);
        } else {
            network = new InheritanceNetwork(defaultString);
        }
        network.printNodes();
        System.out.println("\n------------------------------\n");
        
        Scanner scanner = new Scanner(System.in);            
        String query;
        
        do {
            System.out.print("Enter a query: ");
            query = scanner.nextLine();
            
            if (!query.equalsIgnoreCase("quit")) {
                ArrayList<Path> paths = network.query(query);
                for (Path path : paths) {
                    System.out.println("Possible Path: " + path);
                }
                System.out.println();

                ArrayList<Path> shortestPaths = network.getShortestPath(paths);
                for (Path path : shortestPaths) {
                    System.out.println("Shortest Path: " + path);
                }
                System.out.println();

                ArrayList<Path> inferentialPaths = network.getInferentialPath(paths);
                for (Path path : inferentialPaths) {
                    System.out.println("Inferential Path: " + path);
                }

                System.out.println("\n------------------------------\n");
            }
            
        } while (!query.equalsIgnoreCase("quit"));
    }
    
}

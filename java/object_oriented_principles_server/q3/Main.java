package q3;

import server.server.Server;

/**
 *
 * @author memonick
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        if (args.length > 1) {
            try {
                Server server = new Server(Integer.parseInt(args[1]), args[0]);
            } catch (NumberFormatException e) {
                Server server = new Server(9180, args[0]);
            }
        } else if (args.length > 0) {
            Server server = new Server(9180, args[0]);
        } else {
            Server server = new Server(9180);
        }
    }
    
}

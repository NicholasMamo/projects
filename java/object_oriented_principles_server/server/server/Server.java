package server.server;

import java.io.File;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;
import javax.swing.filechooser.FileSystemView;

import server.headers.*;

/**
 *
 * @author memonick
 * @date Dec 1, 2015
 */

public class Server {
    
    private int port;
    private String workingDirectory;

    /**
     * Create the Server with a default port of 0000
     */
    public Server() {
        this(0000, "");
    }
    
    /**
     * Create the Server with the given port
     * @param port The port that the Server will be listening on
     */
    public Server(int port) {
        this(port, "");
    }
    
    /**
     * Create the Server with the given port
     * @param port The port that the Server will be listening on
     * @param workingDirectory  The working directory
     */
    public Server(int port, String workingDirectory) {
        this.port = port;
        
        File file = new File(workingDirectory);
        System.out.println("Server opened on port " + port);
        if (file.exists()) {
            System.out.println("Working directory: " + workingDirectory);
            this.workingDirectory = workingDirectory;
        } else {
            System.out.println("'" + workingDirectory + "' was not found on the system");
            System.out.println("The working directory was reset to " + FileSystemView.getFileSystemView().getHomeDirectory().toString());
            this.workingDirectory = FileSystemView.getFileSystemView().getHomeDirectory().toString();
        }
        if (this.workingDirectory.charAt(this.workingDirectory.length() - 1) != '/') { // if the file path does not end with a '/'
            this.workingDirectory += '/'; // append the file path with a '/'
        }
        run();
    }
    
    public void run() {
        try {
            ServerSocket sSocket = new ServerSocket(port); // start the Server with the given port number
            System.out.println("Server started at: " + new Date()); // display an information message
            
            // keep listening for requests
            while (true) {
                try (Socket socket = sSocket.accept()) { // when a request is received
                    PrintWriter output = new PrintWriter(socket.getOutputStream(), true); // get the Socket output buffer
                    ResponseHeader response = RequestHeaderParser.parse(port, workingDirectory, socket); // parse the request header
                    output.println(response);
                    socket.close(); // close the Socket when it's done
                }
            }
        } catch (Exception e) {
            System.out.println("The server could not be started!");
            System.out.println(e);
        }
    }
    
    /**
     * Set the working directory of the Server to the one specified
     * @param workingDirectory The new working directory
     */
    public void setWorkingDirectory(String workingDirectory) {
        this.workingDirectory = workingDirectory;
    }
    
    /**
     * Get the working directory of the Server
     * @return The working directory of the Server
     */
    public String getWorkingDirectory() {
        return this.workingDirectory;
    }
    
}

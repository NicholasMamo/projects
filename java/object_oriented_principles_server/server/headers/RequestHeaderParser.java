package server.headers;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.ArrayList;

import server.exceptions.*;
import server.statuscodes.*;

/**
 *
 * @author memonick
 * @date Dec 1, 2015
 */
public abstract class RequestHeaderParser {
    
    /**
     * Parse the request received over the given Socket on the given port, with respect to the given working directory
     * @param port The port that the Server is listening for connections on
     * @param workingDirectory The root directory where files are sought
     * @param socket The socket that received the request
     * @return The ResponseHeader that services the given request
     */
    public static ResponseHeader parse(int port, String workingDirectory, Socket socket) {
        StatusCode code = null; // the status code of the ResponseHeader
        ResponseHeader response = null; // the empty ResponseHeader
        ArrayList<String> headers = new ArrayList<>(); // the list of additional headers, if any, that make up the ResponseHeader
        String body = ""; // the body of the ResponseHeader

        try {
            BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream())); // get the Socket input buffer

            String line = null;
            
            line = input.readLine(); // fetch the first line
            if (line != null && !("").equals(line)) { // if the request is not null or empty
                if (!line.substring(0, line.indexOf(" ")).equals("GET")) { // if the request does not use the GET method
                    code = new MethodNotAllowedCode(); // it must be an unknown method
                } else { // if the request uses the GET method
                    try {
                        String filePath = RequestHeaderParser.getGETFilePath(port, line); // get the file path requested
                        if (RequestHeaderParser.fileExists(workingDirectory + filePath)) { // if the file exists
                            switch (RequestHeaderParser.getFileExtension(filePath)) { // depending on the extension
                                case (".txt"): // if it is a text file
                                    headers.add("Content-type: text/plain; charset=UTF-8"); // add a header to indicate this
                                    try {
                                        body = RequestHeaderParser.getFileContents(workingDirectory, filePath); // fetch the file contents, that will make up the body
                                        code = new OKCode(); // the request was serviced correctly, so create a status code that reflects this
                                    } catch (Exception e) {
                                        code = new InternalServerErrorCode(); // if something goes wrong, indicate this using an InternalServerErrorCode
                                    }
                                    break;
                                case (".html"): // if it is a web page
                                    headers.add("Content-type: text/html; charset=UTF-8"); // add a header to indicate this
                                    try {
                                        body = RequestHeaderParser.getFileContents(workingDirectory, filePath); // fetch the file contents, that will make up the body
                                        code = new OKCode(); // the request was serviced correctly, so create a status code that reflects this
                                    } catch (Exception e) {
                                        code = new InternalServerErrorCode(); // if something goes wrong, indicate this using an InternalServerErrorCode
                                    }
                                    break;
                                case (".css"): // if it is a stylesheet
                                    headers.add("Content-type: text/css; charset=UTF-8"); // add a header to indicate this
                                    try {
                                        body = RequestHeaderParser.getFileContents(workingDirectory, filePath); // fetch the file contents, that will make up the body
                                        code = new OKCode(); // the request was serviced correctly, so create a status code that reflects this
                                    } catch (Exception e) {
                                        code = new InternalServerErrorCode(); // if something goes wrong, indicate this using an InternalServerErrorCode
                                    }
                                    break;
                                case (".js"): // if it is a script
                                    headers.add("Content-type: application/javascript; charset=UTF-8"); // add a header to indicate this
                                    try {
                                        body = RequestHeaderParser.getFileContents(workingDirectory, filePath); // fetch the file contents, that will make up the body
                                        code = new OKCode(); // the request was serviced correctly, so create a status code that reflects this
                                    } catch (Exception e) {
                                        code = new InternalServerErrorCode(); // if something goes wrong, indicate this using an InternalServerErrorCode
                                    }
                                    break;
                                case (""): // if it is a directory
                                    if (filePath.charAt(filePath.length() - 1) != '/') { // if the file path does not end with a '/'
                                        filePath += '/'; // append the file path with a '/'
                                    }
                                    if (RequestHeaderParser.indexExists(workingDirectory, filePath)) {
                                        headers.add("Location: " + filePath + "index.html");
                                        code = new SeeOtherCode();
                                    } else {
                                        body = RequestHeaderParser.getDirectoryContents(port, workingDirectory, filePath); // construct the body
                                        headers.add("Content-type: text/html; charset=UTF-8"); // add a header to indicate this
                                        code = new OKCode(); // the request was serviced correctly, so create a status code that reflects this
                                    }
                                    break;
                                default:
                                    code = new UnsupportedMediaTypeCode(); // if the file type was a directory on another unsupported file type, set the status code to indicate this
                            }
                        } else {
                            code = new NotFoundCode(); // if the file does not exist
                        }
                    } catch (MalformedRequestException malformedRequest) {
                        code = new InternalServerErrorCode(); // if the request could not be processed for some reason, set the status code to indicate this
                    }
                }
            }

            if (code != null) { // if the code was previously-initialized
                response = new ResponseHeader(code); // create the ResponseHeader with the previously-created status code
                for(String header : headers) { // for each additional header created above
                    response.addHeader(header); // add it to the ResponseHeader
                }
                response.setBody(body); // set the body to whatever resulted from the parsing
                return response;
            }
        } catch(IOException exception) {
            return new ResponseHeader(new InternalServerErrorCode()); // if there was an error reading from a file, set the status code to indicate that there was a failure somewhere
        }
        
        return new ResponseHeader(new InternalServerErrorCode()); // if all else fails, set the status code to indicate that there was a failure somewhere
    }

    /**
     * Check whether the file at the given path exists
     * @param filePath The path to the file to be checked
     * @return A boolean indicating whether the file exists (true) or not (false)
     */
    private static boolean fileExists(String filePath) {
        File file = new File(filePath); // create an image of the file with the given path
        return file.exists(); // return true if it exists, false otherwise
    }
    
    /**
     * Get the extension from the give file path
     * @param filePath The file path to parse
     * @return The extension extracted from the file path
     */
    private static String getFileExtension(String filePath) {
        if (filePath.lastIndexOf(".") > -1) {
            return filePath.substring(filePath.lastIndexOf(".")); // fetch the extension - the contents of the string following (and including) the last period        
        } else {
            return "";
        }
    }

    /**
     * Extract the required file path from the given GET line
     * @param port The port of the Server, part of the IP address
     * @param line The GET line to be parsed
     * @return The file path of the file to be loaded
     * @throws MalformedRequestException A MalformedRequestException is thrown if the line could not be parsed
     */
    private static String getGETFilePath(int port, String line) throws MalformedRequestException {
        if (line != null) {
            line = line.replace("%20", " ");
            int index = line.indexOf(" ");
            if (index > -1) {
                return line.substring(line.indexOf(" ") + 1, line.indexOf("HTTP/1.1") - 1); // the path is included between the GET method string and the HTTP/1.1 string
            } else {
                throw new MalformedRequestException("Could not parse request"); // if there was an error, indicate that the request was malformed
            }
        } else {
            throw new MalformedRequestException("Could not parse request"); // if there was an error, indicate that the request was malformed
        }
    }

    /**
     * Get the contents of the file indicated by the given filePath, building from the given working directory
     * @param workingDirectory the directory from where searching starts
     * @param filePath the path leading to the file
     * @return A string containing the contents of the file
     */
    private static String getFileContents(String workingDirectory, String filePath) {
        String line;
        String contents = ""; // the String representing the contents of the file
        try (BufferedReader reader = new BufferedReader(new FileReader(workingDirectory + filePath))) { // try to open the file for reading
            while((line = reader.readLine()) != null) { // while there is still something to read
                contents += line + "\n"; // append the line, and a newline character, to the contents read from the file
            }
        } catch(FileNotFoundException ex) {
            System.out.println("Unable to open file");
        } catch(IOException ex) {
            System.out.println("Error reading file");
        }
        return contents;
    }

    /**
     * Get the contents of the given directory
     * @param workingDirectory The working directory of the Server
     * @param filePath The file path relative to the working directory of the Server
     * @return The body of the ResponseHeader, containing a list of files and directories 
     */
    private static String getDirectoryContents(int port, String workingDirectory, String filePath) {
        File currentDirectory = new File(workingDirectory + filePath); // get the directory
        File[] contents = currentDirectory.listFiles(); // get the list of files in the directory
        if (filePath.charAt(0) != '/') { // if the file path does not start with a '/'
            filePath = '/' + filePath; // prepend the file path with a '/'
        }
        if (filePath.charAt(filePath.length() - 1) != '/') { // if the file path does not end with a '/'
            filePath += '/'; // append the file path with a '/'
        }
        
        String body = "<html>\n\t<head></head>\n\t<body>\n\t\t<h1>" + currentDirectory.getName() + "</h1>\n\t\t<hr/>\n"; // initialize the body
        for (File file : contents) { // for each file in the directory
            if (file.isFile() || file.isDirectory()) { // if it is a file or a directory
                body += "\t\t<a href = '" + filePath + file.getName() + "'>" + file.getName() + "</a><br/>\n"; // create a URL to it
            }
        }
        body += "\t</body>\n</html>"; // conclude the body
            
        return body;
    }
    
    /**
     * Check the given directory for any index pages
     * @param workingDirectory The working directory of the Serve
     * @param filePath The path of the directory relative to the working directory of the Server
     * @return A boolean indicating whether an index file exists in the current directory (true) or not (false)
     */
    private static boolean indexExists(String workingDirectory, String filePath) {
        if (filePath.charAt(filePath.length() - 1) != '/') { // if the file path does not end with a '/'
            filePath += '/'; // append the file path with a '/'
        }
        File index = new File(workingDirectory + filePath + "index.html"); // the supposed file name
        return index.isFile();
    }

}

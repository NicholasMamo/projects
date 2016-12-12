package server.headers;

import java.util.*;

import server.statuscodes.*;

/**
 *
 * @author memonick
 * @date Dec 1, 2015
 */
public class ResponseHeader {
    
    private StatusCode code;
    private String body = "";
    private ArrayList<String> additionalHeaders = new ArrayList<>();
    
    /**
     * Initialize the ResponseHeader with the given code
     * @param code The StatusCode of the ResponseHeader
     */
    public ResponseHeader(StatusCode code) {
        this.code = code;
    }
    
    /**
     * Set the body of the ResponseHeader
     * @param body The body of the ResponseHeader
     */
    public void setBody(String body) {
        this.body = body;
    }
    
    /**
     * Get the body of the ResponseHeader
     * @return The body of the ResponseHeader
     */
    public String getBody() {
        return this.body;
    }
    
    /**
     * Add a header line to the list of additional headers
     * @param header The header to be added to the list of additional headers
     */
    public void addHeader(String header) {
        this.additionalHeaders.add(header);
    }
    
    /**
     * Get the list of header lines in the ResponseHeader
     * @return The list of header lines in the ResponseHeader
     */
    public ArrayList<String> getHeaders() {
        return this.additionalHeaders;
    }
    
    /**
     * Return the formatted ResponseHeader
     * @return The formatted ResponseHeader
     */
    @Override
    public String toString() {
        String s = "HTTP/1.1 " + this.code + "\r\n";
        for (String line : this.additionalHeaders) {
            s += line + "\r\n";
        }
        s += "Date: " + new Date() + "\r\n";
        s += "Server: WWW-NM";
        s += "\r\n\r\n";
        s += this.body;
        return s;
    }
    
}

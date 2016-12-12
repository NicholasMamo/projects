package server.statuscodes;

/**
 *
 * @author memonick
 * @date Dec 1, 2015
 */
public abstract class StatusCode {
    
    String code;
    String description;
    
    /**
     * Initialize the StatusCode with the given code and description
     * @param code The code of the StatusCode
     * @param description The description of the StatusCode
     */
    public StatusCode(String code, String description) {
        this.code = code;
        this.description = description;
    }
    
    /**
     * Set the code of the StatusCode to the one given
     * @param code The new code of the StatusCode
     */
    public void setCode(String code) {
        this.code = code;
    }
    
    /**
     * Get the code of the StatusCode
     * @return The code of the StatusCode
     */
    public String getCode() {
        return this.code;
    }
    
    /**
     * Set the description of the StatusCode to the one given
     * @param description The new description of the StatusCode
     */
    public void setDescription(String description) {
        this.description = description;
    }
    
    /**
     * Get the description of the StatusCode
     * @return The description of the StatusCode
     */
    public String getDescription() {
        return this.description;
    }
    
    /**
     * Return the code of the StatusCode
     * @return The code of the StatusCode
     */
    @Override
    public String toString() {
        return this.code;
    }

}

package skiplist;

/**
 *
 * @author memonick
 * @date Mar 29, 2016
 */
public class Element {
    
    /**
     * The Element in the layer below this Element
     */
    private Element down;
    
    /**
     * The Element in the layer above this Element
     */
    private Element up;
    
    /**
     * The next Element in the current layer
     */
    private Element next;
    
    /**
     * A boolean indicating whether this Element is also in the layer below (true), or not (false) 
     */
    private boolean hasDown = false;
    
    /**
     * A boolean indicating whether this Element is also in the layer below (true), or not (false) 
     */
    private boolean hasUp = false;
    
     /**
     * A boolean indicating whether this Element has a neighbor in the same layer (true), or not (false) 
     */
    private boolean hasNext = false;
    
    /**
     * The value represented by this Element
     */
    private int value;
    
    /**
     * The width (or distance) from the next Element
     */
    private int width = 0;
    
    /**
     * Initialize the Element with the given value
     * @param value the value of the Element
     */
    public Element(int value) {
        this.value = value;
    }
    
    /**
     * Set the Element that lies beneath this Element in the layer below
     * @param element the new Element neighbor that lies beneath this Element in the layer below
     */
    public void setDown(Element element) {
        this.down = element;
        this.hasDown = true;
    }
    
    /**
     * Get the Element that lies beneath this Element in the layer below
     * @return the new Element neighbor that lies beneath this Element in the layer below
     */
    public Element getDown() {
        return this.down;
    }
    
    /**
     * Set the Element that lies above this Element in the layer above
     * @param element the new Element neighbor that lies above this Element in the layer above
     */
    public void setUp(Element element) {
        this.up = element;
        this.hasUp = true;
    }
    
    /**
     * Get the Element that lies above this Element in the layer above
     * @return the new Element neighbor that lies above this Element in the layer above
     */
    public Element getUp() {
        return this.up;
    }
    
    /**
     * Create the Element that lies above this Element, which should have the same value
     * @return the new Element that lies above this Element
     */
    public Element createUp() {
        Element above = new Element(this.value);
        above.setDown(this);
        this.setUp(above);
        return above;
    }
    
    /**
     * Remove the Element above this Element
     */
    public void removeUp() {
        this.up = null;
        this.hasUp = false;
    }
    
    /**
     * Set the Element that lies next to this Element in the same layer
     * @param element the new Element that lies next to this Element in the same layer
     */
    public void setNext(Element element) {
        this.hasNext = true;
        this.next = element;
        this.calculateWidth(element);
    }
    
    /**
     * Get the next Element that lies in the same layer
     * @return Get the next Element that lies in the same layer
     */
    public Element getNext() {
        return this.next;
    }
    
    /**
     * Remove the next Element of this Element
     */
    public void removeNext() {
        this.next = null;
        this.hasNext = false;
    }
    
    /**
     * Set the value of the Element
     * @param value the new value of the Element
     */
    public void setValue(int value) {
        this.value = value;
    }
    
    /**
     * Get the value of the Element
     * @return the value of the Element
     */
    public int getValue() {
        return this.value;
    }
    
    /**
     * Set the width of the Element
     * @param width the new width of the Element
     */
    public void setWidth(int width) {
        this.width = width;
    }
    
    /**
     * Decrement the width of the Element
     */
    public void decrementWidth() {
        this.width--;
    }
    
    /**
     * Increment the width of the Element
     */
    public void incrementWidth() {
        this.width++;
    }
    
    /**
     * Get the width of the Element
     * @return the width of the Element
     */
    public int getWidth() {
        return this.width;
    }
    
    /**
     * Check whether this Element has a neighbor in the layer above
     * @return a boolean indicating whether this Element has a neighbor in the layer above (true), or not (false)
     */
    public boolean hasUp() {
        return this.hasUp;
    }
    
    /**
     * Check whether this Element has a neighbor in the layer below
     * @return a boolean indicating whether this Element has a neighbor in the layer below (true), or not (false)
     */
    public boolean hasDown() {
        return this.hasDown;
    }
    
    /**
     * Check whether this Element has a neighbor in the same layer
     * @return a boolean indicating whether this Element has a neighbor in the same layer (true), or not (false)
     */
    public boolean hasNext() {
        return this.hasNext;
    }
    
    /**
     * Calculate the width (using indices) from the current Element to the one provided
     * @param element the Element from which width (using indices) will be calculated
     */
    private void calculateWidth(Element element) {
        if (this.hasDown()) {
            int newWidth = 0; // the new width from this Element to the one given
            Element visitor = this.getDown(); // calculating the width has to start from at least one level down
            do {
                if (visitor.hasNext()) { // if there is a next Element
                    // if the next value goes beyond the new Element, and there is a layer beneath
                    if (visitor.getNext().getValue() > element.getValue() && visitor.hasDown()) {
                        visitor = visitor.getDown(); // go down, but don't move
                    } else if (visitor.getNext().getValue() < element.getValue()) { // if the next vale does not go beyond the new Element, and is not the element
                        newWidth += visitor.getWidth(); // increment the width by the width of the next step
                        visitor = visitor.getNext(); // move one step
                    }
                } else if (visitor.hasDown()) { // if there is no neighbor, but there is a layer below
                    visitor = visitor.getDown(); // move down one layer
                }
            } while (visitor.hasNext() && !visitor.getNext().equals(element));
             // stop when there are no more nodes to visit, or the Element has been found
            
            if (visitor.hasNext() && visitor.getNext().equals(element)) { // if there is a next Element, and it is the Element that is being sought
                newWidth += visitor.getWidth(); // increment the width by the width of the final step
            }
            
            this.setWidth(newWidth);
        } else {
            this.setWidth(1); // base case
        }
    }
    
    /**
     * Check whether the provided Object is the same as this one
     * @param other the Element to use for comparison
     * @return a boolean indicating whether the provided Object is the same as this one (true), or not (false)
     */
    @Override
    public boolean equals(Object other) {
        if (other instanceof Element) {
            return ((Element)other).getValue() == this.getValue();
        } else {
            return false;
        }
    }
    
    /**
     * Get the textual representation of the Element
     * @return the textual representation of the Element
     */
    @Override
    public String toString() {
        return this.getValue() + " (" + this.getWidth() + ")";
    }
    
}

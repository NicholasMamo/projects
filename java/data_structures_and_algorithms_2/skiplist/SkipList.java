package skiplist;

import java.util.Random;

/**
 *
 * @author memonick
 * @date Mar 29, 2016
 */
public class SkipList {
    
    /**
     * The upper, leftmost Element of the SkipList
     */
    Element first;
    
    /**
     * Initialize the SkipList
     */
    public SkipList() {
        this.first = new Element(Integer.MIN_VALUE);
    }
    
    /**
     * Insert a new Element into the SkipList
     * @param value the new value to insert into the SkipList
     */
    public void insert(int value) {
        if (this.getIndex(value) == -1) { // if the Element does not already exist
            Element start = this.first;
            Element leftmost = start;
            while ((start.hasNext() && start.getNext().getValue() < value) || start.hasDown()) {
                if ((start.hasNext() && start.getNext().getValue() < value)) {
                    start = start.getNext();
                } else {
                    start = start.getDown();
                    leftmost = leftmost.getDown();
                }
            }
            Element newElement = new Element(value);
            this.insert(newElement, leftmost, start); // insert the Element
        }
    }
    
    /**
     * Insert the new Element into the layer that starts from the given Element
     * @param newElement the new Element to insert
     * @param start the Element from which the new layer starts
     * @param previous the Element preceding the new Element
     */
    public void insert(Element newElement, Element start, Element previous) {
        int value = newElement.getValue();
        Element leftmost = start;
        
        /*
         * insert the element
         */
       
        /*
         * if the start value is larger than the new value, insert it there
         * this should never happen, as the start value is always set to be the smallest minimum integer
         */
        if (start.getValue() > value) {
            start.setNext(newElement);
        } else {
            // the new Element will be inserted between start (the Element where the algorithm is at) and the Element after it
            if (previous.hasNext()) {
                newElement.setNext(previous.getNext());
            }
            previous.setNext(newElement);
        }
        
        /*
         * randomly go up one level
         */
        Random random = new Random();
        double r = random.nextDouble();
        if (r < 0.5) { // with 50% chance
            Element aboveElement = newElement.createUp(); // create an Element above the current one
            
            Element newStart; // the start Element of the layer above the current one
            if (leftmost.hasUp()) { // if there is already a layer above the current one
                newStart = leftmost.getUp(); // start from its first Element
            } else { // if there are no layers above
                newStart = leftmost.createUp(); // create a layer above the the current one
                this.first = newStart; // start from this new Element, the start of the new layer
            }
            
            /**
             * Find where to insert the new element in the layer above
             */
            Element newPrevious = newStart;
            while (newPrevious.hasNext() && newPrevious.getNext().getValue() < aboveElement.getValue()) {
                newPrevious = newPrevious.getNext();
            }
            
            insert(aboveElement, newStart, newPrevious); // insert the new Element into the layer just created
        } else {
            /*
             * if the same Element was inserted in the layer above, there is no need to fix indices
             * as they are taken care of by the new Element
             */
            if (leftmost.hasUp()) { // if there is a layer above
                this.incrementIndices(leftmost.getUp(), value); // fix the indices above
            }
        }
        
    }
    
    /**
     * Delete an Element from the SkipList by value
     * @param value the value of the Element to delete
     * @return a boolean indicating whether the Element was deleted (true), or not (false)
     */
    public boolean deleteByValue(int value) {
        if (this.getIndex(value) != -1) { // if the Element does exist
            Element leftmost = this.first;
            Element start = leftmost;
            while ((start.hasNext() && start.getNext().getValue() < value) || start.hasDown()) {
                if ((start.hasNext() && start.getNext().getValue() < value)) {
                    start = start.getNext();
                } else {
                    start = start.getDown();
                    leftmost = leftmost.getDown();
                }
            }
            boolean result = deleteByValueFrom(leftmost, start, value);
            this.refactor();
            return result;
        } else {
            return false;
        }
    }
    
    /**
     * Delete an Element from the SkipList by value, starting from the given Element
     * @param start the first Element in the layer
     * @param previous the Element preceding the new Element
     * @param value the value of the Element to delete
     * @return a boolean indicating whether the Element was deleted (true), or not (false)
     */
    public boolean deleteByValueFrom(Element start, Element previous, int value) {       
        /*
         * if the start value is larger than the new value, then the element does not exist
         * this should never happen as the leftmost value is always the smallest possible value
         */
        
        // if the Element to delete has been found
        if (previous.hasNext() && previous.getNext().getValue() == value) {
            Element toDelete = previous.getNext();
            previous.decrementWidth();
            if (toDelete.hasNext()) {
                previous.setNext(toDelete.getNext());
            } else {
                previous.removeNext();
                previous.setWidth(0);
            }
            
            if (toDelete.hasUp()) {
                Element newPrevious = start.getUp();
                while (newPrevious.hasNext() && newPrevious.getNext().getValue() < value) {
                    newPrevious = newPrevious.getNext();
                }
                return deleteByValueFrom(start.getUp(), newPrevious, value);
            } else {
                if (start.hasUp()) {
                    this.decrementIndices(start.getUp(), value);
                }
                return true;
            }
        } else {
            return false; // if the Element was not found
        }
    }
    
    /**
     * Delete an Element from the SkipList by index
     * @param index the value of the Element to delete
     * @return a boolean indicating whether the Element was deleted (true), or not (false)
     */
    public boolean deleteByIndex(int index) {
        Element leftmost = this.getBottomLeft();
        boolean result = deleteByIndexFrom(leftmost, index);
        this.refactor();
        return result;
    }
    
    /**
     * Delete an Element from the SkipList by index, starting from the given Element
     * @param start the Element from which to start looking
     * @param index the index of the Element to delete
     * @return a boolean indicating whether the Element was deleted (true), or not (false)
     */
    public boolean deleteByIndexFrom(Element start, int index) {
        Element iterator = start;
        int currentIndex = 0;
       
        /*
         * if the start value is larger than the new value, then the element does not exist
         * this should never happen as the leftmost value is always the smallest possible value
         */
        
        // go through every Element until the next one is what should be deleted
        while (iterator.hasNext() && iterator.getWidth() + currentIndex < index) {
            currentIndex += iterator.getWidth();
            iterator = iterator.getNext();
        }
        
        // if the Element to delete has been found
        if (iterator.hasNext() && iterator.getWidth() + currentIndex == index) {
            Element previous = iterator;
            Element toDelete = iterator.getNext();
            int value = toDelete.getValue();
            previous.decrementWidth();
            if (toDelete.hasNext()) {
                previous.setNext(toDelete.getNext());
            } else {
                previous.removeNext();
                previous.setWidth(0);
            }
            
            if (toDelete.hasUp()) {
                return deleteByIndexFrom(start.getUp(), index);
            } else {
                if (start.hasUp()) {
                    this.decrementIndices(start.getUp(), value);
                }
                return true;
            }
        } else {
            return false; // if the Element was not found
        }
    }
    
    /**
     * Get the value of the Element at the given index
     * @param index the index wherein lies the Element
     * @return the value of the Element at the given index
     */
    public int getByIndex(int index) {
        Element visitor = this.first;
        int currentIndex = 0;
        boolean move;
        
        do {
            move = false;
            if (visitor.hasNext() && visitor.getWidth() + currentIndex == index) {
                return visitor.getNext().getValue();
            } else if (visitor.hasNext() && visitor.getWidth() + currentIndex < index) {
                currentIndex += visitor.getWidth();
                visitor = visitor.getNext();
                move = true;
            } else if (visitor.hasDown()) {
                // if the visitor does not have a neighbor, or it exceeds the required index, but there's a layer beneath
                visitor = visitor.getDown();
                move = true;
            }
        } while (move);
        
        return -1;
    }
    
    /**
     * Count the number of Element instances in the SkipList
     * @return the number of Element instances in the SkipList
     */
    public int size() {
        Element visitor = this.first;
        int count = 0;
        boolean move;
        
        do {
            move = false;
            if (visitor.hasNext()) {
                count += visitor.getWidth();
                visitor = visitor.getNext();
                move = true;
            } else if (visitor.hasDown()) {
                // if the visitor does not have a neighbor, but there's a layer beneath
                visitor = visitor.getDown();
                move = true;
            }
        } while (move);
        
        return count;
    }
    
    /**
     * Get the number of steps required to reach the given value, including down steps
     * @param value the value to be reached
     * @return the number of steps required to reach the given value, including down steps
     */
    public int findSteps(int value) {
        Element visitor = first; // the starting Element
        int steps = 0; // the number of steps required
        
        if (visitor.getValue() == value) { // if the Element is at the top
            return steps; // stop here and return 0
        }
        
        do {
            // if the current Element has a neighbor and its value is less than the desired value
            if (visitor.hasNext() && visitor.getNext().getValue() <= value) {
                steps++;
                visitor = visitor.getNext(); // move one step
            } else if (visitor.hasDown()) { // if the current Element is in a lower layer
                steps++;
                visitor = visitor.getDown(); // move one layer down
            } else { // if all else failed
                return -1; // the Element does not exist
            }
        } while (visitor.getValue() != value); // keep doing this until the value is found
        return steps;
    }
    
    /**
     * Print the height of the SkipList
     */
    public void printHeight() {
        System.out.println("Height: " + getHeight());
    }
    
    /**
     * Get the height of the SkipList
     * @return the height of the SkipList
     */
    public int getHeight() {
        Element visitor = first;
        int count = 0;
        while(visitor.hasDown()) {
            count++;
            visitor = visitor.getDown();
        }
        return count;
    }
    
    /**
     * Empty the SkipList
     */
    public void empty() {
        int size = this.size();
        for (int i = 0; i < size; i++) {
            this.deleteByIndex(1);
        }
        refactor();
    }
    
    /**
     * Fix the indices/widths of the above layers by decrementing the indices
     * @param start the start Element of the layer
     * @param value the value that has just been inserted
     */
    public void decrementIndices(Element start, int value) {
        Element leftmost = start;
        // stop when there are no further Element instances, or the next Element goes beyond the value
        while (start.hasNext() && start.getNext().getValue() < value) {
            start = start.getNext();
        }
        
        if (start.hasNext()) { // if there is an Element after the one that the algorithm at
            /*
             * increment its width, as it means that the Element that was inserted is between
             * this Element and another one with a larger value
             */
            start.decrementWidth();
        }
        
        if (leftmost.hasUp()) { // if there is a higher level
            decrementIndices(leftmost.getUp(), value); // fix its indices
        }
    }
    
    /**
     * Fix the indices/widths of the above layers by incrementing the indices
     * @param start the start Element of the layer
     * @param value the value that has just been inserted
     */
    public void incrementIndices(Element start, int value) {
        Element leftmost = start;
        // stop when there are no further Element instances, or the next Element goes beyond the value
        while (start.hasNext() && start.getNext().getValue() < value) {
            start = start.getNext();
        }
        
        if (start.hasNext()) { // if there is an Element after the one that the algorithm at
            /*
             * increment its width, as it means that the Element that was inserted is between
             * this Element and another one with a larger value
             */
            start.incrementWidth();
        }
        
        if (leftmost.hasUp()) { // if there is a higher level
            incrementIndices(leftmost.getUp(), value); // fix its indices
        }
    }
    
    /**
     * Find the element with the given value and return its index
     * @param value the value to look for
     * @return the index of the given value
     */
    public int getIndex(int value) {
        int index = 0; // the index of the Element with the given value
        Element visitor = first; // the starting Element
        
        if (visitor.getValue() == value) { // if the Element is at the top
            return index; // stop here and return 0
        }
        
        do {
            // if the current Element has a neighbor and its value is less than the desired value
            if (visitor.hasNext() && visitor.getNext().getValue() <= value) {
                index += visitor.getWidth();
                visitor = visitor.getNext(); // move one step
            } else if (visitor.hasDown()) { // if the current Element is in a lower layer
                visitor = visitor.getDown(); // move one layer down
            } else { // if all else failed
                return -1; // the Element does not exist
            }
        } while (visitor.getValue() != value); // keep doing this until the value is found
        return index;
    }
    
    /**
     * Get the bottom, leftmost Element in the SkiPlist
     * @return the bottom, leftmost Element in the SkiPlist
     */
    private Element getBottomLeft() {
        Element visitor = first;
        while (visitor.hasDown()) {
            visitor = visitor.getDown();
        }
        return visitor;
    }
    
    /**
     * Fix the SkipList by resetting the first Element
     */
    private void refactor() {
        Element visitor = first;
        // repeat until there are neighbors or there is nothing below
        while (!visitor.hasNext() && visitor.hasDown()) {
            Element below = visitor.getDown();
            below.removeUp();
            visitor = below;
        }
        first = visitor;
    }
    
    /**
     * Get the tabular representation of the given number
     * @param n the number of tabs in the string
     * @return the string of tabs
     */
    public String tabsToString(int n) {
        String s = "";
        for (int i = 0; i < n; i++) {
            s += "\t";
        }
        return s;
    }
    
    /**
     * Get the textual representation of the SkipList
     * @return the textual representation of the SkipList
     */
    @Override
    public String toString() {
        String s = "";
        Element firstInLayer = first;
        Element iterator = firstInLayer;
        int rounds = 0;
        
        do {
            s += iterator;
            // print the layer
            while (iterator.hasNext()) {
                iterator = iterator.getNext();
                s += "\t" + iterator;
            }
            s += "\n";
            if (firstInLayer.hasDown()) {
                firstInLayer = firstInLayer.getDown();
                iterator = firstInLayer;
            }
            rounds ++;
        } while (firstInLayer.hasDown());
        
        if (rounds > 0 && firstInLayer.hasUp()) {
            s += iterator;
            // print the layer
            while (iterator.hasNext()) {
                iterator = iterator.getNext();
                s += "\t" + iterator;
            }
        }
        
        return s;
    }
    
}

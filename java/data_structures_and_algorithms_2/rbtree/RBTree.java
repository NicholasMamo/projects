package rbtree;

import static rbtree.NodeType.BLACK;

/**
 * The class representing the root of the RBTree Tree
 * @author memonick
 * @date Mar 30, 2016
 */
public class RBTree {

    /**
     * The root of the Node
     */
    Node root;
    
    /**
     * Initialize the RB tree
     */
    public RBTree() {
        root = new Node(this);
    }
    
    /**
     * Empty the RBTree tree of any nodes
     */
    public void empty() {
        root = new Node(this);
    }
    
    /**
     * Insert the given value into the RBTree tree
     * @param value the value to insert into the RBTree tree
     */
    public void insert(int value) {
        if (!this.root.hasChild(value)) {
            root.insert(value);
        }
    }
    
    /**
     * Delete the given value from the RBTree tree
     * @param value the value to delete from the RBTree tree
     * @return a boolean indicating whether the value was found and deleted (true), or not (false)
     */
    public boolean delete(int value) {
        if (this.root.hasChild(value)) {
            if (this.count() < 2) {
                this.empty();
                return true;
            } else {
                boolean ret = this.root.delete(this.root, value);
                this.root.setType(BLACK);
                return ret;
            }
        } else {
            return false;
        }
    }
    
    /**
     * Check whether RBTree has the given value
     * @param value the value to look for in the RBTree
     * @return a boolean indicating whether the RBTree has the given value (true), or not (false)
     */
    public boolean hasChild(int value) {
        return this.root.hasChild(value);
    }
    
    /**
     * Get the number of nodes in this RBTree tree
     * @return the number of nodes in this RBTree tree
     */
    public int count() {
        return this.root.count();
    }
    
    /**
     * Print the height of this RBTree tree
     */
    public void printHeight() {
        System.out.println("Height: " + this.root.height());
    }
    
    /**
     * Get the height of this RBTree tree
     * @return the height of this RBTree tree
     */
    public int height() {
        return this.root.height() - 1;
    }
    
    /**
     * Set the root of this RBTree tree
     * @param root the new root of this RBTree tree
     */
    public void setRoot(Node root) {
        root.setType(BLACK);
        this.root = root;
    }
    
    /**
     * Print the pre-order transversal of this RBTree tree
     */
    public void printPreOrder() {
        System.out.println(this.root.preOrderToString());
    }
    
    /**
     * Get the textual representation of this RBTree Tree
     * @return the textual representation of this RBTree Tree
     */
    @Override
    public String toString() {
        return root.toString();
    }
    
}

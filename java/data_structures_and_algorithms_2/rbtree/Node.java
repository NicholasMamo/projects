package rbtree;

import static rbtree.NodeType.*;

/**
 * The class representing the Node
 * @author memonick
 * @date Mar 30, 2016
 */
public class Node {
    
    /**
     * The tree that this node belongs to
     */
    private RBTree tree;

    /**
     * The type of this Node
     */
    private NodeType type = NIL;
    
    /**
     * The value of this Node
     */
    private int value = -1;
    
    /**
     * The level of this Node, with level 0 being the root node
     */
    private int level = 0;
    
    /**
     * The parent of this Node
     */
    private Node parent;
    
    /**
     * The left child of this Node
     */
    private Node leftChild;
    
    /**
     * The right child of this Node
     */
    private Node rightChild;
    
    /**
     * Empty constructor, do not initialize the children
     * The NodeType will automatically be NIL, indicating that it has no children
     * @param tree the tree that this node belongs to
     */
    public Node(RBTree tree) {
        this.tree = tree;
    }
    
    /**
     * Initialize the RBTree with the given value
     * @param tree the tree that this node belongs to
     * @param value the value of the RBTree
     */
    public Node(RBTree tree, int value) {
        this.tree = tree;
        insert(value);
    }
    
    /**
     * Insert the given value into this Node
     * @param value the value to insert into this Node
     */
    public void insert(int value) {
        if (this.type == NIL) { // if this Node is empty
            this.value = value; // insert the value here
            this.leftChild = new Node(this.tree);
            this.rightChild = new Node(this.tree);
            this.leftChild.setParent(this);
            this.rightChild.setParent(this);
            if (this.level == 0) {
                this.type = BLACK; // the root must always be black
            } else {
                this.type = RED; // else always insert red
            }
        } else {
            if (this.leftChild.getType() == RED && this.rightChild.getType() == RED) {
                this.leftChild.setType(BLACK);
                this.rightChild.setType(BLACK);
                if (this.level == 0) {
                    this.type = BLACK; // the root must always be black
                } else {
                    this.type = RED;
                }
            }
            
            if (value < this.value) { // compare the new value to the value of this Node
                this.leftChild.insert(value); // if it's less, then it should go in the left child
            } else {
                this.rightChild.insert(value); // if it's more, then it should go in the right child
            }
            
            // if this node is red and one of its two children are red
            if (this.getType() == RED && (this.getLeftChild().getType() == RED || this.getRightChild().getType() == RED)) {
                this.parent.rotate(); // a rotation is necessary as there can be no consecutive red nodes
            }
        }
    }
    
    /**
     * Delete the given value from the RBTree tree
     * @param x the Node being searched
     * @param value the value to delete from the RBTree tree
     * @return a boolean indicating whether the value was found and deleted (true), or not (false)
     */
    public boolean delete(Node x, int value) {
        if (x.getValue() == value) {
            return step3(x, value);
        } else {
            // step 1
            //x.type = RED;
            if ((x.getLeftChild().getType() == BLACK || x.getLeftChild().getType() == NIL)
                && (x.getRightChild().getType() == BLACK || x.getRightChild().getType() == NIL)) {
                // step 1a
                if (value < x.getValue()) {
                    x = x.leftChild;
                } else {
                    x = x.rightChild;
                }

                return this.step2(x, value);
            } else {
                //step 1b
                return this.step2b(x, value);
            }
        }
    }
    
    /**
     * Get the number of nodes in this Node
     * @return the number of nodes in this Node
     */
    public int count() {
        if (this.type == NIL) {
            return 0;
        } else {
            return 1 + this.leftChild.count() + this.rightChild.count();
        }
    }
    
    /**
     * Get the height of this Node
     * @return the height of this Node
     */
    public int height() {
        if (this.type == NIL) {
            return 0;
        } else {
            return 1 + Math.max(this.rightChild.height(), this.leftChild.height());
        }
    }
    
    private boolean step2(Node x, int value) {
        if (x.getType() != NIL && ((x.getLeftChild().getType() == BLACK || x.getLeftChild().getType() == NIL)
                && (x.getRightChild().getType() == BLACK || x.getRightChild().getType() == NIL))) {
            return this.step2a(x, value);
        } else {
            return this.step2b(x, value);
        }
    }
    
    private boolean step2a(Node x, int value) {
        Node p = x.getParent(); // the parent
        Node t; // the sibling
        Node l; // the sibling's left child
        Node r; // the sibling's right child
        boolean left;

        if (p.getLeftChild().equals(x)) {
            left = true;
            t = p.getRightChild();
        } else {
            left = false;
            t = p.getLeftChild();
        }

        l = t.getLeftChild();
        r = t.getRightChild();

        if (l.getType() != NIL && (l.getType() == BLACK || l.getType() == NIL)
                && (r.getType() == BLACK || r.getType() == NIL)) {
            // step 2a1
            x.flip();
            p.flip();
            t.flip();
            return x.delete(x, value);
        } else if ((l.getType() == RED && isInside(p, l)) || (r.getType() == RED && isInside(p, r))) {
            if (p.getLeftChild().equals(t)) {
                p.rotateLR();
            } else if (p.getRightChild().equals(t)) {
                p.rotateRL();
            }
            x.flip();
            p.flip();
            return x.delete(x, value);
        } else if ((l.getType() == RED && !isInside(p, l)) || (r.getType() == RED && !isInside(p, r))) {
            if (p.getLeftChild().equals(t)) {
                p.rotateLL();
            } else if (p.getRightChild().equals(t)) {
                p.rotateRR();
            }
            x.flip();
            p.flip();
            t.flip();
            r.flip();
            return x.delete(x, value);
        }
        return false;
    }
    
    private boolean step2b(Node x, int value) {
        if (value == x.getValue()) {
            return step3(x, value);
        } else if (x.getType() != NIL) {
            // look ahead for the next X
            if (value < x.getValue()) {
                x = x.getLeftChild();
            } else if (value > x.getValue()){
                x = x.getRightChild();
            }
            
            Node p = x.getParent(); // the parent
            Node t; // the sibling

            if (p.getLeftChild().equals(x)) {
                t = p.getRightChild();
            } else {
                t = p.getLeftChild();
            }

            if(x.getType() == RED) {
                return x.delete(x, value);
            } else if (x.getType() == BLACK) {
                p.getParent().rotate(p, t);
                p.flip();
                t.flip();
                return step2(x, value);
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    
    public boolean step3(Node x, int value) {
        Node p = x.getParent();
        boolean black = (x.getType() == BLACK);
        
        if (x.getLeftChild().getType() == NIL && x.getRightChild().getType() == NIL) {
            if (black) {
                return step2(x, value);
            } else {
                if (p.getLeftChild().equals(x)) {
                    p.removeLeftChild();
                } else if (p.getRightChild().equals(x)) {
                    p.removeRightChild();
                }
                return true;
            }
        } else {
            if (x.getLeftChild().getType() != NIL) {
                int newValue = x.getMaxFromLeft();
                x.setValue(newValue);
                return x.leftChild.delete(x.leftChild, newValue);
            //} else if (x.getRightChild().getType() != NIL) {
            } else { // the right child can't be NIL as well, or the first branch would have been entered
                int newValue = x.getMinFromRight();
                x.setValue(newValue);
                return x.rightChild.delete(x.rightChild, newValue);
            }
        }
    }
    
    private boolean isInside(Node parent, Node child) {
        return parent.getLeftChild().getRightChild().equals(child) || parent.getRightChild().getLeftChild().equals(child);
    }
    
    /**
     * Get the largest value in the left subtree
     * @return the largest value in the left subtree
     */
    private int getMaxFromLeft() {
        int max = -1;
        Node visitor = this.leftChild;
        while (visitor.getType() != NIL) {
            max = visitor.getValue();
            visitor = visitor.getRightChild();
        }
        return max;
    }
    
    /**
     * Get the smallest value in the right subtree
     * @return the smallest value in the right subtree
     */
    private int getMinFromRight() {
        int min = -1;
        Node visitor = this.rightChild;
        while (visitor.getType() != NIL) {
            min = visitor.getValue();
            visitor = visitor.getLeftChild();
        }
        return min;
    }
    
    /**
     * Change the NodeType of the Node
     */
    private void flip() {
        if (this.type == BLACK) {
            this.type = RED;
        } else if (this.type == RED) {
            this.type = BLACK;
        }
    }
    
    /**
     * Perform rotations, if necessary
     */
    private void rotate() {
        if (this.rightChild.getType() == RED && this.rightChild.getLeftChild().getType() == RED) { // RL
            this.rotateRL();
        } else if (this.rightChild.getType() == RED && this.rightChild.getRightChild().getType() == RED) { // RR
            this.rotateRR();
        } else if (this.leftChild.getType() == RED && this.leftChild.getRightChild().getType() == RED) { // LR
            this.rotateLR();
        } else if (this.leftChild.getType() == RED && this.leftChild.getLeftChild().getType() == RED) { // LL
            this.rotateLL();
        }
        
        if (this.level == 0) {
            this.type = BLACK; // the root must always be black
        }
    }
    
    /**
     * Perform the necessary rotation such that the child becomes the parent of the parent
     * @param parent the parent
     * @param child the child
     */
    private void rotate(Node parent, Node child) {
        NodeType parentType = parent.getType();
        NodeType childType = child.getType();
        if (this.getLeftChild().equals(parent)) {
            if (parent.getLeftChild().equals(child)) {
                parent.rotateLL();
            } else if (parent.getRightChild().equals(child)) {
                parent.rotateLR(); // was RR
            }
        } else if (this.getRightChild().equals(parent)) {
            if (parent.getLeftChild().equals(child)) {
                parent.rotateRL(); // was LL
            } else if (parent.getRightChild().equals(child)) {
                parent.rotateRR();
            }
        }
        parent.setType(parentType);
        child.setType(childType);
    }
    
    /**
     * Perform an RL rotation
     */
    private void rotateRL() {
        Node R = this.getRightChild();
        Node RL = R.getLeftChild();
        int newLevel = this.level;
        NodeType type = this.type;
        
        if (newLevel != 0) {
            if (this.getParent().getLeftChild().equals(this)) {
                this.parent.setLeftChild(RL);
            } else {
                this.parent.setRightChild(RL);
            }
        }
        
        this.setType(RL.getType());
        RL.setType(type);
        R.removeLeftChild();
        this.removeRightChild();
        this.setRightChild(RL.getLeftChild());
        RL.setLeftChild(this);
        R.setLeftChild(RL.getRightChild());
        RL.setRightChild(R);
        RL.setLevel(newLevel);
    }
    
    /**
     * Perform an LR rotation
     */
    private void rotateLR() {
        Node L = this.getLeftChild();
        Node LR = L.getRightChild();
        int newLevel = this.level;
        NodeType type = this.type;
        
        if (newLevel != 0) {
            if (this.getParent().getLeftChild().equals(this)) {
                this.parent.setLeftChild(LR);
            } else {
                this.parent.setRightChild(LR);
            }
        }
        
        this.setType(LR.getType());
        LR.setType(type);
        L.removeRightChild();
        this.removeLeftChild();
        this.setLeftChild(LR.getRightChild());
        LR.setRightChild(this);
        L.setRightChild(LR.getLeftChild());
        LR.setLeftChild(L);
        LR.setLevel(newLevel);
    }
    
    /**
     * Perform an RR rotation
     */
    private void rotateRR() {
        Node R = this.getRightChild();
        Node RL = R.getLeftChild();
        int newLevel = this.level;
        NodeType type = this.type;
        
        if (newLevel != 0) {
            if (this.getParent().getLeftChild().equals(this)) {
                this.parent.setLeftChild(R);
            } else {
                this.parent.setRightChild(R);
            }
        }
        
        this.type = R.getType();
        R.setType(type);
        this.setRightChild(RL);
        R.setLeftChild(this);
        R.setLevel(newLevel);
    }
    
    /**
     * Perform an LL rotation
     */
    private void rotateLL() {
        Node L = this.getLeftChild();
        Node LR = L.getRightChild();
        int newLevel = this.level;
        NodeType type = this.type;
        
        if (newLevel != 0) {
            if (this.getParent().getLeftChild().equals(this)) {
                this.parent.setLeftChild(L);
            } else {
                this.parent.setRightChild(L);
            }
        }
        
        this.type = L.getType();
        L.setType(type);
        this.setLeftChild(LR);
        L.setRightChild(this);
        L.setLevel(newLevel);
    }
    
    /**
     * Set the NodeType of this Node
     * @param type the new NodeType of this Node
     */
    public void setType(NodeType type) {
        this.type = type;
    }
    
    /**
     * Get the NodeType of this Node
     * @return the NodeType of this Node
     */
    public NodeType getType() {
        return this.type;
    }
    
    /**
     * Set the parent of this Node
     * @param parent the parent of this Node
     */
    public void setParent(Node parent) {
        this.parent = parent;
        this.setLevel(parent.getLevel() + 1);
    }
    
    /**
     * Get the parent of this Node
     * @return the parent of this Node
     */
    public Node getParent() {
        return this.parent;
    }
    
    /**
     * Set the value of this Node
     * @param value the new value of this Node
     */
    public void setValue(int value) {
        this.value = value;
    }
    
    /**
     * Get the value of this Node
     * @return the value of this Node
     */
    public int getValue() {
        return this.value;
    }
    
    /**
     * Set the level of this Node
     * @param level the new level of this Node
     */
    public void setLevel(int level) {
        this.level = level;
        if (this.type != NIL) {
            this.leftChild.setLevel(level + 1);
            this.rightChild.setLevel(level + 1);
        }
        if (level == 0) {
            this.tree.setRoot(this);
            this.type = BLACK;
        }
    }
    
    /**
     * Get the level of this Node
     * @return the level of this Node
     */
    public int getLevel() {
        return this.level;
    }
    
    /**
     * Set the left child of this Node
     * @param leftChild the new left child of this Node
     */
    public void setLeftChild(Node leftChild) {
        leftChild.setParent(this);
        this.leftChild = leftChild;
    }
    
    /**
     * Get the left child of this Node
     * @return the left child of this Node
     */
    public Node getLeftChild() {
        return this.leftChild;
    }
    
    /**
     * Remove the left child of this Node
     */
    public void removeLeftChild() {
        this.leftChild = new Node(this.tree);
        this.leftChild.setParent(this);
    }
    
    /**
     * Set the right child of this Node
     * @param rightChild the new right child of this Node
     */
    public void setRightChild(Node rightChild) {
        rightChild.setParent(this);
        this.rightChild = rightChild;
    }
    
    /**
     * Get the right child of this Node
     * @return the right child of this Node
     */
    public Node getRightChild() {
        return this.rightChild;
    }
    
    /**
     * Remove the right child of this Node
     */
    public void removeRightChild() {
        this.rightChild = new Node(this.tree);
        this.rightChild.setParent(this);
    }
    
    /**
     * Check whether the value given is a descendant of this Node
     * @param value the value of the Node being sought
     * @return a boolean indicating whether the Node with the given value is a child of this Node (true), or not (false)
     */
    public boolean hasChild(int value) {
        if (this.getType() != NIL) {
            if (this.getValue() == value) {
                return true;
            } else {
                if (value < this.getValue() && this.leftChild.getType() != NIL) {
                    return this.leftChild.hasChild(value);
                } else if (value > this.getValue() && this.rightChild.getType() != NIL) {
                    return this.rightChild.hasChild(value);
                } else {
                    return false;
                }
            }
        } else {
            return false;
        }
    }
    
    /**
     * Get the pre-order transversal of this Node
     * @return the pre-order transversal of this Node
     */
    public String preOrderToString() {
        String s = "";
        if (this.getType() != NIL) {
            if (this.leftChild.getType() != NIL) {
                s += this.leftChild.preOrderToString() + " ";
            }
            s += this.value + " ";
            if (this.rightChild.getType() != NIL) {
                s += this.rightChild.preOrderToString() + " ";
            }
        }
        return s;
    }
    
    /**
     * Check whether this Node is the same as the one provided
     * @param other the other Node being considered
     * @return a boolean indicating whether this Node is the same as the one provided (true), or not (false)
     */
    @Override
    public boolean equals(Object other) {
        if (other instanceof Node) {
            return ((Node) other).getValue() == this.value;
        } else {
            return false;
        }
    }
    
    /**
     * Get the textual representation of this Node
     * @return the textual representation of this Node
     */
    @Override
    public String toString() {
        String s = "";
        for (int i = 0; i < this.level; i++) {
            s += "\t";
        }
        
        if (this.type == NIL) {
            s += this.type + "\n";
        } else {
            s += this.type + " " + this.value + "\n";
            s += this.leftChild;
            s += this.rightChild;
        }
        
        return s;
    }

}

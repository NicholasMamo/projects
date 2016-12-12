package main;

import java.util.ArrayList;

/*
 * @author memonick (Nicholas Mamo)
 * Nyphoon Games
 */
public class Stack {

    private ArrayList<Integer> stack;
    
    public Stack() {
        stack = new ArrayList();
    }
    
    public void push(int i) {
        stack.add(i);
    }
    
    public int peek() {
        return stack.get(stack.size() - 1);
    }
    
    public int pop() {
        if (stack.size() > 0) {
            int i = stack.get(stack.size() - 1);
            stack.remove(stack.size() - 1);
            return i;
        } else {
            return 0;
        }
    }
    
    public int elements() {
        return stack.size();
    }
    
    @Override
    public String toString() {
        String output = "";
        for (int i = stack.size() - 1; i >= 0; i--) {
            if (i == 0) {
                output += stack.get(i);
            } else {
                output += stack.get(i) + " | ";
            }
        }
        return output;
    }
    
}

package rbtree;

import java.util.Scanner;

/**
 * The main class
 * @author memonick
 */
public class Main {
    
    private static final RBTree tree = new RBTree();

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        int command = 9;
        do {
            printMenu();
            command = getCommand();
            interpret(command);
        } while(command != 9);
        /*tree.insert(30);
        tree.insert(15);
        tree.insert(70);
        tree.insert(10);
        tree.insert(20);
        tree.insert(5);
        tree.insert(60);
        tree.insert(85);
        tree.insert(50);
        tree.insert(65);
        tree.insert(80);
        tree.insert(90);
        tree.insert(40);
        tree.insert(55);
        tree.insert(45);*/
        /*tree.insert(15);
        tree.insert(6);
        tree.insert(3);
        tree.insert(12);
        tree.insert(10);
        tree.insert(13);
        tree.insert(7);
        tree.insert(17);
        tree.insert(16);
        tree.insert(20);
        tree.insert(18);
        tree.insert(23);*/
        /*tree.insert(150);
        System.out.println(tree);
        tree.insert(60);
        tree.insert(170);
        tree.insert(30);
        tree.insert(120);
        tree.insert(100);
        tree.insert(130);
        tree.insert(70);
        tree.insert(160);
        tree.insert(200);
        tree.insert(180);
        tree.insert(230);
        tree.insert(140);
        tree.insert(220);
        System.out.println(tree);
        tree.delete(230);
        System.out.println(tree);
        tree.delete(250);
        System.out.println(tree);
        tree.delete(120);
        System.out.println(tree);
        if (tree.delete(250)) {
            System.out.println("deleted!");
        } else {
            System.out.println("not deleted!");
        }
        System.out.println(tree);
        System.out.println("Count: " + tree.count());
        System.out.println("Height: " + tree.height());
        tree.printPreOrder();
        tree.empty();
        System.out.println(tree);*/
        /*tree.insert(150);
        tree.insert(130);
        tree.insert(160);
        tree.insert(140);
        System.out.println(tree);
        tree.delete(160);
        System.out.println(tree);*/
    }
    
    /**
     * Interpret the given command
     * @param command the comamnd to interpret
     */
    public static void interpret(int command) {
        int value = 0;
        if (command >= 1 && command <= 3) {
            value = getValue();
        }
        switch(command) {
            case 1:
                tree.insert(value);
                System.out.println(value + " inserted");
                break;
            case 2:
                System.out.println(tree.hasChild(value) ? value + " found" : value + " not found");
                break;
            case 3:
                System.out.println(tree.delete(value) ? value + " deleted" : value + " not found");
                break;
            case 4:
                System.out.println("Size: " + tree.count());
                break;
            case 5:
                tree.printHeight();
                break;
            case 6:
                tree.empty();
                System.out.println("tree emptied");
                break;
            case 7:
                tree.printPreOrder();
                break;
            case 8:
                System.out.println(tree);
                break;
        }
    }
    
    /**
     * Get the user's value
     * @return the user's value as a number
     */
    public static int getValue() {
        Scanner keyboard = new Scanner(System.in);
        int value;
        System.out.print("Value: ");
        try {
            value = keyboard.nextInt();
        } catch (Exception e) {
            return 0;
        }
        return value;
    }
    
    /**
     * Get the user's command
     * @return the user's command as a number
     */
    public static int getCommand() {
        Scanner keyboard = new Scanner(System.in);
        int choice = 0;
        do {
            System.out.print("Choice (1-9): ");
            try {
                choice = keyboard.nextInt();
            } catch (Exception e) {
                return 11;
            }
        } while (choice < 1 || choice > 9);
        return choice;
    }
    
    /**
     * Print the menu
     */
    public static void printMenu() {
        System.out.println("1: Insert");
        System.out.println("2: Find");
        System.out.println("3: Delete by Value");
        System.out.println("4: Count");
        System.out.println("5: Height");
        System.out.println("6: Empty");
        System.out.println("7: Preorder Traversal");
        System.out.println("8: Print");
        System.out.println("9: Quit");
        System.out.println();
    }
    
}

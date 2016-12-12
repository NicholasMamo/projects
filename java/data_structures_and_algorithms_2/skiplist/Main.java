package skiplist;

import java.util.Scanner;

/**
 *
 * @author memonick
 */
public class Main {
    
    private static final SkipList skiplist = new SkipList();

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        int command = 11;
        do {
            printMenu();
            command = getCommand();
            interpret(command);
        } while(command != 11);
        
        /*System.out.println(skiplist);
        System.out.println();
        skiplist.insert(10);
        System.out.println(skiplist);
        System.out.println();
        skiplist.insert(20);
        skiplist.insert(50);
        skiplist.insert(40);
        skiplist.insert(70);
        skiplist.insert(60);
        skiplist.insert(80);
        skiplist.insert(90);
        skiplist.insert(30);
        System.out.println(skiplist);
        System.out.println();
        skiplist.insert(30);
        System.out.println(skiplist);
        System.out.println();
        skiplist.deleteByValue(80);
        System.out.println(skiplist);
        System.out.println();
        skiplist.deleteByIndex(3);
        System.out.println(skiplist);
        System.out.println();
        System.out.println("Index of 90: " + skiplist.getIndex(90));
        skiplist.printHeight();
        System.out.println("Size of skip list: " + skiplist.size());
        skiplist.empty();
        System.out.println(skiplist);*/   
    }
    
    /**
     * Interpret the given command
     * @param command the comamnd to interpret
     */
    public static void interpret(int command) {
        int value = 0;
        if (command >= 1 && command <= 6) {
            value = getValue();
        }
        switch(command) {
            case 1:
                skiplist.insert(value);
                System.out.println(value + " inserted");
                break;
            case 2:
                System.out.println("Index of " + value + ": " + skiplist.getIndex(value));
                break;
            case 3:
                System.out.println(skiplist.deleteByValue(value) ? value + " deleted" : value + " not found");
                break;
            case 4:
                System.out.println(skiplist.deleteByIndex(value) ? value + " deleted" : value + " not found");
                break;
            case 5:
                System.out.println(skiplist.getByIndex(value));
                break;
            case 6:
                System.out.println(skiplist.findSteps(value) + " steps");
                break;
            case 7:
                System.out.println("Size: " + skiplist.size());
                break;
            case 8:
                skiplist.printHeight();
                break;
            case 9:
                skiplist.empty();
                System.out.println("Skiplist emptied");
                break;
            case 10:
                System.out.println(skiplist);
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
            System.out.print("Choice (1-11): ");
            try {
                choice = keyboard.nextInt();
            } catch (Exception e) {
                return 11;
            }
        } while (choice < 1 || choice > 11);
        return choice;
    }
    
    /**
     * Print the menu
     */
    public static void printMenu() {
        System.out.println("1: Insert");
        System.out.println("2: Find");
        System.out.println("3: Delete by Value");
        System.out.println("4: Delete by Index");
        System.out.println("5: Get by Index");
        System.out.println("6: Steps");
        System.out.println("7: Count");
        System.out.println("8: Height");
        System.out.println("9: Empty");
        System.out.println("10: Print");
        System.out.println("11: Quit");
        System.out.println();
    }
    
}

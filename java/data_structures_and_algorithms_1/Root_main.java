package main;

import java.util.Scanner;

public class Root_main {
	
	public static void main(String args[]) {
		Scanner scanner = new Scanner(System.in);
		System.out.print("Enter a positive number to approximate its square root: ");
		float number = scanner.nextFloat();
		System.out.print("Enter the first guess in the Newton's Method: ");
		double guess = scanner.nextFloat();
                System.out.print("Enter the required decimal places of precision: ");
		int precision = scanner.nextInt();
		if (getRoot(number, guess, precision) < 0) {
                    System.out.println("Invalid Input");
                } else {
                    System.out.println("The approximation to " + number + " with " + guess + " as the first guess is " + getRoot(number, guess, precision));
                }
	}
	
	public static double getRoot(float number, double guess, int precision) {
                if (number > 0 && precision > 0) {
                    double root = guess;
                    double prec = Math.pow(10, -1 * (precision + 1));
                    root = root - (root * root - number)/(2*root);
                    while (Math.abs(root - guess) > prec) {
                        guess = root;
                        root = root - (root * root - number)/(2*root);
                    }
                    return root;
                } else {
                    return -1;
                }
	}

}

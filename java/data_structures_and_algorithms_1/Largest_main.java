package main;

import java.util.Scanner;
import java.util.ArrayList;

public class Largest_main {
	
	public static void main(String args[]) {
		Scanner scanner = new Scanner(System.in);
		System.out.println("Enter numbers (0 to quit): ");
		int number;
		ArrayList<Integer> numbers = new ArrayList<Integer>();
		do {
			number = scanner.nextInt();
			if (number != 0) {
				numbers.add(number);
			}
		} while (number != 0);
		System.out.println("The largest number is " + getLargest(0, numbers));
	}
	
	public static int getLargest(int index, ArrayList<Integer> numbers) {
		if (numbers.size() < 1) { // If there are no elements, return 0
			return 0;
		} else if (numbers.size() == 1) { // If there is just one element, return that element
			return numbers.get(0);
		}
                
                // If two elements remain in the list, compare them and return the largest one
		if (index + 2 >= numbers.size()) {
			return numbers.get(index) > numbers.get(index + 1) ? numbers.get(index) : numbers.get(index + 1);
		} else {
			return getLargest(index + 1, numbers);
		}
	}

}

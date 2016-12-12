package main;

import java.util.Scanner;

public class Palindrome_main {

	public static void main(String args[]) {
		Scanner scanner = new Scanner(System.in);
		System.out.print("Enter a string to check whether it's a palindrome or not: ");
		String string = scanner.nextLine();
		while (string.compareTo("q") != 0) {
			if (getPalindrome(string)) {
				System.out.println(string + " is a palindrome");
			} else {
				System.out.println(string + " is not a palindrome");
			}
			System.out.print("Enter a string to check whether it's a palindrome or not: ");
			string = scanner.nextLine();
		}
	}
	
	public static boolean getPalindrome(String input) {
                input = input.toLowerCase();
                String string = "";
                for (int i = 0; i < input.length(); i++) {
                    if ((input.charAt(i) > 96 && input.charAt(i) < 123) || (input.charAt(i) > 46 && input.charAt(i) < 58)) {
                        string += input.charAt(i);
                    }
                }
		for (int i = 0; i < string.length()/2; i++) {
			if (string.charAt(i) != string.charAt(string.length() - i - 1)) {
				return false;
			}
		}
		return true;
	}
	
}

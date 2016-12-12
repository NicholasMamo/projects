package main;

import java.util.Scanner;

public class Prime_main {

	public static void main(String[] args) {
		
		Scanner scanner = new Scanner(System.in);
		int number;
		System.out.print("Enter a natural number to check whether it's prime or not: ");
		number = scanner.nextInt();
		while (number > 0) {
			if (getPrime(number)) {
				System.out.println(number + " is a prime number");
			} else {
				System.out.println(number + " is not a prime number");
			}
			System.out.print("Enter a natural number to check whether it's prime or not: ");
			number = scanner.nextInt();
		}
                System.out.println("Invalid Input");

	}
	
	public static boolean getPrime (int number) {
            if (number > 0) {
                // If the number is less than 3 and divisible by 2, it is the number 2
                if (number % 2 == 0 && number > 3) {
                    return false;
                }
                
                // Skip multiples of 2
                for (int i = 3; i <= Math.ceil(Math.sqrt(number)); i += 2) {
                        if (number != i && number % i == 0) {
                            return false;
                        }
                }
                
                return true;
            } else {
                return false;
            }
	}

}
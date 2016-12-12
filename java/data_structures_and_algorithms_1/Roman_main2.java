package main;

import java.util.Scanner;

public class Roman_main2 {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		String number = "";
                System.out.print("Enter a number between 1 and 1024: ");
                number = scanner.next();
                while (Integer.parseInt(number) > 0 && Integer.parseInt(number) < 1025) {
                    System.out.println("Roman: " + IntegerToRoman(Integer.parseInt(number)));
                    System.out.print("Enter a number between 1 and 1024: ");
                    number = scanner.next();
                }
                System.out.println("Invalid Input");
	}
	
        public static String IntegerToRoman(int number) {
            String roman = "";
            if (number > 0 && number < 1025) {
                while (number >= 1000) {
                    roman += "M";
                    number -= 1000;
                }
                while (number >= 900) {
                    roman += "CM";
                    number -= 900;
                }
                while (number >= 500) {
                    roman += "D";
                    number -= 500;
                }
                while (number >= 400) {
                    roman += "CD";
                    number -= 400;
                }
                while (number >= 100) {
                    roman += "C";
                    number -= 100;
                }
                while (number >= 90) {
                    roman += "XC";
                    number -= 90;
                }
                while (number >= 50) {
                    roman += "L";
                    number -= 50;
                }
                while (number >= 40) {
                    roman += "XL";
                    number -= 40;
                }
                while (number >= 10) {
                    roman += "X";
                    number -= 10;
                }
                while (number >= 9) {
                    roman += "IX";
                    number -= 9;
                }
                while (number >= 5) {
                    roman += "V";
                    number -= 5;
                }
                while (number >= 4) {
                    roman += "IV";
                    number -= 4;
                }
                while (number >= 1) {
                    roman += "I";
                    number -= 1;
                }
            }
            return roman;
        }

}

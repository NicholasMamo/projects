//package main;
//
//import java.util.Scanner;
//
//public class Roman_main {
//
//	static final char [][] NUMERALS = new char [][] {{'I', 'V'}, 
//                                                            {'X', 'L'}, 
//                                                            {'C', 'D'}, 
//                                                            {'M', ' '}};
//	static boolean pre = true;
//	
//	public static void main(String[] args) {
//		Scanner scanner = new Scanner(System.in);
//		String number = "";
//		do {
//			System.out.print("Enter a number between 1 and 1024: ");
//			number = scanner.next();
//		} while (Integer.parseInt(number) < 1 || Integer.parseInt(number) > 1024);
//		
//		System.out.println("Roman: " + IntegerToRoman(number));
//	}
//	
//        public static String IntegerToRoman(String number) {
//            try {
//                if (Integer.parseInt(number) > 0 && Integer.parseInt(number) < 1025) {
//                    String roman = "";
//                    for (int i = 0; i < number.length() && i < 4; i++) {
//                            if (pre) {
//                                    roman = toRoman(i, number.charAt(number.length() - i - 1)).concat(roman);
//                            } else {
//                                    roman += toRoman(i, number.charAt(number.length() - i - 1));
//                            }
//                    }
//                    return roman;
//                } else {
//                    return "";
//                }
//            } catch (NumberFormatException e) {
//                return "";
//            }
//        }
//        
//	public static String toRoman(int digit, char source) {
//		String destination = "";
//		if (Integer.parseInt("" + source) < 4) {
//			for (int i = 1; i <= Integer.parseInt("" + source); i++) {
//				destination += NUMERALS[digit][0];
//			}
//			pre = true;
//		} else if (Integer.parseInt("" + source) < 6) {
//			for (int i = 4; i <= Integer.parseInt("" + source); i++) {
//				destination += NUMERALS[digit][0];
//			}
//			destination += NUMERALS[digit][1];
//			pre = true;
//		} else if (Integer.parseInt("" + source) < 9) {
//			destination += NUMERALS[digit][1];
//			for (int i = 6; i <= Integer.parseInt("" + source); i++) {
//				destination += NUMERALS[digit][0];
//			}
//			pre = true;
//		} else {
//			for (int i = 9; i <= Integer.parseInt("" + source); i++) {
//				destination += NUMERALS[digit][0];
//			}
//			destination += NUMERALS[digit+1][0];
//			pre = true;
//		}
//		return destination;
//	}
//
//}

package main;

import java.util.Scanner;
import main.Stack;

public class Rpn_main {

	public static void main (String args[]) {
		Scanner scanner = new Scanner(System.in);
		String input;
                System.out.print("Enter an RPN string to calculate: ");
                input = scanner.nextLine();
		System.out.println("Calculation: " + calculate(input));
	}
	
	public static int calculate (String string) {
                Stack stack = new Stack();
                String number = "";
                for (int i = 0; i < string.length(); i++) {
                    char c = string.charAt(i);
                    try {
                        Integer.parseInt("" + c);
                        number += c;
                    } catch (NumberFormatException e) {
                        if (!((c + "").equals("" + ' '))) { // Not a whitespace
                            if (stack.elements() > 1) {
                                int num1 = stack.pop();
                                int num2 = stack.pop();
                                int calc = 0;
                                switch (string.charAt(i)) {
                                    case '-':
                                        calc = num2 - num1;
                                        break;
                                    case '+':
                                        calc = num2 + num1;
                                        break;
                                    case '/':
                                        if (num1 != 0) { // In case of division by zero
                                            calc = num2 / num1;
                                        } else {
                                            calc = Integer.MAX_VALUE;
                                        }
                                        break;
                                    case 'x':
                                        calc = num2 * num1;
                                        break;
                                    default:
                                        calc = 0;
                                }
                                stack.push(calc);
                                System.out.println("Stack: " + stack);
                            }
                        }
                        if (!number.equals("")) {
                            stack.push(Integer.parseInt(number));
                            System.out.println("Stack: " + stack);
                        }
                        number = "";
                    }
                }
                return stack.pop();
	}
	
}

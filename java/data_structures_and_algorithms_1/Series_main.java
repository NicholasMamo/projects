package main;

import java.util.Scanner;

/*
 * @author memonick (Nicholas Mamo)
 */
public class Series_main {

    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a radian angle to approximate its sine and cosine: ");
        double angle = scanner.nextDouble();
        System.out.print("Enter the required decimal places of precision: ");
        int precision = scanner.nextInt();
        System.out.println("getSine(" + angle + ") = " + getSine(angle, precision) + "\nsin(" + angle + ") = " + Math.sin(angle));
        System.out.println("Error = " + Math.abs(getSine(angle, precision) - Math.sin(angle)));
        System.out.println("getCosine(" + angle + ") = " + getCosine(angle, precision) + "\ncos(" + angle + ") = " + Math.cos(angle));
        System.out.println("Error: " + Math.abs(getCosine(angle, precision) - Math.cos(angle)));
//        for (int i = -12; i <= 12; i++) {
//            double angle = Math.PI * i/6;
//            System.out.println("The approximation to sin(" + angle + ") is " + getSine(angle, precision) + " whereas sin(" + angle + ") is " + Math.sin(angle));
//            System.out.println("Error: " + Math.abs(getSine(angle, precision) - Math.sin(angle)));
//            System.out.println("The approximation to cos(" + angle + ") is " + getCosine(angle, precision) + " whereas cos(" + angle + ") is " + Math.cos(angle));
//            System.out.println("Error: " + Math.abs(getCosine(angle, precision) - Math.cos(angle)));
//            System.out.println();
//        }
    }

    public static double getSine(double angle, int precision) {
        angle %= 2 * Math.PI; // Get the angle in the first four quadrants and its absolute        
        
        if (angle < 0) {
            angle += 2 * Math.PI;
        }
        
        // Get quadrant
        int quadrant;
        if (angle < Math.PI/2) {
            quadrant = 1;
        } else if (angle < Math.PI) {
            quadrant = 2;
        } else if (angle < 3 * Math.PI/2) {
            quadrant = 3;
        } else {
            quadrant = 4;
        }
        
        angle %= Math.PI/2;
        
        if (quadrant == 2 || quadrant == 4) {
            angle -= Math.PI/2;
        }
        
        double old = 0, approximation = angle;
        double prec = 9 * Math.pow(10, -1 * precision);
        int n = 1;
        while (Math.abs(approximation - old) > prec) {
            old = approximation;
            approximation += Math.pow(-1, n) * Math.pow(angle, 2 * n + 1) / factorial(2 * n + 1);
            n++;
        }
        
        if (quadrant == 2 || quadrant == 3) {
            approximation *= -1;
        }
        
        return approximation;
    }

    public static double getCosine(double angle, int precision) {
        angle %= 2 * Math.PI; // Get the angle in the first four quadrants
        angle = Math.abs(angle); // Get the absolute of the angle since the cosine is an odd function
        
        // Get quadrant
        int quadrant;
        if (angle < Math.PI/2) {
            quadrant = 1;
        } else if (angle < Math.PI) {
            quadrant = 2;
        } else if (angle < 3 * Math.PI/2) {
            quadrant = 3;
        } else {
            quadrant = 4;
        }
        
        angle %= Math.PI/2;
        
        if (quadrant == 2 || quadrant == 4) {
            angle -= Math.PI/2;
        }
        
        double old = 0, approximation = 1.0;
        double prec = 9 * Math.pow(10, -1 * precision);
        int n = 1;
        while (Math.abs(approximation - old) > prec) {
            old = approximation;
            if ((2 * n) % 4 == 0) {
                approximation += Math.pow(angle, 2 * n) / factorial(2 * n);
            } else {
                approximation -= Math.pow(angle, 2 * n) / factorial(2 * n);
            }
            n++;
        }
        
        if (quadrant == 2 || quadrant == 3) { // Correct the sign, applying the CAST rule
            approximation *= -1;
        }
        
        return approximation;
    }

    public static int factorial(int number) {
        if (number < 2) {
            return 1;
        } else {
            return number * factorial(number - 1);
        }
    }

}

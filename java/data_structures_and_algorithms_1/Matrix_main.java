package main;

/*
 * @author memonick (Nicholas Mamo)
 */

import java.util.Random;

public class Matrix_main {
    
    public static final int LEN = 3;
    
    public static void main(String args[]) {
        double [][][] matrices = new double[2][LEN][LEN];
        matrices[0] = getMatrix();
        matrices[1] = getMatrix();
        
        System.out.println("Matrix 1:");
        printMatrix(matrices[0]);
        System.out.println("Matrix 2:");
        printMatrix(matrices[1]);
        
        double [][] matrix = multiplyMatrices(matrices);
        System.out.println("Result:");
        printMatrix(matrix);
    }
    
    public static double[][] getMatrix() {
        double[][] matrix = new double[LEN][LEN];
        Random generator = new Random();
        
        for (int n = 0; n < LEN; n++) { // for each row
            for (int m = 0; m < LEN; m++) { // for each column
                matrix[n][m] = Integer.MAX_VALUE * generator.nextDouble();
            }
        }
        
        return matrix;
    }
    
    public static void printMatrix(double[][] matrix) {
        System.out.print("[");
        for (int n = 0; n < LEN; n++) { // for each row
            System.out.print("{");
            for (int m = 0; m < LEN; m++) { // for each column
                System.out.print(matrix[n][m]);
                System.out.print(m < LEN - 1? ", " : "");
            }
            System.out.print(n < LEN - 1? "}\n" : "}");
        }
        System.out.println("]\n");
    }
    
    public static double[][] multiplyMatrices(double[][][] matrices) {
        double [][] matrix = new double[LEN][LEN];
        
        for (int n = 0; n < LEN; n++) { // for each row
            for (int m = 0; m < LEN; m++) { // for each column
                matrix[n][m] = 0; // initialize the matrix
            }
        }
        
        // matrix multiplication
        for (int n = 0; n < LEN; n++) { // for each row
            for (int m = 0; m < LEN; m++) { // for each column
                for (int i = 0; i < LEN; i++) { // for each value
                    matrix[n][m] += matrices[0][n][i] * matrices[1][i][m];
                }
            }
        }
        
        return matrix;
    }

}
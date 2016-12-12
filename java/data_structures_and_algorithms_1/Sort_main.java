package main;

import java.util.Random;

/*
 * @author memonick (Nicholas Mamo)
 */

public class Sort_main {
    
    public static void main (String args[]) {
        int[] numbers = new int[16384];
        fill(numbers);
        System.out.print(check(numbers) ? "Sorted: " : "Not Sorted: ");
        print(numbers);
                
        int[] sorted = sort(numbers);
        System.out.print(check(sorted) ? "Sorted: " : "Not Sorted: ");
        print(sorted);
    }
    
    public static void fill(int[] numbers) {
        Random generator = new Random();
        for (int i = 0; i < numbers.length; i++) {
            numbers[i] = generator.nextInt();
        }
    }
    
    public static void print(int[] numbers) {
        for (int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i]);
            System.out.print(i < numbers.length - 1? " | " : "\n\n");
        }
    }
    
    public static boolean check(int[] numbers) {
        boolean flag = true;
        int i = 0;
        while (flag && i < (numbers.length - 2)) {
            if (numbers[i] > numbers[i + 1]) {
                flag = false;
            }
            i++;
        }
        return flag;
    }
    
    public static int[] sort(int[] numbers) {
        int[] sorted = numbers;
        int length = numbers.length;
        int j = length/2;
        boolean flag;
        do {
            flag = false;
            for (int i = 0; i < length - j; i++) {
                if (numbers[i] > numbers[i + j]) {
                    int temp = numbers[i];
                    numbers[i] = numbers[i + j];
                    numbers[i + j] = temp;
                    flag = true;
                }
            }
            if (j > 1) {
                flag = true;
                j /= 2;
            }
        } while (!(!flag && j == 1));
        return sorted;
    }

}

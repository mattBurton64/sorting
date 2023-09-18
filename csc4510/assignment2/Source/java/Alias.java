// This program is intended to investigate the properties of "aliasing" in Java
public class Alias {

    static void sub(int[] integer) {
        integer[0] = 0; // alter the value via the reference
    }

    public static void main(String[] args) {
        int integer = 1; // declaring an integer
        int[] pointer = { integer }; // Create an array to hold the integer value

        // Display the value of integer before and after being passed into the subroutine
        System.out.println("Integer\n=======");
        System.out.println("before: " + integer);
        sub(new int[]{integer}); // pass integer "by reference"
        System.out.println(" after: " + integer);

        // Display the value pointed to by the array before and after being changed
        System.out.println("\nPointer\n=======");
        System.out.println("before: " + pointer[0]);
        sub(pointer);
        System.out.println(" after: " + pointer[0]);
    }
}

// This program is intended to investigate the properties of passing by result in Java
import java.util.Arrays;

class ValueResult {

    static int subInt(int integer) // declaring a subroutine which takes in an integer parameter by result
    {
        integer = 0; // alter the value
        return integer;
    }

    static double subDouble(double floating) // declaring a subroutine which takes in a double parameter by result
    {
        floating = 0.0; // alter the value
        return floating;
    }

    static boolean subBool(boolean bool) // declaring a subroutine which takes in a boolean parameter by result
    {
        bool = false; // alter the value
        return bool;
    }

    static char subChar(char character) // declaring a subroutine which takes in a char parameter by result
    {
        character = 'z'; // alter the value
        return character;
    }

    static void subArray (int array[], int size) // declaring a subroutine which takes in an integer array parameter by result
    {
        for (int i = 0; i < size; i++)
        {
            array[i] = 1;
        }
    }

    static void outArray(int array[], int size) // utility function for outputting the values in an array
    {
        for (int i = 0; i < size; i++)
        {
            System.out.print(array[i]);
            if (i < size)
                System.out.print(" ");
        }
        System.out.print("\n");
    }

    public static void main(String[] args) {
        // Declare multiple variables with initial values
        int integer = 1;
        double floating = 1.0;
        boolean bool = true;
        char character = 'a';
        // Declare multiple arrays of different sizes
        int smallSize = 5;
        int[] smallArray = new int[smallSize];
        Arrays.fill(smallArray, 0);
        int largeSize = 50;
        int[] largeArray = new int[largeSize];
        Arrays.fill(largeArray, 0);

	    // Display the value of each test before and after being passed into their respective subroutines
        System.out.println("Integer\n=======");
        System.out.println("before: " + integer);
        integer = subInt(integer);
        System.out.println(" after: " + integer);

        System.out.println("\nFloat\n=====");
        System.out.println("before: " + floating);
        floating = subDouble(floating);
        System.out.println(" after: " + floating);

        System.out.println("\nBoolean\n=======");
        System.out.println("before: " + bool);
        bool = subBool(bool);
        System.out.println(" after: " + bool);

        System.out.println("\nCharacter\n=========");
        System.out.println("before: " + character);
        character = subChar(character);
        System.out.println(" after: " + character);

        System.out.println("\nSmall Array\n===========");
        System.out.print("before: "); outArray(smallArray, smallSize);
        subArray(smallArray, smallSize);
        System.out.print(" after: "); outArray(smallArray, smallSize);

        System.out.println("\nLarge Array\n===========");
        System.out.print("before: "); outArray(largeArray, largeSize);
        subArray(largeArray, largeSize);
        System.out.print(" after: "); outArray(largeArray, largeSize);
    }
}
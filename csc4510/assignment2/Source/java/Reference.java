// This program is intended to investigate the properties of passing by reference in Java
import java.util.Arrays;

// Object definition code generated with help from chatGPT, using objects to simulate passing by reference
class MyInteger {
    int value;

    MyInteger(int value) {
        this.value = value;
    }
}

class MyDouble {
    double value;

    MyDouble(double value) {
        this.value = value;
    }
}

class MyBoolean {
    boolean value;

    MyBoolean(boolean value) {
        this.value = value;
    }
}

class MyChar {
    char value;

    MyChar(char value) {
        this.value = value;
    }
}

class Reference {

    static void subInt(MyInteger integer) // declaring a subroutine which takes in an integer parameter by reference
    {
        integer.value = 0; // alter the value
    }

    static void subDouble(MyDouble floating) // declaring a subroutine which takes in a double parameter by reference
    {
        floating.value = 0.0; // alter the value
    }

    static void subBool(MyBoolean bool) // declaring a subroutine which takes in a boolean parameter by reference
    {
        bool.value = false; // alter the value
    }

    static void subChar(MyChar character) // declaring a subroutine which takes in a char parameter by reference
    {
        character.value = 'z'; // alter the value
    }

    static void subArray (int array[], int size) // declaring a subroutine which takes in an integer array parameter by reference
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
        MyInteger integer = new MyInteger(1);
        MyDouble floating = new MyDouble(1.0);
        MyBoolean bool = new MyBoolean(true);
        MyChar character = new MyChar('a');
        // Declare multiple arrays of different sizes
        int smallSize = 5;
        int[] smallArray = new int[smallSize];
        Arrays.fill(smallArray, 0);
        int largeSize = 50;
        int[] largeArray = new int[largeSize];
        Arrays.fill(largeArray, 0);

	    // Display the value of each test before and after being passed into their respective subroutines
        System.out.println("Integer\n=======");
        System.out.println("before: " + integer.value);
        subInt(integer);
        System.out.println(" after: " + integer.value);

        System.out.println("\nFloat\n=====");
        System.out.println("before: " + floating.value);
        subDouble(floating);
        System.out.println(" after: " + floating.value);

        System.out.println("\nBoolean\n=======");
        System.out.println("before: " + bool.value);
        subBool(bool);
        System.out.println(" after: " + bool.value);

        System.out.println("\nCharacter\n=========");
        System.out.println("before: " + character.value);
        subChar(character);
        System.out.println(" after: " + character.value);

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
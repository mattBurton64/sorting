# Assignment 5

Write two programs in a functional language (Haskell). One should be simple and the other should be more advanced.

## Usage

Note: The following steps expect you to be in the functional/ directory to execute as intended  
To run the two Haskell programs execute

```terminal
runghc Simple.hs
```

and

```terminal
runghc Advanced.hs
```

To use the doubleMe function from Simple.hs, first enter GHC

```terminal
ghci
```

Next load the program

```ghci
:l Simple.hs
```

Finally, execute the program by enter the number you want to double after the program, separated by a space

```ghci
doubleMe 2
```

## Output

After running the two Haskell programs you should expect to see

```terminal
hello world
```

and

```terminal
1 2 bizzbizz 4 5 bizz buzzbuzz 8 bizz 10 11 bizz bizz buzz bizz 16 buzz bizz 19
```

After running the doubleMe function you should see

```ghci
4
```

## Credits

Learning Haskell - http://learnyouahaskell.com/starting-out#babys-first-functions  
Learning about the concatMap - ChatGPT

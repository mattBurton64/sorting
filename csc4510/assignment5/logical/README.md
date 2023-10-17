# Assignment 5

Write a prolog program that defines the rules of a fmaily tree and models the given tree on blackboard.

## Usage

Note: The following steps expect you to be in the logical/ directory to execute as intended  
To start GNU Prolog execute...

```terminal
gprolog
```

Once GNU Prolog is running, load the family tree knowledgebase for reference

```GNU Prolog
[family].
```

Now with the context loaded, use any of the defined relationships to query the family tree  
Example:

```GNU Prolog
spouse('Allen', 'Anne').
```

```GNU Prolog
spouse('Allen', 'Grace').
```

## Output

After loading the knowledgebase the terminal should look like this

```GNU Prolog
| ?- [family].
compiling /Users/matt/Documents/GitHub/college-classes/csc4510/assignment5/logical/family.pl for byte code...
/Users/matt/Documents/GitHub/college-classes/csc4510/assignment5/logical/family.pl compiled, 119 lines read - 11518 bytes written, 16 ms

(4 ms) yes
```

After running the two example wueries you should see the following...

```GNU Prolog
| ?- spouse('Allen','Anne').

true
```

```GNU Prolog
| ?- spouse('Allen','Grace').

no
```

## Credits

Learning Prolog - https://www.javatpoint.com/prolog-programs  
GProlog help - http://www.gprolog.org/manual/gprolog.pdf
Compiling my knowledgebase - https://www.youtube.com/watch?v=bU1vbhdFFPc&ab_channel=ProfessorHankStalica
Understanding error messages - ChatGPT
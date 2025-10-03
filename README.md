# C-Lisp: Final Submission
 Chris Phornroekngam 
 
 12136967

## Folder Structure

```
├── include/
│   ├── builtins.h
│   ├── eval.h
│   ├── parser.h
│   ├── printer.h
│   └── sexp.h
├── src/
│   ├── builtins.c
│   ├── eval.c
│   ├── main.c
│   ├── parser.c
│   ├── printer.c
│   └── sexp.c
├── TestCases.txt
├── makefile
└── README.md

```

`include/` - Header files are included in this directory. This contains the function prototypes, global variables, like NIL and T for true, as well as the S-Expression struct.

`src/` - Contains the source code for the project as well as `main.c`.

`main.c` - Where the program will execute. Using command line arguments, the user can select Test mode (T) or REPL mode (R).

## Usage
```
make
./c-lisp <running-mode>
```

If for any reason the makefile does not work, it can alternatively be compiled using this command:

```
gcc -Wall -g -Iinclude src/main.c src/parser.c src/printer.c src/sexp.c src/builtins.c -o c-lisp
```

## Test Plan

The tests will be performed in `main.c`. 

The tests can be divided up by sprint.

### Sprint 1: Reading and Printing S-Expressions
The First Sprint has us creating the S-Expression data structure. Primarily, we have created test cases that will create symbols, numbers, lists, and nested lists. Once these are created, we invoke our print function to see if they print correctly. Additionally, I have also included a test case where the S-Expression is not correctly closed off. This will print out an error message. Lastly for this sprint, I have included a test for an improperly terminated list.

### Sprint 2: Predicates, Constructors, and Accessors
The Second Sprint has us creating type checkers as well as contructors and accessors. First, we will create a few atoms: a list, symbol, a string, and a number. We will then use the type checkers functions to see if it is true (T) or false (nil). Then, we will test our car() and cdr() functions to see if they point us to the right cons cell. If try invoking car or cdr on an empty list or symbol, then we will return a NIL and print out an error message.

### Sprint 3: Core Arithmetic and Logic
The Third Sprint has us creating arithmetic and logical operations. We will supply these function calls with numerical S-Expression to see what operations can be performed on them. The arithmetic operations will work with both integers and doubles, if it detects a non-numerical S-Expression, it will return an error as a symbol. Notably, if a user is trying to use the div() function by zero it will return an S-Expression with a divide by zero error. The logical operands however can work on any type of atom. If the operand evaluates to true it will return the global constant T for true and if it is false it will return the global constant NIL. If the there is a comparison between two different types, it will return a not an number error for the inequality functions. All of this this will be tested using a variety of atoms.

### Sprint 5: Eval and Built-In Functions
Sprint 5 features us testing our eval function with our the previously created built-in functions and some special forms. First we will make sure that our `quote` functionality does not evalute the s-expression and instead treats it as an atom. Then, instead of directly calling the built-in funciton, we will use the same input as a user in the REPL. This will call out eval function and parse the correct symbol and match it the appropriate function call. E.g. `(+ 1 2)` will call `add(1, 2)`. We will do this for all the built-in funcitons. We will also test nesting various lisp expressions and built in functions. Lastly, we will test to make sure out we can set variables using set() and perform arithmetic on a variable.

### Sprint 6: Short-Circuiting and Conditionals
In this sprint, we will test conditionals to ensure we are able to branch off. Then we will test our logical operators `and` and `or`.

### Sprint 7 and 8: User Defined and Lambda Functions
Our last two sprints will test both user defined functions as well as lambda functions. We will test this by first creating simply mathematical user defined functions. Lambda will need to be invoked here to perform these operations. Then will we call these funcitons to ensure they have been saved and work. One thing to note, when a function is successfully defined, it will return `#<function>`.

### Running Tests:

To execute our test cases we can run: 

`./c-lisp T > TestCases.txt`.

Normally, our test cases would print to standard output, but for the sake of logging, we will pipe stdout into a file named `TestCases.txt`.

## Test Cases
In order to keep this `README` concise, the full output can be found in this repo under `TestCases.txt`

## Current Bugs/Problems
The only problem we were able to find with this program is the lack of garbage collection. This was never implemented because we were never instructed to do so. Since this was built without garbage collection in mind, adding it is likely not trival and will require a serious rework.
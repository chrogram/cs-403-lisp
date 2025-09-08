# Sprint 1 [2 3] Assignment
 Chris Phornroekngam

## Folder Structure

```
├── include/
│   ├── builtins.h
│   ├── parser.h
│   ├── printer.h
│   └── sexp.h
├── src/
│   ├── builtins.c
│   ├── main.c
│   ├── parser.c
│   ├── printer.c
│   └── sexp.c
├── Makefile
└── README.md
```

`include/` - Header files are included in this directory. This contains the function prototypes, global variables, like NIL and T for true, as well as the S-Expression struct.

`src/` - Contains the source code for the project as well as `main.c`.

`main.c` - Where the program will execute. Using command line arguments, the user can select Test mode (T) or REPL mode (R).

## Usage
```
make
./c-sexp <running-mode>
```

If for any reason the makefile does not work, it can additionally be compiled using this command:

```
gcc -Wall -g -Iinclude src/main.c src/parser.c src/printer.c src/sexp.c src/builtins.c -o c-sexp
```

## Test Plan

The tests will be performed in `main.c`. This is because while the REPL mode is working and can correctly save and parse S-Expression into variable, we cannot as of yet invoke system level functions. So, for now, the functions will be tested in `main.c`. 

The tests can be divided up into 3 sections for each sprint.

### Sprint 1
The First Sprint has us creating the S-Expression data structure. Primarily, we have created test cases that will create symbols, numbers, lists, and nested lists. Once these are created, we invoke our print function to see if they print correctly. Additionally, I have also included a test case where the S-Expression is not correctly closed off. This will print out an error message. Lastly for this sprint, I have included a test for an improperly terminated list.

### Sprint 2
The Second Sprint has us creating type checkers as well as contructors and accessors. First, we will create a few atoms: a list, symbol, a string, and a number. We will then use the type checkers functions to see if it is true (Yes) or false (No). Then, we will test our car() and cdr() functions to see if they point us to the right cons cell. If try invoking car or cdr on an empty list or symbol, then we will return a NIL and print out an error message.

### Sprint 3
The Third Sprint has us creating arithmetic and logical operations. We will supply these function calls with numerical S-Expression to see what operations can be performed on them. The arithmetic operations will work with both integers and doubles, if it detects a non-numerical S-Expression, it will return an error as a symbol. Notably, if a user is trying to use the div() function by zero it will return an S-Expression with a divide by zero error. The logical operands however can work on any type of atom. If the operand evaluates to true it will return the global constant T for true and if it is false it will return the global constant NIL. If the there is a comparison between two different types, it will return a not an number error for the inequality functions. All of this this will be tested using a variety of atoms.

To execute our test cases we can run: 

`./c-sexp T > TestCases.txt`.

Normally, our test cases would print to standard output, but for the sake of logging, we will pipe stdout into a file named `TestCases.txt`

## Test Cases
```
--- Sprint 1: Reading and Printing S-Expressions ---
Parsing Symbol
Parsed== 'a':: 
a

Parsing String
Parsed== '"hello"':: 
"hello"

Parsing Number
Parsed== '123':: 
123

Parsing List
Parsed== '(a b c)':: 
(a b c)

Unclosed Parenthesis Test
Error: Unmatched opening parenthesis.
Parsed== '(a b c ':: 


Parsing Nested List
Parsed== '((a (789) x) (b (456) y))':: 
((a (789) x) (b (456) y))

Parsing Dotted Pair
Parsed== '(a . (b . (c . d)))':: 
(a b c . d)

--- Sprint 2: Predicates, Constructors, and Accessors ---

is_symbol Test Cases:
Is 'a' a symbol? Yes
Is (1 2) a symbol? No

is_number Test Cases:
Is '123' a number? Yes
Is 'a' a number? No

is_string Test Cases:
Is "foo_bar" a string? Yes
Is 'a' a string? No

is_list Test Cases:
Is '(1 2)' a list? Yes
Is '123' a list? No

is_nil Test Cases:
Is T a nil? No
Is nil a nil? Yes

car/cdr Test Cases:
car of (1 2) is: 1
car of '123' is: Error: 'car' called on a non-list or empty list.
nil

cdr of (1 2) is: (2)
cdr of (1 2 3) is: (2 3)
cdr of (1) is: nil
cdr of '123' is: Error: 'cdr' called on a non-list or empty list.
nil

--- Sprint 3: Core Arithmetic and Logic ---

add() Test Cases:
add(5, 10) -> 	15
add(1.5, 2.25) -> 	3.75

sub() Test Cases:
sub(10, 5) -> 	5
sub(5, 10) -> 	-5

multiply() Test Cases:
mul(5, 10) -> 	50
mul(0, 10) -> 	0
mul(5, 1.5) -> 	7.5

divide() Test Cases:
div(10, 5) -> 	2
div(2.25, 3) -> 	0.75
div(0, 5) -> 	0
div(5, 0) -> 	DivisionByZero

mod() Test Cases:
mod(10, 3) -> 	1
mod(10, 0) -> 	DivisionByZero

Relational Function Test Cases:
gt(5, 10)  -> 	nil
gt(10, 5)  -> 	T
gt(5, 5)  -> 	nil
gt(a, 5) -> 	Not-a-number
gt(5, a) -> 	Not-a-number
gte(10, 5) -> 	nil
gte(10, 10) -> 	T
lt(10, 5)  -> 	T
lte(5, 10) -> 	T
eq(foo, foo)-> 	T
eq(foo, bar)-> 	nil
eq(foo, 1)-> 	nil
not(nil)   -> 	T
not(T)   -> 	nil

Arithmetic on Non-Numbers Test Cases:
add(5, foo) -> 	Not-a-number
sub(foo, 5) -> 	Not-a-number
```

## Current Bugs/Problems
The biggest issue with this current program is that the REPL program can only parse S-Expression and can't do any operations with them. I originally had issues with hanging/unclosed parenthesis, but they seem to all be sorted out. Quote notation still needs to be added. I have not ran into an issue that would require me adding this functionality, but I suspect when I flesh out my eval() function more this will be required.
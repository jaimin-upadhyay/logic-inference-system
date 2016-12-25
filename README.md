# Logic Inference System
C++ project to draw logical inferences based on provided information, using resolution inference algorithm. The program accepts a input file called `input.txt` with queries and sentences for the knowledge base and outputs a `output.txt` file with the results.

The knowledge bases can contain sentences with the following defined operators:

        NOT X                 ~X
        X OR Y                X | Y
        X AND Y               X & Y
        X IMPLIES Y           X => Y

For instance, given the below information the program can determine whether  `~Kills(Curiosity, Tuna)` is `TRUE` or `FALSE` i.e. whether `Curiosity` killed `Tuna`:
        
        Dog(D)
        Owns(Jack,D)
        Dog(y) & Owns(x,y) => AnimalLover(x)
        ~(AnimalLover(x) & Animal(y) & Kills(x,y))
        Kills(Jack, Tuna) | Kills(Curiosity, Tuna)
        Cat(Tuna)
        Cat(x) => Animal(x)

## Format for input.txt:
        <NQ = NUMBER OF QUERIES>
        <QUERY 1>
        . . .
        <QUERY NQ>
        <NS = NUMBER OF GIVEN SENTENCES IN THE KNOWLEDGE BASE>
        <SENTENCE 1>
        . . .
        <SENTENCE NS>
where
+ Each query will be a single literal of the form Predicate(Constant) or ~Predicate(Constant).
+ Variables are all single lowercase letters.
+ All predicates (such as Sibling) and constants (such as John) are case-sensitive alphabetical strings that
begin with an uppercase letter.
+ Each predicate takes at least one argument. Predicates will take at most 100 arguments. A given
predicate name will not appear with different number of arguments.
+ There will be at most 100 queries and 1000 sentences in the knowledge base.
+ All variables are assumed to be universally quantified.
+ Operator priorities apply. Parentheses may be used in the sentences given to you for the KB, to group
terms, e.g., (A(x) | B(x)) => C(x).
+ The knowledge base given is assumed to be consistent with no contracting rules or facts.
+ See the sample input below for spacing patterns.

## Format for output.txt:
For each query, determine if that query can be inferred from the knowledge base or not, one query per line:

        <ANSWER 1>
        . . .
        <ANSWER NQ>
where
each answer should be either TRUE if you can prove that the corresponding query sentence is true given the
knowledge base, or FALSE if you cannot.

## Examples:

### Example 1:

#### Input:
        6
        F(Bob)
        H(John)
        ~H(Alice)
        ~H(John)
        G(Bob)
        G(Tom)
        14
        A(x) => H(x)
        D(x,y) => ~H(y)
        B(x,y) & C(x,y) => A(x)
        B(John,Alice)
        B(John,Bob)
        D(x,y) & Q(y) => C(x,y)
        D(John,Alice)
        Q(Bob)
        D(John,Bob)
        F(x) => G(x)
        G(x) => H(x)
        H(x) => F(x)
        R(x) => H(x)
        R(Tom)

#### Output:
        FALSE
        TRUE
        TRUE
        FALSE
        FALSE
        TRUE

### Example 2:

#### Input:
        2
        Ancestor(Liz,Billy)
        Ancestor(Liz,Bob)
        6
        Mother(Liz,Charley)
        Father(Charley,Billy)
        ~Mother(x,y) | Parent(x,y)
        ~Father(x,y) | Parent(x,y)
        ~Parent(x,y) | Ancestor(x,y)
        ~(Parent(x,y) & Ancestor(y,z)) | Ancestor(x,z)
        
#### Output:
        TRUE
        FALSE
        
### Example 3:

#### Input:
        1
        ~Kills(Curiosity, Tuna)
        7
        Dog(D)
        Owns(Jack,D)
        Dog(y) & Owns(x,y) => AnimalLover(x)
        ~(AnimalLover(x) & Animal(y) & Kills(x,y))
        Kills(Jack, Tuna) | Kills(Curiosity, Tuna)
        Cat(Tuna)
        Cat(x) => Animal(x)
        
#### Output:
        FALSE




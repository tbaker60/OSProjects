# Toby Baker
# OS Proj 2 - Banker's Algorithm problem

This folder contains all of the files needed for project 2:
    bankersAlgorithm.C
    inputData.txt
    structs.h (can be ignored. Was not needed)

To run this program please input the following commands into the terminal:
gcc bankersAlgorithm.C
./a.out

# Notes on development
Developing this programming I got more reacquainted with matrices, especially in C,
since I haven't touched them in a while, and I originally developed most of my code
using multiple arrays. I also became more familiar with how the bankers algorithm
actually works, especially in a code form as opposed to from a more abstract perspective.

# Issues
I had to reexamine this code a good few times because of how many loops are involved
with matrices which can make code a little confusing if you just glance over it quickly.
When developing initially I wrote my code using multiple arrays of my own Process structs 
with one per process instead of using one matrix for all of the data I would need for
allocation and another for max allocation. I was happier with the code after refactoring 
to use the matrices because it keeps everything cleaner and doesn't require you to go look
at my structs header file and understand the little bit that was going on over there.
Using matrices made my code simpler and easier to understand and also works much better to
implement the banker algorithm than my struct array implementation would have.
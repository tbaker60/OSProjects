# Toby Baker
# OS Proj 1 - Producer-Consumer problem

My repo has a good amount of extra files that became obsolete as I continued to update 
and work on this project. The only ones that really matter for the submission are 
producer.c, consumer.c, and header.h

To run my file, please input the following commands in the terminal:
gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer
./producer & ./consumer &

# Notes on development
In the creation of this program, I got quite tangled up in how to actually set up
the two processes to be able to run simultaneously since that is not something I have
ever had to do before. I also had to work around the minor differences in C and C++,
which is what has been used for all of my coding courses. 
I also had to use linux for the first time which involved a lengthy install and subsequent
reinstall processes through virtualBox and having to teach myself how to use it in a short
period of time.

#Issues
I have not been able to quite grasp what outputs I'm getting and I can't quite figure out 
what my threads are doing and if they're running properly. I went through several different
builds of this project, as you can see on my github repo, and really tried attacking this
from every different angle. I've also never written a real readme file before and the instructions
were not very specific so I fear I have missed something here. Understanding the documentation
for the pthread and shm operations was also incredibly difficult without guidance and without 
detailed background knowledge which has in part led to my program not working perfectly.

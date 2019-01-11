###############################################################
# Program:
#     Assignment 01, Vector
#     Brother XXXX, CS235
# Author:
#     <your name here>
# Summary:
#     <put a description here>
# Time:
#     <how long did it take to complete this program?>
###############################################################

##############################################################
# The main rule
##############################################################
a.out: Vector.h assignment01.o
	g++ -o a.out assignment01.o -std=c++11
	tar -cf assignment01.tar Vector.h assignment01.cpp makefile

##############################################################
# The individual components
#      assignment01.o     : the driver program
##############################################################
assignment01.o: Vector.h assignment01.cpp
	g++ -c assignment01.cpp -std=c++11


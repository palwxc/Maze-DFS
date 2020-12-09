#include <iostream>
#include <string>

#ifndef MAZE
#define MAZE

using std::cout;
using std::endl;
using std::cin;
using std::string;


/*
Writes to a string array containing: 
    * the your (the student author’s) Campus Username (at index 0)
    * and Student ID# (at index 1).
Takes as input a pre-existing length-2 string array.
*/
void get_identity(string my_id[]);


/**
Use this to help you enumerate the directions.
Gets passed into one function below.
**/
enum direction
{
    NORTH,
    SOUTH,
    EAST,
    WEST
};


/**
Creates a dynamically allocated array of strings.
Returns a pointer to that array.
**/
string * build_matrix(int rows);


/**
Fills the matrix with one line per string in the array.
Use the getline method.
Why don't you need to send in cols?
**/
void fill_matrix(string *matrix, int rows);


/**
Print the matrix as in the sample_output.txt
**/
void print_matrix(string *matrix, int rows);


/**
Delete the dynamically allocated array of strings.
Why don't you need to send in cols?
**/
void delete_matrix(string *matrix, int rows);


/**
Finds the starting position of Niobe.
Note: x and y are passed by reference; what does this do for you?
Why don't you need cols here? Hint: not the same reason as last two.
**/
void find_start(string *matrix, int rows, int &x, int &y);


/**
This is the recursive backtracking function you need to write.
It should return true if you found the solution,
and false if there is no solution.
It should leave a trail of @ signs along the path to the solution.
Make sure to build your solution with strong emphasis on the pseudocode;
do not try to code it first, first work out the solution on paper/markerboard.
**/
bool find_exit( string *matrix, int x, int y);


/**
Returns true if x and y are the final exit location, 
and false otherwise.
**/
bool at_end(string *matrix, int x, int y);


/**
Returns true if the position indexed by x and y is a valid move, 
and false otherwise.
What is a valid move?
**/
bool valid_move(string *matrix, int x, int y, direction d);


#endif

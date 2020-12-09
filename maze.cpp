#include "maze.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

bool check_string(string tmp, int row, bool &previousN);

void check_matrix(string *matrix, int rows);

void make_valid_move(string *matrix, int &x, int &y, direction d);

void get_identity(string my_id[])
{
    my_id[0]="palwxc";
    my_id[1]="12398940";
}


string * build_matrix(int rows)
{
    string *dynamicArray;
    if(rows>0)
    {
        dynamicArray = new string [rows];
        return dynamicArray;
    }
    else
    {
        cout << "Invalid parameter for rows to build_matrix." << endl;
        return dynamicArray=0;
    }
}


void fill_matrix(string *matrix, int rows)
{
    if(rows<=0)
        cout << "Invalid rows parameter for fill_matrix." << endl;
    else if(matrix == NULL)
        cout << "Matrix cannot be filled because matrix has not been built." << endl;
    else
    {
        //false while N has not appeared
        bool previousN=false;
        string tmp;
        int width;
        cin >> width;
        getline(cin, tmp);
        for(int i=0; i<rows; i++)
        {
            do{
                getline(cin, tmp);
                if(tmp.length()!=width)
                    cout << "String for line " << i << " is the wrong size." << endl;
                else
                    matrix[i]=tmp;
            }while(tmp.length()!=width || !check_string(tmp, i, previousN));
        }
    }
    check_matrix(matrix, rows);
}
/**
Checks that string only consists of |, E, N, or space.
previousN is a bool that is true if 'N' has already appeared in maze.
Returns false if any characters in string are not valid.
**/
bool check_string(string tmp, int row, bool &previousN)
{
    //Used to check if N appears multiple times in tmp
    bool repeatN=false;
    for(int i=0; i<tmp.length(); i++)
    {
        if(tmp.at(i)!='|' && tmp.at(i)!=' ' && tmp.at(i)!='E' && tmp.at(i)!='N')
        {
            cout << "Invalid character(s) entered for row " << row << "." << endl;
            return false;
        }
        if(tmp.at(i)=='N' && previousN)
        {
            cout << "Error: N has already appeared in maze." << endl;
            return false;
        }
        else if(tmp.at(i)=='N' && repeatN)
        {
            cout << "Error: N appears multiple times in row " << row << "." << endl;
            return false;
        }
        else if(tmp.at(i)=='N')
            repeatN=true;
    }
    if(repeatN)
        previousN=true;
    return true;
}

/**
Checks if N and E appear at least once in the maze.
Prints alert if there is no N. Prints alert if there are multiple exits.
**/
void check_matrix(string *matrix, int rows)
{
    int checkE=0;
    bool checkN=false;
    for(int i=0; i<rows; i++)
        for(int j=0; j<matrix[i].length(); j++)
        {
            if(matrix[i].at(j)=='E')
                checkE++;
            if(!checkN)
                if(matrix[i].at(j)=='N')
                    checkN=true;
        }
    if(checkE==1 && checkN)
        return;
    else if(!checkN)
        cout << "Warning: There is no Niobe in the maze. The maze cannot be solved without a start point." << endl;
    cout << "Warning: There are " << checkE << " Exit(s) in the maze." << endl;
}

void print_matrix(string *matrix, int rows)
{
    for(int i=0; i<rows; i++)
        cout << matrix[i] << endl;
    cout << endl;
}

void delete_matrix(string *matrix, int rows)
{
    delete[] matrix;
    matrix=NULL;
}

/**
x runs horizontally, y runs vertically
x corresponds to the strings in the matrix array, y corresponds to rows
x=0, y=0 is the top-left of the maze
**/
void find_start(string *matrix, int rows, int &x, int &y)
{
    for(int i=0; i<rows; i++)
        for(int j=0; j<matrix[i].length(); j++)
            if(matrix[i].at(j)=='N')
            {
                x=j;
                y=i;
                return;
            }
    cout << "Error: No Niobe found in maze." << endl;
}
/**
Run find_start before using find_exit.
x and y are the ints that were updated by find_start
**/
bool find_exit(string *matrix, int x, int y)
{
    bool exit=true;
    int previousX=x;
    int previousY=y;
    direction d=NORTH;
    do{
        if(valid_move(matrix, x, y, d))
        {
            make_valid_move(matrix, x, y, d);
            if(matrix[y].at(x)=='E')
                return true; //only called once

            matrix[y].at(x)='@';

            if(find_exit(matrix, x, y))
                return true; //called every time a valid step is made
            else
            {
                matrix[y].at(x)=' ';
                x=previousX;
                y=previousY;
            }
        }
        switch(d){
            case NORTH:
                d=SOUTH;
                break;
            case SOUTH:
                d=EAST;
                break;
            case EAST:
                d=WEST;
                break;
            case WEST:
                exit=false;
                break;
        }
    }while(exit);
    return false; //only called once
}

/**
true if position is E, false if position isn't E
**/
bool at_end(string *matrix, int x, int y)
{
    if(matrix[y].at(x)=='E')
       return true;
    return false;
}

/**
true if position plus direction is space or E
false if anything else, or if moving would go off maze
**/
bool valid_move(string *matrix, int x, int y, direction d)
{
    switch(d){
        case NORTH:
            if(matrix[y-1].at(x)==' ' || matrix[y-1].at(x)=='E')
                return true;
            break;
        case SOUTH:
            if(matrix[y+1].at(x)==' ' || matrix[y+1].at(x)=='E')
                return true;
            break;
        case EAST:
            if(matrix[y].at(x+1)==' ' || matrix[y].at(x+1)=='E')
                return true;
            break;
        case WEST:
            if(matrix[y].at(x-1)==' ' || matrix[y].at(x-1)=='E')
                return true;
            break;
    }
    return false;
}

/**
Moves the current position indexes based on a pre-approved direction
**/
void make_valid_move(string *matrix, int &x, int &y, direction d)
{
    switch(d){
        case NORTH:
            y--;
            break;
        case SOUTH:
            y++;
            break;
        case EAST:
            x++;
            break;
        case WEST:
            x--;
            break;
    }
}

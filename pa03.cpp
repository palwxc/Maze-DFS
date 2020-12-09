#include "maze.h"

int main()
{
    int rows, xStart, yStart, mazeCounter=0;
    do{
        cin >> rows;
        if(rows>0)
        {
            string *myMaze = build_matrix(rows);
            fill_matrix(myMaze, rows);
            find_start(myMaze, rows, xStart, yStart);
            if(find_exit(myMaze, xStart, yStart))
            {
                cout << "Map " << mazeCounter << " -- Solution found:" << endl;
                print_matrix(myMaze, rows);
            }
            else
            {
                cout << "Map " << mazeCounter << " -- No solution found:" << endl;
                print_matrix(myMaze, rows);
            }
            mazeCounter++;
            delete_matrix(myMaze, rows);
        }
        else if(rows<0)
            cout << "Invalid parameter for rows entered." << endl;
    }while(rows!=0);
    return 0;
}


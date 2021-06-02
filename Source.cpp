//-----> ROLL NUMBER : L17-4027
//-----> ALI HAIDER
//-----> ASSIGNMENT# 2 
//-----> NOTE:- IT WORKS WITH GIVEN HEADER WHICH SHOWS EVERY STEP TAKEN TO FIND RIGHT PATH(GRAPHICS).

#include<iostream>
#include<conio.h>
#include<windows.h>
#include<fstream>
#include"Header.h"
using namespace std;
template<class T>
class StackADT
{
private:
	T* data;
	int count;
	int size;

public:

	//----> ISFULL

	bool isFull()
	{
		if (count == size)
			return true;
		return false;
	}

	//----> ISEMPTY

	bool isEmpty()
	{
		if (count == 0)
			return true;
		return false;
	}

	//----> PUSH

	bool Push(T val)
	{
		if (!isFull())
		{
			data[count] = val;
			count++;
			return true;
		}
		else
		{
			return false;
		}

	}

	//---->POP

	bool Pop(T &val)
	{
		if (!isEmpty())
		{
			count--;
			val = data[count];
			return true;
		}
		else
			return false;
	}

	//---->TOP

	bool Top(T &val)
	{
		if (Pop(val))
		{
			if (push(val))
			{
				return true;
			}
		}
		return false;
	}

	//---->CONSTRUCTOR

	StackADT()
	{
		size = 10;
		count = 0;
		data = new T[size];
	}

	//---->OVERLOADED

	StackADT(int size1)
	{
		size = size1;
		count = 0;
		data = new T[size];
	}

	//---->DESTRUCTOR

	~StackADT()
	{
		delete[]data;
	}
};

class Coordinate
{
public:
	int x;
	int y;

	Coordinate(int x1 = 0, int y1 = 0)
	{
		x = x1;
		y = y1;
	}

	void Print()
	{
		cout << x << " " << y;
	}
};

bool PathFinder(StackADT<Coordinate> &stack1, char** maze, int row, int col)
{
	int way = 0;

	//---> Look for an opening in the first row
	for (int i = 0; i < col; i++)
	{
		if (maze[0][i] == '-')
		{
			Coordinate temp(0, i);
			stack1.Push(temp);
			way = 1;
		}
	}

	//---> Looking for path in last row
	for (int i = 0; i < col; i++)
	{
		if (maze[row - 1][i] == '-')
		{
			Coordinate temp(row - 1, i);
			stack1.Push(temp);
			way = 1;
		}
	}

	//----> Looking for path in first colom
	for (int i = 0; i < row; i++)
	{
		if (maze[i][0] == '-')
		{
			Coordinate temp(i,0);
			stack1.Push(temp);
			way = 1;
		}
	}

	//----> Looking for path in last colom
	for (int i = 0; i < row; i++)
	{
		if (maze[i][col - 1] == '-')
		{
			Coordinate temp(i,col-1);
			stack1.Push(temp);
			way = 1;
		}
	}
	if (way == 1)
		return true;
	return false;
}

bool GameOverChecker(int X, int Y, int row, int col, int count)
{
	if (X == 0 && (Y >= 0 && Y <= col) && count >= 1)
	{
		return true;
	}

	if (X == row - 1 && (Y >= 0 && Y <= col) && count >= 1)
	{
		return true;
	}

	if (Y == 0 && (X >= 0 && X <= row - 1) && count >= 1)
	{
		return true;
	}

	if (Y == col-1 && (X >= 0 && X <= row - 1) && count >= 1)
	{
		return true;
	}

	return false;
}

void Print(char** maze,int row,int col)
{
	int x1 = 400, x2 = 410, y1 = 160, y2 = 170;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (maze[i][j] == '*')
				myRect(x1, y1, x2, y2, 255, 0, 0, 255, 0, 0);
			else
				myRect(x1, y1, x2, y2, 255, 255, 255, 255, 255, 255);

			x1 = x1 + 20;
			x2 = x2 + 20;
		}

		y1 = y1 + 20;
		y2 = y2 + 20;
		x1 = 400;
		x2 = 410;
	}
}
int main()
{

	//----> Part A and B
	StackADT<int> obj1(10);
	StackADT<char> obj2(10);

	cout << "\t\t\t\t\t\t~~~~~OUTPUT~~~~~\n";
	int newval;
	cout << obj1.Pop(newval);

	obj1.Push(1);
	obj1.Push(2);
	obj2.Push('3');
	obj1.Push(5);

	if (!obj1.isFull())
		obj1.Push(4);

	for (int i = 0; i < 6; i++)
	{
		obj1.Pop(newval);
		cout << newval;
	}

	//----------------->

	//----> MAZE SOLVER

	ifstream fin;
	fin.open("Maze.txt");

	int row = 0;
	int col = 0;

	fin >> row;
	fin >> col;

	//-----> ALLOCATION
	char** maze = new char*[row];

	for (int i = 0; i < row; i++)
		maze[i] = new char[col];

	//----> POPULATE

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			fin >> maze[i][j];
		}
	}

	Print(maze, row, col);
	Sleep(1000);

	//----> PATH FINDING
	StackADT<Coordinate>stack1;
	int count = 0;
	int way = 0;
	int path = 0;

	if (PathFinder(stack1, maze, row, col))
	{
		while (!stack1.isEmpty())
		{
			Coordinate temp;
			stack1.Pop(temp);

			int X = temp.x;
			int Y = temp.y;

			int X1 = 0;
			int Y1 = 0;

			if (Y != col - 1) {
				if (maze[X][Y + 1] == '-')
				{
					X1 = X;
					Y1 = Y + 1;
					Coordinate temp(X, Y + 1);
					stack1.Push(temp);

					path = 1;
					count++;
					//maze[X][Y] = '*';
				}
			}

			if (Y != 0) {
				if (maze[X][Y - 1] == '-')
				{
					X1 = X;
					Y1 = Y - 1;
					Coordinate temp(X, Y - 1);
					stack1.Push(temp);
					path = 1;
					count++;
					//maze[X][Y] = '*';
				}
			}

			if (X != row - 1) {
				if (maze[X + 1][Y] == '-')
				{
					X1 = X+1;
					Y1 = Y;
					Coordinate temp(X + 1, Y);
					stack1.Push(temp);

					path = 1;
					count++;
					//maze[X][Y] = '*';
				}
			}

			if (X != 0) {
				if (maze[X - 1][Y] == '-')
				{
					X1 = X-1;
					Y1 = Y;
					Coordinate temp(X - 1, Y);
					stack1.Push(temp);

					path = 1;
					count++;
					//maze[X][Y] = '*';
				}
			}

			if (path == 0)
			{
				count = 0;
			}

			if (path == 1)
			{
				path = 0;
			}

			maze[X][Y] = '*';


			Print(maze, row, col);
			Sleep(1000);
		

			if (GameOverChecker(X1, Y1, row, col, count))
			{
				way = 1;
				cout << "\n\nYES THERE IS A WAY OUT!";
				break;
			}
		}
	}

	if (way == 0)
	{
		cout << "\n\nNO WAY!";
	}
	_getch();

}
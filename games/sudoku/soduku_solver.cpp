
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
bool row(int y,int x,int n);
bool column(int y,int x,int n);
bool square(int y,int x,int n);
void printBoard(int board[9][9]);
int board[9][9];

int main()
{
	int empty=0,numForTile=0; //row column temp
	bool canBeSolved=1;

	board[0][0] = 2;
	board[0][1] = 0;
	board[0][2] = 3;
	board[0][3] = 4;
	board[0][4] = 0;
	board[0][5] = 6;
	board[0][6] = 5;
	board[0][7] = 1;
	board[0][8] = 0;

	board[1][0] = 5;
	board[1][1] = 0;
	board[1][2] = 4;
	board[1][3] = 2;
	board[1][4] = 0;
	board[1][5] = 8;
	board[1][6] = 0;
	board[1][7] = 0;
	board[1][8] = 0;

	board[2][0] = 6;
	board[2][1] = 0;
	board[2][2] = 0;
	board[2][3] = 0;
	board[2][4] = 5;
	board[2][5] = 0;
	board[2][6] = 8;
	board[2][7] = 0;
	board[2][8] = 0;

	board[3][0] = 4;
	board[3][1] = 0;
	board[3][2] = 8;
	board[3][3] = 5;
	board[3][4] = 0;
	board[3][5] = 1;
	board[3][6] = 7;
	board[3][7] = 6;
	board[3][8] = 2;

	board[4][0] = 0;
	board[4][1] = 0;
	board[4][2] = 0;
	board[4][3] = 0;
	board[4][4] = 0;
	board[4][5] = 0;
	board[4][6] = 3;
	board[4][7] = 8;
	board[4][8] = 1;

	board[5][0] = 3;
	board[5][1] = 6;
	board[5][2] = 0;
	board[5][3] = 8;
	board[5][4] = 0;
	board[5][5] = 0;
	board[5][6] = 0;
	board[5][7] = 0;
	board[5][8] = 0;

	board[6][0] = 0;
	board[6][1] = 0;
	board[6][2] = 0;
	board[6][3] = 0;
	board[6][4] = 6;
	board[6][5] = 0;
	board[6][6] = 0;
	board[6][7] = 0;
	board[6][8] = 0;

	board[7][0] = 9;
	board[7][1] = 0;
	board[7][2] = 2;
	board[7][3] = 1;
	board[7][4] = 0;
	board[7][5] = 0;
	board[7][6] = 6;
	board[7][7] = 0;
	board[7][8] = 3;

	board[8][0] = 1;
	board[8][1] = 5;
	board[8][2] = 0;
	board[8][3] = 3;
	board[8][4] = 7;
	board[8][5] = 4;
	board[8][6] = 0;
	board[8][7] = 9;
	board[8][8] = 0;

	printBoard(board);

	
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(!board[i][j])
				empty++;
		}
	}
		
	
	while(empty && canBeSolved)
	{
		
		canBeSolved=0;
		for(int i=0;i<9;i++)
		{
			for(int j=0;j<9;j++)
			{
				if(board[i][j]!=0)//if tile has number (not empty)
					continue; //continue to next tile
				
				numForTile=0;
				for(int num=1;num<10;num++)//run from 1 to 9 because those are possible solutions for tile
				{
					if(row(i,j,num) && column(i,j,num) && square(i,j,num))//if num is not found in all 3
					{
						if(numForTile==0)
							numForTile=num;
							//then continue running on for num
						else
						{
							//if we found ANOTHER number that matches
							numForTile=0; //cancel solution
							break; // takes me back to j loop
						}
					}	
				}
				
				
				//we also get here when for num finishes
				if(numForTile!=0)//if number found for tile
				{
					board[i][j]=numForTile;
					canBeSolved=1;
					empty--;
				}
			}
		}
	}	
	if(!canBeSolved)
		cout << "It cannot be solved" << endl;
	else if(!empty)
			cout << "solved" << endl;
		cout << endl;
		printBoard(board);
	cout << endl;
}


void printBoard(int board[9][9])
{
	cout << "-------------------------------------------\n";
	for(int y=0; y<9; y++)
	{
		if(3 == y || 6 == y)
		{
			cout << "*************************************\n";
		}
		for(int x=0; x<9; x++)
		{
			if(3==x || 6 ==x)
			{
				cout << "* ";
			}
			
			cout << board[x][y] << " ";
		}
		cout << endl;
	}
}

bool column(int y,int x,int n)
{//returns if num is not in column
	for(int j=0;j<9;j++)
	{

		if(board[y][j]==n)
		{
			return 0;
		}	
	}
	return 1;
}
bool row(int y,int x,int n)
{//returns if num is not in row
	for(int i=0;i<9;i++)
	{
		if(board[i][x]==n)
			return 0;
	}
	return 1;
}
bool square(int y,int x,int n)
{//returns if number is not in square
	/*int row=ceil((y+1)/3.0);
	int column=ceil((x+1)/3.0);
	for(int i=(row-1)*3;i<((row-1)*3+3);i++)
		for(int j=(column-1)*3;j<((column-1)*3+3);j++)
		{
			if(board[i][j]==n)
				return 0;
		}*/
		
		
			//for blocks 3X3: set starting index using vars k,j
	int k=0;
	int j=0;
	if(x <= 2)
	{
		k = 0;
	}
	else if(x > 2 && x < 6)
	{
		k = 3;
	}
	else
	{
		k = 6;
	}
	
	if(y <= 2)
	{
		j = 0;
	}
	else if(y > 2 && y < 6)
	{
		j = 3;
	}
	else
	{
		j = 6;
	}
	
	for(int ol=k; ol< k+3; ol++)
	{ 
		for(int il =j; il<j+3; il++)
		{
			if(n == board[il][ol])
			{
				return 0;
			}
		}
		
	}
	
	return 1;
	//return 1;
}

/*
Name:			Nathanael Nading
Date:			10.09.2018
Description:	Ticket buying for a Tupolev Tu-154 plane.
*/

#include <iostream>
#include <string>

using namespace std;

/*
1.  You must keep the seating plan for your plane type.

2.  Your plane type must be indicated in your program description.

3.  You must present the seating plan for the user to choose a seat and show which seats are available and already sold.

4.  You must use 2 dimensional arrays for processing requests

5.  You must allow for a family to purchase more than one type of seat (parents in first-class and children in coach as an example)

6.  You must provide an opportuntiy to the user to change their mind on the seats before checking out.

7.  You must provide an itemized receipt.
*/

const int SIZEXF = 6;
const int SIZEYF = 3;

//function prototypes
void seatingF(char seatRec[SIZEXF][SIZEYF]);

int main()
{
	//variables
	int hold = 0;
	string userInput = " ";
	char userXChar = ' ';
	char userYChar = ' ';
	int userXInt = 0;
	int userYInt = 0;
	
	char seatRecF[SIZEXF][SIZEYF] = { ' ', '0', '0', '0', '0', ' ',
									  ' ', '0', '0', '0', '0', ' ',
									  '0', '0', '0', '0', '0', '0' };

	//user interaction
	cout << "Hello! What section would you like to order tickets from first?" << endl
		<< "(Please enter the number next to your choice)" << endl;
	cout << "	1.	First-Class" << endl
		<< "	2.	Business" << endl
		<< "	3.	Economy" << endl;
	cin >> userInput;

	if (userInput == "1")							//First-Class
	{
		cout << "Please enter the coordinates of your order." << endl
			<< "(Please enter 77 with to cancel)" << endl << endl;
		seatingF(seatRecF);
		cout << endl;
		cin >> userXChar >> userYChar;

		userXInt = userXChar - '0';
		userYInt = userYChar - '0';

		if (seatRecF[userXInt][userYInt] == 'X' || ' ')		//the seat is already taken
		{
			cout << "That seat is already taken; please take another one." << endl;
		}
		else if (seatRecF[userXInt][userYInt] == '0')	//the seat is available
		{
			cout << "Ticket bought." << endl;
			seatRecF[userXInt][userYInt] = 'X';
		}
		else if (userXInt == 7 && userYInt == 7)		//exit
		{

		}
		else											//Bubba
		{

		}

		cout << seatRecF[userXInt][userYInt];
	}//end if
	else if (userInput == "2")						//Business
	{

	}//end if
	else if (userInput == "3")						//Economy
	{

	}//end if
	else											//Bubba
	{

	}//end if

	cin >> hold;
	return 0;
}

//functions
void seatingF(char seatRec[SIZEXF][SIZEYF])
{
	cout << "	1 2 3	4 5 6" << endl;
	for (int y = 0; y < SIZEYF; y++)
	{
		cout << endl;
		cout << y + 1 << "	";
		for (int x = 0; x < SIZEXF; x++)
		{
			cout << seatRec[x][y];
			if (x == 2)
				cout << "	";
			else
				cout << " ";
		}
	}
}
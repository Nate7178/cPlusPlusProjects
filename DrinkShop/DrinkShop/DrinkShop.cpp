/*
Name: Nathanael Nading
Date: 09.20.2018
Description: Beverages Store
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

//constant variables
const double COFFEE = 3.12;						//price of coffee
const double TEA = 2.25;						//price of tea
const double SODA = 1.00;						//price of soda

//global variables
string answer = " ";							//records user input
int coffeeAmount = 0;							//records the amount of coffee bought
int teaAmount = 0;								//records the amount of tea bought
int sodaAmount = 0;								//records the amount of soda bought
int amount = 0;									//records the user input for amounts
int couponLoop = 0;								//loop for if the user selects item they hadn't bought
double subTotal = 0.0;							//records the subtotal
double couponCost = 0.0;						//stores the amount saved

//function prototypes
void order(int addOrSub);						//records adjustments to orders
void options(string question, string choice1,
	string choice2, string choice3, int exit);	//prints out questions and options
void receipt(string food, int amount,
	double cost);								//prints out the beginning of the reciept
void coupon(int amount, double cost);			//makes sure the user chooses a valid coupon option
void menu();									//stores the main code for the program

//main application
int main()
{
	menu();
	return 0;
}

//functions
void order(int addOrSub)						//records adjustments to orders
{
	int amountCheck = 0;
	switch (addOrSub)								//checks whether the user is buying or canceling
	{
		case 1:											//if the user is buying
		{
			if (answer == "1")								//coffee
			{
				subTotal += COFFEE * amount;					//records cost
				coffeeAmount += amount;							//records amount
			}
			else if (answer == "2")							//tea
			{
				subTotal += TEA * amount;						//records cost
				teaAmount += amount;							//records amount
			}
			else if (answer == "3")							//soda
			{
				subTotal += SODA * amount;						//records cost
				sodaAmount += amount;							//records amount
			}
			break;
		}
		case 2:											//if the user is cancelling
		{
			if (answer == "1")								//coffee
			{
				coffeeAmount -= amount;							//removes amount
				subTotal -= COFFEE * amount;					//adds cost
				if (coffeeAmount < 0)							//if they have less than 0 after cancelling
				{
					amountCheck = 0 - amount;						//records how much over the user went
					coffeeAmount = 0;								//sets their amount to 0
					subTotal += COFFEE * amountCheck;				//adds the cost extra cost back to the subtotal
				}	
			}
			else if (answer == "2")							//tea
			{
				teaAmount -= amount;							//removes amount
				subTotal -= TEA * amount;						//adds cost

				if (teaAmount < 0)								//if they have less than 0 after cancelling
				{	
					amountCheck = 0 - amount;						//records how much over the user went
					teaAmount = 0;									//sets their amount to 0
					subTotal += TEA * amountCheck;					//adds the cost extra cost back to the subtotal
				}
			}
			else if (answer == "3")							//soda
			{
				sodaAmount -= amount;							//removes amount
				subTotal -= SODA * amount;						//adds cost

				if (sodaAmount < 0)								//if they have less than 0 after cancelling
				{
					amountCheck = 0 - amount;						//records how much over the user went
					sodaAmount = 0;									//sets their amount to 0
					subTotal += SODA * amountCheck;					//adds the cost extra cost back to the subtotal
				}
			}
			break;
		}
	}//end switch
}

void options(string question, string choice1,
	string choice2, string choice3, int exit)				//prints out question and options
{
	int bubProof = 0;

	cout << question << endl						//asks the question
		<< "	1.		" << choice1 << endl		//provides choices
		<< "	2.		" << choice2 << endl
		<< "	3.		" << choice3 << endl;

	do
	{
		cin >> answer;									//records the answer

		bubProof = 0;									//allows the user to exit

		if (answer != "1" && answer != "2"
			&& answer != "3")							//if the user inputs an invalid option
		{
			bubProof = 1;								//prevents the user from exiting the loop
			cout << "Invalid option; please try again."
				<< endl;
		}

		if (answer == "9" && exit == 1)
			bubProof = 0;
	} while (bubProof == 1);						//in case the user inputs an invalid option

	cout << endl << endl;
}

void receipt(string food, int amount,
	double cost)								//prints out reciepts
{
	if (amount == 0)							//if the user didn't order any of this thing
	{}												//nothing is printed on the reciept
	else if (amount == 1)						//if the user ordered one thing
	{
		cout << food << "			$" << setw(7) << right << cost << endl;	//prints it on the reciept
	}
	else											//if the user ordered more than one thing
	{
		cout << food << "	x" << amount
			<< "		$"
			<< setw(7) << right
			<< cost * amount << endl;					//prints it on the reciept
	}

	subTotal += amount * cost;						//adds the cost to the subtotal
}

void coupon(int amount, double cost)			//determines if the coupon is used on an existing item
{
	if (amount <= 0)								//if the user has none of that item
	{
		cout << "Sorry, you can not choose that option;"
			<< "please try again." << endl;
		couponLoop = 0;									//prevents them from using the coupon on that.
	}
	else											//if the user has some of that item
	{
		couponCost = cost * .5;
		cout << "Coupon added to receipt. You saved $"
			<< couponCost << ".";
		couponLoop = 1;									//allows them to continue to the receipt
	}
}

void menu()										//stores the main code for the program
{
	//variables
	int cancelLoop = 0;								//to return to options after canceling
	int orderLoop = 0;								//to order more drinks
	int bubLoop = 0;								//in case the user enters an invalid option for amount
	bool coupon25 = false;							//records whether the user has used a coupon or not
	bool coupon50 = false;							//records whether user has used a coupon or not
	ifstream inFile;								//in order to use the file later
	string password = " ";							//stores the password to close the program
	string couponCode25 = " ";						//stores the coupon code for 25% off one item
	string couponCode50 = " ";						//stores the coupon code for 50% off the order
	string couponCodeUser = " ";					//stores the user's guess for the coupon code
	string hold = " ";								//to hold the screen at the end

	inFile.open("C:/Users/nnading265/Desktop/Beverages.txt");
	//opens the file which holds the coupon codes and passwords
	inFile >> couponCode25 >> couponCode50 >> password;
	//records the coupon codes and passwords

	//user interaction
	cout << "Hello! What would you like to order? Enter the number next to your order." << endl
		<< "(You can enter 9 to advance to the final option)";

	do												//if the user wants multiple orders
	{
		options("", "Coffee	$3.12",
			"Tea	$2.25",
			"Soda	$1.00", 1);							//gives food options

		if (answer != "9")								//if the user is ordering something
		{
			cout << "How many cups would you like?" << endl;

			do
			{
				bubLoop = 0;								//in case the user enters an invalid option

				if (!(cin >> amount))							//if the user doesn't enter an integer
				{
					bubLoop = 1;									//keeps the user in the loop
					cin.clear();									//clears amount's value
					cin.ignore(10000, '\n');						//skips to the next line
					cout << "Invalid amount; please try again." << endl;
				}

			} while (bubLoop == 1);						//while the user doesn't enter an integer
			
			cout << endl << endl;

			order(1);									//records their order
		}

		do											//in case the user cancels
		{
			cout << "Serving(s) of Coffee:		 " << setw(7) << right << coffeeAmount
				<< endl
				<< "Serving(s) of Tea:		 " << setw(7) << right << teaAmount
				<< endl
				<< "Serving(s) of Soda:		 " << setw(7) << right << sodaAmount
				<< endl
				<< "Subtotal:			$" << fixed << setprecision(2) << setw(7) << right << subTotal
				<< endl << endl;
			//gives amount bought so far

			options("Would you like anything else?",
				"Pay", "Order More", "Cancel", 0);	//asks if they want to do anything else

			if (answer == "1")						//pay
			{
				if (coffeeAmount == 0 && teaAmount == 0 && sodaAmount == 0)
				{										//if the user hasn't ordered anything
					cout << "Please order something else in order to pay.";
					cancelLoop = 1;							//returns them to the beginning of the program
					orderLoop = 0;
				}
				else
				{
					cout << endl << endl;
					cancelLoop = 1;							//skips outside of the two outside loops
					orderLoop = 1;
				}				
			}
			else if (answer == "2")					//order more
			{
				cout << endl << endl;
				cout << "What would you like to order now?" << endl
					<< "(You can enter 9 to advance to the final option)";
				cancelLoop = 1;							//returns to the beginning of the function
				orderLoop = 0;
			}
			else if (answer == "3")					//cancel
			{
				options("Which drink would you like to cancel?",
					"Coffee", "Tea", "Soda", 0);		//asks them what they want to cancel

				cout << "How many cups would you like to remove from your order?" << endl;
				cin >> amount;							//records how much they want to remove from their option

				order(2);								//removes their order

				cancelLoop = 0;							//returns to "what would you like to do?"
			}
		} while (cancelLoop == 0);
	} while (orderLoop == 0);

	cout << "Would you like to use a coupon?" << endl
		<< "(If yes, enter your code; if no, enter anything)" << endl;
	cin >> couponCodeUser;						//records the user's code guess

	if (couponCodeUser == couponCode50)				//if they have the 50% off coupon
	{
		do
		{
			options("Which item would you like to use your coupon on?",
				"Coffee", "Tea", "Soda", 0);				//asks them which item they want to use their coupon on

			if (answer == "1")								//coffee
				coupon(coffeeAmount, COFFEE);					//records their choice
			else if (answer == "2")							//tea
				coupon(teaAmount, TEA);							//records their choice
			else if (answer == "3")							//soda
				coupon(sodaAmount, SODA);						//records their choice
		} while (couponLoop == 0);						//in case it's used on an item they didn't buy
		coupon50 = true;								//records they have that coupon
	}
	else if (couponCodeUser == couponCode25)		//if they have the 25% coupon
	{
		cout << "25% has been taken off the total bill.";
		coupon25 = true;								//records they have the coupon
	}
	else											//if they don't have a coupon
	{
		cout << "No coupon detected.";
	}

	cout << endl << endl << endl;

	subTotal = 0.0;								//resets the subtotal

	receipt("COFFEE", coffeeAmount, COFFEE);	//records and prints
	receipt("TEA", teaAmount, TEA);				//the recieipt and
	receipt("SODA", sodaAmount, SODA);			//subtotal

	cout << endl;

	cout << "SUBTOTAL:		$" << setw(7) << right << subTotal << endl;

	if (coupon25 == true)						//if they have a 25% coupon
	{
		couponCost = subTotal * .25;				//records the coupon
		
		cout << "COUPON DISCOUNT:	-$" << setw(7) << right << couponCost << endl;
	}
	else if (coupon50 == true)					//if they have the 50% coupon
	{
		cout << "COUPON DISCOUNT:	-$" << setw(7) << right << couponCost << endl;
	}

	cout << "TAX:			$" << setw(7) << right << subTotal * .08 << endl;
	cout << "TOTAL:			$" << setw(7) << right << subTotal * .08 + (subTotal - couponCost) << endl;
	//prints the rest of the reciept

	do
	{
		cin >> hold;								//waits until the person in charge closes the program
	} while (hold != password);

	inFile.close();								//closes the file
}
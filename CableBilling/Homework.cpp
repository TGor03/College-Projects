#include <iostream> 
#include <iomanip>
using namespace std;
//Named constants - residential customers 
const double RES_BILL_PROC_FEES = 4.50;
const double RES_BASIC_SERV_COST = 20.50;
const double RES_COST_PREM_CHANNEL = 7.50;

//Named constants - business customers 
const double BUS_BILL_PROC_FEES = 15.00;
const double BUS_BASIC_SERV_COST = 75.00;
const double BUS_BASIC_CONN_COST = 5.00;
const double BUS_COST_PREM_CHANNEL = 50.00;

int main() {
	//Variable declaration
	int accountNumber;
	char customerType;
	int numOfPremChannels;
	int numOfBasicServConn;
	double amountDue;

	cout << fixed << showpoint; cout << setprecision(2); //To output floating-point numbers in a fixed decimal format with a decimal point and trailing zeros, set the manipulators fixed and showpoint. 
	//Also, to output floating-point numbers with two decimal places, set the precision to two decimal places.
	//Recall that to use these manipulators, the program must include the header file iomanip.

	cout << "This program computes a cable bill." << endl;

	cout << "Enter account number (an integer): "; // Prompt the user to enter the account number.
	cin >> accountNumber; // Get the customer account number.
	cout << "Enter customer type R or r(Residential), B or b (Business): "; // Prompt the user to enter the customer code.
	cin >> customerType; // Get the customer code.
	cout << endl;

	switch (customerType) {
	case 'r':
	case 'R': // If the customer code is r or R,
		cout << "Enter the number of premium channels: "; // Prompt the user to enter the number of premium channels.
		cin >> numOfPremChannels; // Prompt the user to enter the number of premium channels.
		cout << endl;
		amountDue = RES_BILL_PROC_FEES + RES_BASIC_SERV_COST + numOfPremChannels * RES_COST_PREM_CHANNEL; // Calculate the billing amount.
		cout << "Account number: " << accountNumber << endl; // Print the account number and the billing amount.
		cout << "Amount due: $" << amountDue << endl;
		break;
	case 'b':
	case 'B': // If the customer code is b or B,
		cout << "Enter the number of basic service connections: "; // If the customer code is b or B,
		cin >> numOfBasicServConn; // Get the number of basic service connections.
		cout << endl;
		cout << "Enter the number of premium channels: "; // Prompt the user to enter the number of premium channels.
		cin >> numOfPremChannels; // Prompt the user to enter the number of premium channels.
		cout << endl;

		//Print the account number and the billing amount.
		if (numOfBasicServConn <= 10) amountDue = BUS_BILL_PROC_FEES
			+ BUS_BASIC_SERV_COST
			+ numOfPremChannels *
			BUS_COST_PREM_CHANNEL;
		else
			amountDue = BUS_BILL_PROC_FEES
			+ BUS_BASIC_SERV_COST
			+ (numOfBasicServConn - 10) *
			BUS_BASIC_CONN_COST
			+ numOfPremChannels *
			BUS_COST_PREM_CHANNEL;
		cout << "Account number: " << accountNumber << endl;
		cout << "Amount due : $" << amountDue << endl;
		break;
	default: // If the customer code is something other than r, R, b, or B, output an error message.
		cout << "Invalid customer type." << endl;
	}
}
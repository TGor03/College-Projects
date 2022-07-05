// Title: 
// Name: Trenton Gorman
// Date: 
// Description: 
#include <iostream>
#include <fstream>
using namespace std;


//Named constants
const int NO_OF_TESTS = 3;

int main()
{
	//Declare variables
	string fName, lName;
	double test1, test2, test3, average;
	
	//Declare your file stream variables...
	ifstream inData;
	ofstream outData;

	//Opening the files
	inData.open("test_scores.txt");
	outData.open("results.txt");

	//Read data from your file
	inData >> fName >> lName;
	inData >> test1 >> test2 >> test3;

	//Calculate the average
	average = (test1 + test2 + test3) / NO_OF_TESTS;

	//Output

	//Write program title and description to file
	outData << "EXAM AVERAGE PROGRAM" << endl << endl;
	outData << "This program will find the average of 3 test scores." << endl << endl;

	outData << "Name: " << fName << " " << lName << endl;

	outData << "Test 1: " << test1 << endl;
	outData << "Test 1: " << test1 << endl;
	outData << "Test 1: " << test1 << endl;

	outData << "Average test score: " << average << endl << endl;

	return 0;
}

// Title: Better summer job 
// Name: Trenton Gorman
// Date: 4/1/22
// Description: Calculates summer job budgets for multiple users

/*Shopping list
Buy bigger brain
Just completely remove the tax rate defines
Fix or remove whatever you were doing with the percent form idea
Call doctor to lower adhd medicine cause you hyperfixated on one program and wasted two hours of your life
Actually write unit tests this is too big of a program to not have them
Ctrl+A then backspace and make this simpler cause there is no way your teacher wants to grade this
Remove all the reminder comments before submitting
Check to make sure your passing by reference not copying
Add ten million more checks cause this is so flimsy
Actually check if entered string is the type of what you want instead of just continuing blindly
*/

#include <iostream>// Input output stream
#include <string>  // Char arrays are always going to be buffer overflows with how forgetful you are
#include <iomanip> // Input output manipulators
#include <vector>  // Safe lists because I am too lazy to make my own linked list implementation
using namespace std;

// Not sure if allowed to use headers so everything is just in the main file
//NOTE: All instances of macros will be replaced on compile
#define DASHBREAK(x)	for(int i=0; i<x; i++){ std::cout << '-';}; std::cout << endl; // Just displays a set amount of dashes 
#define CLEARSCREEN() 	system("cls");
#define WAITFORENTER()	system("pause"); // TODO: Make platform agnostic
#define COLWIDTH		50
// Just comment this out if for some reason you switch to user defined tax rates
#define TAXRATE			15

// Simple enum just to make it a bit more readable
enum class BudgetType {
	BudgetShopping,
	BudgetEntertainment,
	BudgetSavings,
	BudgetCustom // Not necessary for assignment but its really late and I want to show that I put effort into it
};

// Represents a item in the budget rate list
struct BudgetItem {
	BudgetType type;
	double rate;
	string label;
};

// Represents a collection of rates
struct BudgetRates {
	vector< BudgetItem > rate_list;

	// Tax rate is only ever accessed from here, so you could easily change tax rate per user but we dont need that right now.

#ifdef TAXRATE
	//NOTE: ONLY USE THIS REFERENCE TO TAX RATE DO NOT USE THE DEFINE
	double tax_rate = TAXRATE;
#else
	double tax_rate = 0;
#endif

	//									   ---------------These are optional arguments--------------------
	bool add_budgeted_item(double _rate, BudgetType _type = BudgetType::BudgetCustom, string _label = "") {
		rate_list.push_back(BudgetItem{ _type, _rate, _label }); // Place a new budgetitem in the list. Declarative initalizer for a new budget item object
		if (rate_leftover() < 0) { // Check if someone put rates in that go over 100
			rate_list.pop_back(); // Remove the last added budget item off the list
			cout << "Invalid rate input" << endl;
			cout << "Percent leftover - %" << rate_leftover() << endl;
			return false;
		}
		return true;
	}

	double rate_leftover() {
		if (rate_list.size() == 0) return percent_form ? 100 - tax_rate : 1 - tax_rate;
		double _total = 0;
		_total += tax_rate;
		for (BudgetItem _item : rate_list) {
			_total += _item.rate;
		}
		return percent_form ? 100 - _total : 1 - _total;
	}

	// Optional argument, just for later compatibility, allows user to specify if percent or decimal form is used
	BudgetRates(bool _form = true) {
		percent_form = _form;
	}
private:
	bool percent_form = true; // By default percent form is true
};


//TODO: Rework struct in a way that avoids having to manually print out name, total pay, and taxes
struct User {
	string name;
	BudgetRates userRates = BudgetRates(); // Call constructor to set percent form, just uses default value of true
	double total_pay;

	//REWORK
	void display_budget() {

		/*FUNCNOTE: Right now you are adding 4 to every single setw call when printing integer cause setprecision
		is truncating decimal places but if you get the string length to fit it in the columns,
		you are getting the non truncated double length which destroys the column spacing*/

		// I am incredibly lazy and do not want to make unit tests so basic error checking it is
		if (!check_rates_valid()) {
			cout << "Invalid budget rate defined." << endl;
			throw std::invalid_argument("Recieved bad budget rates."); //Worst case scenario
		}

		// No exponents and locked to precision length, setw from the left, and set decimal precision to two places
		cout << fixed << left << showpoint << setprecision(2);

		// Calculate tax payment
		double taxes = (userRates.tax_rate / 100) * total_pay;

		cout << setw(COLWIDTH - name.length()) << "Name: " << name << endl;
		cout << setw(COLWIDTH + 4 - to_string(total_pay).length()) << "Wages: " << total_pay << endl;
		cout << setw(COLWIDTH + 4 - to_string(taxes).length()) << "Taxes: " << taxes << endl;

		//TODO: Make this all dependent on percent form value instead of just assuming we are using percent form
		double remainder = total_pay * (1 - userRates.tax_rate / 100);
		//TODO: Make a reusable iterator since i do this multiple times throughout the program. Probably should just use a lambda
		//TODO: Completely remake this garbage

		// Loop through all user rates and then display the rate header
		for (auto& rate : userRates.rate_list) {
			double payment = (rate.rate / 100) * total_pay;
			remainder -= payment;
			string s = to_string(payment);
			cout << setw(COLWIDTH + 4 - to_string(payment).length());
			switch (rate.type) {
			case BudgetType::BudgetShopping:
				cout << "Shopping: ";
				break;
			case BudgetType::BudgetEntertainment:
				cout << "Entertainment: ";
				break;
			case BudgetType::BudgetSavings:
				cout << "Savings: ";
				break;
			case BudgetType::BudgetCustom:
				cout << rate.label + ": ";
				break;
			}
			// Display the rate itself
			cout << payment << endl;
		}

		// Show Remainder
		cout << setw(COLWIDTH + 4 - to_string(remainder).length()) << "Remainder: " << remainder << endl;

	}
private:
	//REWORK
	bool check_rates_valid() {
		return userRates.rate_leftover() >= 0;
	}
};

//TODO: This definitely could be cleaned up quite a bit
void add_user(vector<User>* userlist) {
	User newuser;
	double current_item_rate;
	string current_item_label;
	char continuechar;

	cout << "Please input your full name - ";
	getline(cin, newuser.name); // Newline absolutely has to be cleared before we can get this because it will just put a blank name
	cout << "What is your total wage - ";
	cin >> newuser.total_pay;


	// This is litterally useless and not at all part of the assignment but past you is not a bright bulb
#ifdef TAXRATE
	CLEARSCREEN();
	//Warn users cause your friends complained about being confused at why they only could budget 85% when you forced them to test it
	cout << "Please note that tax rate is already set to %" << TAXRATE << endl;
	cout << "So you only have %85 left to budget." << endl;
	WAITFORENTER();
	CLEARSCREEN();
#else
	CLEARSCREEN();
	cout << "Please set your tax rate %" << endl;
	cin >> newuser.userRates.tax_rate;
	CLEARSCREEN();
#endif

	do {
		int selection;
		CLEARSCREEN();
		cout << "Rate Input Tool" << endl;
		DASHBREAK(50);

		//Display budget menu
		cout << "!!!What is left of the budget!!! - %" << newuser.userRates.rate_leftover() << endl;
		cout << "Please select the type of budget item you would like to add" << endl;
		cout << "	1 - Shopping" << endl;
		cout << "	2 - Entertainment" << endl;
		cout << "	3 - Savings" << endl;
		cout << "	4 - Custom" << endl;
		cout << "Selection: ";
		cin >> selection;
		cin.ignore();
		cout << endl;

		//REWORK
		//There is definetly a better way to do this
		switch (selection) {
		case 1:
			cout << "Shopping budget percentage: %";
			cin >> current_item_rate;
			newuser.userRates.add_budgeted_item(current_item_rate, BudgetType::BudgetShopping);
			break;
		case 2:
			cout << "Entertainment budget percentage: %";
			cin >> current_item_rate;
			newuser.userRates.add_budgeted_item(current_item_rate, BudgetType::BudgetEntertainment);
			break;
		case 3:
			cout << "Savings budget percentage: %";
			cin >> current_item_rate;
			newuser.userRates.add_budgeted_item(current_item_rate, BudgetType::BudgetSavings);
			break;
		case 4:
		default:
			cout << "Custom budget percentage: %";
			cin >> current_item_rate;
			cin.ignore();
			cout << "Custom budget label: " << endl;
			getline(cin, current_item_label);
			newuser.userRates.add_budgeted_item(current_item_rate, BudgetType::BudgetCustom, current_item_label);
			break;
		}

		//There is probably a cleaner more complicated way to do this but thats a future me problem
		if (newuser.userRates.rate_leftover() == 0) {
			CLEARSCREEN();
			cout << "You have filled out your budget. Press enter to continue." << endl;
			WAITFORENTER();
			break;
		}

		cout << "Add another budget item? (Y/n)" << endl;
		cin >> continuechar;
	} while (continuechar == 'y');

	userlist->push_back(newuser);
}

int main() {
	vector<User> users;
	char selection;

#ifndef TAXRATE
	cout << "Budget calculator" << endl;
#else
	cout << "Budget calculator with set tax rate %" << TAXRATE << endl;
#endif
	DASHBREAK(50);

	//Just keep adding users till prompted to stop
	while (true) {
		add_user(&users);
		cout << "Add another user? (Y/n)" << endl;
		cin >> selection;
		if (selection == 'n') break;
		cin.ignore();
	}

	//Display all the budgets
	CLEARSCREEN();
	cout << "Budget List" << endl;
	DASHBREAK(50);
	for (auto& user : users) {
		user.display_budget();
		DASHBREAK(50);
	}
	WAITFORENTER();
}

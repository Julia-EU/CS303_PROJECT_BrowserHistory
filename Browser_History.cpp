#include <iostream>
#include <string>
#include "History_Functions.h"
#include <fstream>
using namespace std;

//**** Comments on Method functionality are in History_Functions.cpp file ****
//
//This program maintains a history of web pages visited by user
//Primary function - ADD, REMOVE, DISPLAY PAGES
//Additional functions - 1) Read/Save pages From/To file
					// - 2) Clear history
					// - 3) Search history


int main() {

	History Web;
	bool browsing = true;

	while (browsing == true) {

		string choice;
		string options = "1234567";
		cout << "\nWelcome to The JULIA BROWSER" << endl;
		cout << "\n1) Visit web page (add)" << endl;
		cout << "2) View browser history" << endl;
		cout << "3) Delete web page from history" << endl;
		cout << "4) Clear browser history" << endl;
		cout << "5) Search browser history" << endl;
		cout << "6) Save browser history to file" << endl;
		cout << "7) Quit" << endl;

		cout << "\nPlease enter a valid choice from 1 - 7" << endl;
		cin >> choice;

		while (choice.size() > 1 || !ValidMenuSelection(choice)) {
			cout << "\nPlease enter a valid choice from 1 - 7" << endl;
			cin >> choice;
		}
		cout << endl;

		char ch = choice[0];


		if (ch == '1') {

			string selection;

			cout << "Would you like to visit a new webpage or load browser history from file?: " << endl;
			cout << "1) Input page\n2) Load from file";

			while (selection.size() > 1 || selection[0] != '1' && selection[0] != '2') {
				cout << "\nPlease enter a valid selection between 1 & 2: ";
				cin >> selection;
			}

			if (selection[0] == '2') {
				cout << endl;
				ReadHistory(Web);
				cout << "\nYour current web history is as follows: " << endl;
				Web.DISPLAY_PAGES();
			}

			else {
				bool valid_entry = true;
				string webpage;
				cout << "\nPlease enter a URL to visit (No Spaces. Anything after the first space will be ignored): " << endl;
				cin >> webpage;

				for (int i = 0; i < webpage.size(); i++) {
					if (isspace(webpage[i])) {
						cout << "\nThere is a space in your URL. Unable to visit page" << endl;
						valid_entry = false;
						break;
					}
				}

				if (valid_entry) {
					Web.ADD(webpage);
				}

				else {
					break;
				}
			}

		}

		else if (ch == '2') {

			cout << "Here are the pages you've visited, from most recent to least recent:" << endl;
			Web.DISPLAY_PAGES();

		}

		else if (ch == '3') {

			string index;
			string integer = "0123456789";
			cout << "Please enter the index of the page you would like to delete from your history" << endl;
			cout << "(Hint: Observe your history. The index is the position of the webpage from the top starting at 0)\n---> ";
			cin >> index;

			while (!ValidIndex(index)) {
				cout << "\nPlease enter a valid integer" << endl;
				cin >> index;
			}

			bool removed = Web.REMOVE(stoi(index));

			if (removed) {
				cout << "The webpage at that index has been removed from your history" << endl;
			}

		}

		else if (ch == '4') {

			Web.CLEAR();
			if (Web.empty()) {
				cout << "Your secrets are safe now..." << endl;
			}

			else {
				cout << "ERROR: could not clear browser history" << endl;
			}
		}

		else if (ch == '5') {

			string searchTerm;
			cout << "Please input a web URL or search term to look for:  ";
			cin >> searchTerm;
			cout << endl;
			Web.SEARCH(searchTerm);

		}

		else if (ch == '6') {

			SaveHistory(Web);

		}

		else if (ch == '7') {

			browsing = false;
			cout << "Thank you for using JULIA BROWSER. Bye for now!" << endl;
			break;
			

		}

	}

}
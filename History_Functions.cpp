#include "History_Functions.h"


//add to front of list
void History::ADD(string LINK) {

	Node* tempNode = new Node;
	tempNode->data = LINK;
	tempNode->nextPtr = nullptr;
	if (head == nullptr) { //if list is empty, set head to input node 
		head = tempNode;
		tail = tempNode;
	}
	else {
		tempNode->nextPtr = head; //Set input node next pointer to point to current head, and set head to input node
		head = tempNode;
	}

	num_Pages += 1;
}

//add to back of list
void History::push_back(string n) {
	Node* tempNode = new Node;
	tempNode->data = n;
	tempNode->nextPtr = nullptr;
	if (head == nullptr) {
		head = tempNode;
		tail = tempNode;
	}
	else {
		tail->nextPtr = tempNode;  //Set tail pointer next pointer to input node
		tail = tempNode;
	}

	num_Pages += 1;
}

//remove front of list
void History::pop_front() {
	Node* tempNode = new Node;

	if (head == nullptr) {
		cout << "The list is empty";
		return;
	}
	else {
		//Set input node to the top item in list and set point first item node to next pointer.
		tempNode = head; 
		head = head->nextPtr;
		//Delete the input node containing first item and set to null
		delete tempNode;
		tempNode = nullptr;
	}

	num_Pages -= 1; 
}

//remove back of list
void History::pop_back() {
	Node* tempNode = new Node;

	if (head == nullptr) {
		cout << "The list is empty";
		return;
	}
	if (head->nextPtr == nullptr) {
		delete head;  //if only one item in list, delete first item node and set to null
		head = nullptr;
		return;
	}

	//Else, set input node to first item and traverse list until second to last node
	tempNode = head;

	while (tempNode->nextPtr->nextPtr != nullptr) {
		tempNode = tempNode->nextPtr;
	}

	delete tempNode->nextPtr; //delete second to last node's next pointer (or last node)
	tempNode->nextPtr = nullptr;
	tail = tempNode; //set tail to input node as it is now last node

	num_Pages -= 1;
	return;

}


//return top item in list
string History::front() {
	Node* tempNode = new Node;

	if (head == nullptr) {
		cout << "This list is empty";
	}
	else {
		tempNode = head;
		return tempNode->data;
	}
}

//return last item in list
string History::back() {
	Node* tempNode = new Node;

	if (head == nullptr) {
		cout << "This list is empty";
	}
	else {
		tempNode = head;

		while (tempNode->nextPtr != nullptr) { //Traverse list until last node, return node
			tempNode = tempNode->nextPtr;
		}

		return tempNode->data;

	}
}

//check if empty (i.e. if first item pointer is null)
bool History::empty() {
	return (head == nullptr);
}


//insert item at specific index
void History::insert(size_t index, const string& value) {
	if (index > (num_Pages - 1)) { //if index entry is greater than index size of list
		cout << "Index out of range. Item has been added to back of list\n";
		push_back(value);
	}

	else if (index == 0) {
		ADD(value); //if list is empty, add to list as first item 
	}

	else {
		Node* currNode = head; //node to traverse list till index
		Node* insertNode = new Node; //node to be inserted at index
		insertNode->data = value;
		insertNode->nextPtr = nullptr;
		Node* prevNode = new Node; //Node with next pointer pointing to index node (or previous node)

		int count = 0;
		while (count < index) {
			prevNode = currNode;
			currNode = currNode->nextPtr;
			count += 1;
		}

		prevNode->nextPtr = insertNode; //set previous node next pointer to inserted node
		insertNode->nextPtr = currNode; //set inserted node next pointer to node previously at index

		num_Pages += 1;
	}
	return;
}

//delete item at index 
bool History::REMOVE(size_t index) {
	if (index > (num_Pages - 1)) {
		cout << "Index out of range.\n";
		return false;
	}

	else if (index == (num_Pages - 1)) {
		pop_front();
		return true;
	}

	else {
		Node* delNode = head;
		Node* prevNode = new Node;

		int count = 0;
		while (count < index) {
			prevNode = delNode;
			delNode = delNode->nextPtr;
			count += 1;
		}

		prevNode->nextPtr = delNode->nextPtr;
		delete delNode;
		delNode = nullptr;

		num_Pages -= 1;
		return true;
	}
}

//search for web page or suggested web pages based on search term
void History::SEARCH(string value) {
	vector<string> searchlinks;
	Node* tempNode = head;
	int count = 0;
	while (tempNode != nullptr) { //Traverse list and print items until tail node's next pointer (or null node)
		size_t found = tempNode->data.find(value);//search for term in each node string
		if (found != string::npos) {//if index of search term is not out of range, then the current node contains the term
			searchlinks.push_back(tempNode->data); //add node string (or web page) to vector, in case there are more than one
			count += 1;
		}
		tempNode = tempNode->nextPtr;
	}
	if (count == 0) {
		cout << "You have not visited any pages with with this string of characters: '" << value << "'" << endl;
	}

	else {//print webpages in vector
		cout << "You could be looking for the following page(s): " << endl;
		for (int i = 0; i < searchlinks.size(); i++) {
			cout << ">  " << searchlinks[i] << endl;
		}
	}
}

//print pages
void History::DISPLAY_PAGES() {
	Node* tempNode = head;

	while (tempNode != nullptr) {
		cout << tempNode->data << endl;
		tempNode = tempNode->nextPtr;
	}
	cout << " TOT ----- " << num_Pages << endl;

}

//clear list
void History::CLEAR() {
	Node* DelNode = head;
	int count = num_Pages; //set count to number of items in list for iteration 

	while (count != 1) {
		pop_back(); //iterate and delete last node until one item left
		count -= 1;
	}

	if (count == 1) {
		pop_front(); //delete final item
	}

	cout << "Your browser history is clear!" << endl;
}

//read words (or webpages) from file according to space delimination 
void ReadHistory(History &Pagelist) {

	ifstream inFile;
	string choice;
	cout << "Do you want to enter a file name or use sample file?" << endl;
	cout << "1)Input '1' to enter file name\n2)Input '2' to use sample file" << endl;
	cin >> choice;
	while (choice.size() > 1 || choice[0] != '1' && choice[0] != '2') {
		cout << "\nPlease enter a valid choice between 1 & 2" << endl;
		cin >> choice;
	}

	if (stoi(choice) == 1) {
		string file;
		cout << "Please enter a valid file name ending with '.txt' (e.g. samplereadfile.txt): "; 
		cin >> file;
		inFile.open(file);
		if (!inFile.is_open()) { //exit if error opening file
			cout << "Could not open file" << endl;
			return;
		}
	}

	else {
		inFile.open("samplepages.txt");
		if (!inFile.is_open()) {
			cout << "Could not open file" << endl;
			return;
		}
	}

	string Word;
	while (inFile >> Word) {//steam each string word from file into list
		Pagelist.ADD(Word);
	}

	inFile.close();

}

//Save browser history to text file from list
void SaveHistory(History &Pagelist) {//friend function of History class so as to access pointer functionality within class item

	int Filesize = Pagelist.num_Pages;
	History tempList;
	ofstream outFile;
	string file;

	cout << "Please enter a valid file name ending with '.txt' (e.g. samplesavefile.txt): ";
	cin >> file;
	outFile.open(file);
	if (!outFile.is_open()) {
		cout << "Could not open file for saving" << endl;
		return;
	}

	Node* tempNode = Pagelist.head;

	while (tempNode != nullptr) {
		outFile << tempNode->data << endl;
		tempNode = tempNode->nextPtr;
	}
	outFile << " TOT ----- " << Pagelist.num_Pages << endl;

	cout << "Your file has been saved to current repository" << endl;

	outFile.close();
}

//validation functions for user choices in main
bool ValidMenuSelection(string str) {
	return str.find_first_not_of("1234567") == string::npos;
}

bool ValidIndex(string str) {
	return str.find_first_not_of("0123456789") == string::npos;
}
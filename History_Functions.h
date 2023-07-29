#pragma once
#include<iostream>
#include<conio.h>
#include<vector>
#include<fstream>
#include <string>

using namespace std;

//Linked list class for Web History

struct Node {
	string data;
	Node* nextPtr;
};

class History
{
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	string currentPage = " ";
	int num_Pages = 0;

public:
	//LinkList()
	//{
	//	head = nullptr;
	//	tail = nullptr;
	//}
	void ADD(string LINK);
	bool REMOVE(size_t index);
	void SEARCH(string value);
	void CLEAR();
	void DISPLAY_PAGES();
	void push_back(string n);
	void pop_front();
	void pop_back();
	string front();
	string back();
	bool empty();
	void insert(size_t index, const string& value);
	friend void SaveHistory(History &Pagelist);
};


void ReadHistory(History &Pagelist);
bool ValidMenuSelection(string str);
bool ValidIndex(string str);

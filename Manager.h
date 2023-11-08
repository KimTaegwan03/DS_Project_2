#pragma once
#include "SelectionTree.h"
#include "BpTree.h"

class Manager
{
private:
	char* cmd;
	BpTree* bptree;
	SelectionTree* stree;

public:
	Manager(int bpOrder)	//constructor
	{
		/* You must fill here */
		bptree = new BpTree(&flog,bpOrder);
		stree = new SelectionTree(&flog);
		cmd = new char[256];


	}


	~Manager()//destructor
	{
		/* You must fill here */
		delete bptree;
		delete stree;
		delete[] cmd;
	}

	ifstream fin;
	ofstream flog;
	

	void run(const char* command);
	bool LOAD();
	bool ADD();

	bool SEARCH_BP_BOOK(string book);
	bool SEARCH_BP_RANGE(string start, string end);

	bool PRINT_BP();
	bool PRINT_ST(int code);

	bool DELETE();

	void printErrorCode(int n);
	void printSuccessCode(string command);

};


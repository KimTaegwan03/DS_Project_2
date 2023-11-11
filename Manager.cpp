#include "Manager.h"
#include <cstdlib>

using namespace std;

void Manager::run(const char* command) 
{
	fin.open(command);
	flog.open("log.txt");
	if(!fin)
	{
		flog << "File Open Error" << endl;
		return;
	}
	while (!fin.eof())
	{
		/* You must fill here */

		fin.getline(cmd,256);

		int cnt = strlen(cmd);

		char* p = strtok(cmd,"\t ");

		if(!strcmp(p,"LOAD")){			// LOAD command
			if(!bptree->getRoot())
				LOAD();
			else
				printErrorCode(100);
		}
		else if(!strcmp(p,"ADD")){		// ADD command
			int blank = 0;
			for(int i = 0;i<cnt;i++){
				if(cmd[i] == '\t'){
					blank++;
				}
			}
			if(blank == 3)
				ADD();
			else
				printErrorCode(200);
		}
		else if(!strcmp(p,"SEARCH_BP")){	// SEARCH_BP command
			p = strtok(NULL,"");
			int len = strlen(p);
			int tab_cnt = 0;
			char* end = 0;
			for(int i = 0;i<len;i++){
				if(p[i]=='\t') {
					tab_cnt++;
					p[i] = '\0';
					end = &p[i+1];
				}
			}
			if(tab_cnt == 0){		// single SEARCH_BP
				SEARCH_BP_BOOK(p);
			}
			else if(tab_cnt == 1){	// range SEARCH_BP
				SEARCH_BP_RANGE(p,end);
			}
			else{
				printErrorCode(300);
			}
		}
		else if(!strcmp(p,"PRINT_BP")){	// PRINT_BP command
			if(bptree->getRoot())
				PRINT_BP();
			else
				printErrorCode(400);
		}
		else if(!strcmp(p,"PRINT_ST")){	// PRINT_ST command
			p = strtok(NULL,"\t ");
			PRINT_ST(atoi(p));
		}
		else if(!strcmp(p,"DELETE")){	// DELETE command
			if(stree->Delete())
				printSuccessCode("DELETE");
			else
				printErrorCode(600);
		}
		else if(!strcmp(p,"EXIT")){		// EXIT command
			printSuccessCode("EXIT");
			break;
		}
	}
	flog.close();
	fin.close();
	return;
}

bool Manager::LOAD()
{
	ifstream fbook;

	fbook.open("loan_book.txt");
	if(!fbook){
		printErrorCode(100);
	}
	while(!fbook.eof()){	// Parsing data and insert
		char* p;
		int code;
		LoanBookData* data = new LoanBookData();
		fbook.getline(cmd,256);

		p = strtok(cmd,"\t");	// Name

		data->setName(p);

		p = strtok(NULL,"\t");	// Code

		data->setCode(code = atoi((const char*)p));

		p = strtok(NULL,"\t");	// Author

		data->setAuthor(p);

		p = strtok(NULL,"\t");	// Year

		data->setYear(atoi((const char*)p));

		p = strtok(NULL,"\t");	// LoanCount

		data->setCount(atoi((const char*)p));

		bptree->Insert(data,stree);
		
	}
	printSuccessCode("LOAD");

	return true;
}

bool Manager::ADD()		// ADD data in bptree
{
	LoanBookData* data = new LoanBookData();
	
	char* p = strtok(NULL,"\t");	// Name

	data->setName(p);

	p = strtok(NULL,"\t");		// Code

	data->setCode(atoi((const char*)p));

	p = strtok(NULL,"\t");		// Author

	data->setAuthor(p);

	p = strtok(NULL,"\t");		// LoanCount

	data->setYear(atoi((const char*)p));

	data->setCount(0);

	flog<<"========ADD========\n";	// print ADD log
	if(data->getCode() == 0)
		flog<<data->getName()<<'/'<<"000"<<'/'<<data->getAuthor()<<'/'<<data->getYear()<<'\n';
	else
		flog<<data->getName()<<'/'<<data->getCode()<<'/'<<data->getAuthor()<<'/'<<data->getYear()<<'\n';
	flog<<"====================\n\n";

	bptree->Insert(data,stree);

	return true;
}

bool Manager::SEARCH_BP_BOOK(string book) 	// Search and print book data in bptree
{
	if(!bptree->searchBook(book)){
		printErrorCode(300);
	}
}

bool Manager::SEARCH_BP_RANGE(string s, string e)	// Search and print book data in bptree
{
	if(!bptree->searchRange(s,e)){
		printErrorCode(300);
	}
}

bool Manager::PRINT_BP() // Print all book data
{
	BpTreeNode* cur = bptree->getRoot();

	while(cur->getMostLeftChild()){		// Go to most left data node
		cur = cur->getMostLeftChild();
	}

	flog<<"========PRINT_BP========\n";
	while(cur){								// Print all data
		for(auto iter = cur->getDataMap()->begin(); iter != cur->getDataMap()->end();iter++){
			if(iter->second->getCode() != 0)
				flog<< iter->second->getName() << '/' << iter->second->getCode() << '/' << iter->second->getAuthor() << '/' << iter->second->getYear() << '/' << iter->second->getLoanCount() <<'\n';
			else
				flog<< iter->second->getName() << '/' << "000" << '/' << iter->second->getAuthor() << '/' << iter->second->getYear() << '/' << iter->second->getLoanCount() <<'\n';
			
		}
		cur = cur->getNext();
	}
	flog<<"========================\n\n";
	return 1;
}

bool Manager::PRINT_ST(int code) 	// Print all data in heap match the code
{
	if(!stree->printBookData(code)){
		printErrorCode(500);
	}
}

bool Manager::DELETE() 		// Delete root of selection tree
{
	printSuccessCode("DELETE");
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "========ERROR========" << endl;
	flog << n << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode(string command) {//SUCCESS CODE PRINT 
	flog << "========"<<command<<"========" << endl;
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}


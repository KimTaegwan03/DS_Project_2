#include "Manager.h"

void Manager::run(const char* command) 
{
	fin.open(command);
	if(!fin)
	{
		flog << "File Open Error" << endl;
		return;
	}
	while (!fin.eof())
	{
		/* You must fill here */

		fin.getline(cmd,256);

		if(!strcmp(cmd,"LOAD")){
			LOAD();
		}




	}	
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
	while(!fbook.eof()){
		char* p;
		LoanBookData* data = new LoanBookData();
		fbook.getline(cmd,256);

		p = strtok(cmd,"\t");	//name

		data->setName(p);

		p = strtok(NULL,"\t");

		data->setCode(atoi(p));

		p = strtok(NULL,"\t");

		data->setAuthor(p);

		p = strtok(NULL,"\t");

		data->setYear(atoi(p));

		p = strtok(NULL,"\t");

		data->setCount(atoi(p));

		bptree->Insert(data);

	}




	return true;
}

bool Manager::ADD()
{
	
	return true;
}

bool Manager::SEARCH_BP_BOOK(string book) 
{
	
}

bool Manager::SEARCH_BP_RANGE(string s, string e) 
{
	
}

bool Manager::PRINT_BP() 
{
	
}

bool Manager::PRINT_ST() 
{

}

bool Manager::DELETE() 
{

}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "=======================" << endl;
	flog << "ERROR " << n << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode() {//SUCCESS CODE PRINT 
	flog << "=======================" << endl;
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}


#include "Manager.h"
#include <cstdlib>

using namespace std;

void Manager::run(const char* command) 
{
	fin.open(command);
	flog.open("log.txt",ios::app);
	if(!fin)
	{
		flog << "File Open Error" << endl;
		return;
	}
	while (!fin.eof())
	{
		/* You must fill here */

		fin.getline(cmd,256);

		char* p = strtok(cmd,"\t");

		if(!strcmp(p,"LOAD")){
			LOAD();
		}
		else if(!strcmp(p,"PRINT_BP")){
			PRINT_BP();
		}
		else if(!strcmp(p,"SEARCH_BP")){
			p = strtok(NULL,"");
			int len = strlen(p);
			int tab_cnt = 0;
			for(int i = 0;i<len;i++){
				if(p[i]=='\t') tab_cnt++;
			}
			if(tab_cnt == 0){
				SEARCH_BP_BOOK(p);
			}
			else if(tab_cnt == 1){
				// Allocate char[2] make start end and do it
				char start[2];
				char end[2];

				start[0] = p[0];
				start[1] = '\0';

				end[0] = p[2];
				end[1] = '\0';

				SEARCH_BP_RANGE(start,end);
			}
			

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
	while(!fbook.eof()){
		char* p;
		LoanBookData* data = new LoanBookData();
		fbook.getline(cmd,256);

		p = strtok(cmd,"\t");	//name

		data->setName(p);

		p = strtok(NULL,"\t");

		data->setCode(atoi((const char*)p));

		p = strtok(NULL,"\t");

		data->setAuthor(p);

		p = strtok(NULL,"\t");

		data->setYear(atoi((const char*)p));

		p = strtok(NULL,"\t");

		data->setCount(atoi((const char*)p));

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
	if(!bptree->searchBook(book)){
		printErrorCode(300);
	}
}

bool Manager::SEARCH_BP_RANGE(string s, string e) 
{
	if(!bptree->searchRange(s,e)){
		printErrorCode(300);
	}
}

bool Manager::PRINT_BP() 
{
	BpTreeNode* cur = bptree->getRoot();

	while(cur->getMostLeftChild()){
		cur = cur->getMostLeftChild();
	}
	flog<<"========PRINT_BP========\n";
	while(cur){
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


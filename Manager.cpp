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

		if(!strcmp(p,"LOAD")){
			LOAD();
		}
		else if(!strcmp(p,"ADD")){
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
		else if(!strcmp(p,"PRINT_BP")){
			PRINT_BP();
		}
		else if(!strcmp(p,"PRINT_ST")){
			p = strtok(NULL,"\t ");
			PRINT_ST(atoi(p));
		}
		else if(!strcmp(p,"SEARCH_BP")){
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
			if(tab_cnt == 0){
				SEARCH_BP_BOOK(p);
			}
			else if(tab_cnt == 1){
				SEARCH_BP_RANGE(p,end);
			}
			else{
				printErrorCode(300);
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
		int code;
		LoanBookData* data = new LoanBookData();
		fbook.getline(cmd,256);

		p = strtok(cmd,"\t");	//name

		data->setName(p);

		p = strtok(NULL,"\t");

		data->setCode(code = atoi((const char*)p));

		p = strtok(NULL,"\t");

		data->setAuthor(p);

		p = strtok(NULL,"\t");

		data->setYear(atoi((const char*)p));

		p = strtok(NULL,"\t");

		data->setCount(atoi((const char*)p));

		

		if(!bptree->Insert(data)){
			LoanBookData* fullbook = bptree->searchDataNode(data->getName())->getDataMap()->find(data->getName())->second;
			//bptree->Delete();
			stree->Insert(fullbook);
			delete data;
			
		}
		
		
	}
	printSuccessCode();

	return true;
}

bool Manager::ADD()
{
	LoanBookData* data = new LoanBookData();
	
	char* p = strtok(NULL,"\t");	//name

	data->setName(p);

	p = strtok(NULL,"\t");

	data->setCode(atoi((const char*)p));

	p = strtok(NULL,"\t");

	data->setAuthor(p);

	p = strtok(NULL,"\t");

	data->setYear(atoi((const char*)p));

	data->setCount(0);

	flog<<"========ADD========\n";
	if(data->getCode() == 0)
		flog<<data->getName()<<'/'<<"000"<<'/'<<data->getAuthor()<<'/'<<data->getYear()<<'\n';
	else
		flog<<data->getName()<<'/'<<data->getCode()<<'/'<<data->getAuthor()<<'/'<<data->getYear()<<'\n';
	flog<<"====================\n\n";

	if(!bptree->Insert(data)){
		LoanBookData* fullbook = bptree->searchDataNode(data->getName())->getDataMap()->find(data->getName())->second;
		//bptree->Delete();
		stree->Insert(fullbook);
		delete data;
		
	}

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
	if(bptree->getRoot()==0){
		printErrorCode(400);
	}
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

bool Manager::PRINT_ST(int code) 
{
	if(!stree->printBookData(code)){
		printErrorCode(500);
	}
}

bool Manager::DELETE() 
{

}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "========ERROR========" << endl;
	flog << n << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode() {//SUCCESS CODE PRINT 
	flog << "========LOAD========" << endl;
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}


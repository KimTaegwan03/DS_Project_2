#include "Manager.h"

using namespace std;

int main() {
	// Manager manager(3); //value is order of bptree 
	// manager.run("command.txt");
	// return 0;








	LoanBookHeap STree;
	LoanBookData data1;
	LoanBookData data2;
	LoanBookData data3;
	LoanBookData data4;

	data1.setName("bb");
	data1.setCode(200);
	data1.setAuthor("b");
	data1.setYear(2023);
	data1.setCount(0);

	data2.setName("aa");
	data2.setCode(200);
	data2.setAuthor("a");
	data2.setYear(1999);
	data2.setCount(4);

	data3.setName("dd");
	data3.setCode(200);
	data3.setAuthor("b");
	data3.setYear(2023);
	data3.setCount(0);

	data4.setName("cc");
	data4.setCode(200);
	data4.setAuthor("a");
	data4.setYear(1999);
	data4.setCount(4);

	STree.Insert(&data1);

	cout<<STree.getRoot()->getBookData()->getName()<<endl;

	STree.Insert(&data2);

	cout<<STree.getRoot()->getBookData()->getName()<<endl;

	STree.Insert(&data3);

	cout<<STree.getRoot()->getBookData()->getName()<<endl;

	STree.Insert(&data4);

	cout<<STree.getRoot()->getBookData()->getName()<<endl<<endl;

}


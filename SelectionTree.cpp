#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData* newData) {
    LoanBookHeap* insert_heap = NULL;

    insert_heap = &heap[newData->getCode()/100];

    insert_heap->Insert(newData);

    if(insert_heap->getRoot()->getBookData() == newData){
        reStruct();
    }

    return 1;

}

bool SelectionTree::Delete() {
    //root->getHeap()->
}

bool SelectionTree::printBookData(int bookCode) {
    LoanBookHeap* target = &heap[bookCode/100];

    int cnt = target->getSize();

    LoanBookData* dataArr = new LoanBookData[cnt];

    for(int i = 0;i<cnt;i++){
        dataArr[i].setName(target->getRoot()->getBookData()->getName());
        dataArr[i].setCode(target->getRoot()->getBookData()->getCode());
        dataArr[i].setAuthor(target->getRoot()->getBookData()->getAuthor());
        dataArr[i].setYear(target->getRoot()->getBookData()->getYear());
        dataArr[i].setCount(target->getRoot()->getBookData()->getLoanCount());
        target->Delete();
    }

    for(int i = 0;i<cnt;i++){
        if(dataArr[i].getCode() != 0)
            *fout<< dataArr[i].getName() << '/' << dataArr[i].getCode() << '/' << dataArr[i].getAuthor() << '/' << dataArr[i].getYear() << '/' << dataArr[i].getLoanCount() <<'\n';
        else
            *fout<< dataArr[i].getName() << '/' << "000" << '/' << dataArr[i].getAuthor() << '/' << dataArr[i].getYear() << '/' << dataArr[i].getLoanCount() <<'\n';

    }

    for(int i = 0;i<cnt;i++){
        target->Insert(&dataArr[i]);
    }

}

void SelectionTree::reStruct(){
    int k = 8;
    int j = 7;

    for(int i = k-2;i>=(k-1)/2;i--){
        if(heap[j].getRoot() && heap[j-1].getRoot()){
            if(heap[j].getRoot()->getBookData()->getName()>heap[j-1].getRoot()->getBookData()->getName()) {
                winner[i].setBookData(heap[j-1].getRoot()->getBookData());
                winner[i].setHeap(&heap[j-1]);
            }
            else{
                winner[i].setBookData(heap[j].getRoot()->getBookData());
                winner[i].setHeap(&heap[j]);
            }
        }
        else if(heap[j].getRoot()){
            winner[i].setBookData(heap[j].getRoot()->getBookData());
            winner[i].setHeap(&heap[j]);
        }
        else if(heap[j-1].getRoot()){
            winner[i].setBookData(heap[j-1].getRoot()->getBookData());
            winner[i].setHeap(&heap[j-1]);
        }
        j-=2;
    }

    for(int i = (k-1)/2-1;i>=0;i--){
        j = 2*i+1;
        if(winner[j].getBookData() && winner[j+1].getBookData()){
            if(winner[j].getBookData()->getName() > winner[j+1].getBookData()->getName()) {
                winner[i].setBookData(winner[j+1].getBookData());
                winner[i].setHeap(winner[j+1].getHeap());
                
            }
            else{
                winner[i].setBookData(winner[j].getBookData());
                winner[i].setHeap(winner[j].getHeap());
                
            }
        }
        else if(winner[j].getBookData()){
            winner[i].setBookData(winner[j].getBookData());
            winner[i].setHeap(winner[j].getHeap());
        }
        else if(winner[j+1].getBookData()){
            winner[i].setBookData(winner[j+1].getBookData());
            winner[i].setHeap(winner[j+1].getHeap());
        }

        winner[i].setLeftChild(&winner[j]);
        winner[i].setRightChild(&winner[j+1]);
        winner[j].setParent(&winner[i]);
        winner[j+1].setParent(&winner[i]);
    }
    root = &winner[0];
}
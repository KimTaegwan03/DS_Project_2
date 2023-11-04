#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData* newData) {
    // LoanBookHeap* insert_heap = NULL;

    // insert_heap = heap[newData->getCode()/100];
    
    // if(!insert_heap){
    //     heap[newData->getCode()/100] = new LoanBookHeap();
    //     insert_heap = heap[newData->getCode()/100];
    // }

    // insert_heap->Insert(newData);

    // if(insert_heap->getRoot()->getBookData() == newData){
    //     reStruct();
    // }

}

bool SelectionTree::Delete() {
    //root->getHeap()->
}

bool SelectionTree::printBookData(int bookCode) {

}

void SelectionTree::reStruct(){
    // int k = 8;
    // int j = 7;

    // for(int i = k-2;i>=(k-1)/2;i--){
    //     if(heap[j]->getRoot()->getBookData()->getName()>heap[j-1]->getRoot()->getBookData()->getName()) {
    //         winner[i].setBookData(heap[j-1]->getRoot()->getBookData());
    //         winner[i].setHeap(heap[j-1]);
    //     }
    //     else{
    //         winner[i].setBookData(heap[j]->getRoot()->getBookData());
    //         winner[i].setHeap(heap[j]);
    //     }
    //     j-=2;
    // }

    // for(int i = (k-1)/2-1;i>=0;i--){
    //     j = 2*i+1;
    //     if(winner[j].getBookData()->getName() > winner[j+1].getBookData()->getName()) {
    //         winner[i].setBookData(winner[j+1].getBookData());
    //         winner[i].setHeap(winner[j+1].getHeap());
            
    //     }
    //     else{
    //         winner[i].setBookData(winner[j].getBookData());
    //         winner[i].setHeap(winner[j].getHeap());
            
    //     }

    //     winner[i].setLeftChild(&winner[j]);
    //     winner[i].setRightChild(&winner[j+1]);
    //     winner[j].setParent(&winner[i]);
    //     winner[j+1].setParent(&winner[i]);
    // }
    // root = &winner[0];
}
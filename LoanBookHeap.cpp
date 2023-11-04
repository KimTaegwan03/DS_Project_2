#include "LoanBookHeap.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) {

}

void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {

}

bool LoanBookHeap::Insert(LoanBookData* data) {
    if(!root){
        LoanBookHeapNode* n_root = new LoanBookHeapNode();

        n_root->setBookData(data);

        root = n_root;
    }
    else{
        LoanBookHeapNode* n_node = new LoanBookHeapNode();
    }
}
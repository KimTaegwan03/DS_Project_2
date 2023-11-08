#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"

class LoanBookHeap
{
private:
    LoanBookHeapNode* root;
    vector<LoanBookHeapNode*> heapArr;
    int size;

public:
    LoanBookHeap() {
        this->root = NULL;
        this->size = 0;
    }
    ~LoanBookHeap() {

    }
    
    void increaseSize() {size++;}
    void setRoot(LoanBookHeapNode* pN) { this->root = pN; }
    LoanBookHeapNode* getRoot() { return root; }
    int getSize() {return size;}

    void heapifyUp(LoanBookHeapNode* pN);
    void heapifyDown(LoanBookHeapNode* pN);
    
    bool Insert(LoanBookData* data);
    bool Delete();

    void initArr(LoanBookHeapNode** heapArr,LoanBookHeapNode* cur,int index);
    LoanBookHeap* deepCopy();
};
#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"
#include <queue>

class LoanBookHeap
{
private:
    LoanBookHeapNode* root;
    int size;

public:
    LoanBookHeap() {
        this->root = NULL;
        this->size = 0;
    }
    ~LoanBookHeap() {  

        queue<LoanBookHeapNode*> q;     // Disallocate using BFS
        if(root)
            q.push(root);

        while(!q.empty()){
            LoanBookHeapNode* fr = q.front();
            if(fr->getLeftChild()) q.push(fr->getLeftChild());
            if(fr->getRightChild()) q.push(fr->getRightChild());

            q.pop();

            delete fr->getBookData();
            delete fr;
        }
    }
    
    void increaseSize() {size++;}
    void setRoot(LoanBookHeapNode* pN) { this->root = pN; }
    LoanBookHeapNode* getRoot() { return root; }
    int getSize() {return size;}

    void heapifyUp(LoanBookHeapNode* pN);
    void heapifyDown(LoanBookHeapNode* pN);
    
    bool Insert(LoanBookData* data);
    bool Delete();

    LoanBookHeap* deepCopy();
};
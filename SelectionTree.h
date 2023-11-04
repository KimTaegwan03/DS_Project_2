#pragma once
#include "SelectionTreeNode.h"

#include <fstream>
#include <iostream>

class SelectionTree
{
private:
    SelectionTreeNode* root;
    ofstream* fout;
    SelectionTreeNode* winner;

    //LoanBookHeap* heap[8];

public:
    SelectionTree(ofstream* fout) {
        this->root = NULL;
        this->fout = fout;

        // for(int i = 0;i<8;i++){
        //     heap[i] = new LoanBookHeap();
        // }

        // int k = 8;

        // winner = new SelectionTreeNode[k-1];

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
    ~SelectionTree() {

    }

    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    bool Insert(LoanBookData* newData);
    bool Delete();
    bool printBookData(int bookCode);
    void reStruct();
};
#pragma once
#include "SelectionTreeNode.h"

#include <fstream>
#include <iostream>

class SelectionTree
{
private:
    SelectionTreeNode* root;
    ofstream* fout;
    LoanBookHeap heap[8];

public:
    SelectionTree(ofstream* fout) {
        this->root = NULL;
        this->fout = fout;

        SelectionTreeNode* node = new SelectionTreeNode[7];

        for(int i = 0;i<3;i++){
            node[i].setLeftChild(&node[2*i+1]);
            node[i].setRightChild(&node[2*i+2]);
            if(i>=1){
                node[i].setParent(&node[i/2]);
            }
        }

        for(int i = 3;i<7;i++){
            node[i].setParent(&node[i/2]);
        }
        
        root = &node[0];

    }
    ~SelectionTree() {
        
    }

    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    bool Insert(LoanBookData* newData);
    bool Delete();
    bool printBookData(int bookCode);
    void reStruct();
    SelectionTreeNode* getNode(int idx);
};
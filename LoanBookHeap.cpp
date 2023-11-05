#include "LoanBookHeap.h"
#include <cmath>

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) {
    if(pN == root) return;
    if(pN->getBookData()->getName() < pN->getParent()->getBookData()->getName()){
        LoanBookData* tmp = pN->getBookData();
        pN->setBookData(pN->getParent()->getBookData());
        pN->getParent()->setBookData(tmp);
        heapifyUp(pN->getParent());
    }

    return;
}

void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {
    if(pN->getLeftChild() == NULL && pN->getRightChild() == NULL) return;

    LoanBookHeapNode* target = pN->getLeftChild();

    if(pN->getRightChild() && pN->getRightChild()->getBookData()->getName() < target->getBookData()->getName()){
        target = pN->getRightChild();
    }

    if(pN->getBookData()->getName() > target->getBookData()->getName()){
        LoanBookData* tmp = pN->getBookData();
        pN->setBookData(target->getBookData());
        target->setBookData(tmp);
        heapifyDown(target);
    }

    return;
}

bool LoanBookHeap::Insert(LoanBookData* data) {
    if(!root){
        LoanBookHeapNode* n_root = new LoanBookHeapNode();
        n_root->setBookData(data);

        root = n_root;

        size++;

        return 1;
    }
    else{
        LoanBookHeapNode* n_node = new LoanBookHeapNode();
        LoanBookHeapNode* cur = root;
        LoanBookHeapNode* pre = NULL;

        n_node->setBookData(data);
        
        int level = floor(log2(size+1));
        int j = pow(2,level);
        int dest = (size+1) % j;
        bool flag = 0;

        for(int i = 0;i<level;i++){
            j/=2;
            pre = cur;
            if(dest/j == 1){
                cur = cur->getRightChild();
                flag = 1;
            }
            else{
                cur = cur->getLeftChild();
                flag = 0;
            }
        }

        n_node->setParent(pre);
        if(flag){
            pre->setRightChild(n_node);
        }
        else{
            pre->setLeftChild(n_node);
        }
        
        heapifyUp(n_node);

        size++;

        return 1;
    }
}

bool LoanBookHeap::Delete(){
    root->setBookData(heapArr[size-1]->getBookData());

    if(heapArr[size-1]->getParent()->getLeftChild() == heapArr[size-1]){
        heapArr[size-1]->getParent()->setLeftChild(NULL);
    }
    else{
        heapArr[size-1]->getParent()->setRightChild(NULL);
    }

    delete heapArr[size-1];

    size--;

    if(size == 0){
        root = NULL;
    }

    heapifyDown(root);
}

void LoanBookHeap::initArr(LoanBookHeapNode** heapArr,LoanBookHeapNode* cur,int index){
    if(cur){
        heapArr[index] = cur;
        initArr(heapArr,cur->getLeftChild(),2*index+1);
        initArr(heapArr,cur->getRightChild(),2*index+2);
    }
}
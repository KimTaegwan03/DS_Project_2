#include "LoanBookHeap.h"
#include <cmath>
#include <queue>

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
            dest = dest % j;
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

    if(size == 1){
        delete root;
        root = 0;
        return 1;
    }

    LoanBookHeapNode* cur = root;
    LoanBookHeapNode* pre = NULL;

    int level = floor(log2(size));
    int j = pow(2,level);
    int dest = (size) % j;
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
        dest = dest % j;
    }

    root->setBookData(cur->getBookData());

    if(pre->getLeftChild() == cur){
        pre->setLeftChild(NULL);
    }
    else{
        pre->setRightChild(NULL);
    }

    delete cur;

    size--;

    heapifyDown(root);
}

void LoanBookHeap::initArr(LoanBookHeapNode** heapArr,LoanBookHeapNode* cur,int index){
    if(cur){
        heapArr[index] = cur;
        initArr(heapArr,cur->getLeftChild(),2*index+1);
        initArr(heapArr,cur->getRightChild(),2*index+2);
    }
}

LoanBookHeap* LoanBookHeap::deepCopy(){
    LoanBookHeap* output = new LoanBookHeap();
    queue<LoanBookHeapNode*> q;
    q.push(root);
    while(!q.empty()){
        LoanBookData* n_data = new LoanBookData();
        LoanBookData* o_data = q.front()->getBookData();
        LoanBookHeapNode* fr_node = q.front();

        n_data->setName(o_data->getName());
        n_data->setCode(o_data->getCode());
        n_data->setAuthor(o_data->getAuthor());
        n_data->setYear(o_data->getYear());
        n_data->setCount(o_data->getLoanCount());

        output->Insert(n_data);

        if(fr_node->getLeftChild()){
            q.push(fr_node->getLeftChild());
        }

        if(fr_node->getRightChild()){
            q.push(fr_node->getRightChild());
        }

        q.pop();

    }
    return output;
    
}
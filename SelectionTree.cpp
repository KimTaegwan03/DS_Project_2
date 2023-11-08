#include "SelectionTree.h"
#include <cmath>

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
    root->getHeap()->Delete();

    reStruct();

    return 1;
}

bool SelectionTree::printBookData(int bookCode) {
    LoanBookHeap* target = &heap[bookCode/100];

    int cnt = target->getSize();

    if(cnt == 0){
        return 0;
    }

    *fout<<"========PRINT_ST========\n";
    LoanBookHeap* copy = target->deepCopy();

   

    for(int i = 0;i<cnt;i++){
        if(copy->getRoot()->getBookData()->getCode() != 0)
            *fout<< copy->getRoot()->getBookData()->getName() << '/' << copy->getRoot()->getBookData()->getCode() << '/' << copy->getRoot()->getBookData()->getAuthor() << '/' << copy->getRoot()->getBookData()->getYear() << '/' << copy->getRoot()->getBookData()->getLoanCount() <<'\n';
        else
            *fout<< copy->getRoot()->getBookData()->getName() << '/' << "000" << '/' << copy->getRoot()->getBookData()->getAuthor() << '/' << copy->getRoot()->getBookData()->getYear() << '/' << copy->getRoot()->getBookData()->getLoanCount() <<'\n';
        copy->Delete();
    }
    delete copy;
    // for(int i = 0;i<cnt;i++){
    //     target->Insert(&dataArr[i]);
    // }

    *fout<<"=========================\n\n";

    reStruct();
    return 1;
}

void SelectionTree::reStruct(){
    int k = 8;
    int j = 7;

    for(int i = k-1;i>=k/2;i--){
        auto winner = getNode(i);
        if(heap[j].getRoot() && heap[j-1].getRoot()){
            if(heap[j].getRoot()->getBookData()->getName()>heap[j-1].getRoot()->getBookData()->getName()) {
                winner->setBookData(heap[j-1].getRoot()->getBookData());
                winner->setHeap(&heap[j-1]);
            }
            else{
                winner->setBookData(heap[j].getRoot()->getBookData());
                winner->setHeap(&heap[j]);
            }
        }
        else if(heap[j].getRoot()){
            winner->setBookData(heap[j].getRoot()->getBookData());
            winner->setHeap(&heap[j]);
        }
        else if(heap[j-1].getRoot()){
            winner->setBookData(heap[j-1].getRoot()->getBookData());
            winner->setHeap(&heap[j-1]);
        }
        else if(!heap[j].getRoot() && !heap[j-1].getRoot()){
            winner->setBookData(NULL);
            winner->setHeap(NULL);
        }
        j-=2;
    }

    for(int i = k/2-1;i>=1;i--){
        j = 2*i;
        auto winner_j1 = getNode(j+1);
        auto winner_j = getNode(j);
        auto winner_i = getNode(i);
        if(winner_j->getHeap() && winner_j1->getHeap()){
            if(winner_j->getBookData()->getName() > winner_j1->getBookData()->getName()) {
                winner_i->setBookData(winner_j1->getBookData());
                winner_i->setHeap(winner_j1->getHeap());
                
            }
            else{
                winner_i->setBookData(winner_j->getBookData());
                winner_i->setHeap(winner_j->getHeap());
                
            }
        }
        else if(winner_j->getHeap()){
            winner_i->setBookData(winner_j->getBookData());
            winner_i->setHeap(winner_j->getHeap());
        }
        else if(winner_j1->getHeap()){
            winner_i->setBookData(winner_j1->getBookData());
            winner_i->setHeap(winner_j1->getHeap());
        }
        else if(!winner_j->getHeap() && !winner_j1->getHeap()){
            winner_i->setBookData(NULL);
            winner_i->setHeap(NULL);
        }
    }
}

SelectionTreeNode* SelectionTree::getNode(int idx){

    if(idx == 1){
        return root;
    }

    SelectionTreeNode* cur = root;
    SelectionTreeNode* pre = NULL;
    
    int level = floor(log2(idx));
    int j = pow(2,level);
    int dest = idx % j;
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

    return cur;
}

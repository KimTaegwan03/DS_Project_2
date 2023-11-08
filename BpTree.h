#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "LoanBookData.h"
#include "SelectionTree.h"
#include <fstream>
#include <iostream>
#include <queue>

class BpTree {
private:
	BpTreeNode* root;
	int			order;		// m children
	ofstream* fout;

public:
	BpTree(ofstream *fout, int order = 3) {
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	~BpTree(){
		queue<BpTreeNode*> q;

		if(root){
			BpTreeNode* data_node = root;

			while(data_node->getMostLeftChild()){
				data_node = data_node->getMostLeftChild();
			}
			BpTreeNode* x = data_node;
			while(x){
				x = data_node->getNext();
				for(auto i = data_node->getDataMap()->begin();i!=data_node->getDataMap()->end();i++){
					delete i->second;
				}
				data_node->getDataMap()->clear();
				delete data_node;
				data_node = x;
			}
		}

		if(root)
			q.push(root);

		while(!q.empty()){
			BpTreeNode* fr = q.front();

			if(fr->getMostLeftChild()->getMostLeftChild()) {
				q.push(fr->getMostLeftChild());
				if(fr->getIndexMap()->size()==1){
					q.push(fr->getIndexMap()->begin()->second);
				}
				else if(fr->getIndexMap()->size()==2){
					q.push(fr->getIndexMap()->rbegin()->second);
				}
			}
			fr->getIndexMap()->clear();
			delete fr;
			q.pop();
		}
		
	};
	/* essential */
	bool		Insert(LoanBookData* newData,SelectionTree* stree);
	bool		Delete(string name);
	bool		excessDataNode(BpTreeNode* pDataNode);
	bool		excessIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; }
	BpTreeNode* searchDataNode(string name);

	bool searchBook(string name);
	bool searchRange(string start, string end);

	// bool deleteFromData(string name,BpTreeNode* node);
	// bool deleteFromIndex(string name,BpTreeNode* node);
	// bool borrowKeyFromNextData(BpTreeNode* node,BpTreeNode* next);
	// bool borrowKeyFromPrevData(BpTreeNode* node,BpTreeNode* prev);
	// bool mergeNodeWithNextData(BpTreeNode* node,BpTreeNode* next);
	// bool mergeNodeWithPrevData(BpTreeNode* node,BpTreeNode* prev);
	
	
	// bool borrowKeyFromNextIndex(int pos,BpTreeNode* node,BpTreeNode* next);
	// bool borrowKeyFromPrevIndex(int pos,BpTreeNode* node,BpTreeNode* prev);
	// bool mergeNodeWithNextIndex(int pos,BpTreeNode* node,BpTreeNode* next);
	// bool mergeNodeWithPrevIndex(int pos,BpTreeNode* node,BpTreeNode* prev);





};

#endif

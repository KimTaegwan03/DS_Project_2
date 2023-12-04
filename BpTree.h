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

		// Disallocate all nodes using BFS
		queue<BpTreeNode*> q;

		if(root)
			q.push(root);

		while(!q.empty()){
			BpTreeNode* fr = q.front();

			if(fr->getMostLeftChild()) {
				q.push(fr->getMostLeftChild());
				for(auto i = fr->getIndexMap()->begin();i!=fr->getIndexMap()->end();i++){
					q.push(i->second);
				}
				fr->getIndexMap()->clear();
			}
			else{
				for(auto i = fr->getDataMap()->begin();i!=fr->getDataMap()->end();i++){
					delete i->second;
				}
				fr->getDataMap()->clear();
			}
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

	void borrowFromNextData(BpTreeNode* pCur,BpTreeNode* next_node);
	void borrowFromPrevData(BpTreeNode* pCur,BpTreeNode* prev_node);
	void mergeWithNextData(BpTreeNode* pCur,BpTreeNode* next_node);
	void mergeWithPrevData(BpTreeNode* pCur,BpTreeNode* prev_node);

	void borrowFromNextIndex(BpTreeNode* pCur,BpTreeNode* next_node);
	void borrowFromPrevIndex(BpTreeNode* pCur,BpTreeNode* prev_node);
	void mergeWithNextIndex(BpTreeNode* pCur,BpTreeNode* next_node);
	void mergeWithPrevIndex(BpTreeNode* pCur,BpTreeNode* prev_node);

	void deleteIndex(string name,BpTreeNode* node);

};

#endif

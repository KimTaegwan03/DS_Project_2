#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData) {
	
	if(!root) {
		BpTreeIndexNode* n_root = new BpTreeIndexNode();
		BpTreeDataNode* n_data = new BpTreeDataNode();

		n_root->insertIndexMap(newData->getName(),n_data);
		n_data->insertDataMap(newData->getName(),newData);

		root = n_root;
		
		return 1;
	}

	BpTreeNode* cur = root;

	// Search BpTree for Data with Name
	while(cur->getMostLeftChild()){
		if(!cur->getIndexMap()->empty()){
			BpTreeNode* j = cur->getMostLeftChild();
			bool flag = 1;
			for(map<string,BpTreeNode*>::iterator i = cur->getIndexMap()->begin();i!=cur->getIndexMap()->end();i++){
				if(i->first > newData->getName()){
					cur = j;
					flag = 0;
					break;
				}
				j = i->second;
			}

			// MostRightChild
			if(flag){
				cur = j;
			}
		}
	}

	if(cur->getDataMap()->find(newData->getName()) != cur->getDataMap()->end()){
		cur->getDataMap()->find(newData->getName())->second->updateCount();
		return 1;
	}

	// cur is data node to insert new data
	cur->insertDataMap(newData->getName(),newData);

	// map size > 2, split
	if(cur->getDataMap()->size()>2){
		this->splitDataNode(cur);
	}

	return true;
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	BpTreeDataNode* q = new BpTreeDataNode();
	auto i = pDataNode->getDataMap()->begin();
	i++;
	
	q->insertDataMap(i->first,i->second);

	pDataNode->getParent()->insertIndexMap(i->first,q);

	pDataNode->deleteMap(i->first);

	i++;

	q->insertDataMap(i->first,i->second);

	pDataNode->deleteMap(i->first);

	if(pDataNode->getParent()->getIndexMap()->size()>2){
		splitIndexNode(pDataNode->getParent());
	}
	
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {

	if(pIndexNode != root){
		BpTreeIndexNode* q = new BpTreeIndexNode();
		auto i = pIndexNode->getIndexMap()->begin();
		i++;

		pIndexNode->getParent()->insertIndexMap(i->first,q);

		q->setMostLeftChild(i->second);

		pIndexNode->deleteMap(i->first);

		i++;

		q->insertIndexMap(i->first,i->second);

		if(pIndexNode->getParent()->getIndexMap()->size()>2){
			splitIndexNode(pIndexNode->getParent());
		}
	}
	else{
		BpTreeIndexNode* n_root = new BpTreeIndexNode();
		BpTreeIndexNode* q = new BpTreeIndexNode();
		auto i = pIndexNode->getIndexMap()->begin();
		i++;
		n_root->setMostLeftChild(pIndexNode);

		n_root->insertIndexMap(i->first,q);

		q->setMostLeftChild(i->second);

		pIndexNode->deleteMap(i->first);

		i++;

		q->insertIndexMap(i->first,i->second);

		pIndexNode->deleteMap(i->first);

		root = n_root;

	}
}

BpTreeNode* BpTree::searchDataNode(string name) {
	BpTreeNode* pCur = root;
	
	return pCur;
}

bool BpTree::searchBook(string name) {

}

bool BpTree::searchRange(string start, string end) {
	
}

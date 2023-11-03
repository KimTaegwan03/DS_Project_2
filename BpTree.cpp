#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData) {
	
	if(!root) {
		BpTreeDataNode* n_data = new BpTreeDataNode();

		n_data->insertDataMap(newData->getName(),newData);

		root = n_data;
		
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
	if(pDataNode != root){
		BpTreeDataNode* q = new BpTreeDataNode();
		auto i = pDataNode->getDataMap()->begin();
		
		for(int a = 0;a<order/2;a++){
			i++;
		}

		// move to q node
		for(int a = 0;a<=order/2;a++){
			q->insertDataMap(i->first,i->second);
			i++;
		}

		while(pDataNode->getDataMap()->size()>order/2){
			pDataNode->deleteMap(pDataNode->getDataMap()->rbegin()->first);
		}

		pDataNode->getParent()->insertIndexMap(q->getDataMap()->begin()->first,q);

		q->setParent(pDataNode->getParent());

		q->setNext(pDataNode->getNext());
		if(pDataNode->getNext())
			pDataNode->getNext()->setPrev(q);
		pDataNode->setNext(q);
		q->setPrev(pDataNode);


		if(excessDataNode(pDataNode)){
			splitIndexNode(pDataNode->getParent());
		}
	}
	else{
		BpTreeIndexNode* n_root = new BpTreeIndexNode();
		BpTreeDataNode* q = new BpTreeDataNode();
		auto i = pDataNode->getDataMap()->begin();
		
		for(int a = 0;a<order/2;a++){
			i++;
		}

		// move to q node
		for(int a = 0;a<=order/2;a++){
			q->insertDataMap(i->first,i->second);
			i++;
		}

		while(pDataNode->getDataMap()->size()>order/2){
			pDataNode->deleteMap(pDataNode->getDataMap()->rbegin()->first);
		}

		n_root->insertIndexMap(q->getDataMap()->begin()->first,q);

		n_root->setMostLeftChild(pDataNode);


		pDataNode->setParent(n_root);
		q->setParent(n_root);

		q->setNext(pDataNode->getNext());
		if(pDataNode->getNext())
			pDataNode->getNext()->setPrev(q);
		pDataNode->setNext(q);
		q->setPrev(pDataNode);

		root = n_root;
	}
	
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {

	if(pIndexNode != root){
		BpTreeIndexNode* q = new BpTreeIndexNode();
		auto i = pIndexNode->getIndexMap()->begin();

		for(int a = 0;a<order/2;a++){
			i++;
		}

		pIndexNode->getParent()->insertIndexMap(i->first,q);

		q->setMostLeftChild(i->second);

		i++;


		// move to q node
		for(int a = 0;a<order/2;a++){
			q->insertIndexMap(i->first,i->second);
			i++;
		}

		while(pIndexNode->getDataMap()->size()>order/2){
			pIndexNode->deleteMap(pIndexNode->getIndexMap()->rbegin()->first);
		}

		q->setParent(pIndexNode->getParent());


		if(excessIndexNode(pIndexNode)){
			splitIndexNode(pIndexNode->getParent());
		}
	}
	else{
		BpTreeIndexNode* n_root = new BpTreeIndexNode();
		BpTreeIndexNode* q = new BpTreeIndexNode();
		auto i = pIndexNode->getIndexMap()->begin();
		
		for(int a = 0;a<order/2;a++){
			i++;
		}

		n_root->insertIndexMap(i->first,q);

		q->setMostLeftChild(i->second);

		i++;

		// move to q node
		for(int a = 0;a<order/2;a++){
			q->insertIndexMap(i->first,i->second);
			i++;
		}

		while(pIndexNode->getIndexMap()->size()>order/2){
			pIndexNode->deleteMap(pIndexNode->getIndexMap()->rbegin()->first);
		}

		n_root->setMostLeftChild(pIndexNode);

		root = n_root;

		pIndexNode->setParent(n_root);
		q->setParent(n_root);

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

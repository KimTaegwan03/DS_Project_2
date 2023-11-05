#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData) {
	
	if(!root) {
		BpTreeDataNode* n_data = new BpTreeDataNode();

		n_data->insertDataMap(newData->getName(),newData);

		root = n_data;
		
		return 1;
	}

	BpTreeNode* cur = searchDataNode(newData->getName());

	// Search BpTree for Data with Name

	// cur = searchDataNode(newData->getName())
	// while(cur->getMostLeftChild()){
	// 	if(!cur->getIndexMap()->empty()){
	// 		BpTreeNode* j = cur->getMostLeftChild();
	// 		bool flag = 1;
	// 		for(map<string,BpTreeNode*>::iterator i = cur->getIndexMap()->begin();i!=cur->getIndexMap()->end();i++){
	// 			if(i->first > newData->getName()){
	// 				cur = j;
	// 				flag = 0;
	// 				break;
	// 			}
	// 			j = i->second;
	// 		}

	// 		// MostRightChild
	// 		if(flag){
	// 			cur = j;
	// 		}
	// 	}
	// }

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

bool BpTree::Delete(string Data){
	bool find = false;
	BpTreeNode* cur = root;
	BpTreeNode* j = NULL;

	while(cur->getMostLeftChild()){
		j = cur->getMostLeftChild();
		bool flag = 1;
		for(auto iter = cur->getIndexMap()->begin();iter != cur->getIndexMap()->end();iter++){
			if(iter->first == Data) find = true;
			if(iter->first > Data){
				cur = j;
				flag = 0;
				break;
			}
			j = iter->second;
		}

		if(flag){
			cur = j;
		}
	}

	if(!find){
		if(cur->getDataMap()->size() > 1){
			cur->deleteMap(Data);
		}
		else{
			BpTreeNode* sibling_next = cur->getNext();
			BpTreeNode* sibling_prev = cur->getPrev();

			if(sibling_next->getParent() == cur->getParent()){

			}
		}
	}


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
	
	BpTreeNode* j = NULL;

	while(pCur->getMostLeftChild()){
		j = pCur->getMostLeftChild();
		bool flag = 1;
		for(auto iter = pCur->getIndexMap()->begin();iter != pCur->getIndexMap()->end();iter++){
			if(iter->first > name){
				pCur = j;
				flag = 0;
				break;
			}
			j = iter->second;
		}

		if(flag){
			pCur = j;
		}
	}
	return pCur;
}

bool BpTree::searchBook(string name) {
	BpTreeNode* pCur = searchDataNode(name);

	for(auto iter = pCur->getDataMap()->begin();iter != pCur->getDataMap()->end();iter++){
		if(iter->first == name){
			*fout<<"========SEARCH_BP========\n";
			if(iter->second->getCode() != 0)
				*fout<< iter->second->getName() << '/' << iter->second->getCode() << '/' << iter->second->getAuthor() << '/' << iter->second->getYear() << '/' << iter->second->getLoanCount() <<'\n';
			else
				*fout<< iter->second->getName() << '/' << "000" << '/' << iter->second->getAuthor() << '/' << iter->second->getYear() << '/' << iter->second->getLoanCount() <<'\n';
			
			*fout<<"==========================\n\n";
			return 1;
		}
	}
	return 0;
}

bool BpTree::searchRange(string start, string end) {
	BpTreeNode* pCur = root;
	BpTreeNode* j = NULL;
	bool flag = 1;

	while(pCur->getMostLeftChild()){
		j = pCur->getMostLeftChild();
		for(auto iter = pCur->getIndexMap()->begin();iter != pCur->getIndexMap()->end();iter++){
			if(iter->first > start){
				pCur = j;
				flag = 0;
				break;
			}
			j = iter->second;
		}

		if(flag){
			pCur = j;
		}
	}

	if(pCur->getDataMap()->begin()->first < start){
		return 0;
	}
	*fout<<"========SEARCH_BP========\n";
	while(pCur){
		for(auto iter = pCur->getDataMap()->begin();iter!=pCur->getDataMap()->end();iter++){
			if(iter->first >= start && end >= iter->first){
				flag = 1;
				if(iter->second->getCode() != 0)
					*fout<< iter->second->getName() << '/' << iter->second->getCode() << '/' << iter->second->getAuthor() << '/' << iter->second->getYear() << '/' << iter->second->getLoanCount() <<'\n';
				else
					*fout<< iter->second->getName() << '/' << "000" << '/' << iter->second->getAuthor() << '/' << iter->second->getYear() << '/' << iter->second->getLoanCount() <<'\n';
			
			}
			else{
				*fout<<"==========================\n\n";
				return 1;
			}
		}
		pCur = pCur->getNext();
	}
	*fout<<"==========================\n\n";
	return 1;
}

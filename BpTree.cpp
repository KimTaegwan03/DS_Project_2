#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData,SelectionTree* stree) {
	
	// No root
	if(!root) {
		BpTreeDataNode* n_data = new BpTreeDataNode();
		n_data->insertDataMap(newData->getName(),newData);
		root = n_data;
		return 1;
	}

	BpTreeNode* cur = searchDataNode(newData->getName());

	// Same book already exists, Increase LoanCount
	if(cur->getDataMap()->find(newData->getName()) != cur->getDataMap()->end()){
		cur->getDataMap()->find(newData->getName())->second->updateCount();

		// Depending on Book Code, Decide deletion.
		LoanBookData* data = cur->getDataMap()->find(newData->getName())->second;
		
		delete newData;

		if(data->getCode() == 0 && data->getLoanCount() >= 3){
			stree->Insert(data);
			Delete(data->getName());
			return 0;
		}
		else if(data->getCode() == 100 && data->getLoanCount() >= 3){
			stree->Insert(data);
			Delete(data->getName());
			return 0;
		}
		else if(data->getCode() == 200 && data->getLoanCount() >= 3){
			stree->Insert(data);
			Delete(data->getName());
			return 0;
		}
		else if(data->getCode() == 300 && data->getLoanCount() >= 4){
			stree->Insert(data);
			Delete(data->getName());
			return 0;
		}
		else if(data->getCode() == 400 && data->getLoanCount() >= 4){
			stree->Insert(data);
			Delete(data->getName());
			return 0;
		}
		else if(data->getCode() == 500 && data->getLoanCount() >= 2){
			stree->Insert(data);
			Delete(data->getName());
			return 0;
		}
		else if(data->getCode() == 600 && data->getLoanCount() >= 2){
			stree->Insert(data);
			Delete(data->getName());
			return 0;
		}
		else if(data->getCode() == 700 && data->getLoanCount() >= 2){
			stree->Insert(data);
			Delete(data->getName());
			return 0;
		}

		return 1;
	}

	cur->insertDataMap(newData->getName(),newData);

	// size > 2, Split data node
	if(excessDataNode(cur)){
		splitDataNode(cur);
	}

	return true;
}




bool BpTree::Delete(string name){		// BpTree Deletion Function
	BpTreeNode* pCur = root;
	BpTreeNode* j = NULL;
	bool find = 0;	// Key in internal node flag

	while(pCur->getMostLeftChild()){	// Find Data Node
		j = pCur->getMostLeftChild();
		bool flag = 1;
		for(auto iter = pCur->getIndexMap()->begin();iter != pCur->getIndexMap()->end();iter++){
			if(iter->first == name) find = 1;
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

	// No key in Internal Node and not first data in node
	if(!find && pCur->getDataMap()->begin()->first != name){
		pCur->deleteMap(name);
	}
	else{
		if(pCur->getDataMap()->size() < 2){				// Underflow
			BpTreeNode* next_node = pCur->getNext();
			BpTreeNode* prev_node = pCur->getPrev();
			

			// Rebalancing Node to delete data without underflow
			if(next_node && pCur->getParent() == next_node->getParent()
			&& next_node->getDataMap()->size() > 1){
				borrowFromNextData(pCur,next_node);
			}
			else if(prev_node && pCur->getParent() == prev_node->getParent()
			&& prev_node->getDataMap()->size() > 1){
				borrowFromPrevData(pCur,prev_node);
			}
			else if(next_node && pCur->getParent() == next_node->getParent()
			&& next_node->getDataMap()->size() <= 1){
				mergeWithNextData(pCur,next_node);
			}
			else if(prev_node && pCur->getParent() == prev_node->getParent()
			&& prev_node->getDataMap()->size() <= 1){
				mergeWithPrevData(pCur,prev_node);
			}
		}

		// delete the data from the data node
		pCur->deleteMap(name);

		// Check parent node recursive to delete key in internal node
		if(pCur->getParent())
			deleteIndex(name,pCur->getParent());
	}

	// No data in the tree, delete root
	if(!root->getMostLeftChild()){
		if(root->getDataMap()->size() == 0){
			delete root;
			root = 0;
		}
	}

	return 1;
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {		// Split Data Node to satisfy rule
	if(pDataNode != root){
		BpTreeDataNode* q = new BpTreeDataNode();
		auto i = pDataNode->getDataMap()->rbegin();

		q->insertDataMap(i->first,i->second);

		i++;

		q->insertDataMap(i->first,i->second);

		while(pDataNode->getDataMap()->size() > 1){
			pDataNode->deleteMap(pDataNode->getDataMap()->rbegin()->first);
		}

		pDataNode->getParent()->insertIndexMap(q->getDataMap()->begin()->first,q);

		q->setParent(pDataNode->getParent());

		q->setNext(pDataNode->getNext());
		if(pDataNode->getNext())
			pDataNode->getNext()->setPrev(q);
		pDataNode->setNext(q);
		q->setPrev(pDataNode);


		// Parent node dissatisfy rule, Split the node
		if(excessIndexNode(pDataNode->getParent())){
			splitIndexNode(pDataNode->getParent());
		}
	}

	// The node is root, allocate new node
	else{
		BpTreeIndexNode* n_root = new BpTreeIndexNode();
		BpTreeDataNode* q = new BpTreeDataNode();
		auto i = pDataNode->getDataMap()->rbegin();

		q->insertDataMap(i->first,i->second);

		i++;

		q->insertDataMap(i->first,i->second);

		while(pDataNode->getDataMap()->size() > 1){
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

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {	// Split Data Node to satisfy rule

	if(pIndexNode != root){
		BpTreeIndexNode* q = new BpTreeIndexNode();
		auto i = pIndexNode->getIndexMap()->rbegin();

		q->insertIndexMap(i->first,i->second);
		i->second->setParent(q);

		i++;

		pIndexNode->getParent()->insertIndexMap(i->first,q);
		i->second->setParent(q);
		q->setMostLeftChild(i->second);

		while(pIndexNode->getIndexMap()->size()>order/2){
			pIndexNode->deleteMap(pIndexNode->getIndexMap()->rbegin()->first);
		}

		q->setParent(pIndexNode->getParent());

		// Parent node dissatisfy rule, Split the node
		if(excessIndexNode(pIndexNode->getParent())){
			splitIndexNode(pIndexNode->getParent());
		}
	}

	// The node is root, allocate new node
	else{
		BpTreeIndexNode* n_root = new BpTreeIndexNode();
		BpTreeIndexNode* q = new BpTreeIndexNode();
		auto i = pIndexNode->getIndexMap()->begin();
		
		i++;

		n_root->insertIndexMap(i->first,q);
		i->second->setParent(q);
		q->setMostLeftChild(i->second);

		i++;

		q->insertIndexMap(i->first,i->second);
		i->second->setParent(q);


		while(pIndexNode->getIndexMap()->size()>order/2){
			pIndexNode->deleteMap(pIndexNode->getIndexMap()->rbegin()->first);
		}

		n_root->setMostLeftChild(pIndexNode);

		root = n_root;

		pIndexNode->setParent(n_root);
		q->setParent(n_root);

	}
}

BpTreeNode* BpTree::searchDataNode(string name) {	// Search the tree with name and return data node
	BpTreeNode* pCur = root;
	

	while(pCur->getMostLeftChild()){
		BpTreeNode* j = pCur->getMostLeftChild();
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

bool BpTree::searchBook(string name) {		// Search tree with name and print the book data
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

bool BpTree::searchRange(string start, string end) {		// Search tree with start key and print book datas from start to end
	BpTreeNode* pCur = root;
	BpTreeNode* j = NULL;
	bool flag = 1;

	while(pCur->getMostLeftChild()){
		j = pCur->getMostLeftChild();
		for(auto iter = pCur->getIndexMap()->begin();iter != pCur->getIndexMap()->end();iter++){
			if(iter->first[0] >= start[0]){
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

	if(pCur->getDataMap()->begin()->first[0] < start[0]){
		return 0;
	}
	*fout<<"========SEARCH_BP========\n";
	while(pCur){
		for(auto iter = pCur->getDataMap()->begin();iter!=pCur->getDataMap()->end();iter++){
			if(iter->first[0] >= start[0] && end[0] >= iter->first[0]){
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

// Borrow key and book data from the next sibling data node for rabalancing
void BpTree::borrowFromNextData(BpTreeNode* pCur,BpTreeNode* next_node){
	pCur->insertDataMap(next_node->getDataMap()->begin()->first,next_node->getDataMap()->begin()->second);
	pCur->getParent()->deleteMap(next_node->getDataMap()->begin()->first);
	next_node->deleteMap(next_node->getDataMap()->begin()->first);
	pCur->getParent()->insertIndexMap(next_node->getDataMap()->begin()->first,next_node);
}

// Borrow key and book data from the prev sibling data node for rabalancing
void BpTree::borrowFromPrevData(BpTreeNode* pCur,BpTreeNode* prev_node){
	pCur->insertDataMap(prev_node->getDataMap()->rbegin()->first,prev_node->getDataMap()->rbegin()->second);
	prev_node->deleteMap(pCur->getDataMap()->begin()->first);
	pCur->getParent()->deleteMap(pCur->getDataMap()->rbegin()->first);
	pCur->getParent()->insertIndexMap(pCur->getDataMap()->begin()->first,pCur);
}

// Merge node with the next sibling data node for rebalancing
void BpTree::mergeWithNextData(BpTreeNode* pCur,BpTreeNode* next_node){
	pCur->insertDataMap(next_node->getDataMap()->begin()->first,next_node->getDataMap()->begin()->second);
	pCur->getParent()->deleteMap(pCur->getDataMap()->rbegin()->first);
	pCur->setNext(next_node->getNext());
	if(next_node->getNext()){
		next_node->getNext()->setPrev(pCur);
	}
	next_node->getDataMap()->clear();
	delete next_node;

	if(pCur->getParent()->getIndexMap()->size() < 1){	// Parent node has underflow. rebalancing again
		if(pCur->getParent() == root){
			root = pCur;
			delete pCur->getParent();
			pCur->setParent(0);
		}
		else{
			BpTreeNode* paren = pCur->getParent();
			BpTreeNode* next_index;
			BpTreeNode* prev_index;

			if(paren->getParent()->getMostLeftChild() == paren){
				next_index = paren->getParent()->getIndexMap()->begin()->second;
			}
			else if(paren->getParent()->getIndexMap()->begin()->second == paren && paren->getParent()->getIndexMap()->size() >1){
				next_index = paren->getParent()->getIndexMap()->rbegin()->second;
			}
			else{
				next_index = nullptr;
			}

			if(paren->getParent()->getIndexMap()->begin()->second == paren){
				prev_index = paren->getParent()->getMostLeftChild();
			}
			else if(paren->getParent()->getIndexMap()->size() > 1 && paren->getParent()->getIndexMap()->rbegin()->second == paren){
				prev_index = paren->getParent()->getIndexMap()->begin()->second;
			}
			else{
				prev_index = nullptr;
			}

			if(next_index && next_index->getIndexMap()->size() > 1){
				borrowFromNextIndex(paren,next_index);
			}
			else if(prev_index && prev_index->getIndexMap()->size() > 1){
				borrowFromPrevIndex(paren,prev_index);
			}
			else if(next_index && next_index->getIndexMap()->size() <= 1){
				mergeWithNextIndex(paren,next_index);
			}
			else if(prev_index && prev_index->getIndexMap()->size() <= 1){
				mergeWithPrevIndex(paren,prev_index);
			}
		}
	}
}

// Merge node with the prev sibling data node for rebalancing
void BpTree::mergeWithPrevData(BpTreeNode* pCur,BpTreeNode* prev_node){
	pCur->getParent()->deleteMap(pCur->getDataMap()->begin()->first);
	pCur->insertDataMap(prev_node->getDataMap()->begin()->first,prev_node->getDataMap()->begin()->second);
	if(pCur->getParent()->getIndexMap()->size() >= 1)
		pCur->getParent()->deleteMap(prev_node->getDataMap()->begin()->first);
	if(pCur->getParent()->getMostLeftChild() == prev_node){
		pCur->getParent()->setMostLeftChild(pCur);
	}
	else{
		pCur->getParent()->insertIndexMap(pCur->getDataMap()->begin()->first,pCur);
	}
	pCur->setPrev(prev_node->getPrev());
	if(prev_node->getPrev()){
		prev_node->getPrev()->setNext(pCur);
	}
	prev_node->getDataMap()->clear();
	delete prev_node;

	if(pCur->getParent()->getIndexMap()->size() < 1){		// Parent node has underflow. rebalancing again
		if(pCur->getParent() == root){
			root = pCur;
			delete pCur->getParent();
			pCur->setParent(0);
		}
		else{
			BpTreeNode* paren = pCur->getParent();
			BpTreeNode* next_index;
			BpTreeNode* prev_index;

			if(paren->getParent()->getMostLeftChild() == paren){
				next_index = paren->getParent()->getIndexMap()->begin()->second;
			}
			else if(paren->getParent()->getIndexMap()->begin()->second == paren && paren->getParent()->getIndexMap()->size() >1){
				next_index = paren->getParent()->getIndexMap()->rbegin()->second;
			}
			else{
				next_index = nullptr;
			}

			if(paren->getParent()->getIndexMap()->begin()->second == paren){
				prev_index = paren->getParent()->getMostLeftChild();
			}
			else if(paren->getParent()->getIndexMap()->size() > 1 && paren->getParent()->getIndexMap()->rbegin()->second == paren){
				prev_index = paren->getParent()->getIndexMap()->begin()->second;
			}
			else{
				prev_index = nullptr;
			}

			if(next_index && next_index->getIndexMap()->size() > 1){
				borrowFromNextIndex(paren,next_index);
			}
			else if(prev_index && prev_index->getIndexMap()->size() > 1){
				borrowFromPrevIndex(paren,prev_index);
			}
			else if(next_index && next_index->getIndexMap()->size() <= 1){
				mergeWithNextIndex(paren,next_index);
			}
			else if(prev_index && prev_index->getIndexMap()->size() <= 1){
				mergeWithPrevIndex(paren,prev_index);
			}
		}
	}
}

// Borrow key and child from the next sibling index node for rabalancing
void BpTree::borrowFromNextIndex(BpTreeNode* pCur,BpTreeNode* next_node){
	for(auto i = pCur->getParent()->getIndexMap()->begin();i!=pCur->getParent()->getIndexMap()->end();i++){
		if(i->second == next_node){
			pCur->insertIndexMap(i->first,next_node->getMostLeftChild());
			next_node->getMostLeftChild()->setParent(pCur);
			break;
		}
	}
	next_node->setMostLeftChild(next_node->getIndexMap()->begin()->second);
	pCur->getParent()->deleteMap(pCur->getIndexMap()->begin()->first);
	pCur->getParent()->insertIndexMap(next_node->getIndexMap()->begin()->first,next_node);
	next_node->deleteMap(next_node->getIndexMap()->begin()->first);
}

// Borrow key and child from the prev sibling index node for rabalancing
void BpTree::borrowFromPrevIndex(BpTreeNode* pCur,BpTreeNode* prev_node){
	for(auto i = pCur->getParent()->getIndexMap()->begin();i!=pCur->getParent()->getIndexMap()->end();i++){
		if(i->second == pCur){
			pCur->insertIndexMap(i->first,pCur->getMostLeftChild());
			break;
		}
	}
	pCur->setMostLeftChild(prev_node->getIndexMap()->rbegin()->second);
	prev_node->getIndexMap()->rbegin()->second->setParent(pCur);
	pCur->getParent()->deleteMap(pCur->getIndexMap()->begin()->first);
	pCur->getParent()->insertIndexMap(prev_node->getIndexMap()->rbegin()->first,pCur);
	prev_node->deleteMap(prev_node->getIndexMap()->rbegin()->first);
}

// Merge node with the next sibling index node for rebalancing
void BpTree::mergeWithNextIndex(BpTreeNode* pCur,BpTreeNode* next_node){
	for(auto i = pCur->getParent()->getIndexMap()->begin();i!=pCur->getParent()->getIndexMap()->end();i++){
		if(i->second == next_node){
			pCur->insertIndexMap(i->first,next_node->getMostLeftChild());
			next_node->getMostLeftChild()->setParent(pCur);
			break;
		}
	}

	pCur->insertIndexMap(next_node->getIndexMap()->begin()->first,next_node->getIndexMap()->begin()->second);
	next_node->getIndexMap()->begin()->second->setParent(pCur);
	pCur->getParent()->deleteMap(pCur->getIndexMap()->begin()->first);
	next_node->getIndexMap()->clear();
	delete next_node;

	if(pCur->getParent()->getIndexMap()->size() < 1){			// Parent node has underflow. rebalancing again
		if(pCur->getParent() == root){
			root = pCur;
			delete pCur->getParent();
			pCur->setParent(0);
		}
		else{
			BpTreeNode* paren = pCur->getParent();
			BpTreeNode* next_index;
			BpTreeNode* prev_index;

			if(paren->getParent()->getMostLeftChild() == paren){
				next_index = paren->getParent()->getIndexMap()->begin()->second;
			}
			else if(paren->getParent()->getIndexMap()->begin()->second == paren && paren->getParent()->getIndexMap()->size() >1){
				next_index = paren->getParent()->getIndexMap()->rbegin()->second;
			}
			else{
				next_index = nullptr;
			}

			if(paren->getParent()->getIndexMap()->begin()->second == paren){
				prev_index = paren->getParent()->getMostLeftChild();
			}
			else if(paren->getParent()->getIndexMap()->size() > 1 && paren->getParent()->getIndexMap()->rbegin()->second == paren){
				prev_index = paren->getParent()->getIndexMap()->begin()->second;
			}
			else{
				prev_index = nullptr;
			}

			if(next_index && next_index->getIndexMap()->size() > 1){
				borrowFromNextIndex(paren,next_index);
			}
			else if(prev_index && prev_index->getIndexMap()->size() > 1){
				borrowFromPrevIndex(paren,prev_index);
			}
			else if(next_index && next_index->getIndexMap()->size() <= 1){
				mergeWithNextIndex(paren,next_index);
			}
			else if(prev_index && prev_index->getIndexMap()->size() <= 1){
				mergeWithPrevIndex(paren,prev_index);
			}
		}
	}
}

// Merge node with the prev sibling index node for rebalancing
void BpTree::mergeWithPrevIndex(BpTreeNode* pCur,BpTreeNode* prev_node){
	for(auto i = pCur->getParent()->getIndexMap()->begin();i!=pCur->getParent()->getIndexMap()->end();i++){
		if(i->second == pCur){
			pCur->insertIndexMap(i->first,pCur->getMostLeftChild());
			pCur->getParent()->deleteMap(pCur->getIndexMap()->begin()->first);
			break;
		}
	}
	if(pCur->getParent()->getMostLeftChild() == prev_node){
		pCur->getParent()->setMostLeftChild(pCur);
	}
	else{
		string tmp = pCur->getParent()->getIndexMap()->begin()->first;
		pCur->getParent()->deleteMap(pCur->getParent()->getIndexMap()->begin()->first);
		pCur->getParent()->insertIndexMap(tmp,pCur);
	}
	pCur->insertIndexMap(prev_node->getIndexMap()->begin()->first,prev_node->getIndexMap()->begin()->second);
	prev_node->getIndexMap()->begin()->second->setParent(pCur);
	pCur->setMostLeftChild(prev_node->getMostLeftChild());
	prev_node->getMostLeftChild()->setParent(pCur);
	prev_node->getIndexMap()->clear();
	delete prev_node;

	if(pCur->getParent()->getIndexMap()->size() < 1){		// Parent node has underflow. rebalancing again
		if(pCur->getParent() == root){
			delete root;
			root = pCur;
			pCur->setParent(0);
		}
		else{
			BpTreeNode* paren = pCur->getParent();
			BpTreeNode* next_index;
			BpTreeNode* prev_index;

			if(paren->getParent()->getMostLeftChild() == paren){
				next_index = paren->getParent()->getIndexMap()->begin()->second;
			}
			else if(paren->getParent()->getIndexMap()->begin()->second == paren && paren->getParent()->getIndexMap()->size() >1){
				next_index = paren->getParent()->getIndexMap()->rbegin()->second;
			}
			else{
				next_index = nullptr;
			}

			if(paren->getParent()->getIndexMap()->begin()->second == paren){
				prev_index = paren->getParent()->getMostLeftChild();
			}
			else if(paren->getParent()->getIndexMap()->size() > 1 && paren->getParent()->getIndexMap()->rbegin()->second == paren){
				prev_index = paren->getParent()->getIndexMap()->begin()->second;
			}
			else{
				prev_index = nullptr;
			}

			if(next_index && next_index->getIndexMap()->size() > 1){
				borrowFromNextIndex(paren,next_index);
			}
			else if(prev_index && prev_index->getIndexMap()->size() > 1){
				borrowFromPrevIndex(paren,prev_index);
			}
			else if(next_index && next_index->getIndexMap()->size() <= 1){
				mergeWithNextIndex(paren,next_index);
			}
			else if(prev_index && prev_index->getIndexMap()->size() <= 1){
				mergeWithPrevIndex(paren,prev_index);
			}
		}
	}
}

// If the key is in internal node, delete it
void BpTree::deleteIndex(string name,BpTreeNode* node){
	for(auto i = node->getIndexMap()->begin();i!=node->getIndexMap()->end();i++){
		if(i->first == name){
			BpTreeNode* minData = i->second;
			while(minData->getMostLeftChild()){
				minData = minData->getMostLeftChild();
			}
			node->insertIndexMap(minData->getDataMap()->begin()->first,i->second);
			node->deleteMap(name);
			return;
		}
	}

	// Find recursive
	if(node->getParent())
		deleteIndex(name,node->getParent());
}
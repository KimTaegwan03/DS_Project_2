#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData,SelectionTree* stree) {
	
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

		// Depending on Book Code, Decide on deletion.
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

	// cur is data node to insert new data
	cur->insertDataMap(newData->getName(),newData);

	// map size > 2, split
	if(cur->getDataMap()->size()>2){
		this->splitDataNode(cur);
	}

	return true;
}

bool BpTree::Delete(string name){
	
	auto node = searchDataNode(name);

	node->deleteMap(name);

	return 1;


	
	// if(!node){
	// 	node = searchDataNode(name);
	// }

	// if(node->getMostLeftChild() == 0){
	// 	deleteFromData(name,node);
	// }
	// else{
	// 	deleteFromIndex(name,node);
	// }

	// if(node->getMostLeftChild() && node->getIndexMap()->size() < 1){
	// 	if(node == root){
	// 		if(root->getIndexMap()->size() == 0 && root->getMostLeftChild()){
	// 			root = root->getMostLeftChild();
	// 			delete root->getParent();
	// 			root->setParent(0);
	// 		}
	// 		return 1;
	// 	}
	// 	else{
	// 		int pos = -1;

	// 		if(node->getParent()->getMostLeftChild() == node){
	// 			pos = 0;
	// 		}
	// 		else if(node->getParent()->getIndexMap()->begin()->second == node){
	// 			pos = 1;
	// 		}
	// 		else if(node->getParent()->getIndexMap()->rbegin()->second == node){
	// 			pos = 2;
	// 		}

	// 		BpTreeNode* next_node;
	// 		BpTreeNode* prev_node;

	// 		if(node->getParent()->getIndexMap()->size() > pos + 1){
	// 			if(pos == 0){
	// 				next_node = node->getParent()->getIndexMap()->begin()->second;
	// 			}
	// 			else if(pos == 1){
	// 				next_node = node->getParent()->getIndexMap()->rbegin()->second;
	// 			}
	// 		}
	// 		else{
	// 			next_node = nullptr;
	// 		}

	// 		if(pos){
	// 			if(pos == 1){
	// 				prev_node = node->getParent()->getMostLeftChild();
	// 			}
	// 			else{
	// 				prev_node = node->getParent()->getIndexMap()->begin()->second;
	// 			}
	// 		}
	// 		else{
	// 			prev_node = nullptr;
	// 		}

	// 		if(next_node && next_node->getParent() == node->getParent() && next_node->getIndexMap()->size() > 1){
	// 			borrowKeyFromNextIndex(pos,node,next_node);
	// 		}
	// 		else if(prev_node && prev_node->getParent() == node->getParent() && prev_node->getIndexMap()->size() > 1){
	// 			borrowKeyFromPrevIndex(pos,node,prev_node);
	// 		}
	// 		else if(next_node && next_node->getParent() == node->getParent() && next_node->getIndexMap()->size() <= 1){
	// 			mergeNodeWithNextIndex(pos,node,next_node);
	// 		}
	// 		else if(prev_node && prev_node->getParent() == node->getParent() && prev_node->getIndexMap()->size() <= 1){
	// 			mergeNodeWithPrevIndex(pos,node,prev_node);
	// 		}
	// 	}
	// }
	// else if(!node->getMostLeftChild() && node->getDataMap()->size() < 1){
	// 	if(node == root){
	// 		return 1;
	// 	}
	// 	else{
	// 		BpTreeNode* next_node = node->getNext();
	// 		BpTreeNode* prev_node = node->getPrev();

	// 		if(next_node && next_node->getParent() == node->getParent() && next_node->getDataMap()->size() > 1){
	// 			borrowKeyFromNextData(node,next_node);
	// 		}
	// 		else if(prev_node && prev_node->getParent() == node->getParent() && prev_node->getDataMap()->size() > 1){
	// 			borrowKeyFromPrevData(node,prev_node);
	// 		}
	// 		else if(next_node && next_node->getParent() == node->getParent() && next_node->getDataMap()->size() <= 1){
	// 			mergeNodeWithNextData(node,next_node);
	// 		}
	// 		else if(prev_node && prev_node->getParent() == node->getParent() && prev_node->getDataMap()->size() <= 1){
	// 			mergeNodeWithPrevData(node,prev_node);
	// 		}
	// 	}

	// }
	// if(node->getParent()){
	// 	Delete(name,node->getParent());
	// }
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

// bool BpTree::deleteFromData(string name,BpTreeNode* node){
// 	node->deleteMap(name);
// 	if(node->getParent() && node->getParent()->getIndexMap()->find(name) != node->getIndexMap()->end()){
// 		node->getParent()->deleteMap(name);
// 		//if(node->getDataMap()->size() >= 1)
// 		node->getParent()->insertIndexMap(node->getDataMap()->begin()->first,node);
// 	}
// }

// bool BpTree::deleteFromIndex(string name,BpTreeNode* node){
// 	if(node->getIndexMap()->find(name) != node->getIndexMap()->end()){
// 		BpTreeNode* tmp = node->getIndexMap()->find(name)->second;
// 		BpTreeNode* mostLeastKey = tmp->getMostLeftChild();
// 		while(mostLeastKey->getMostLeftChild()){
// 			mostLeastKey = mostLeastKey->getMostLeftChild();
// 		}
// 		node->deleteMap(name);
// 		node->insertIndexMap(mostLeastKey->getDataMap()->begin()->first,tmp);
// 	}
// }

// bool BpTree::borrowKeyFromNextData(BpTreeNode* node,BpTreeNode* next){
// 	node->deleteMap(node->getDataMap()->begin()->first);
// 	node->insertDataMap(next->getDataMap()->begin()->first,next->getDataMap()->begin()->second);
// 	next->deleteMap(node->getDataMap()->begin()->first);
// 	node->getParent()->deleteMap(node->getDataMap()->begin()->first);
// 	node->getParent()->insertIndexMap(next->getDataMap()->begin()->first,next);
// }

// bool BpTree::borrowKeyFromPrevData(BpTreeNode* node,BpTreeNode* prev){
// 	node->getParent()->deleteMap(node->getDataMap()->begin()->first);
// 	node->deleteMap(node->getDataMap()->begin()->first);
// 	node->insertDataMap(prev->getDataMap()->rbegin()->first,prev->getDataMap()->rbegin()->second);
// 	prev->deleteMap(node->getDataMap()->begin()->first);
// 	node->getParent()->insertIndexMap(node->getDataMap()->begin()->first,node);
// }

// bool BpTree::mergeNodeWithNextData(BpTreeNode* node,BpTreeNode* next){
// 	node->insertDataMap(next->getDataMap()->begin()->first,next->getDataMap()->begin()->second);
// 	node->setNext(next->getNext());
// 	if(node->getNext()) next->getNext()->setPrev(node);
// 	node->getParent()->deleteMap(next->getDataMap()->begin()->first);
// 	next->deleteMap(next->getDataMap()->begin()->first);
// 	delete next;
// }
// bool BpTree::mergeNodeWithPrevData(BpTreeNode* node,BpTreeNode* prev){
// 	prev->insertDataMap(node->getDataMap()->begin()->first,node->getDataMap()->begin()->second);
// 	prev->setNext(node->getNext());
// 	if(prev->getNext()) prev->getNext()->setPrev(prev);
// 	node->getParent()->deleteMap(node->getDataMap()->begin()->first);
// 	node->deleteMap(node->getDataMap()->begin()->first);
// 	delete node;
// }


// bool BpTree::borrowKeyFromNextIndex(int pos,BpTreeNode* node,BpTreeNode* next){
// 	node->insertIndexMap()
// }
// bool BpTree::borrowKeyFromPrevIndex(int pos,BpTreeNode* node,BpTreeNode* prev){

// }
// bool BpTree::mergeNodeWithNextIndex(int pos,BpTreeNode* node,BpTreeNode* next){

// }
// bool BpTree::mergeNodeWithPrevIndex(int pos,BpTreeNode* node,BpTreeNode* prev){

// }
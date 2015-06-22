#include "huffman.h"
#include <iostream>

Huffman::Huffman(std::vector<long> counted){
	Heap h(counted);
	
	node* min1;
	node* min2;
	node* father;
	while(h.size() > 2){
		min1 = h.delete_pair();
		min2 = h.delete_pair();
		father = intro_nodes(min1,min2);
		h.intro_pair(father);
	}
	min1 = h.delete_pair();
	min2 = h.delete_pair();
	root = intro_nodes(min1,min2);
}

Huffman::node* Huffman::intro_nodes(Huffman::node* new1, Huffman::node* new2){
	node* father = new node;
	father->left = new1;
	father->right = new2;
	father->num = new1->num + new2->num;
	return father;
}

/*bool Huffman::is_leaf(Huffman::node* no){
	if ((no->left == nullptr) && (no->right == nullptr)){ return true; }
	return false;
}*/

void Huffman::path(Huffman::node* no, std::vector<std::vector<bool>>& all_paths, std::vector<bool> path_ch){
	if (no->is_leaf()){
		all_paths[(int)no->ch + 128] = path_ch;
	}else{
		auto path_ch_right = path_ch;
		path_ch.push_back(false);
		path(no->left, all_paths, path_ch);
		path_ch_right.push_back(true);
		path(no->right, all_paths,path_ch_right);
	}
}

//-----------------------------------------HEAP-----------------------------------------

Heap::Heap(std::vector<long> counted){
	for(int i=-128;i<((int)counted.size()-128);i++){
		Huffman::node* no = new Huffman::node;
		no->ch =(char)i;
		no->num = counted[i+128];
		no->left = no->right = nullptr;
		intro_pair(no)	;
		//std::cout << "entrou " << i << std::endl;
	}
}

int Heap::size(){
	return heap.size();
}

int Heap::min_children(int ind){
	int min_children = -1;
	int children_left = children(ind).first;
	int children_right = children(ind).second;
	if(children_left >= 0){
		if(children_right >= 0){
			if((heap[children_right]->num < heap[children_left]->num)){
				min_children = children_right;
			} else {
				min_children = children_left;
			}
		}else{
			min_children = children_left;
		}
	}
	return min_children;
}
//método que retorna true se a heap está corretamente ordenada e false caso contrário 
bool Heap::ok(){
	int i = 1;
	while(i <= (heap.size()/2)){
		if(heap[i-1] < heap[min_children(i-1)]){
			return false;
		}
		i++;
	}
	return true;
}

int Heap::parent(int ind){
	int ind_parent;

	ind_parent = ((ind+1)/2) - 1;

	return ind_parent;
}

std::pair<int,int> Heap::children (int ind){
	int size = heap.size();
	ind = ind + 1;
	if(2*ind-1 < size){
		if((2*ind < size)){
			return std::make_pair((2*ind)-1,2*ind);
		}else{
			return std::make_pair((2*ind)-1,-1);
		}
	}
	return std::make_pair(-1,-1);
}

void Heap::siftdown(int ind){
	int children_left;
	int children_right;
	int min;
	while (ind < (heap.size()/2)){
	 min = min_children(ind);
		if (min >= 0 && heap[min]->num < heap[ind]->num){
			swap(*heap[ind],*heap[min]);
			ind = min;
		} else {
			break;
		}
	}
}

void Heap::siftup(int ind){
	while ((ind > 0) && (heap[parent(ind)]->num > heap[ind]->num)){
		swap(*heap[ind],*heap[parent(ind)]);
		ind = parent(ind);;
	}
}

bool Heap::intro_pair(Huffman::node* p){
	heap.push_back(p);
	siftup(heap.size()-1);	
	if(ok()) return true;
	return false;	
}


Huffman::node* Heap::delete_pair(){
	int i = heap.size();
	auto no = heap[0];
	heap[0] = heap[i-1];
	heap.pop_back();
	siftdown(0);
	return no;
}

void Heap::swap(Huffman::node& p1, Huffman::node& p2){
	Huffman::node auxiliar = p1;
	p1 = p2;
	p2 = auxiliar;
}

void Heap::show(){
	for(int i = 0; i < heap.size();i++){
		std::cout << heap[i]->ch<<";"<<heap[i]->num<<"\n";
	}
}

bool Heap::is_heap() {
	bool is_h = true;
	for (int i=0 ; i<heap.size(); i++) {
		if ((children(i).first >= 0) && (heap[children(i).first]->num < heap[i]->num)) { 
			is_h = false;
			//std::cout << i << ", " << children(i).first << std::endl;
		}
		if (children(i).second >= 0 && heap[children(i).second]->num < heap[i]->num) { 
			is_h = false;
			//std::cout << i << ", " << children(i).second << std::endl;
		}
	}
	return is_h; 
}

bool Heap::is_empty(){
	if(heap.empty()){
		return true;
	}
	return false;
}

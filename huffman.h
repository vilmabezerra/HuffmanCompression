#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <vector>
#include <utility>	

class Heap;

class Huffman{
	friend class Heap;	
	public:
		struct node{
			char ch;
			long num;
			node* left;
			node* right;
			bool is_leaf(){
				if ((left == nullptr) && (right == nullptr)){ return true; }
				return false;
			};
		};
		Huffman(std::vector<long>);
		node* root;
		//bool is_leaf(node*);
		void path(node*, std::vector<std::vector<bool>>&, std::vector<bool>);
	private:
		node* intro_nodes(node*,node*);
};

class Heap{
	public:
		Heap(std::vector<long>);
		bool intro_pair(Huffman::node*);
		Huffman::node* delete_pair();
		void show();
		bool is_heap();
		bool is_empty();
		int size();

	private:
		std::vector<Huffman::node*> heap;
		bool ok();
		void swap(Huffman::node&,Huffman::node&);
		void siftdown(int);
		void siftup(int);
		int parent(int);
		std::pair<int,int> children (int);
		int min_children(int);
};


#endif //HUFFMAN_H

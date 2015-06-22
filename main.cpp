#include <iostream>
#include <string>
#include <vector>
#include "functions.h"
//#include "heap.h"
#include "huffman.h"


int main(int argc, char const *argv[]){
	std::string file_name;
	std::vector<long> counted;
	char decision;
	std::vector<bool> one_path;
	std::vector<std::vector<bool>> all_paths(256);
	bool right_answer = false;

	while(!right_answer){
		std::cout << "Você deseja comprimir (C) ou Descomprimir(D)?\n";
		std::cin >> decision;
		char comand = -1;

		if(decision == 'C'){
			std::cout << "Nome do arquivo de entrada: ";
			std::cin >> file_name;		

			counted = count(file_name);
			
			Huffman h(counted);

			/*//Passeando pela árvore
			Huffman::node* no = h.root;
			while((comand != 0) && (!no->is_leaf())){
				std::cout<<"L to left and R to right\n";
				std::cin>>comand;
				if(comand == 'L'){
					no = no->left;
					std::cout<<"char: "<< no->ch<<"\n";
				}else{
					no = no->right;
					std::cout<<"char: "<< no->ch << "\n";
				}
			}*/

			h.path(h.root,all_paths,one_path);
			compressing(file_name, all_paths, counted);

			std::cout<<"O arquivo comprimido está em "<<file_name<<"_compressed\n";
			right_answer = true;
		}else{
			if(decision == 'D'){
				std::cout << "Nome do arquivo comprimido: ";
				std::cin >> file_name;

				counted = count_to_descomp(file_name);

				Huffman h(counted);
				/*//Passeando pela árvore
				Huffman::node* no = h.root;
				while((comand != 0) && (!no->is_leaf())){
					std::cout<<"L to left and R to right\n";
					std::cin>>comand;
					if(comand == 'L'){
						no = no->left;
						std::cout<<"char: "<< no->ch<<"\n";
					}else{
						no = no->right;
						std::cout<<"char: "<< no->ch << "\n";
					}
				}*/

				descompressing(file_name,h.root);

				std::cout<<"O arquivo descomprimido está em "<<file_name<<"_descompressed\n";
				right_answer = true;
			}
		}
	}

	return 0;
}

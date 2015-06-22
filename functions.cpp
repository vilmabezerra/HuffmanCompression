#include "functions.h"

std::vector<long> count (std::string file){
	std::vector<long> count(256,0);
	char ch;
	std::ifstream inFile(file, std::ios::in | std::ios::binary);

	if(!inFile ) {
	std::cout<< "Não foi possivel abrir o arquivo de entrada1 : "<< file<<"\n";
	}else{
		while (inFile.get(ch)){
			count[ch-(-128)]++;
		}
	}
	return count;
}

std::vector<long> count_to_descomp (std::string file){
	std::vector <long> count(256);
	char ch;
	unsigned long long total;
	std::ifstream inFile(file, std::ios::in | std::ios::binary);

	inFile >> total;
	inFile.get(ch);

	for (int i=0 ; i<256; i++) {
		inFile >> count[i];
		inFile.get(ch);
	}
	return count;
}

void clear_block(char block[]){
	memset(block, 0, 512);
}

void set_clear_bit(bool bit, char block[], int bit_block){
	int num_char = bit_block/8;
	int i = bit_block%8;
	if(bit){
		block[num_char] |= 1 << i;
	}else{
		block[num_char] &= ~(1 << i);
	}
}

void push_block(char block[], std::ofstream &outFile, int quant){
	outFile.write(block,quant);
}

void head_outfile(std::ofstream &outFile, std::vector<long> counted){
	int i;
	long long total=0;
	for(i = 0; i<256;i++){
		total = total + counted[i];
	}
	outFile << total << std::endl;

	for(i = 0;i<256;i++){
		outFile << counted[i]<< " ";
	}

}

bool checking_bit(char ch, int i){
	int bit = (ch >> i) & 1;
	if(bit == 1){ return true; }
	return false;
}

bool if_leaf_push(Huffman::node* auxiliar, char block[], int &char_block, unsigned long long& total, std::ofstream &outFile){
	int block_size = 512;
	if(auxiliar->is_leaf()){
		if(char_block<block_size){
			block[char_block++] = auxiliar->ch;
		}else{
			if(total<block_size){
				push_block(block,outFile,total);
			}else{push_block(block,outFile,block_size);}
			clear_block(block);
			char_block = 0;
			block[char_block++] = auxiliar->ch;
			if ((long long)total - block_size < 0) total = 0;
			else total -= block_size;
		}
		return true;
	}
	return false;
}

void compressing(std::string file, std::vector<std::vector<bool>> paths, std::vector<long> counted){
	char ch;
	int auxiliar, path_c,size_path_c;
	int block_bit_size = 512*8;
	int bit_block = 0;
	int block_size = 512;
	char block[block_size];
	long long total=0;

	for(int i = 0; i<256;i++){
		total = total + counted[i];
	}


	std::ifstream inFile(file, std::ios::in | std::ios::binary);
	std::string  out_file = file + "_compressed";
	std::ofstream outFile(out_file, std::ios::out | std::ios::binary);
	
	head_outfile(outFile, counted);
	
	if(!inFile ) {
	std::cout<< "Não foi possivel abrir o arquivo de entrada2 : "<< file<< "\n";
	}else{
		while (inFile.get(ch)){
			path_c = ch+128;
			size_path_c = paths[path_c].size();
			auxiliar=0;
			while(auxiliar< size_path_c){
				if(bit_block<block_bit_size){
					set_clear_bit(paths[path_c][auxiliar],block,bit_block);
				}else{
					push_block(block,outFile, block_size);
					clear_block(block);
					bit_block = 0;
					set_clear_bit(paths[path_c][auxiliar],block,bit_block);
				}
				auxiliar++;
				bit_block++;
			}
		}
		if(total != 0)	{push_block(block,outFile,block_size);}
	}
}

void descompressing(std::string file, Huffman::node* root){
	char ch = 'a';
	Huffman::node* auxiliar = root;
	std::vector <long> count(256);
	unsigned long long total;
	bool bit;
	int char_block = 0;
	int block_size = 512;
	char block[block_size];

	std::string  out_file = file + "_descompressed";
	std::ofstream outFile(out_file, std::ios::out | std::ios::binary);
	std::ifstream inFile(file, std::ios::in | std::ios::binary);
	inFile >> total;
	inFile.get(ch);

	for (int i=0 ; i<256; i++) {
		inFile >> count[i];
		inFile.get(ch);
	}

	while(total>0){
		inFile.get(ch);
		for(int i = 0; i<8; i++){
			bit = checking_bit(ch,i);
			if(bit){
				auxiliar = auxiliar->right;
				if(if_leaf_push(auxiliar, block,char_block,total,outFile)){
					auxiliar = root;
				}
			}else{
				auxiliar = auxiliar->left;
				if(if_leaf_push(auxiliar,block,char_block,total,outFile)){
					auxiliar = root;
				}
			}
		}
	}
}

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include "huffman.h"

std::vector<long> count (std::string);
std::vector<long> count_to_descomp (std::string);
void clear_block(char[]);
void set_clear_bit(bool, char[], int);
void push_block(char[], std::ofstream&,int);
void head_outfile(std::ofstream&, std::vector<long>);
bool checking_bit(char, int);
bool if_leaf_push(Huffman::node*, char[], int&, unsigned long long&,std::ofstream&);
void compressing(std::string, std::vector<std::vector<bool>>, std::vector<long>);
void descompressing(std::string, Huffman::node*);

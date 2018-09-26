#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "structure.h"

int getStrLen(char* str){
	int i = 0;
	while(str[i] != '\0'){
		i++;
	}
	return i;
}

void strAddChar( char* src, char* dest, char c){
	int i= 0;
	while(src[i] == '1' || src[i] == '0'){
		dest[i] = src[i];
		i++;
	}
	dest[getStrLen(src)]=c;
	dest[getStrLen(src)+1]='\0';
	//printf("src:%s,dest:%s,ch:%c\n",src,dest,c);
}

void generateCode(Node* tree, char* code){
	if (tree != NULL){
		if ( tree->type == 'n'){
			tree->code = code;
			//printf("char:%d freq:%d code:%s\n",(unsigned char)tree->ch,tree->freq,tree->code);
		}
		if (tree->left != NULL){
			char* lcode = malloc(sizeof(char)*(getStrLen(code)+1));
			strAddChar(code,lcode,'0');
			generateCode(tree->left, lcode);	
		}
		if (tree->right != NULL){
			char* rcode = malloc(sizeof(char)*(getStrLen(code)+1));
			strAddChar(code,rcode,'1');
			generateCode(tree->right, rcode);		
		}
	}
}

void reinsertNodeToList(Node* tree, List* chList){
	if (tree != NULL){
		if ( tree->type == 'n'){
			printf("insertL(&chList,makeNode(%d,%d));\n",(unsigned char)tree->ch,(unsigned int)tree->freq);
			//insertL(chList,tree);
		}
		if (tree->left != NULL){
			reinsertNodeToList(tree->left, chList);
		}
		if (tree->right != NULL){
			reinsertNodeToList(tree->right, chList);
		}
	}
}

void buildHuffmanTree(List* chList){
	Node* tmpTree;
	Node* tmpNode = chList->node;
	//int i;
	if (chList->length == 1){
		chList->node->code = malloc(sizeof(char));
		chList->node->code[0]=0;
	}else {
		while (chList->length>1){
			tmpTree = makeNode(255,0);
			tmpTree->type = 'c';
			tmpTree->right = popL(chList);
			tmpTree->left = popL(chList);
			tmpTree->freq = tmpTree->left->freq + tmpTree->right->freq;
			insertL(chList,tmpTree);
		}
		tmpTree = popL(chList);
		char* code= malloc(sizeof(char));
		code[0] = '\0';
		generateCode(tmpTree,code);
		chList->node = tmpNode;
		Node* current = chList->node;
		while(current != NULL){
			if (current->type == 'n'){
				if (current->code[getStrLen(current->code)-1] == '1' || current->code[getStrLen(current->code)-1] == '0'){
				} else {
					current->code[getStrLen(current->code)-1] = '\0';
				}
			}
			current = current->next;
		}
	}
}

/*
int main(){
	Node* tree;
	List chList;
	int codeTable[100];
	int i;
	chList.length = 0;
	Node* node;
	chList = insertL(chList,makeNode(117,1));
	chList = insertL(chList,makeNode(108,1));
	chList = insertL(chList,makeNode(107,1));
	chList = insertL(chList,makeNode(103,1));
	chList = insertL(chList,makeNode(88,1));
	chList = insertL(chList,makeNode(86,1));
	chList = insertL(chList,makeNode(85,1));
	showL(chList);
	printf("===============\n");
	buildHuffmanTree(chList);
	fillTable(codeTable, tree, 9, chList.length);
	return 0;
}*/

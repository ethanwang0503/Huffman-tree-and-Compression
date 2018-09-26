#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void showL(List L) {
	Node* current = L.node;
	while(current != NULL){
		if (current->type == 'n'){
			printf("ch:%d freq:%d type %c code:%s\n",(unsigned char)current->ch,(unsigned int)current->freq,current->type,current->code);
		}
		current = current->next;
	}
	
}

void showNode(Node* node) {
	printf("ch:%d freq:%d type %c code:%s\n",(unsigned char)node->ch,(unsigned int)node->freq,node->type,node->code);
}

Node* makeNode(char ch, unsigned int freq) {
	Node* new = malloc(sizeof(Node));
	new->ch = ch;
	new->freq = freq;
	new->code = 0;
	new->type = 'n';
	new->next = NULL;
	new->left = NULL;
	new->right = NULL;
	return new;
}

void freeN(Node* node){
	if ( node== NULL && node->left == NULL && node->right == NULL){
		free(node->code);
		free(node);		
	}else{
		if (node->next != NULL){
			freeN(node->next);
		}
		if (node->left != NULL){
			freeN(node->left);
		}
		if (node->right != NULL){
			freeN(node->right);
		}
	}
}


void freeL(List* L){
	if (L->node != NULL){
		freeN(L->node);
	}
	free(L);
}


void insertL(List* L,Node* new) {
	if (L->length == 0){
		L->node = new;
		L->length++;
		return;
	}else if (L->length == 1){
		if ( (new->freq > L->node->freq) || ( new->freq == L->node->freq && (unsigned char)new->ch < (unsigned char)L->node->ch) ){
			L->node->next = new;
			
		}else{
			new->next = L->node;
			L->node = new;
		}
		L->length++;
		return;
	}else{
		if ( (new->freq < L->node->freq) || ( new->freq == L->node->freq && (unsigned char)new->ch > (unsigned char)L->node->ch) ){
			new->next = L->node;
			L->node = new;
			L->length++;
			return;
		}else{
			Node* current = L->node;
			while(current->next != NULL){
				if ((new->freq < current->next->freq) || (new->freq == current->next->freq && (unsigned char)new->ch > (unsigned char)current->next->ch)){
					new->next = current->next;
					current->next = new;
					L->length++;
					return;
				} else {
					current = current->next;
				}
			}
			if(current->next == NULL){
				current->next = new;
				L->length++;
				return;
			}
		}
	}
}

void deleteL(List* L, char ch) {
	Node* previous = L->node;
	Node* current = L->node;
	if (L->node->ch == ch){
		L->node = L->node->next;
	} else {
		while(current->ch != ch && current->next != NULL ){
			previous = current;
			current = current->next;
		}
		previous->next = current->next;
	}
	L->length--;
}

Node* popL(List* L) {
	Node* current = NULL;
	if ( L != NULL){
		current = L->node;
		L->node = L->node->next;
		L->length--;
	}
	return current;
}

/*
int main(void){
	Node* node;
 	List chList;
	chList.length = 0;
insertL(&chList,makeNode(72,672));
insertL(&chList,makeNode(94,331));
insertL(&chList,makeNode(228,83));
insertL(&chList,makeNode(173,21));
insertL(&chList,makeNode(179,21));
insertL(&chList,makeNode(142,40));
insertL(&chList,makeNode(71,164));
insertL(&chList,makeNode(20,655));
insertL(&chList,makeNode(46,328));
insertL(&chList,makeNode(73,164));
insertL(&chList,makeNode(163,81));
insertL(&chList,makeNode(187,81));
insertL(&chList,makeNode(80,651));
insertL(&chList,makeNode(87,324));
insertL(&chList,makeNode(189,81));
insertL(&chList,makeNode(244,81));
insertL(&chList,makeNode(223,161));
insertL(&chList,makeNode(198,646));
insertL(&chList,makeNode(219,160));
insertL(&chList,makeNode(209,80));
insertL(&chList,makeNode(33,79));
insertL(&chList,makeNode(92,318));
insertL(&chList,makeNode(6,1267));
insertL(&chList,makeNode(96,318));
insertL(&chList,makeNode(77,157));
insertL(&chList,makeNode(154,40));
insertL(&chList,makeNode(227,39));
insertL(&chList,makeNode(123,76));
insertL(&chList,makeNode(49,629));
insertL(&chList,makeNode(3,621));
insertL(&chList,makeNode(180,311));
insertL(&chList,makeNode(11,308));
insertL(&chList,makeNode(16,1223));
insertL(&chList,makeNode(100,605));
insertL(&chList,makeNode(132,604));
insertL(&chList,makeNode(141,1208));
insertL(&chList,makeNode(12,1203));
insertL(&chList,makeNode(127,76));
insertL(&chList,makeNode(218,76));
insertL(&chList,makeNode(75,150));
insertL(&chList,makeNode(217,150));
insertL(&chList,makeNode(164,75));
insertL(&chList,makeNode(181,74));
insertL(&chList,makeNode(236,592));
insertL(&chList,makeNode(131,2371));
insertL(&chList,makeNode(232,1182));
	showL(chList);
}*/

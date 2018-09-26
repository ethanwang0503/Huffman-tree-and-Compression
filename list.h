typedef struct Node {
	char ch;	//read 8-bits as a char;
	unsigned int freq;	//the frequency of ch in input file.
	char* code; 	// binary code in string type.
	char type;  	//'n' for node, 'c' for combine node;
	struct Node *next,*left,*right; // next pointer for pQueue, left and right points for tree.
} Node;


typedef struct{
	int length;
	Node* node;
} List;

Node* makeNode(char, unsigned int);
void insertL(List*, Node*);
void deleteL(List* , char);
Node* popL(List*);
void showL(List);
void showNode(Node*);
void freeL(List*);


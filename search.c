#include "decode.h"
#define d 256
#define SEARCHBUF 300
int searchRk(char* pat, char* txt){
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;
    int q = 3;
    int count = 0;
    for (i = 0; i < M-1; i++){ h = (h*d)%q;}
    for (i = 0; i < M; i++){
        p = (d*p + pat[i])%q;
        t = (d*t + txt[i])%q;
    }
 
    for (i = 0; i <= N - M; i++){
        if ( p == t ){
            for (j = 0; j < M; j++){
                if (txt[i+j] != pat[j])
                    break;
            }
            if (j == M){count++;}
        }

        if ( i < N-M ){
            t = (d*(t - txt[i]*h) + txt[i+M])%q;
            if (t < 0){t = (t + q);}
        }
    }
    return count;
}

void initSearch(FILE* fpin, Data* data, unsigned int* dataLen, List* chList, char* text, int* textIndex, int* currentBits){
	int i;
	// Init Data;
	data->length = 0;
	for (i = 0; i< BUF; i++){
		data->bitarray[i] = 0;
	}
	// HuffmanCode and fread file to generate data, and write into target file.
	(*dataLen) = 0;
	Node* current = chList->node;
	while(current != NULL){
		if ( current->type == 'n'){
			(*dataLen) += current->freq;
		}
		current = current->next;
	}
	(*currentBits) = 0;
	(*textIndex) = 0;
	text[(*textIndex)] = '\0';
}

int fillText( FILE* fpin, Data* data, unsigned int* dataLen, List* chList, char* text, int* textIndex,  int* currentBits){
	char* code = malloc(sizeof(char)*512);
	code[0]='\0';
	int codeLen = 0;
	int bit = 1;
	while( bit != -1 && (*dataLen) > 0 && (*textIndex) < SEARCHBUF*2){
		bit = read_bit(fpin, currentBits, data);
		if ( bit != -1){
			if ( bit == 1 ){
				code[codeLen] = '1';
				code[codeLen+1] = '\0';
				codeLen++;
			}else if ( bit == 0 ){
				code[codeLen] = '0';
				code[codeLen+1] = '\0';
				codeLen++;
			}
			Node* current = chList->node;
			while(current != NULL && codeLen > 0){
				if ( current->type == 'n'){
					if (strcmp(current->code, code) == 0){
						text[(*textIndex)] = current->ch;
						text[(*textIndex)+1] = '\0';
						(*textIndex)++;
						codeLen = 0;
						(*dataLen)--;
					}
				}
				current = current->next;
			}
		}
	}
	return (*dataLen);
}


int search(char* pattern , char* inputPath ){
	Header header;
	Data data;
	List chList;
	chList.length = 0;
	FILE *fp;
	if ((fp = fopen(inputPath,"rb")) == NULL) {
        	exit(1);
    	}
	// Store the Dictionary into the header;
	getHeaderFromFile(fp, &header, &chList);
	// Find the pattern in file
	int result = 0,i=0,patLen = strlen(pattern);

	char text[SEARCHBUF*2+1];
	int textIndex;
	int currentBits;
	unsigned int dataLen  = 0;
	initSearch(fp, &data, &dataLen, &chList, text, &textIndex, &currentBits);
	while( dataLen > 0 ){
		dataLen = fillText(fp, &data, &dataLen, &chList, text, &textIndex,  &currentBits);
		result += searchRk(pattern, text);
		for(i=0; i<patLen-1;i++){
			text[i] = text[SEARCHBUF*2-patLen+1+i];
		}
		for(i=patLen-1; i<SEARCHBUF*2;i++){
			text[i] = '\0';
		}
		textIndex=patLen-1;
	}
	fclose(fp);
	return result;
}

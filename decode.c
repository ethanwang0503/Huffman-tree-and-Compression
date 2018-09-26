#include "decode.h"

void getHeaderFromFile(FILE* fp, Header* header,List* chList){
	Node* node = NULL;
	int i;
	// // Init Header;
	for (i = 0; i< 256; i++){
		header->freq[i] = 0;
	}
	// // Read data into Header;
	fread(header,sizeof(Header),1,fp);
	// Rebuild List
	for (i = 0; i< 256; i++){
		if (header->freq[i] > 0){
			node = makeNode(i,header->freq[i]);
			insertL(chList,node);
			//printf("id:%d len:%d, %d\n",i, chList->length,i==chList->length-1);
		}
	}
	// Rebuild Huffman Tree.
	buildHuffmanTree(chList);
	//showL(*chList);
}

int read_bit(FILE *fp, int* currentBits, Data* data) {
	int bit;
	if ((*currentBits) == data->length) {
		if (feof(fp)){
			return -1;
		}else {
            		size_t bytes_read = fread(data->bitarray, 1, BUF, fp);
            		if (bytes_read < BUF) {
                		if (feof(fp)){return 0;}
            		}
            		data->length = bytes_read << 3;
            		(*currentBits) = 0;
        	}
    	}

    	if (data->length == 0) return -1;
    	bit = (data->bitarray[(*currentBits) >> 3] >> (7 - (*currentBits) % 8)) & 0x1;
    	(*currentBits)++;
	return bit;
}

void writeFile( FILE* fpin, Header* header, Data* data, List* chList, char* outputPath ){
	FILE* fpout = fopen(outputPath,"wb");
	int bit,currentBits ,i;
	unsigned int dataLen  = 0;
	// Init Data;
	data->length = 0;
	for (i = 0; i< BUF; i++){
		data->bitarray[i] = 0;
	}
	// HuffmanCode and fread file to generate data, and write into target file.
	bit = 1;
	currentBits = 0;
	char* code = malloc(sizeof(char)*256);
	code[0]='\0';
	//initCodeList(code,256);
	int codeLen = 0;
	for (i = 0; i< 256; i++){
		if (header->freq[i] > 0 ){
			dataLen += header->freq[i];
		}
	}
	while( bit != -1 && dataLen > 0){
		bit = read_bit(fpin, &currentBits, data);
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
						fwrite(&current->ch, 1, 1, fpout);
						codeLen = 0;
						dataLen--;
					}
				}
				current = current->next;
			}
		}
	}
	fclose(fpout);
}


int decode(char* inputPath, char* outputPath){
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
	writeFile(fp, &header,&data, &chList, outputPath);
	fclose(fp);
	return 0;
}


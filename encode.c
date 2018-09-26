#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "hcode.h"
#include "structure.h"

int statCharFromInput( unsigned int* statData, char* inputPath ){
	FILE *fp;
    	if ((fp = fopen(inputPath,"rb")) == NULL) {
        	return 1;
    	}
	char buffer[1024];
	unsigned int i,length = 1024;
	// Init Statistic Array
	for (i = 0; i< 256; i++){
		statData[i] = 0;
	}
	//Loop the file til EOF
	if(fp){
		while( length == 1024){
			length = fread(buffer, 1, 1024, fp);
			for ( i=0; i< length; i++){
				statData[(unsigned char)buffer[i]]++;
			}
		}
		fclose(fp);
	}
	return 0;
}

void getDicToHeader(unsigned int* statData, Header* header,List* chList){
	Node* node;
	chList->length = 0;
	unsigned int sumSize = 0,i;
	// // Init Header;
	for (i = 0; i< 256; i++){
		header->freq[i] = 0;
	}
	// Fill data into Header buffer;
	for (i = 0; i< 256; i++){
		if (statData[i] > 0){
			sumSize += statData[i];
			node = makeNode(i,statData[i]);
			//showNode(node);
			insertL(chList,node);
		}
	}
	// Create Huffman Tree and use the code to fill the header.
	buildHuffmanTree(chList);
	Node* current = chList->node;
	while(current != NULL){
		if (current->type == 'n'){
			header->freq[(unsigned char)current->ch] = (unsigned int)current->freq;
		}
		current = current->next;
	}
}


unsigned int write_bit(FILE *fp, Data* data, unsigned int bit) {
	unsigned int i;
	if (data->length == BUF << 3) {
		size_t bytes_written = fwrite(data->bitarray, 1, BUF, fp);
		if (bytes_written < BUF && ferror(fp)){
			return -1;
		}
		data->length = 0;
		for (i = 0; i< BUF; i++){
			data->bitarray[i] = 0;
		}
	}
	if (bit == '1'){
		data->bitarray[data->length >> 3] |= (0x1 << (7 - data->length % 8));
	}    
	++data->length;
	return 0;
}

void writeData( char* inputPath, Header* header, Data* data, List* chList, char* outputPath ){
	unsigned int i;
	char ch;
	char* dict[256];
	FILE* fpin = fopen(inputPath,"rb");
	FILE* fpout = fopen(outputPath,"wb");
	// Write Header
	fwrite(header,sizeof(Header),1,fpout);
	// Init Data;
	data->length = 0;
	for (i = 0; i< BUF; i++){
		data->bitarray[i] = 0;
	}
	// Put code in dictionary
	Node* current = chList->node;
	while(current != NULL){
		dict[(unsigned char)current->ch] = current->code;
		current = current->next;
	}
	// HuffmanCode and fread file to generate data, and write into target file.
	while ((ch = fgetc(fpin)) != EOF){
		char* cp = dict[(unsigned char)ch];
		while(*cp =='0' || *cp =='1' ){
			if( write_bit(fpout, data, *cp)){exit(1);}
			//printf("%c",*cp);
			cp++;
		}
	}
	fclose(fpin);
	if (data->length != 0){
		unsigned int i = BUF*8 - data->length + 1;
		while(i){
			if(write_bit(fpout, data, '0') == -1){exit(1);}
			i--;
		}
	}
	fclose(fpout);
}

unsigned int encode(char* inputPath, char* outputPath){
	unsigned int statData[256];
	Header header;
	Data data;
	List chList;
	// Statistic the Char from the input file;
	if (statCharFromInput(statData, inputPath)){
		return 0;	
	}
	// Store the Dictionary into the header;
	getDicToHeader(statData, &header, &chList);
	writeData(inputPath, &header, &data, &chList,outputPath);
	return 0;
}



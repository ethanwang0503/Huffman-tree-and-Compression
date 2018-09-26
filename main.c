#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "encode.h"
#include "decode.h"
#include "search.h"

int main(int argc, char *argv[]){
	int opt = 0;
	char* input;
	char* output;
	char* pattern;
	opt = getopt(argc, argv, ":e:d:s:t:");
	switch (opt)
	{
		case 'e':
			input = argv[2];
			output = argv[3];
			return encode(input,output);
		case 'd':
			input = argv[2];
			output = argv[3];
			return decode(input,output);
		case 's':
			pattern = argv[2];
			input = argv[3];
			printf("%d\n",search(pattern,input));
		default:// Other case
			exit(1);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "hcode.h"
#include "structure.h"
int decode(char* , char* );
void getHeaderFromFile(FILE* , Header* ,List* );
int read_bit(FILE*, int* , Data* );

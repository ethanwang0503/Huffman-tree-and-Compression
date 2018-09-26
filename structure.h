#define BUF 1
typedef struct{
	unsigned int length;
	char bitarray[BUF];
} Data;

typedef struct{
	unsigned int freq[256];
} Header;


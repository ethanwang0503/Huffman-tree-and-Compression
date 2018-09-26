huffman: main.o encode.o decode.o list.o hcode.o search.o
	gcc -o huffman main.o encode.o decode.o list.o hcode.o search.o

main.o: main.c
	gcc -Wall -Werror -c main.c

encode.o: encode.c
	gcc -Wall -Werror -c encode.c

decode.o: decode.c
	gcc -Wall -Werror -c decode.c

search.o: search.c decode.c
	gcc -Wall -Werror -c search.c decode.c

list.o: list.c
	gcc -Wall -Werror -c list.c

hcode.o: hcode.c list.h
	gcc -Wall -Werror -c hcode.c list.h

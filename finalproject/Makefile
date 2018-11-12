project: main.o lzwcompress.o lzwdecompress.o huffcompress.o huffdecompress.o
	cc main.o lzwcompress.o lzwdecompress.o huffcompress.o huffdecompress.o table.o leaftree.o list.o treestack.o -o project
main.o: main.c functions.h
	cc -c main.c
table.o: table.c table.h
	cc -c table.c 
leaftree.o: leaftree.c leaftree.h
	cc -c leaftree.c 
list.o: list.c list.h
	cc -c list.c
treestack.o: treestack.c treestack.h
	cc -c treestack.c
lzwcompress.o: lzwcompress.c table.o functions.h
	cc -c lzwcompress.c
lzwdecompress.o: lzwdecompress.c table.o functions.h
	cc -c lzwdecompress.c
huffcompress.o: huffcompress.c leaftree.o list.o functions.h
	cc -c huffcompress.c
huffdecompress.o: huffdecompress.c treestack.o functions.h
	cc -c huffdecompress.c
clean:
	rm *.o

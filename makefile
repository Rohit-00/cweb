build: parser.o main.o handler.o formatter.o
	gcc obj/main.o obj/parser.o obj/handler.o obj/formatter.o -o bin/app

parser.o: src/parser.c 
	gcc -Iinclude -c src/parser.c -o obj/parser.o 

main.o: src/main.c 
	gcc -Iinclude -c src/main.c -o obj/main.o 

handler.o: src/handler.c 
	gcc -Iinclude -c src/handler.c -o obj/handler.o

formatter.o: src/formatter.c 
	gcc -Iinclude -c src/formatter.c -o obj/formatter.o

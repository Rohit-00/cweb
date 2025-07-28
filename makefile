.PHONY: build dirs clean

build: dirs parser.o main.o handler.o formatter.o database.o
	gcc obj/main.o obj/parser.o obj/handler.o obj/formatter.o obj/database.o -o bin/app

dirs:
	mkdir -p obj bin database

parser.o: src/parser.c | dirs
	gcc -Iinclude -c src/parser.c -o obj/parser.o 

main.o: src/main.c | dirs
	gcc -Iinclude -c src/main.c -o obj/main.o 

handler.o: src/handler.c | dirs
	gcc -Iinclude -c src/handler.c -o obj/handler.o

formatter.o: src/formatter.c | dirs
	gcc -Iinclude -c src/formatter.c -o obj/formatter.o

database.o: src/database.c | dirs
	gcc -Iinclude -c src/database.c -o obj/database.o

clean:
	rm -rf obj bin database

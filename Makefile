bin_vis: main.o
	clang -Wall -Wextra -lm -o bin_vis main.o

main.o: src/main.c
	clang -Wall -Wextra -c src/main.c

clean:
	rm *.o

clean_output:
	rm -rf output

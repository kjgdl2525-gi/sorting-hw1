CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -O2
CPPFLAGS = -Isrc
SORT_SRC = src/sort.c src/insertionSort.c src/mergeSort.c src/heapSort.c
.PHONY: run test bench sanitize clean
src/main.out: src/main.c $(SORT_SRC) src/sort.h
	$(CC) $(CPPFLAGS) $(CFLAGS) src/main.c $(SORT_SRC) -o $@
tests/test_sort.out: tests/test_sort.c $(SORT_SRC) src/sort.h
	$(CC) $(CPPFLAGS) $(CFLAGS) tests/test_sort.c $(SORT_SRC) -o $@
run: src/main.out
	./src/main.out
test: tests/test_sort.out
	./tests/test_sort.out
bench: src/main.out
	./src/main.out > report/results.csv
sanitize:
	$(CC) $(CPPFLAGS) -std=c17 -Wall -Wextra -g -O1 -fsanitize=address,undefined tests/test_sort.c $(SORT_SRC) -o tests/sanitize.out
	./tests/sanitize.out
clean:
	rm -f src/*.out tests/*.out

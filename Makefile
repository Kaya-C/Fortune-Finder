fortuneFinder:	initializer.c	grid.c	status.c main.c
		gcc -o fortuneFinder	initializer.c	grid.c	status.c main.c

gtest:		initializer.c	grid.c	status.c	 main.c
		gcc -o gtest --coverage	initializer.c	grid.c	status.c	main.c

gcov: gtest
	gcov gtest-main.c
	gcov gtest-initializer.c
	gcov gtest-grid.c
	gcov gtest-status.c

clean:
	rm -f fortuneFinder gtest *gcda *.o *.gcno *.gcov test_results.txt

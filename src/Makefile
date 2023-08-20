..PHONY: all install uninstall clean dvi dist tests check memcheck test
CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
OS = $(shell uname -s)
GCOVFLAGS = -fprofile-arcs -ftest-coverage
SRCS = unit_test/unit_tests.cc  model/*.cc model/**/*.cc
LC = lcov -c -d .

all: install

clean:
	rm -rf *.o *.gcno *.gcda *.info test.out
	rm -rf ./report
	rm -rf *.dSYM
	rm -rf *.gch
	rm -fr test
	rm -rf gcov_test
	rm -rf gcov_report/

rebuild: clean all

test: clean
	$(CC) $(CFLAGS) $(SRCS) -lgtest -pthread -o test
	./test

tests: test

memcheck: test
ifeq ($(OS), Darwin)
	leaks -atExit -- ./test
else
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
endif


gcov_report: clean
	$(CC) $(CFLAGS) $(GCOVFLAGS) -o gcov_test -lgtest -pthread  $(SRCS)
	./gcov_test
	$(LC) -t "gcov_report" --no-external -o report.info || true
	geninfo . --ignore-errors mismatch --output-filename report.info
	genhtml -o gcov_report report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./gcov_report/index-sort-f.html

install: uninstall 
	make clean
	mkdir build
	cd view/3d_viewer && qmake && make && make clean && rm Makefile && cd ../../ && mv view/3d_viewer/3dv.app build

uninstall:
	rm -rf build


dist: install
	rm -rf Archive_3dv/
	mkdir Archive_3dv/
	mkdir Archive_3dv/src
	mv ./build/3dv.app Archive_3dv/src/
	tar cvzf Archive_3dv.tgz Archive_3dv/
	rm -rf Archive_3dv/

dvi:
	open readme_3dviewer.md 

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cc
	clang-format -n ./*/*.cc
	clang-format -n ./*/*.h
	clang-format -n ./*/*/*.cc
	clang-format -n ./*/*/*.h
	rm -rf .clang-format




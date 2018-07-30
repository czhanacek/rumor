
LIBRARIES=
all:
	g++ -g -std=c++14 *.cpp -o rumor $(LIBRARIES)

run:
	make all
	./rumor
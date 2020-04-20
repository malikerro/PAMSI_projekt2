# dla przypomnienia: 
# Jeśli chciałbym skompilować to bez makefifa,
# to muszę wrzucić wszystko do jednego folderu i odpalić komendę:
# g++ main.cpp testy.cpp algorytmy.cpp (ew. więcej plików składowych
# w zachowanej kolejności - main -> pliki2-korzystający z plik1 -> plik1 i tp.)
# program odpalamy: ./a.exe

#  To sa opcje dla kompilacji
CXXFLAGS=-g -Iinc -Wall -pedantic #-std=c++0x

__start__: projekt_1
	./projekt_1

projekt_1: main.o testy.o algorytmy.o
	g++ -Wall -pedantic main.o testy.o algorytmy.o -o projekt_1

main.o: main.cpp
	g++ -c ${CXXFLAGS} main.cpp

testy.o: testy.cpp
	g++ -c ${CXXFLAGS} testy.cpp

algorytmy.o: algorytmy.cpp
	g++ -c ${CXXFLAGS} algorytmy.cpp

clean:
	rm *.o projekt_1.exe
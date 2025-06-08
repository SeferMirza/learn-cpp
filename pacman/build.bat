del pacman.exe
del test.o
g++ -c main.cpp -o test.o -IC:\projects\SFML-2.6.1\include
g++ .\test.o -o pacman.exe -LC:\projects\SFML-2.6.1\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main
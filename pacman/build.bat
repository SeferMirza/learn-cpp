del pacman.exe
del test.o
g++ -I"C:\SFML-2.6.0\include" -c main.cpp -o test.o
g++ -L"C:\SFML-2.6.0\lib" .\test.o -o pacman.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main

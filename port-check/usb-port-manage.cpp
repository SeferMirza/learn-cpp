#include <iostream>
#include <cstdlib>
#include <windows.h>

int main() {
    // COM5 portunu devre dışı bırak
    system("devcon disable COM5");
    std::cout << "Seri port devre dışı bırakıldı." << std::endl;

    // 3 saniye bekle
    Sleep(3000);

    // COM5 portunu tekrar etkinleştir
    system("devcon enable COM5");
    std::cout << "Seri port tekrar etkinleştirildi." << std::endl;

    return 0;
}
#include "spreadsheet.h"
#include <iostream>

int main() {
    SpreadSheet sheet(3, 3);

    std::cout << "Original Sheet:" << std::endl;
    std::cout << sheet << std::endl;

    sheet.mirrorH();
    std::cout << "Mirror Horizontal:" << std::endl;
    std::cout << sheet << std::endl;

    sheet.mirrorV();
    std::cout << "Mirror Vertical:" << std::endl;
    std::cout << sheet << std::endl;

    sheet.mirrorD();
    std::cout << "Mirror Diagonal:" << std::endl;
    std::cout << sheet << std::endl;

    sheet.mirrorSD();
    std::cout << "Mirror Secondary Diagonal:" << std::endl;
    std::cout << sheet << std::endl;

    return 0;
}

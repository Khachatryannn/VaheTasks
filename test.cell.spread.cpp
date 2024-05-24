#include "cell.h"
#include "spreadsheet.h"
#include <cassert>
#include <iostream>
#include <vector>

void testCell() {
    // Test constructors
    Cell c1;
    Cell c2(42);
    Cell c3(3.14);
    Cell c4('a');
    Cell c5(true);
    Cell c6("hello");
    std::vector<int> vec = {1, 2, 3};
    Cell c7(vec);

    // Test copy constructor
    Cell c8(c6);
    assert(c8 == c6);

    // Test move constructor
    Cell c9(std::move(c8));
    assert(c9 == c6);

    // Test assignment operators
    c1 = 100;
    assert(c1 == Cell(100));
    c1 = 2.71;
    assert(c1 == Cell(2.71));
    c1 = 'b';
    assert(c1 == Cell('b'));
    c1 = false;
    assert(c1 == Cell(false));
    c1 = "world";
    assert(c1 == Cell("world"));
    c1 = vec;
    assert(c1 == Cell(vec));

    // Test type conversion operators
    assert(static_cast<int>(c2) == 42);
    assert(static_cast<double>(c3) == 3.14);
    assert(static_cast<char>(c4) == 'a');
    assert(static_cast<bool>(c5) == true);
    assert(static_cast<std::string>(c6) == "hello");
    assert(static_cast<std::vector<int>>(c7) == vec);

    std::cout << "All Cell tests passed!" << std::endl;
}

void testSpreadSheet() {
    // Test constructors
    SpreadSheet sheet1;
    SpreadSheet sheet2(3);
    SpreadSheet sheet3(3, 4);

    // Test copy constructor
    sheet2[0][0] = 1;
    sheet2[1][1] = 2;
    sheet2[2][2] = 3;
    SpreadSheet sheet4(sheet2);
    assert(sheet4 == sheet2);

    // Test move constructor
    SpreadSheet sheet5(std::move(sheet4));
    assert(sheet5 == sheet2);

    // Test assignment operators
    sheet1 = sheet2;
    assert(sheet1 == sheet2);
    SpreadSheet sheet6;
    sheet6 = std::move(sheet5);
    assert(sheet6 == sheet2);

    // Test element access
    assert(sheet6[0][0] == Cell(1));
    assert(sheet6[1][1] == Cell(2));
    assert(sheet6[2][2] == Cell(3));

    // Test mirror operations
    SpreadSheet sheet7 = sheet2;
    sheet7.mirrorH();
    assert(sheet7[0][3] == Cell(1));
    assert(sheet7[1][2] == Cell(2));
    assert(sheet7[2][1] == Cell(3));

    sheet7 = sheet2;
    sheet7.mirrorV();
    assert(sheet7[2][0] == Cell(1));
    assert(sheet7[1][1] == Cell(2));
    assert(sheet7[0][2] == Cell(3));

    sheet7 = sheet2;
    sheet7.mirrorD();
    assert(sheet7[0][0] == Cell(1));
    assert(sheet7[1][1] == Cell(2));
    assert(sheet7[2][2] == Cell(3));

    sheet7 = sheet2;
    sheet7.mirrorSD();
    assert(sheet7[0][2] == Cell(3));
    assert(sheet7[1][1] == Cell(2));
    assert(sheet7[2][0] == Cell(1));

    // Test rotation
    sheet7 = sheet2;
    sheet7.rotate(1);
    assert(sheet7[0][0] == Cell(0));
    assert(sheet7[0][1] == Cell(0));
    assert(sheet7[0][2] == Cell(1));
    assert(sheet7[1][0] == Cell(0));
    assert(sheet7[1][1] == Cell(2));
    assert(sheet7[1][2] == Cell(0));
    assert(sheet7[2][0] == Cell(3));
    assert(sheet7[2][1] == Cell(0));
    assert(sheet7[2][2] == Cell(0));

    // Test row and column removal
    sheet7 = sheet2;
    sheet7.removeRow(1);
    assert(sheet7.row() == 2);
    sheet7.removeCol(1);
    assert(sheet7.col() == 3);

    // Test resizing
    sheet7.resize(4, 5);
    assert(sheet7.row() == 4);
    assert(sheet7.col() == 5);

    std::cout << "All SpreadSheet tests passed!" << std::endl;
}

int main() {
    testCell();
    testSpreadSheet();
    
    return 0;
}

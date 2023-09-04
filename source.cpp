#include "spreadsheet.h"
#include "spreadsheetCell.h"

#include <cstddef>
#include <iostream>
#include <ostream>

std::ostream& operator<<(std::ostream&, const Spreadsheet::Point&);
std::ostream& operator<<(std::ostream&, const SpreadsheetCell&);
std::ostream& operator<<(std::ostream&, const Spreadsheet&);

int main() {
    ////test 1
    //Spreadsheet ob;
    //ob.addRow(2);
    ////SpreadsheetCell* c = ob.getCell(1, 1);//ayspisi cell der goyutyun chuni
    ////std::cout << "null or not" << c << std::endl;
    ////std::cout << c->getValue() << std::endl;
    ////test2
    //ob.addColumn(2);
    //ob.setCell(0, 0, "hello");
    //ob.setCell(0, 1, "3.14");
    //ob.setCell(1, 1, "val");
    //std::cout << ob;
    ////test3
    //std::cout << ob.getCell(0, 0)->getValue() << std::endl;
    //std::cout << ob.getCell(1, 0)->getValue() << std::endl;
    //SpreadsheetCell* cell = ob.getCell(1, 1);
    //std::cout << cell->getValue() << std::endl;
    //cell->setValue("new");
    //std::cout << ob;
    ////test4
    ////double v = cell->getDoubleValue();//Error
    //double v2 = ob.getCell(1, 0)->getDoubleValue();
    //std::cout << v2 << std::endl;
    ////SpreadsheetCell* intCell = ob.getCell(1, 0);
    ////intCell->setValue("99");
    ////std::cout << ob << std::endl;
    //Spreadsheet ob;
    //ob.addColumn(5);
    //ob.addRow(2);
    //ob.setCell(0, 0, "Hello");
    //Spreadsheet ob1;
    //ob1 = std::move(ob);
    //SpreadsheetCell sp;
    //sp.setValue("Hello");
    //std::cout << ob1[sp];
    //Spreadsheet sp1;
    //sp1.addColumn(2);
    //sp1.addRow(3);
    //sp1.getCell(0, 0)->setValue("Hello");
    //std::cout << sp1 << std::endl;
    //Spreadsheet sp2;
    //sp2.addColumn(3);
    //sp2.addRow(2);
    //sp2.getCell(1, 1)->setValue("3.14");
    //std::cout << sp2 << std::endl;
    //Spreadsheet sp3 = sp1 + sp2;
    //std::cout << sp3;
    //SpreadsheetCell sp;
    //sp.setValue("Hello world");
    //std::cout << sp;
    SpreadsheetCell sp;
    sp.setValue("16");
    std::cout << sp++;
    std::cout << sp;
    return 0;
}

std::ostream& operator<<(std::ostream& out, const Spreadsheet& obj) {
    size_t max_size_of_value = 0;
    for (size_t i {}; i < obj.getRow(); ++i) {
        for (size_t j {}; j < obj.getColumn(); ++j) {
            std::string current_SpreadsheetCell_value = obj.getCell(i, j)->getValue();
            if (max_size_of_value < current_SpreadsheetCell_value.size()) {
                max_size_of_value = current_SpreadsheetCell_value.size();
            }
        }
    }
    size_t width = 5;
    size_t cell_size = max_size_of_value + width + 2;
    for (size_t i {}; i < obj.getRow(); ++i) {
        for (size_t j {}; j < cell_size*obj.getColumn(); ++j) {
            std::cout << "-";
        }
        std::cout << std::endl;
        for (size_t j {}; j < obj.getColumn(); ++j) {
            std::string current_SpreadsheetCell_value = obj.getCell(i, j)->getValue(); 
            std::cout << "|" << current_SpreadsheetCell_value;
            for (size_t k {}; k < cell_size - current_SpreadsheetCell_value.size() - 2; ++k) {
                std::cout << " ";
            }
            std::cout << "|";
        }
        std::cout << std::endl;
    }
    for (size_t j {}; j < cell_size*obj.getColumn(); ++j) {
        std::cout << "-";
    }
    std::cout << std::endl;
    return out;
}

std::ostream& operator<<(std::ostream& out, const SpreadsheetCell& obj) {
    out << obj.getValue() << std::endl;
    return out;
}

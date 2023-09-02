#pragma once

#include "spreadsheetCell.h"

class Spreadsheet {
public:
    class Point {
    public:
        Point(int = 0, int = 0);
        int x() const;
        int y() const;
    private:
        int m_x;
        int m_y;
    };
    Spreadsheet() = default;
    Spreadsheet(const Spreadsheet&);
    Spreadsheet(Spreadsheet&&);

    int getRow() const;
    int getColumn() const;
    void addRow(int);
    void addColumn(int);
    void setCell(int, int, const std::string&);
    
    Spreadsheet& operator=(const Spreadsheet&);
    Spreadsheet& operator=(Spreadsheet&&);
    Spreadsheet operator+(const Spreadsheet&) const;
    SpreadsheetCell operator[](const Point&) const;
    Point operator[](const SpreadsheetCell&) const;

    SpreadsheetCell* getCell(int, int) const;

    ~Spreadsheet();

private:
    SpreadsheetCell** m_table = nullptr;
    int m_count_row = 0;
    int m_count_column = 0; 
};

#include "spreadsheet.h"
#include "spreadsheetCell.h"

#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <string>

std::ostream& operator<<(std::ostream&, const Spreadsheet&);

//Spreadsheet::Point

Spreadsheet::Point::Point(int x, int y) {
    if (x < 0 || y < 0) {
        throw std::runtime_error("Error: none valid coordinates");
    }
    m_x = x;
    m_y = y;
}

int Spreadsheet::Point::x() const {
    return m_x;
}

int Spreadsheet::Point::y() const {
    return m_y;
}

std::ostream& operator<<(std::ostream& out, const Spreadsheet::Point& obj) {
    out << "x: " << obj.x() << ", ";
    out << "y: " << obj.y();
    return out;
}

//Spreadsheet

Spreadsheet::Spreadsheet(const Spreadsheet& obj) {
    Spreadsheet* tmp {};
    if (obj.m_table == nullptr) {
        for (size_t i {}; i < m_count_row; ++i) {
            delete [] m_table[i];
        }
        delete m_table;
        m_table = nullptr;
    }
    else if (obj.m_table[0] == nullptr) {
        tmp = new Spreadsheet;
        tmp->m_count_row = obj.m_count_row;
        tmp->m_count_column = obj.m_count_column;
        tmp->m_table = new SpreadsheetCell*[tmp->m_count_row];
        for (size_t i {}; i < tmp->m_count_row; ++i) {
            tmp->m_table[i] = nullptr;
        }
    }
    else {
        tmp = new Spreadsheet;
        tmp->m_count_column = obj.m_count_column;
        tmp->m_count_row = obj.m_count_row;
        tmp->m_table = new SpreadsheetCell*[tmp->m_count_row];
        for (size_t i {}; i < tmp->m_count_row; ++i) {
            tmp->m_table[i] = new SpreadsheetCell[tmp->m_count_column];
            for (size_t j {}; j < tmp->m_count_column; ++j) {
                tmp->m_table[i][j] = obj.m_table[i][j];
            }
        }
    }
    std::swap(tmp->m_count_row, m_count_row);
    std::swap(tmp->m_count_column, m_count_column);
    std::swap(tmp->m_table, m_table);
    delete tmp;
}

Spreadsheet::Spreadsheet(Spreadsheet&& obj) {
    m_count_column = obj.m_count_column;
    m_count_row = obj.m_count_row;
    m_table = obj.m_table;
    obj.m_table = nullptr;
}

int Spreadsheet::getRow() const {
    return m_count_row;
}

int Spreadsheet::getColumn() const {
    return m_count_column;
}

void Spreadsheet::addRow(int row) {
    if (row <= 0) {
        throw std::runtime_error("Error: none valid row");
    }
    if (m_table == nullptr) {
        m_count_row = row;
        m_table = new SpreadsheetCell*[m_count_row];
        for (size_t i {}; i < m_count_row; ++i) {
            if (m_count_column == 0) {
                m_table[i] = nullptr;
            }
            else {
                m_table[i] = new SpreadsheetCell[m_count_column];
            }
        }
    }
    else {
        SpreadsheetCell** tmp = new SpreadsheetCell*[m_count_row + row];

        if (m_table[0] == nullptr) {
            for (size_t i {}; i < m_count_row + row; ++i) {
                tmp[i] = nullptr;
            }
        }
        else {
            for (size_t i {}; i < m_count_row + row; ++i) {
                tmp[i] = new SpreadsheetCell[m_count_column];
            }
            for (size_t i {}; i < m_count_row; ++i) {
                for (size_t j {}; j < m_count_column; ++j) {
                    tmp[i][j] = m_table[i][j];
                }
            }
        }
        for (size_t i {}; i < m_count_row; ++i) {
            delete [] m_table[i];
        }
        delete m_table;
        m_table = tmp;
        tmp = nullptr;
        m_count_row += row;
    }
}

void Spreadsheet::addColumn(int column) {
    if (column <= 0) {
        throw std::runtime_error("Error: none valid column");
    }
    if (m_table == nullptr) {
        m_count_column = column;
    }
    else {
        SpreadsheetCell** tmp = new SpreadsheetCell*[m_count_row];

        for (size_t i {}; i < m_count_row; ++i) {
            tmp[i] = new SpreadsheetCell[m_count_column + column];
        }
        for (size_t i {}; i < m_count_row; ++i) {
            for (size_t j {}; j < m_count_column; ++j) {
                tmp[i][j] = m_table[i][j];
            }
        }
        for (size_t i {}; i < m_count_row; ++i) {
            delete [] m_table[i];
        }
        delete m_table;
        m_table = tmp;
        tmp = nullptr;
        m_count_column += column;
    }
}

void Spreadsheet::setCell(int y, int x, const std::string& str) {
    if (
            (x > m_count_column || x < 0) ||
            (y > m_count_row || y < 0)
        ) {
        throw std::runtime_error("Error: none valid coordinates");
    } 
    m_table[y][x].setValue(str);
}

Spreadsheet& Spreadsheet::operator=(const Spreadsheet& obj) {
    if (this == &obj) {
        return *this;
    }
    Spreadsheet* tmp {};
    if (obj.m_table == nullptr) {
        for (size_t i {}; i < m_count_row; ++i) {
            delete [] m_table[i];
        }
        delete m_table;
        m_table = nullptr;
    }
    else if (obj.m_table[0] == nullptr) {
        tmp = new Spreadsheet;
        tmp->m_count_row = obj.m_count_row;
        tmp->m_count_column = obj.m_count_column;
        tmp->m_table = new SpreadsheetCell*[tmp->m_count_row];
        for (size_t i {}; i < tmp->m_count_row; ++i) {
            tmp->m_table[i] = nullptr;
        }
    }
    else {
        tmp = new Spreadsheet;
        tmp->m_count_column = obj.m_count_column;
        tmp->m_count_row = obj.m_count_row;
        tmp->m_table = new SpreadsheetCell*[tmp->m_count_row];
        for (size_t i {}; i < tmp->m_count_row; ++i) {
            tmp->m_table[i] = new SpreadsheetCell[tmp->m_count_column];
            for (size_t j {}; j < tmp->m_count_column; ++j) {
                tmp->m_table[i][j] = obj.m_table[i][j];
            }
        }
    }
    std::swap(tmp->m_count_row, m_count_row);
    std::swap(tmp->m_count_column, m_count_column);
    std::swap(tmp->m_table, m_table);
    for (size_t i {}; m_table != nullptr && i < tmp->m_count_row; ++i) {
        delete [] tmp->m_table[i];
    }
    delete tmp->m_table;
    delete tmp;
    return *this;
}

Spreadsheet& Spreadsheet::operator=(Spreadsheet&& obj) {
    for (size_t i {}; i < m_count_row; ++i) {
        delete [] m_table[i];
    }
    delete m_table;
    m_count_row = obj.m_count_row;
    m_count_column = obj.m_count_column;
    m_table = obj.m_table;
    obj.m_table = nullptr;
    return *this;
}

Spreadsheet Spreadsheet::operator+(const Spreadsheet& obj) const {
    Spreadsheet tmp;
    if (
        obj.m_count_column == 0 &&
        m_count_column == 0 &&
        (obj.m_count_row != 0 || m_count_row != 0)
            ) {
        tmp.addRow(obj.m_count_row + m_count_row);
        return tmp;
    }
    else if (
            (obj.m_count_column != 0 || m_count_column != 0) &&
            obj.m_count_row == 0 &&
            m_count_row == 0
            ) {
        tmp.addColumn(std::max(obj.m_count_column, m_count_column));
        return tmp;
    }
    else if (
            (obj.m_count_column != 0 || m_count_column != 0) &&
            (obj.m_count_row != 0 || m_count_row != 0)
            ) {
        tmp.addRow(obj.m_count_row + m_count_row);
        tmp.addColumn(std::max(obj.m_count_column, m_count_column));
    }
    size_t i {};
    for (; i < m_count_row; ++i) {
        for (size_t j {}; j < m_count_column; ++j) {
            *tmp.getCell(i, j) = *this->getCell(i, j);
        }
    }
    for (size_t k {}; i < obj.m_count_row + m_count_row; ++i, ++k) {
        for (size_t j {}; j < obj.m_count_column; ++j) {
            *tmp.getCell(i, j) = *obj.getCell(k, j);
        }
    }
    return std::move(tmp);
}

SpreadsheetCell Spreadsheet::operator[](const Point& point) const {
    if (
        point.x() >= m_count_column ||
        point.y() >= m_count_row ||
        point.x() < 0 ||
        point.y() < 0
        ) {
        throw std::runtime_error("Error:none valid point");
    }
    return m_table[point.y()][point.x()];
}

Spreadsheet::Point Spreadsheet::operator[](const SpreadsheetCell& obj) const {
    for (size_t i {}; i < m_count_row; ++i) {
        for (size_t j {}; j < m_count_column; ++j) {
            if (obj == m_table[i][j]) {
                return Point(j, i);
            }
        }
    }
    throw std::runtime_error("Error: SpreadsheetCell is not definite");
}

SpreadsheetCell* Spreadsheet::getCell(int y, int x) const {
    if (
            (x > m_count_column || x < 0) ||
            (y > m_count_row || y < 0)
        ) {
        throw std::runtime_error("Error: none valid coordinates");
    }
    return &(m_table[y][x]);
}

Spreadsheet::~Spreadsheet() {
    if (m_table != nullptr) {
        for (size_t i {}; i < m_count_row; ++i) {
            delete [] m_table[i];
        }
        delete m_table;
    }
}

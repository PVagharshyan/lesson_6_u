#include "spreadsheetCell.h"

#include <iostream>
#include <stdexcept>
#include <string>

int str_to_int(const std::string& m_str) {
    int result{};
    for (int i{}; i < m_str.length(); ++i) {
        if (m_str[i] == '.') {
            return result/10;
        }
        else if (m_str[i] > '9' || m_str[i] < '0') {
            throw std::runtime_error("Error");
        }
        result += ((int)m_str[i] - 48);
        result *= 10;
    }
    return result/10;  
}

double str_to_double(const std::string& m_str) {
    double result_10 {};
    int i = 0;
    for (; i < m_str.length(); ++i) {
        if (m_str[i] == '.') {
            result_10 /= 10;
            break;
        }
        else if (m_str[i] > '9' || m_str[i] < '0') {
            throw std::runtime_error("Error");
        }
        result_10 += ((int)m_str[i] - 48);
        result_10 *= 10;
    }
    ++i;
    double result_01 {};
    for (int j = m_str.length() - 1; j >= i; --j) {
        if (m_str[i] > '9' || m_str[i] < '0') {
            throw std::runtime_error("Error");
        }
        result_01 += ((int)m_str[j] - 48);
        result_01 /= 10;
    }
    return (result_10 + result_01); 
}

SpreadsheetCell::SpreadsheetCell(const std::string& value) 
    : m_str { value  }
{}

SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& obj) {
    m_str = obj.m_str;
}

SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& obj) {
    m_str = obj.m_str;
    return *this;
}

SpreadsheetCell& SpreadsheetCell::operator=(SpreadsheetCell&& obj) {
    m_str = std::move(obj.m_str);
    return *this;
}

bool SpreadsheetCell::operator==(const SpreadsheetCell& obj) const {
    return m_str == obj.m_str;
}

int SpreadsheetCell::getIntValue() const {
    return str_to_int(m_str);
}

double SpreadsheetCell::getDoubleValue() const {
    return str_to_double(m_str);
}

std::string SpreadsheetCell::getValue() const {
    return m_str;
}

void SpreadsheetCell::setValue(const std::string& str) {
    m_str = str;
}





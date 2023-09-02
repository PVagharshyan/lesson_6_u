#pragma once

#include <iostream>
#include <string>

class SpreadsheetCell{
public:
    SpreadsheetCell(const std::string& = "");
    SpreadsheetCell(const SpreadsheetCell&);
    SpreadsheetCell(SpreadsheetCell&&) = default;

    SpreadsheetCell& operator=(const SpreadsheetCell&);
    SpreadsheetCell& operator=(SpreadsheetCell&&);
    bool operator==(const SpreadsheetCell&) const;

    int getIntValue() const;
    double getDoubleValue() const;
    std::string getValue() const;
    void setValue(const std::string&);
private:
    std::string m_str;
};



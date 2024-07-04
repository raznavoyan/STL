#ifndef __CELL__H__
#define __CELL__H__

#include "cell.h"

Cell::Cell() : val("") {}

Cell::Cell(const Cell& rhv) : val(rhv.val) {}

Cell::Cell(Cell&& rhv) : val(std::move(rhv.val)) {}

Cell::Cell(int val) : val(std::to_string(val)) {}

Cell::Cell(double val) : val(std::to_string(val)) {}

Cell::Cell(char val) : val(std::string(1, val)) {}

Cell::Cell(bool val) : val(val ? "true" : "false") {}

Cell::Cell(std::string val) : val(val) {}

Cell::Cell(const std::vector<int>& val) {
    std::string s;
    for (int i : val) {
        s += i;
        s += " ";
    }
    this->val = s;
}

const Cell& Cell::operator=(const Cell& rhv) {
    if (this != &rhv) {
        val = rhv.val;
    }
    return *this;
}

const Cell& Cell::operator=(Cell&& rhv) {
    if (this != &rhv) {
        val = std::move(rhv.val);
    }
    return *this;
}

const Cell& Cell::operator=(int rhv) {
    val = std::to_string(rhv);
    return *this;
}

const Cell& Cell::operator=(double rhv) {
    val = std::to_string(rhv);
    return *this;
}

const Cell& Cell::operator=(char rhv) {
    val = std::string(1, rhv);
    return *this;
}

const Cell& Cell::operator=(bool rhv) {
    val = rhv ? "true" : "false";
    return *this;
}

const Cell& Cell::operator=(std::string rhv) {
    val = rhv;
    return *this;
}

const Cell& Cell::operator=(const std::vector<int>& rhv) {
    for (int i : rhv) {
        val += i + " ";
    }
    return *this;
}

Cell::operator int() const {
    return std::stoi(val);
}

Cell::operator double() const {
    return std::stod(val);
}

Cell::operator char() const {
    return val[0];
}

Cell::operator bool() const {
    return (val != "false" || val != "0" || val != "");
}

Cell::operator std::string() const {
    return val;
}

Cell::operator std::vector<int>() const {
    std::vector<int> result;
    std::stringstream ss(val);
    int num;
    while (ss >> num) {
        result.push_back(num);
    }
    return result;
}

bool operator==(const Cell& lhv, const Cell& rhv) {
    return static_cast<std::string>(lhv) == static_cast<std::string>(rhv);
}

bool operator!=(const Cell& lhv, const Cell& rhv) {
    return static_cast<std::string>(lhv) != static_cast<std::string>(rhv);
}

std::ostream& operator<<(std::ostream& out, const Cell& ob) {
    out << static_cast<std::string>(ob);
    return out;
}

std::istream& operator>>(std::istream& in, Cell& ob) {
    in >> ob;
    return in;
}

#endif
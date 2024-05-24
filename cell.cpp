#include "cell.h"

// Overloaded stream operators for vector<int>
std::ostream& operator<<(std::ostream& out, const std::vector<int>& ob) {
    for (size_t i = 0; i < ob.size(); ++i) {
        if (i != 0) out << " ";
        out << ob[i];
    }
    return out;
}

std::istream& operator>>(std::istream& in, std::vector<int>& ob) {
    ob.clear();
    std::string line;
    std::getline(in, line);
    std::istringstream iss(line);
    int num;
    while (iss >> num) {
        ob.push_back(num);
    }
    return in;
}

// Cell class implementation
Cell::Cell() : val("") {}
Cell::Cell(const Cell& rhv) : val(rhv.val) {}
Cell::Cell(Cell&& rhv) : val(std::move(rhv.val)) {}
Cell::Cell(int val) : val(std::to_string(val)) {}
Cell::Cell(double val) : val(std::to_string(val)) {}
Cell::Cell(char val) : val(1, val) {}
Cell::Cell(bool val) : val(val ? "true" : "false") {}
Cell::Cell(std::string val) : val(val) {}
Cell::Cell(const std::vector<int>& val) {
    std::ostringstream oss;
    oss << val;
    this->val = oss.str();
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
    val = std::move(rhv);
    return *this;
}

const Cell& Cell::operator=(const std::vector<int>& rhv) {
    std::ostringstream oss;
    oss << rhv;
    val = oss.str();
    return *this;
}

Cell::operator int() const {
    return std::stoi(val);
}

Cell::operator double() const {
    return std::stod(val);
}

Cell::operator char() const {
    return val.empty() ? '\0' : val[0];
}

Cell::operator bool() const {
    return val == "true";
}

Cell::operator std::string() const {
    return val;
}

Cell::operator std::vector<int>() const {
    std::vector<int> vec;
    std::istringstream iss(val);
    int num;
    while (iss >> num) {
        vec.push_back(num);
    }
    return vec;
}

bool operator==(const Cell& lhv, const Cell& rhv) {
    return lhv.operator std::string() == rhv.operator std::string();
}

bool operator!=(const Cell& lhv, const Cell& rhv) {
    return !(lhv == rhv);
}

std::ostream& operator<<(std::ostream& out, const Cell& ob) {
    out << static_cast<std::string>(ob);
    return out;
}

std::istream& operator>>(std::istream& in, Cell& ob) {
    std::string val;
    std::getline(in, val);
    ob = val;
    return in;
}

#include "spreadsheet.h"

// Column class implementation
SpreadSheet::Column::Column(Cell* col) : col(col) {}

Cell& SpreadSheet::Column::operator[](size_t pos) {
    return col[pos];
}

const Cell& SpreadSheet::Column::operator[](size_t pos) const {
    return col[pos];
}

// SpreadSheet class implementation
SpreadSheet::SpreadSheet() : board(nullptr), rowcnt(0), colcnt(0) {}

SpreadSheet::SpreadSheet(const SpreadSheet& rhv) : rowcnt(rhv.rowcnt), colcnt(rhv.colcnt) {
    board = new Cell*[rowcnt];
    for (size_t i = 0; i < rowcnt; ++i) {
        board[i] = new Cell[colcnt];
        for (size_t j = 0; j < colcnt; ++j) {
            board[i][j] = rhv.board[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet&& rhv) : board(rhv.board), rowcnt(rhv.rowcnt), colcnt(rhv.colcnt) {
    rhv.board = nullptr;
    rhv.rowcnt = 0;
    rhv.colcnt = 0;
}

SpreadSheet::SpreadSheet(size_t size) : rowcnt(size), colcnt(size) {
    board = new Cell*[rowcnt];
    for (size_t i = 0; i < rowcnt; ++i) {
        board[i] = new Cell[colcnt];
    }
}

SpreadSheet::SpreadSheet(size_t row, size_t col) : rowcnt(row), colcnt(col) {
    board = new Cell*[rowcnt];
    for (size_t i = 0; i < rowcnt; ++i) {
        board[i] = new Cell[colcnt];
    }
}

SpreadSheet::~SpreadSheet() {
    clear();
}

const SpreadSheet& SpreadSheet::operator=(const SpreadSheet& rhv) {
    if (this != &rhv) {
        clear();
        rowcnt = rhv.rowcnt;
        colcnt = rhv.colcnt;
        board = new Cell*[rowcnt];
        for (size_t i = 0; i < rowcnt; ++i) {
            board[i] = new Cell[colcnt];
            for (size_t j = 0; j < colcnt; ++j) {
                board[i][j] = rhv.board[i][j];
            }
        }
    }
    return *this;
}

const SpreadSheet& SpreadSheet::operator=(SpreadSheet&& rhv) {
    if (this != &rhv) {
        clear();
        board = rhv.board;
        rowcnt = rhv.rowcnt;
        colcnt = rhv.colcnt;
        rhv.board = nullptr;
        rhv.rowcnt = 0;
        rhv.colcnt = 0;
    }
    return *this;
}

SpreadSheet::Column SpreadSheet::operator[](size_t pos) {
    return Column(board[pos]);
}

const SpreadSheet::Column SpreadSheet::operator[](size_t pos) const {
    return Column(board[pos]);
}

void SpreadSheet::clear() noexcept {
    if (board) {
        for (size_t i = 0; i < rowcnt; ++i) {
            delete[] board[i];
        }
        delete[] board;
        board = nullptr;
        rowcnt = 0;
        colcnt = 0;
    }
}

size_t SpreadSheet::row() const {
    return rowcnt;
}

size_t SpreadSheet::col() const {
    return colcnt;
}

void SpreadSheet::mirrorH() {
    for (size_t i = 0; i < rowcnt; ++i) {
        for (size_t j = 0; j < colcnt / 2; ++j) {
            std::swap(board[i][j], board[i][colcnt - j - 1]);
        }
    }
}

void SpreadSheet::mirrorV() {
    for (size_t i = 0; i < rowcnt / 2; ++i) {
        std::swap(board[i], board[rowcnt - i - 1]);
    }
}

void SpreadSheet::mirrorD() {
    for (size_t i = 0; i < rowcnt; ++i) {
        for (size_t j = 0; j < i; ++j) {
            std::swap(board[i][j], board[j][i]);
        }
    }
}

void SpreadSheet::mirrorSD() {
    for (size_t i = 0; i < rowcnt; ++i) {
        for (size_t j = 0; j < colcnt - i - 1; ++j) {
            std::swap(board[i][j], board[rowcnt - j - 1][colcnt - i - 1]);
        }
    }
}

void SpreadSheet::rotate(int cnt) {
    cnt = cnt % 4;
    if (cnt < 0) cnt += 4;
    for (int k = 0; k < cnt; ++k) {
        SpreadSheet temp(colcnt, rowcnt);
        for (size_t i = 0; i < rowcnt; ++i) {
            for (size_t j = 0; j < colcnt; ++j) {
                temp.board[j][rowcnt - i - 1] = board[i][j];
            }
        }
        *this = std::move(temp);
    }
}

void SpreadSheet::removeRow(size_t row) {
    if (row >= rowcnt) return;
    Cell** newBoard = new Cell*[rowcnt - 1];
    for (size_t i = 0, k = 0; i < rowcnt; ++i) {
        if (i == row) continue;
        newBoard[k++] = board[i];
    }
    delete[] board[row];
    delete[] board;
    board = newBoard;
    --rowcnt;
}

void SpreadSheet::removeRows(std::initializer_list<size_t> rows) {
    for (size_t row : rows) {
        removeRow(row);
    }
}

void SpreadSheet::removeCol(size_t col) {
    if (col >= colcnt) return;
    for (size_t i = 0; i < rowcnt; ++i) {
        for (size_t j = col; j < colcnt - 1; ++j) {
            board[i][j] = board[i][j + 1];
        }
    }
    --colcnt;
}

void SpreadSheet::removeCols(std::initializer_list<size_t> cols) {
    for (size_t col : cols) {
        removeCol(col);
    }
}

void SpreadSheet::resizeRow(size_t r) {
    if (r <= rowcnt) return;
    Cell** newBoard = new Cell*[r];
    for (size_t i = 0; i < rowcnt; ++i) {
        newBoard[i] = board[i];
    }
    for (size_t i = rowcnt; i < r; ++i) {
        newBoard[i] = new Cell[colcnt];
    }
    delete[] board;
    board = newBoard;
    rowcnt = r;
}

void SpreadSheet::resizeCol(size_t c) {
    if (c <= colcnt) return;
    for (size_t i = 0; i < rowcnt; ++i) {
        Cell* newRow = new Cell[c];
        for (size_t j = 0; j < colcnt; ++j) {
            newRow[j] = board[i][j];
        }
        delete[] board[i];
        board[i] = newRow;
    }
    colcnt = c;
}

void SpreadSheet::resize(size_t r, size_t c) {
    resizeRow(r);
    resizeCol(c);
}

SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols) {
    SpreadSheet result(rows.size(), cols.size());
    size_t i = 0, j;
    for (size_t row : rows) {
        j = 0;
        for (size_t col : cols) {
            result.board[i][j] = board[row][col];
            ++j;
        }
        ++i;
    }
    return result;
}

bool operator==(const SpreadSheet& lhv, const SpreadSheet& rhv) {
    if (lhv.row() != rhv.row() || lhv.col() != rhv.col()) return false;
    for (size_t i = 0; i < lhv.row(); ++i) {
        for (size_t j = 0; j < lhv.col(); ++j) {
            if (lhv[i][j] != rhv[i][j]) return false;
        }
    }
    return true;
}

bool operator!=(const SpreadSheet& lhv, const SpreadSheet& rhv) {
    return !(lhv == rhv);
}

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob) {
    for (size_t i = 0; i < ob.row(); ++i) {
        for (size_t j = 0; j < ob.col(); ++j) {
            out << std::setw(10) << ob[i][j];
            if (j < ob.col() - 1) out << " | ";
        }
        out << "\n";
        if (i < ob.row() - 1) {
            out << std::string(ob.col() * 13 - 1, '-') << "\n";
        }
    }
    return out;
}

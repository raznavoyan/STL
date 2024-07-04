#include "spreadsheet.h"

SpreadSheet::SpreadSheet() : board(nullptr), rowcnt(0), colcnt(0) {}

SpreadSheet::SpreadSheet(const SpreadSheet& rhv) : rowcnt(rhv.rowcnt), colcnt(rhv.colcnt) {
    board = new Cell*[rowcnt];
    for (size_t i = 0; i < rowcnt; i++) {
        board[i] = new Cell[colcnt];
        for (size_t j = 0; j < colcnt; j++) {
            board[i][j] = rhv.board[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet&& rhv) : board(rhv.board), rowcnt(rhv.rowcnt), colcnt(rhv.colcnt) {
    rhv.board = nullptr;
    rhv.rowcnt = 0;
    rhv.colcnt = 0;
}

SpreadSheet::SpreadSheet(size_t size) : SpreadSheet(size, size) {}

SpreadSheet::SpreadSheet(size_t row, size_t col) : rowcnt(row), colcnt(col) {
    board = new Cell*[rowcnt];
    for (size_t i = 0; i < rowcnt; i++) {
        board[i] = new Cell[colcnt];
    }
}

SpreadSheet::~SpreadSheet() {
    if (board != nullptr) {
        for (size_t i = 0; i < rowcnt; i++) {
            delete[] board[i];
        }
        delete[] board;
    }
}

const SpreadSheet& SpreadSheet::operator=(const SpreadSheet& rhv) {
    if (this != &rhv) {
        if (board != nullptr) {
            for (size_t i = 0; i < rowcnt; i++) {
                delete[] board[i];
            }
            delete[] board;
        }
        rowcnt = rhv.rowcnt;
        colcnt = rhv.colcnt;
        board = new Cell*[rowcnt];
        for (size_t i = 0; i < rowcnt; i++) {
            board[i] = new Cell[colcnt];
            for (size_t j = 0; j < colcnt; j++) {
                board[i][j] = rhv.board[i][j];
            }
        }
    }
    return *this;
}

const SpreadSheet& SpreadSheet::operator=(SpreadSheet&& rhv) {
    if (this != &rhv) {
        if (board != nullptr) {
            for (size_t i = 0; i < rowcnt; i++) {
                delete[] board[i];
            }
            delete[] board;
        }
        rowcnt = rhv.rowcnt;
        colcnt = rhv.colcnt;
        board = rhv.board;
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
    if (board != nullptr) {
        for (size_t i = 0; i < rowcnt; i++) {
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
    for (size_t i = 0; i < rowcnt; i++) {
        for (size_t j = 0; j < colcnt / 2; j++) {
            std::swap(board[i][j], board[i][colcnt - j - 1]);
        }
    }
}

void SpreadSheet::mirrorV() {
    for (size_t i = 0; i < rowcnt / 2; i++) {
        for (size_t j = 0; j < colcnt; j++) {
            std::swap(board[i][j], board[rowcnt - i - 1][j]);
        }
    }
}

void SpreadSheet::mirrorD() {
    if (rowcnt == colcnt) {
        for (size_t i = 0; i < rowcnt; i++) {
            for (size_t j = i + 1; j < colcnt; j++) {
                std::swap(board[i][j], board[j][i]);
            }
        }
    }
}

void SpreadSheet::mirrorSD() {
    if (rowcnt == colcnt) {
        for (size_t i = 0; i < rowcnt; i++) {
            for (size_t j = 0; j < colcnt - i - 1; j++) {
                std::swap(board[i][j], board[rowcnt - j - 1][colcnt - i - 1]);
            }
        }
    }
}

void SpreadSheet::rotate(int cnt) {
    cnt = cnt % 4;
    while (cnt > 0) {
        mirrorD();
        mirrorH();
        cnt--;
    }
}

void SpreadSheet::removeRow(size_t row) {
    if (row < rowcnt) {
        delete[] board[row];
        for (size_t i = row; i < rowcnt - 1; i++) {
            board[i] = board[i + 1];
        }
        rowcnt--;
    }
}

void SpreadSheet::removeRows(std::initializer_list<size_t> rows) {
    for (auto row : rows) {
        removeRow(row);
    }
}

void SpreadSheet::removeCol(size_t col) {
    if (col < colcnt) {
        for (size_t i = 0; i < rowcnt; i++) {
            for (size_t j = col; j < colcnt - 1; j++) {
                board[i][j] = board[i][j + 1];
            }
        }
        colcnt--;
    }
}

void SpreadSheet::removeCols(std::initializer_list<size_t> cols) {
    for (auto col : cols) {
        removeCol(col);
    }
}

void SpreadSheet::resizeRow(size_t r) {
    if (r > rowcnt) {
        Cell** newBoard = new Cell*[r];
        for (size_t i = 0; i < rowcnt; i++) {
            newBoard[i] = board[i];
        }
        for (size_t i = rowcnt; i < r; i++) {
            newBoard[i] = new Cell[colcnt];
        }
        delete[] board;
        board = newBoard;
        rowcnt = r;
    }
}

void SpreadSheet::resizeCol(size_t c) {
    if (c > colcnt) {
        for (size_t i = 0; i < rowcnt; i++) {
            Cell* newCol = new Cell[c];
            for (size_t j = 0; j < colcnt; j++) {
                newCol[j] = board[i][j];
            }
            delete[] board[i];
            board[i] = newCol;
        }
        colcnt = c;
    }
}

void SpreadSheet::resize(size_t r, size_t c) {
    resizeRow(r);
    resizeCol(c);
}

SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols) {
    SpreadSheet slicedSheet(rows.size(), cols.size());
    size_t r = 0;
    for (auto row : rows) {
        size_t c = 0;
        for (auto col : cols) {
            slicedSheet.board[r][c] = board[row][col];
            c++;
        }
        r++;
    }
    return slicedSheet;
}

SpreadSheet::Column::Column(Cell* col) : col(col) {}

Cell& SpreadSheet::Column::operator[](size_t pos) {
    return col[pos];
}

const Cell& SpreadSheet::Column::operator[](size_t pos) const {
    return col[pos];
}

bool operator==(const SpreadSheet& lhv, const SpreadSheet& rhv) {
    if (lhv.rowcnt != rhv.rowcnt || lhv.colcnt != rhv.colcnt) {
        return false;
    }
    for (size_t i = 0; i < lhv.rowcnt; i++) {
        for (size_t j = 0; j < lhv.colcnt; j++) {
            if (lhv.board[i][j] != rhv.board[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const SpreadSheet& lhv, const SpreadSheet& rhv) {
    return !(lhv == rhv);
}

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob) {
    for (size_t i = 0; i < ob.row(); i++) {
        for (size_t j = 0; j < ob.col(); j++) {
            out << ob[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}

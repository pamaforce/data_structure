#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// 字符串模式匹配 - 简单匹配
int simpleMatch(const string& s, const string& t) {
    for (size_t i = 0; i <= s.size() - t.size(); i++) {
        size_t j;
        for (j = 0; j < t.size(); j++) {
            if (s[i + j] != t[j]) break;
        }
        if (j == t.size()) return i;
    }
    return -1;
}

// KMP 算法
void computeKMPTable(const string& t, vector<int>& table) {
    int j = 0;
    table[0] = 0;
    for (size_t i = 1; i < t.size(); i++) {
        while (j > 0 && t[i] != t[j]) {
            j = table[j - 1];
        }
        if (t[i] == t[j]) j++;
        table[i] = j;
    }
}

int kmpMatch(const string& s, const string& t) {
    vector<int> table(t.size());
    computeKMPTable(t, table);
    int j = 0;
    for (size_t i = 0; i < s.size(); i++) {
        while (j > 0 && s[i] != t[j]) {
            j = table[j - 1];
        }
        if (s[i] == t[j]) j++;
        if (j == t.size()) return i - t.size() + 1;
    }
    return -1;
}

// 数组顺序存储和基本操作
class Array {
private:
    vector<int> arr;

public:
    void initArray(int size) {
        arr.resize(size);
    }

    void destroyArray() {
        arr.clear();
    }

    int value(int index) {
        if (index < 0 || index >= arr.size()) throw out_of_range("索引超出范围");
        return arr[index];
    }

    void assign(int index, int value) {
        if (index < 0 || index >= arr.size()) throw out_of_range("索引超出范围");
        arr[index] = value;
    }

    void print() {
        for (int v : arr) {
            cout << v << " ";
        }
        cout << endl;
    }
};

// 稀疏矩阵表示和操作
struct SparseElement {
    int row, col, value;
};

// 稀疏矩阵三元组顺序表表示
class SparseMatrix {
private:
    vector<SparseElement> elements;
    int rows, cols;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c) {}

    void addElement(int r, int c, int value) {
        if (r >= rows || c >= cols) throw out_of_range("索引超出矩阵范围");
        elements.push_back({r, c, value});
    }

    SparseMatrix transpose() {
        SparseMatrix transposed(cols, rows);
        for (const auto& e : elements) {
            transposed.addElement(e.col, e.row, e.value);
        }
        return transposed;
    }

    void print() {
        for (const auto& e : elements) {
            cout << "(" << e.row << ", " << e.col << ") = " << e.value << endl;
        }
    }

    SparseMatrix multiply(const SparseMatrix& other) {
        if (cols != other.rows) throw invalid_argument("矩阵维度不匹配，无法相乘");
        SparseMatrix result(rows, other.cols);
        for (const auto& a : elements) {
            for (const auto& b : other.elements) {
                if (a.col == b.row) {
                    result.addElement(a.row, b.col, a.value * b.value);
                }
            }
        }
        return result;
    }
};

// 稀疏矩阵十字链表表示
struct CrossNode {
    int row, col, value;
    CrossNode* right;
    CrossNode* down;
    CrossNode(int r, int c, int v) : row(r), col(c), value(v), right(nullptr), down(nullptr) {}
};

class CrossSparseMatrix {
private:
    vector<CrossNode*> rowHeads;
    vector<CrossNode*> colHeads;
    int rows, cols;

public:
    CrossSparseMatrix(int r, int c) : rows(r), cols(c) {
        rowHeads.resize(r, nullptr);
        colHeads.resize(c, nullptr);
    }

    void addElement(int r, int c, int value) {
        if (r >= rows || c >= cols) throw out_of_range("索引超出矩阵范围");
        CrossNode* newNode = new CrossNode(r, c, value);

        if (!rowHeads[r] || rowHeads[r]->col > c) {
            newNode->right = rowHeads[r];
            rowHeads[r] = newNode;
        } else {
            CrossNode* curr = rowHeads[r];
            while (curr->right && curr->right->col < c) {
                curr = curr->right;
            }
            newNode->right = curr->right;
            curr->right = newNode;
        }

        if (!colHeads[c] || colHeads[c]->row > r) {
            newNode->down = colHeads[c];
            colHeads[c] = newNode;
        } else {
            CrossNode* curr = colHeads[c];
            while (curr->down && curr->down->row < r) {
                curr = curr->down;
            }
            newNode->down = curr->down;
            curr->down = newNode;
        }
    }

    void print() {
        for (int i = 0; i < rows; i++) {
            CrossNode* curr = rowHeads[i];
            while (curr) {
                cout << "(" << curr->row << ", " << curr->col << ") = " << curr->value << endl;
                curr = curr->right;
            }
        }
    }

    CrossSparseMatrix transpose() {
        CrossSparseMatrix transposed(cols, rows);
        for (int i = 0; i < rows; i++) {
            CrossNode* curr = rowHeads[i];
            while (curr) {
                transposed.addElement(curr->col, curr->row, curr->value);
                curr = curr->right;
            }
        }
        return transposed;
    }

    CrossSparseMatrix multiply(const CrossSparseMatrix& other) {
        if (cols != other.rows) throw invalid_argument("矩阵维度不匹配，无法相乘");
        CrossSparseMatrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            CrossNode* rowCurr = rowHeads[i];
            while (rowCurr) {
                CrossNode* colCurr = other.colHeads[rowCurr->col];
                while (colCurr) {
                    int newRow = rowCurr->row;
                    int newCol = colCurr->col;
                    int newValue = rowCurr->value * colCurr->value;
                    CrossNode* resultCurr = result.rowHeads[newRow];
                    CrossNode* prev = nullptr;
                    while (resultCurr && resultCurr->col < newCol) {
                        prev = resultCurr;
                        resultCurr = resultCurr->right;
                    }
                    if (resultCurr && resultCurr->col == newCol) {
                        resultCurr->value += newValue;
                    } else {
                        CrossNode* newNode = new CrossNode(newRow, newCol, newValue);
                        if (!prev) {
                            newNode->right = result.rowHeads[newRow];
                            result.rowHeads[newRow] = newNode;
                        } else {
                            newNode->right = prev->right;
                            prev->right = newNode;
                        }
                        CrossNode* colPrev = nullptr;
                        CrossNode* colIter = result.colHeads[newCol];
                        while (colIter && colIter->row < newRow) {
                            colPrev = colIter;
                            colIter = colIter->down;
                        }
                        if (!colPrev) {
                            newNode->down = result.colHeads[newCol];
                            result.colHeads[newCol] = newNode;
                        } else {
                            newNode->down = colPrev->down;
                            colPrev->down = newNode;
                        }
                    }
                    colCurr = colCurr->down;
                }
                rowCurr = rowCurr->right;
            }
        }
        return result;
    }
};

// 字符统计
void countCharacters(const string& input) {
    unordered_map<char, int> charCount;
    for (char c : input) {
        charCount[c]++;
    }
    for (const auto& pair : charCount) {
        cout << pair.first << " " << pair.second << endl;
    }
}

int main() {
    // 字符串模式匹配
    cout << "题目1&2&3：字符串模式匹配 - 简单匹配和 KMP 算法" << endl;
    string s = "abacabcdbacadebcdfeabcdfeg", t = "bacadebcd";
    cout << "简单匹配结果: " << simpleMatch(s, t) << endl;
    cout << "KMP 匹配结果: " << kmpMatch(s, t) << endl;

    // 数组操作
    cout << "\n题目4.1：数组操作测试" << endl;
    Array array;
    array.initArray(5);
    for (int i = 0; i < 5; i++) {
        array.assign(i, i + 1);
    }
    array.print();
    cout << "索引 3 的值: " << array.value(3) << endl;
    array.destroyArray();

    // 稀疏矩阵三元组顺序表表示
    cout << "\n题目4.2.1：稀疏矩阵操作测试（三元组顺序表表示）" << endl;
    SparseMatrix matrix(3, 3);
    matrix.addElement(0, 0, 5);
    matrix.addElement(1, 2, 8);
    matrix.addElement(2, 1, 3);
    cout << "原矩阵:" << endl;
    matrix.print();
    SparseMatrix transposed = matrix.transpose();
    cout << "转置矩阵:" << endl;
    transposed.print();

    // 稀疏矩阵十字链表表示
    cout << "\n题目4.2.2：稀疏矩阵操作测试（十字链表表示）" << endl;
    CrossSparseMatrix crossMatrix(3, 3);
    crossMatrix.addElement(0, 0, 5);
    crossMatrix.addElement(1, 2, 8);
    crossMatrix.addElement(2, 1, 3);
    cout << "原矩阵:" << endl;
    crossMatrix.print();
    CrossSparseMatrix transposedCross = crossMatrix.transpose();
    cout << "转置矩阵:" << endl;
    transposedCross.print();

    // 字符统计
    cout << "\n附加题1：字符统计" << endl;
    string input = "acbacc";
    countCharacters(input);

    // 稀疏矩阵乘法测试
    cout << "\n附加题2：稀疏矩阵乘法（十字链表表示）" << endl;
    CrossSparseMatrix matrixA(3, 3);
    matrixA.addElement(0, 0, 2);
    matrixA.addElement(1, 2, 3);
    matrixA.addElement(2, 1, 4);
    CrossSparseMatrix matrixB(3, 3);
    matrixB.addElement(0, 1, 5);
    matrixB.addElement(1, 2, 6);
    matrixB.addElement(2, 0, 7);
    cout << "矩阵 A:" << endl;
    matrixA.print();
    cout << "矩阵 B:" << endl;
    matrixB.print();
    CrossSparseMatrix productMatrix = matrixA.multiply(matrixB);
    cout << "矩阵 A * B 的结果:" << endl;
    productMatrix.print();

    return 0;
}
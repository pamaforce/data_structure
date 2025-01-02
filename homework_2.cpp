#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <list>
#include <string>
#include <cstring>
using namespace std;

// 题目1. 顺序表实现
class SeqList {
private:
    vector<int> data;

public:
    void create(vector<int> elements) {
        data = elements;
    }

    void insert(int index, int value) {
        if (index < 0 || index > data.size()) throw out_of_range("索引超出范围");
        data.insert(data.begin() + index, value);
    }

    void remove(int index) {
        if (index < 0 || index >= data.size()) throw out_of_range("索引超出范围");
        data.erase(data.begin() + index);
    }

    int findByValue(int value) {
        for (int i = 0; i < data.size(); i++) {
            if (data[i] == value) return i;
        }
        return -1;
    }

    int findByIndex(int index) {
        if (index < 0 || index >= data.size()) throw out_of_range("索引超出范围");
        return data[index];
    }

    void print() {
        for (int value : data) {
            cout << value << " ";
        }
        cout << endl;
    }

    void insertAverage() {
        if (data.empty()) {
            throw runtime_error("顺序表为空，无法计算平均值");
        }
        int sum = 0;
        for (int value : data) {
            sum += value;
        }
        int average = sum / data.size();
        int position = data.size() / 2;
        insert(position, average);
    }
};

// 题目2. 单链表实现
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void createHeadInsert(vector<int> elements) {
        head = nullptr;
        for (int value : elements) {
            Node* newNode = new Node(value);
            newNode->next = head;
            head = newNode;
        }
        cout << "链表已成功创建（头插法）。" << endl;
    }

    void createTailInsert(vector<int> elements) {
        head = nullptr;
        Node* tail = nullptr;
        for (int value : elements) {
            Node* newNode = new Node(value);
            if (!head) {  // 如果链表为空
                head = tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
        cout << "链表已成功创建（尾插法）。" << endl;
    }

    void print() {
        if (!head) {
            cout << "链表为空。" << endl;
            return;
        }

        Node* current = head;
        cout << "链表内容：";
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void insert(int index, int value) {
        if (index < 0) throw out_of_range("索引超出范围");
        Node* newNode = new Node(value);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        for (int i = 1; i < index; i++) {
            if (!current || !current->next) throw out_of_range("索引超出范围");
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    void remove(int index) {
        if (index < 0 || !head) throw out_of_range("索引超出范围");
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        for (int i = 1; i < index; i++) {
            if (!current || !current->next) throw out_of_range("索引超出范围");
            current = current->next;
        }

        Node* temp = current->next;
        if (!temp) throw out_of_range("索引超出范围");
        current->next = temp->next;
        delete temp;
    }

    int findByValue(int value) {
        Node* current = head;
        int index = 0;
        while (current) {
            if (current->data == value) return index;
            current = current->next;
            index++;
        }
        return -1;
    }

    int findByIndex(int index) {
        if (index < 0) {
            throw out_of_range("索引超出范围：索引不能为负数");
        }
        Node* current = head;
        int currentIndex = 0;
        while (current) {
            if (currentIndex == index) {
                return current->data;
            }
            current = current->next;
            currentIndex++;
        }
        throw out_of_range("索引超出范围：链表长度不足");
    }


    void reverse() {
        Node* prev = nullptr;
        Node* current = head;
        while (current) {
            Node* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }
};


// 题目3. 链表倒置
void reverseList(Node*& head) {
    Node* prev = nullptr;
    Node* current = head;
    while (current) {
        Node* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

// 题目4. 双向链表实现
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    DNode* head;

public:
    DoublyLinkedList() : head(nullptr) {}

    void create(vector<int> elements) {
        for (int value : elements) {
            insertTail(value);
        }
    }

    void insertTail(int value) {
        DNode* newNode = new DNode(value);
        if (!head) {
            head = newNode;
        } else {
            DNode* tail = head;
            while (tail->next) {
                tail = tail->next;
            }
            tail->next = newNode;
            newNode->prev = tail;
        }
    }

    void insert(int index, int value) {
        if (index < 0) throw out_of_range("索引超出范围");
        DNode* newNode = new DNode(value);
        if (index == 0) {
            newNode->next = head;
            if (head) head->prev = newNode;
            head = newNode;
            return;
        }
        DNode* current = head;
        for (int i = 0; i < index - 1; i++) {
            if (!current) throw out_of_range("索引超出范围");
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next) current->next->prev = newNode;
        current->next = newNode;
    }

    void remove(int index) {
        if (index < 0 || !head) throw out_of_range("索引超出范围");
        DNode* current = head;
        for (int i = 0; i < index; i++) {
            if (!current) throw out_of_range("索引超出范围");
            current = current->next;
        }
        if (current->prev) current->prev->next = current->next;
        if (current->next) current->next->prev = current->prev;
        if (current == head) head = current->next;
        delete current;
    }

    int findByValue(int value) {
        DNode* current = head;
        int index = 0;
        while (current) {
            if (current->data == value) return index;
            current = current->next;
            index++;
        }
        return -1;
    }

    void print() {
        DNode* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

// 题目5. 多项式操作
struct PolyNode {
    int coef;  // 系数
    int exp;   // 指数
    PolyNode* next;
    PolyNode(int c, int e) : coef(c), exp(e), next(nullptr) {}
};

class Polynomial {
private:
    PolyNode* head;

public:
    Polynomial() : head(nullptr) {}

    void create(vector<pair<int, int> > terms) {
        for (auto term : terms) {
            insert(term.first, term.second);
        }
    }

    void insert(int coef, int exp) {
        PolyNode* newNode = new PolyNode(coef, exp);
        if (!head || head->exp < exp) {
            newNode->next = head;
            head = newNode;
            return;
        }
        PolyNode* current = head;
        while (current->next && current->next->exp > exp) {
            current = current->next;
        }
        if (current->next && current->next->exp == exp) {
            current->next->coef += coef;
            if (current->next->coef == 0) {
                PolyNode* temp = current->next;
                current->next = temp->next;
                delete temp;
            }
            delete newNode;
        } else {
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void print() {
        PolyNode* current = head;
        while (current) {
            cout << current->coef << "x^" << current->exp;
            if (current->next) cout << " + ";
            current = current->next;
        }
        cout << endl;
    }
};

// 题目6. 顺序表右移
void rightShift(vector<int>& arr, int n) {
    int len = arr.size();
    n = n % len;
    reverse(arr.begin(), arr.end());
    reverse(arr.begin(), arr.begin() + n);
    reverse(arr.begin() + n, arr.end());
}

// 题目7. 静态链表实现
struct StaticNode {
    int data;
    int next;
};

class StaticLinkedList {
private:
    StaticNode nodes[100];
    int head;
    int free;

public:
    StaticLinkedList() : head(-1), free(0) {
        for (int i = 0; i < 99; i++) {
            nodes[i].next = i + 1;
        }
        nodes[99].next = -1;
    }

    void insert(int value) {
        if (free == -1) throw runtime_error("静态链表已满");
        int newIndex = free;
        free = nodes[free].next;
        nodes[newIndex].data = value;
        nodes[newIndex].next = head;
        head = newIndex;
    }

    void print() {
        int current = head;
        while (current != -1) {
            cout << nodes[current].data << " ";
            current = nodes[current].next;
        }
        cout << endl;
    }
};

// 题目8. 双向链表查找
void findPreAndNext(DNode* head, int n) {
    DNode* current = head;
    int index = 0;
    while (current && index < n) {
        current = current->next;
        index++;
    }
    if (!current) {
        cout << "位置越界" << endl;
        return;
    }
    if (current->prev) cout << "前驱: " << current->prev->data << endl;
    else cout << "无前驱" << endl;
    if (current->next) cout << "后继: " << current->next->data << endl;
    else cout << "无后继" << endl;
}

// 题目9. 约瑟夫环
void josephus(int n, int m) {
    list<int> circle;
    for (int i = 1; i <= n; i++) {
        circle.push_back(i);
    }
    auto it = circle.begin();
    while (circle.size() > 1) {
        for (int i = 1; i < m; i++) {
            it++;
            if (it == circle.end()) it = circle.begin();
        }
        it = circle.erase(it);
        if (it == circle.end()) it = circle.begin();
    }
    cout << "最后剩下的人是: " << circle.front() << endl;
}

int main() {
    // 测试题目1
    cout << "题目1：顺序表实现" << endl;
    SeqList seqList;
    seqList.create({1, 2, 3, 4, 5});
    seqList.print();
    seqList.insert(2, 10);
    seqList.print();
    seqList.remove(3);
    seqList.print();
    cout << "按值查找10的位置: " << seqList.findByValue(10) << endl;
    cout << "按索引查找2的位置: " << seqList.findByIndex(2) << endl;
    seqList.insertAverage();
    seqList.print();

    // 测试题目2
    cout << "\n题目2：单链表实现" << endl;
    LinkedList linkedList;
    vector<int> headInsert = {1, 2, 3, 4, 5};
    linkedList.createHeadInsert(headInsert);
    cout << "链表内容（头插法创建后）: ";
    linkedList.print();
    vector<int> tailInsert = {6, 7, 8};
    linkedList.createTailInsert(tailInsert);
    cout << "链表内容（尾插法追加后）: ";
    linkedList.print();
    linkedList.insert(3, 20);
    cout << "链表内容（插入20后）: ";
    linkedList.print();
    linkedList.remove(2);
    cout << "链表内容（删除第3个节点后）: ";
    linkedList.print();
    cout << "按值查找20的位置: " << linkedList.findByValue(20) << endl;
    try {
        cout << "按索引查找3的位置: " << linkedList.findByIndex(3) << endl;
    } catch (const out_of_range& e) {
        cout << "错误：" << e.what() << endl;
    }
    linkedList.reverse();
    cout << "链表内容（反转后）: ";
    linkedList.print();

    // 测试题目3
    cout << "\n题目3：链表倒置" << endl;
    Node* listHead = new Node(1);
    listHead->next = new Node(2);
    listHead->next->next = new Node(3);
    Node* current = listHead;
    cout << "原链表: ";
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
    reverseList(listHead);
    cout << "倒置后链表: ";
    current = listHead;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;

    // 测试题目4
    cout << "\n题目4：双向链表实现" << endl;
    DoublyLinkedList doublyLinkedList;
    doublyLinkedList.create({1, 2, 3, 4, 5});
    doublyLinkedList.print();
    doublyLinkedList.insert(2, 10);
    doublyLinkedList.print();
    doublyLinkedList.remove(3);
    doublyLinkedList.print();

    // 测试题目5
    cout << "\n题目5：多项式操作" << endl;
    Polynomial polynomial;
    polynomial.create({{3, 2}, {5, 1}, {6, 0}});
    polynomial.print();
    polynomial.insert(4, 1);
    polynomial.print();

    // 测试题目6
    cout << "\n题目6：顺序表右移" << endl;
    vector<int> arr = {1, 2, 3, 4, 5};
    rightShift(arr, 3);
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;

    // 测试题目7
    cout << "\n题目7：静态链表实现" << endl;
    StaticLinkedList staticList;
    staticList.insert(1);
    staticList.insert(2);
    staticList.insert(3);
    staticList.print();

    // 测试题目8
    cout << "\n题目8：双向链表查找" << endl;
    DNode* doublyHead = new DNode(1);
    doublyHead->next = new DNode(2);
    doublyHead->next->prev = doublyHead;
    doublyHead->next->next = new DNode(3);
    doublyHead->next->next->prev = doublyHead->next;
    findPreAndNext(doublyHead, 1);

    // 测试题目9
    cout << "\n题目9：约瑟夫环" << endl;
    josephus(7, 3);

    return 0;
}

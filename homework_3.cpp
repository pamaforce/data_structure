#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <memory>
#include <list>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
using namespace std;

// 题目1：顺序栈和链栈实现
class SeqStack {
private:
    stack<int> stk;

public:
    void push(int value) {
        stk.push(value);
        cout << "进栈：" << value << endl;
    }

    void pop() {
        if (stk.empty()) {
            cout << "栈为空，无法出栈。" << endl;
            return;
        }
        cout << "出栈：" << stk.top() << endl;
        stk.pop();
    }

    int top() {
        if (stk.empty()) {
            throw runtime_error("栈为空，无栈顶元素。");
        }
        return stk.top();
    }

    void print() {
        stack<int> temp = stk;
        cout << "栈内元素（从栈顶到栈底）：";
        while (!temp.empty()) {
            cout << temp.top() << " ";
            temp.pop();
        }
        cout << endl;
    }
};

struct Node {
    int data;
    shared_ptr<Node> next;

    Node(int val) : data(val), next(nullptr) {}
};

class LinkStack {
private:
    shared_ptr<Node> topNode;

public:
    LinkStack() : topNode(nullptr) {}

    void push(int value) {
        shared_ptr<Node> newNode = make_shared<Node>(value);
        newNode->next = topNode;
        topNode = newNode;
        cout << "进栈：" << value << endl;
    }

    void pop() {
        if (!topNode) {
            cout << "链栈为空，无法出栈。" << endl;
            return;
        }
        cout << "出栈：" << topNode->data << endl;
        topNode = topNode->next;
    }

    int top() {
        if (!topNode) {
            throw runtime_error("链栈为空，无栈顶元素。");
        }
        return topNode->data;
    }

    void print() {
        shared_ptr<Node> temp = topNode;
        cout << "链栈内元素（从栈顶到栈底）：";
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// 题目2：使用顺序栈模拟队列操作
class StackQueue {
private:
    stack<int> inStack, outStack;

    void transfer() {
        while (!inStack.empty()) {
            outStack.push(inStack.top());
            inStack.pop();
        }
    }

public:
    void enqueue(int value) {
        inStack.push(value);
        cout << "入队：" << value << endl;
    }

    void dequeue() {
        if (outStack.empty()) {
            if (inStack.empty()) {
                cout << "队列为空，无法出队。" << endl;
                return;
            }
            transfer();
        }
        cout << "出队：" << outStack.top() << endl;
        outStack.pop();
    }

    void print() {
        if (outStack.empty()) transfer();
        stack<int> temp = outStack;
        cout << "队列内元素（从队首到队尾）：";
        while (!temp.empty()) {
            cout << temp.top() << " ";
            temp.pop();
        }
        cout << endl;
    }
};

// 题目3：顺序队列和链式队列实现
class SeqQueue {
private:
    queue<int> q;

public:
    void enqueue(int value) {
        q.push(value);
        cout << "入队：" << value << endl;
    }

    void dequeue() {
        if (q.empty()) {
            cout << "顺序队列为空，无法出队。" << endl;
            return;
        }
        cout << "出队：" << q.front() << endl;
        q.pop();
    }

    int front() {
        if (q.empty()) {
            throw runtime_error("顺序队列为空，无队首元素。");
        }
        return q.front();
    }

    void print() {
        queue<int> temp = q;
        cout << "顺序队列内元素（从队首到队尾）：";
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << endl;
    }
};

struct QueueNode {
    int data;
    shared_ptr<QueueNode> next;

    QueueNode(int val) : data(val), next(nullptr) {}
};

class LinkQueue {
private:
    shared_ptr<QueueNode> frontNode, rearNode;

public:
    LinkQueue() : frontNode(nullptr), rearNode(nullptr) {}

    void enqueue(int value) {
        shared_ptr<QueueNode> newNode = make_shared<QueueNode>(value);
        if (!rearNode) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        cout << "入队：" << value << endl;
    }

    void dequeue() {
        if (!frontNode) {
            cout << "链式队列为空，无法出队。" << endl;
            return;
        }
        cout << "出队：" << frontNode->data << endl;
        frontNode = frontNode->next;
        if (!frontNode) rearNode = nullptr;
    }

    int front() {
        if (!frontNode) {
            throw runtime_error("链式队列为空，无队首元素。");
        }
        return frontNode->data;
    }

    void print() {
        shared_ptr<QueueNode> temp = frontNode;
        cout << "链式队列内元素（从队首到队尾）：";
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// 附加题1：解决迷宫问题
void solveMaze(vector<vector<int>>& maze, int x, int y, vector<vector<int>>& solution) {
    int n = maze.size();
    if (x < 0 || x >= n || y < 0 || y >= n || maze[x][y] == 0 || solution[x][y] == 1) return;

    solution[x][y] = 1;
    if (x == n - 1 && y == n - 1) {
        cout << "找到一条路径：" << endl;
        for (const auto& row : solution) {
            for (int cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
        cout << endl;
        solution[x][y] = 0;
        return;
    }

    solveMaze(maze, x + 1, y, solution);
    solveMaze(maze, x, y + 1, solution);
    solveMaze(maze, x - 1, y, solution);
    solveMaze(maze, x, y - 1, solution);

    solution[x][y] = 0;
}

// 题目4&附加题2：杨辉三角的格式化输出
void printPascalsTriangle(int n) {
    vector<vector<int>> triangle(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        triangle[i][0] = triangle[i][i] = 1;
        for (int j = 1; j < i; j++) {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
    }
    for (int i = 0; i < n; i++) {
        cout << string((n - i - 1) * 2, ' ');
        for (int j = 0; j <= i; j++) {
            cout << setw(4) << triangle[i][j];
        }
        cout << endl;
    }
}

// 附加题3：火车出站序列
void generateTrainSequences(vector<int>& trains, vector<int>& station, vector<int>& output, int n) {
    if (trains.empty() && station.empty()) {
        for (int i : output) cout << i << " ";
        cout << endl;
        return;
    }

    if (!trains.empty()) {
        station.push_back(trains.back());
        trains.pop_back();
        generateTrainSequences(trains, station, output, n);
        trains.push_back(station.back());
        station.pop_back();
    }

    if (!station.empty()) {
        output.push_back(station.back());
        station.pop_back();
        generateTrainSequences(trains, station, output, n);
        station.push_back(output.back());
        output.pop_back();
    }
}

int main() {
    cout << "题目1：顺序栈和链栈的实现" << endl;
    SeqStack seqStack;
    seqStack.push(1);
    seqStack.push(2);
    seqStack.push(3);
    seqStack.print();
    seqStack.pop();
    seqStack.print();

    LinkStack linkStack;
    linkStack.push(10);
    linkStack.push(20);
    linkStack.push(30);
    linkStack.print();
    linkStack.pop();
    linkStack.print();

    cout << "\n题目2：使用顺序栈模拟队列操作" << endl;
    StackQueue queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.print();
    queue.dequeue();
    queue.print();

    cout << "\n题目3：顺序队列和链式队列的实现" << endl;
    SeqQueue seqQueue;
    seqQueue.enqueue(1);
    seqQueue.enqueue(2);
    seqQueue.enqueue(3);
    seqQueue.print();
    seqQueue.dequeue();
    seqQueue.print();

    LinkQueue linkQueue;
    linkQueue.enqueue(10);
    linkQueue.enqueue(20);
    linkQueue.enqueue(30);
    linkQueue.print();
    linkQueue.dequeue();
    linkQueue.print();

    cout << "\n附加题1：解决迷宫问题" << endl;
    vector<vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}};
    vector<vector<int>> solution(4, vector<int>(4, 0));
    solveMaze(maze, 0, 0, solution);

    cout << "\n题目4&附加题2：杨辉三角的格式化输出" << endl;
    printPascalsTriangle(10);

    cout << "\n附加题3：火车出站序列" << endl;
    vector<int> trains = {3, 2, 1};
    vector<int> station, output;
    generateTrainSequences(trains, station, output, 3);

    return 0;
}

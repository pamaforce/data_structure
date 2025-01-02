#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>
using namespace std;

class Graph {
private:
    unordered_map<char, vector<char>> adjList;

public:
    // 添加边
    void addEdge(char u, char v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // 打印邻接表
    void printAdjList() {
        cout << "邻接表:" << endl;
        for (const auto& pair : adjList) {
            cout << pair.first << ": ";
            for (char neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // 深度优先搜索（DFS）
    void dfsHelper(char node, unordered_map<char, bool>& visited, string& result) {
        visited[node] = true;
        result += node;
        for (char neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                dfsHelper(neighbor, visited, result);
            }
        }
    }

    string dfs(char start) {
        unordered_map<char, bool> visited;
        string result;
        dfsHelper(start, visited, result);
        return result;
    }

    // 广度优先搜索（BFS）
    string bfs(char start) {
        unordered_map<char, bool> visited;
        queue<char> q;
        string result;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            char node = q.front();
            q.pop();
            result += node;

            for (char neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        return result;
    }
};

int main() {
    Graph graph;
    graph.addEdge('A', 'B');
    graph.addEdge('A', 'D');
    graph.addEdge('A', 'C');
    graph.addEdge('B', 'E');
    graph.addEdge('C', 'F');
    graph.addEdge('E', 'G');
    graph.addEdge('F', 'H');
    graph.addEdge('H', 'I');
    graph.printAdjList();
    cout << "\n深度优先搜索（DFS）结果: " << graph.dfs('A') << endl;
    cout << "\n广度优先搜索（BFS）结果: " << graph.bfs('A') << endl;

    return 0;
}

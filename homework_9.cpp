#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 顺序查找
int sequentialSearch(const vector<int>& arr, int key) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == key) return i;
    }
    return -1;
}

// 折半查找
int binarySearch(const vector<int>& arr, int key, int& comparisons) {
    int left = 0, right = arr.size() - 1;
    comparisons = 0;
    while (left <= right) {
        comparisons++;
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) return mid;
        if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// 二叉排序树节点
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// 插入节点
TreeNode* insert(TreeNode* root, int key) {
    if (!root) return new TreeNode(key);
    if (key < root->value)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
    return root;
}

// 查找节点
TreeNode* search(TreeNode* root, int key) {
    if (!root || root->value == key) return root;
    if (key < root->value)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// 输出节点左右子信息
void printNodeInfo(TreeNode* root, int key) {
    TreeNode* node = search(root, key);
    if (!node) {
        cout << "节点 " << key << " 未找到" << endl;
        return;
    }
    cout << "节点 " << key << " 的信息:" << endl;
    cout << "左子节点: " << (node->left ? to_string(node->left->value) : "null") << endl;
    cout << "右子节点: " << (node->right ? to_string(node->right->value) : "null") << endl;
}

int main() {
    vector<int> arr = {5, 13, 19, 21, 37, 56, 64, 75, 80, 88, 92};
    cout << "必做题部分，顺序查找和折半查找测试:" << endl;

    int key1 = 21, key2 = 85;
    int index1 = sequentialSearch(arr, key1);
    int index2 = sequentialSearch(arr, key2);
    cout << "顺序查找 " << key1 << " 的位置: " << (index1 != -1 ? to_string(index1) : "未找到") << endl;
    cout << "顺序查找 " << key2 << " 的位置: " << (index2 != -1 ? to_string(index2) : "未找到") << endl;

    int comparisons1, comparisons2;
    index1 = binarySearch(arr, key1, comparisons1);
    index2 = binarySearch(arr, key2, comparisons2);
    cout << "折半查找 " << key1 << " 的位置: " << (index1 != -1 ? to_string(index1) : "未找到")
         << "，比较次数: " << comparisons1 << endl;
    cout << "折半查找 " << key2 << " 的位置: " << (index2 != -1 ? to_string(index2) : "未找到")
         << "，比较次数: " << comparisons2 << endl;

    cout << "\n选做题部分，二叉排序树测试:" << endl;
    vector<int> bstElements = {50, 30, 40, 80, 35, 90, 85, 20, 10, 25, 88, 23};
    TreeNode* root = nullptr;
    for (int val : bstElements) {
        root = insert(root, val);
    }

    printNodeInfo(root, 50);
    printNodeInfo(root, 80);
    printNodeInfo(root, 90);
    printNodeInfo(root, 10);

    return 0;
}

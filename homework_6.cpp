#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// 定义二叉树节点结构
struct TreeNode {
    char value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char val) : value(val), left(nullptr), right(nullptr) {}
};

// 构建二叉树
TreeNode* buildTree(const string& preorder, const string& inorder, int preStart, int preEnd, int inStart, int inEnd, unordered_map<char, int>& inorderIndex) {
    if (preStart > preEnd || inStart > inEnd) return nullptr;

    char rootValue = preorder[preStart];
    TreeNode* root = new TreeNode(rootValue);
    int rootIndex = inorderIndex[rootValue];
    int leftSize = rootIndex - inStart;

    root->left = buildTree(preorder, inorder, preStart + 1, preStart + leftSize, inStart, rootIndex - 1, inorderIndex);
    root->right = buildTree(preorder, inorder, preStart + leftSize + 1, preEnd, rootIndex + 1, inEnd, inorderIndex);

    return root;
}

// 前序遍历
void preorderTraversal(TreeNode* root, string& result) {
    if (!root) return;
    result += root->value;
    preorderTraversal(root->left, result);
    preorderTraversal(root->right, result);
}

// 中序遍历
void inorderTraversal(TreeNode* root, string& result) {
    if (!root) return;
    inorderTraversal(root->left, result);
    result += root->value;
    inorderTraversal(root->right, result);
}

// 后序遍历
void postorderTraversal(TreeNode* root, string& result) {
    if (!root) return;
    postorderTraversal(root->left, result);
    postorderTraversal(root->right, result);
    result += root->value;
}

// 计算叶子结点个数
int countLeaves(TreeNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

// 计算二叉树深度
int treeDepth(TreeNode* root) {
    if (!root) return 0;
    return max(treeDepth(root->left), treeDepth(root->right)) + 1;
}

int main() {
    cout << "必做题部分" << endl;
    string preorder = "ABDFGCE";
    string inorder = "BFDGACE";

    // 构建二叉树
    unordered_map<char, int> inorderIndex;
    for (int i = 0; i < inorder.size(); i++) {
        inorderIndex[inorder[i]] = i;
    }

    TreeNode* root = buildTree(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1, inorderIndex);

    string preResult;
    preorderTraversal(root, preResult);
    cout << "前序遍历结果: " << preResult << endl;

    string inResult;
    inorderTraversal(root, inResult);
    cout << "中序遍历结果: " << inResult << endl;

    string postResult;
    postorderTraversal(root, postResult);
    cout << "后序遍历结果: " << postResult << endl;

    int leaves = countLeaves(root);
    cout << "二叉树叶子结点个数: " << leaves << endl;

    int depth = treeDepth(root);
    cout << "二叉树深度: " << depth << endl;

    cout << "\n选做题部分" << endl;
    vector<string> testCases = {"ABC", "BAC", "FDXEAG", "XDEFAG"};
    for (size_t i = 0; i < testCases.size(); i += 2) {
        string testPreorder = testCases[i];
        string testInorder = testCases[i + 1];

        unordered_map<char, int> testInorderIndex;
        for (int j = 0; j < testInorder.size(); j++) {
            testInorderIndex[testInorder[j]] = j;
        }

        TreeNode* testRoot = buildTree(testPreorder, testInorder, 0, testPreorder.size() - 1, 0, testInorder.size() - 1, testInorderIndex);
        string testPostResult;
        postorderTraversal(testRoot, testPostResult);
        cout << "后序遍历结果: " << testPostResult << endl;
    }

    return 0;
}

// https://leetcode.cn/problems/binary-tree-preorder-traversal/

#include <bits/stdc++.h>

using namespace std;

class Solution144 {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> st;
        TreeNode *node = root;
        while (true) {
            while (node != nullptr) {
                ans.push_back(node->val);
                st.push(node);
                node = node->left;
            }
            if (st.empty()) break;
            node = st.top(); st.pop();
            node = node->right; // 转入右子树
        }
        return ans;
    }

    vector<int> preorderTraversal_implementation2(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> st;
        if (root != nullptr) st.push(root);
        while (!st.empty()) {
            TreeNode *node = st.top(); st.pop();
            ans.push_back(node->val);
            if (node->right != nullptr) st.push(node->right);
            if (node->left != nullptr) st.push(node->left); // 先推右后推左，先出栈访问的才是左子树
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
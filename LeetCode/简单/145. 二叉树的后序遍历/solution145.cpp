// https://leetcode.cn/problems/binary-tree-postorder-traversal/

#include <bits/stdc++.h>

using namespace std;

class Solution145 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode *> st;
        TreeNode *node = root;
        TreeNode *prev = nullptr; // 记录刚访问完的子树
        while (true) {
            while (node != nullptr) {
                st.push(node);
                node = node->left;
            }
            if (st.empty()) break;
            node = st.top();
            if (node->right == nullptr || node->right == prev) { // node没有右子树或者右子树已经访问完了，则可以访问node了
                ans.push_back(node->val);
                prev = node;
                st.pop();
                node = nullptr; // 将node变为null，然后下一轮循环会自动回溯，取栈peek，往右子树递归
            }
            else {
                node = node->right;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
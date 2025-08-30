// https://leetcode.cn/problems/binary-tree-inorder-traversal/

#include <bits/stdc++.h>

using namespace std;

class Solution94 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode *> st;
        TreeNode *node = root;
        while (true) {
            while (node != nullptr) {
                st.push(node);
                node = node->left;
            }
            if (st.empty()) break;
            node = st.top();
            ans.push_back(node->val);
            st.pop();
            node = node->right;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
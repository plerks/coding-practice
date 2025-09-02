// https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution106 {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        stack<TreeNode*> st;
        TreeNode* root = new TreeNode(postorder.back());
        st.push(root);
        int index = inorder.size() - 1;
        for (int i = postorder.size() - 2; i >= 0; i--) { // i 为此轮要构建的节点
            if (st.top()->val != inorder[index]) { // 构建最右侧通路
                st.top()->right = new TreeNode(postorder[i]);
                st.push(st.top()->right);
            }
            else { // 回退
                TreeNode* node = nullptr;
                while (!st.empty() && st.top()->val == inorder[index]) {
                    node = st.top(); st.pop();
                    index--;
                }
                node->left = new TreeNode(postorder[i]);
                st.push(node->left);
            }
        }
        return root;
    }
};

int main(int argc, char const *argv[]) {
    Solution106 solu;
    auto a = solu.buildTree(*new vector<int>{9,3,15,20,7}, *new vector<int>{9,15,7,20,3});
    return 0;
}
// https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

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

class Solution105 {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        stack<TreeNode*> st;
        TreeNode* root = new TreeNode(preorder[0]);
        st.push(root);
        int index = 0; // 中序遍历中的下标
        for (int i = 1; i < preorder.size(); i++) { // i 为此轮要构建的节点
            if (st.top()->val != inorder[index]) { // 构建最左侧通路。inorder[index]指示了这条通路的末尾
                st.top()->left = new TreeNode(preorder[i]);
                st.push(st.top()->left);
            }
            else { // 最左侧通路构建完。没有右子树的话，栈顶元素会等于inorder[index]，有右子树的话也会这样，回退，记住最后的那个节点，递归构建右子树
                TreeNode* node = nullptr;
                while (!st.empty() && st.top()->val == inorder[index]) {
                    node = st.top(); st.pop();
                    index++;
                }
                // 此处node一定不会是nullptr，至少是刚刚的最左侧通路的起点
                node->right = new TreeNode(preorder[i]);
                st.push(node->right);
            }
        }
        return root;
    }
};

int main(int argc, char const *argv[]) {
    Solution105 solu;
    auto a = solu.buildTree(*new vector<int>{3,9,20,15,7}, *new vector<int>{9,3,15,20,7});
    return 0;
}
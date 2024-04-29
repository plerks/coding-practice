/*
url: https://leetcode.cn/problems/reverse-odd-levels-of-binary-tree/description/
标签: 层序遍历, 层序遍历区分层节点
*/

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

class Solution2415 {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        // 题中给定树为满二叉树
        int level = 0;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            /* 一次循环结束时，这个vec会析构，见<https://blog.csdn.net/xkdlzy/article/details/107437823>:
            每次进入循环体时，循环体中的局部对象都会重新构造；离开循环体时，循环体中的局部对象被析构。 */
            vector<TreeNode *> vec;
            for (int i = 0; i < size; i++) {
                TreeNode *node = q.front();
                q.pop();
                vec.push_back(node);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            if (level % 2 == 1) {
                int count = vec.size();
                for (int i = 0; i < count / 2; i++) {
                    swap(vec[i]->val, vec[count - 1 - i]->val);
                }
            }
            level++;
        }
        return root;
    }
};

int main(int argc, char const *argv[]) {
    Solution2415 solu;
    TreeNode *root = new TreeNode(2, new TreeNode(3), new TreeNode(5));
    solu.reverseOddLevels(root);
    return 0;
}
/*
url: https://leetcode.cn/problems/maximum-binary-tree/
参考: https://leetcode.cn/problems/maximum-binary-tree/solutions/1759348/zui-da-er-cha-shu-by-leetcode-solution-lbeo/
      https://leetcode.cn/problems/maximum-binary-tree/solutions/1761712/by-ac_oier-s0wc/
标签: 【算法题单】单调栈
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

class Solution654 {
public:
    // 这题能想到用线段树的解法，用线段树求区间最大值，然后递归建树，时间复杂度O(nlogn)，宫水三叶题解有此做法。不过最佳做法是用单调栈，时间复杂度O(n)
    
    /* 参考官方题解，用单调栈，nums中的所有整数互不相同。观察[3,2,1,6,0,5]这个用例，每个元素nums[i]左侧第一个大于自己的，与右侧
    第一个大于自己的，其中较小者为自己的父节点
    */
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        int n = nums.size();
        vector<TreeNode*> tree(n);
        for (int i = 0; i < n; i++) {
            tree[i] = new TreeNode(nums[i]);
        }

        vector<int> left(n, -1); // 左边第一个大于自己的
        vector<int> right(n, -1); // 右边第一个大于自己的
        stack<int> st;
        // nums中的所有整数互不相同
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] < nums[i]) {
                right[st.top()] = i;
                st.pop();
            }
            if (!st.empty()) left[i] = st.top();
            st.push(i);
        }

        TreeNode* root = nullptr;
        // 把节点连接起来
        for (int i = 0; i < n; i++) {
            if (left[i] == -1 && right[i] == -1) root = tree[i]; // 没有父节点，i为根
            else if (left[i] != -1 && (right[i] == -1 || nums[left[i]] < nums[right[i]])) { // i的父节点在左边
                tree[left[i]]->right = tree[i];
            }
            else { // i的父节点在右边
                tree[right[i]]->left = tree[i];
            }
        }
        return root;
    }

    /* 参考宫水三叶题解和官方题解，单调栈的另外一种解法，不用记录left和right。
        这个写法较难理解，用[3,2,1,6,0,5]来看这个写法，开始是3，然后2比3小，3的右孩子为2，然后1比2小，2的右孩子为1，当前为：
        3
         \
          2
           \
            1
        然后6一直让1 2 3出栈，最后一次是3，于是把3作为6的右孩子
          6
         / 
        3
         \
          2
           \
            1
        然后0，接成6的右孩子：
          6
         / \
        3   0
         \
          2
           \
            1
        最后是5，5把栈中的0变成自己的左孩子，然后自己成为栈中剩下的6的右孩子，然后变成答案
    */
    TreeNode* constructMaximumBinaryTree_implementation2(vector<int>& nums) {
        int n = nums.size();
        vector<TreeNode*> tree(n);
        for (int i = 0; i < n; i++) {
            tree[i] = new TreeNode(nums[i]);
        }
        stack<TreeNode*> st; // 从左到右单减
        for (int i = 0; i < n; i++) {
            while (!st.empty() && st.top()->val < tree[i]->val) {
                tree[i]->left = st.top();
                st.pop();
            }
            if (!st.empty()) st.top()->right = tree[i];
            st.push(tree[i]);
        }
        // 最后一定栈底为根
        TreeNode* root = nullptr;
        while (!st.empty()) {
            root = st.top();
            st.pop();
        }
        return root;
    }
};

int main(int argc, char const *argv[]) {
    Solution654 solu;
    auto root1 = solu.constructMaximumBinaryTree(*new vector<int>{3,2,1,6,0,5});

    auto root2 = solu.constructMaximumBinaryTree_implementation2(*new vector<int>{3,2,1,6,0,5});
    return 0;
}
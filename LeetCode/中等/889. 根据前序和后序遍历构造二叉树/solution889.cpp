// https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-postorder-traversal/

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

class Solution889 {
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        int n = preorder.size();
        unordered_map<int, int> idx; // 在postorder中的位置
        for (int i = 0; i < n; i++) {
            idx[postorder[i]] = i;
        }
        return dfs(preorder, postorder, idx, 0, n, 0);
    }

    // 用preorder[preL, preR)和postorder[postL, x)建树，x可以通过树的规模算出来，不用传参数
    TreeNode* dfs(vector<int>& preorder, vector<int>& postorder, unordered_map<int, int>& idx, int preL, int preR, int postL) {
        if (preL == preR) return nullptr; // 空树
        if (preL + 1 == preR) return new TreeNode(preorder[preL]); // 单节点，没有子树根了，特判，否则preL + 1会越界
        int p1 = idx[preorder[preL + 1]]; // 左子树根在postorder中的位置
        int leftSize = p1 - postL + 1; // post[0, p1]对应左子树，leftSize为左子树规模
        // 如果只有单儿子，会优先建成左子树
        TreeNode* left = dfs(preorder, postorder, idx, preL + 1, preL + 1 + leftSize, postL);
        TreeNode* right = dfs(preorder, postorder, idx, preL + 1 + leftSize, preR, postL + leftSize);
        return new TreeNode(preorder[preL], left, right);
    }
};

int main(int argc, char const *argv[]) {
    Solution889 solu;
    auto a = solu.constructFromPrePost(*new vector<int>{1,2,4,5,3,6,7}, *new vector<int>{4,5,2,6,7,3,1});
    return 0;
}
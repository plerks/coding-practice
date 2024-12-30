/*
url: https://leetcode.cn/problems/linked-list-in-binary-tree/?envType=daily-question&envId=2024-12-30
参考: https://leetcode.cn/problems/linked-list-in-binary-tree/solutions/3034003/dan-di-gui-xie-fa-pythonjavacgo-by-endle-00js/
      https://leetcode.cn/problems/linked-list-in-binary-tree/solutions/122916/er-cha-shu-zhong-de-lie-biao-by-leetcode-solution/
*/
#include <bits/stdc++.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution1367 {
public:
    // 我的解法，81ms
    bool isSubPath(ListNode* head, TreeNode* root) {
        vector<int> nums;
        while (head != nullptr) {
            nums.push_back(head->val);
            head = head->next;
        }
        int n = nums.size();
        bool ans = false;

        // map[x]表示x这个节点能以多长的长度匹配到head的末尾(匹配必须到达head末尾)
        unordered_map<TreeNode *, unordered_set<int>> map;

        auto dfs = [&](auto &dfs, TreeNode* root) {
            if (root == nullptr) return;
            // 叶节点
            if (root->left == nullptr && root->right == nullptr && root->val == nums.back()) {
                if (n == 1) {
                    ans = true;
                    return;
                }
                map[root].insert(1);
            }
            else {
                // 自底而上，先计算子节点
                dfs(dfs, root->left);
                dfs(dfs, root->right);
                if (root->left) {
                    for (int len : map[root->left]) {
                        if (n - len - 1 >= 0 && root->val == nums[n - len - 1]) {
                            if (len + 1 == n) {
                                ans = true;
                                return;
                            }
                            map[root].insert(len + 1);
                        }
                    }
                }
                if (root->right) {
                    for (int len : map[root->right]) {
                        if (n - len - 1 >= 0 && root->val == nums[n - len - 1]) {
                            if (len + 1 == n) {
                                ans = true;
                                return;
                            }
                            map[root].insert(len + 1);
                        }
                    }
                }
                // root可以接上左右儿子的匹配长度，也可以自己和nums末尾匹配
                if (root->val == nums.back()) map[root].insert(1);
            }
        };

        dfs(dfs, root);
        return ans;
    }

    // 参考灵茶山艾府题解，执行用时0ms
    bool isSubPath_implementation2(ListNode* head, TreeNode* root) {
        return dfs(head, head, root);
    }

    bool dfs(ListNode* initHead, ListNode* head, TreeNode* root) {
        if (head == nullptr) return true;
        if (root == nullptr) return false;
        // 最开始我是这样写的，但是会超时
        /* bool ans = false;
        if (root->val == head->val) {
            ans |= dfs(initHead, head->next, root->left);
            ans |= dfs(initHead, head->next, root->right);
        }
        ans |= dfs(initHead, initHead, root->left);
        ans |= dfs(initHead, initHead, root->right); */

        /* 灵茶山艾府题解写法，一方面利用了短路的特性，不过仅仅只用短路特性还是会超时，
        这里最关键的点在于 head == initHead 这个判断，仅仅在 head == initHead 时才对子节点做
        从头开始的匹配，这样做的原因在于，若某次dfs匹配成功了一半，那么如果没有 head == initHead，
        匹配成功的每个节点，都会接着产生重复的对后续节点的从头开始匹配。
        此外，这样写也并未漏掉对每个节点，进行从头开始的匹配。
        */
        return root->val == head->val && (dfs(initHead, head->next, root->left) || dfs(initHead, head->next, root->right))
        || head == initHead && (dfs(initHead, initHead, root->left) || dfs(initHead, initHead, root->right));
    }

    // 官方题解的做法，实际上隐含了上面 head == initHead 实现的剔除重复，执行用时0ms
    bool isSubPath_implementation3(ListNode* head, TreeNode* root) {
        if (root == nullptr) return false;

        // no_backtrack_dfs不会回溯在 head 中的比对位置，相当于单独对以每个节点为根，dfs对比链表
        auto no_backtrack_dfs = [&](auto &no_backtrack_dfs, ListNode* head, TreeNode* root) {
            if (head == nullptr) return true;
            if (root == nullptr) return false;
            if (head->val != root->val) return false;
            return no_backtrack_dfs(no_backtrack_dfs, head->next, root->left) || no_backtrack_dfs(no_backtrack_dfs, head->next, root->right);
        };

        return no_backtrack_dfs(no_backtrack_dfs, head, root) || isSubPath_implementation3(head, root->left) || isSubPath_implementation3(head, root->right);
    }
};

int main(int argc, char const *argv[]) {
    ListNode* listNode1 = new ListNode(4);
    ListNode* listnode2 = new ListNode(2);
    listNode1->next = listnode2;

    TreeNode* node41 = new TreeNode(4);
    TreeNode* node42 = new TreeNode(4);
    TreeNode* node43 = new TreeNode(4);
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    node41->left = node42;
    node41->right = node43;
    node42->left = node1;
    node1->left = node2;

    Solution1367 solu;
    cout << solu.isSubPath(listNode1, node41) << endl;
    cout << solu.isSubPath_implementation2(listNode1, node41) << endl;
    cout << solu.isSubPath_implementation3(listNode1, node41) << endl;
    return 0;
}

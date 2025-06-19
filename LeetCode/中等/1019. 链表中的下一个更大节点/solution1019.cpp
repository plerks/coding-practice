/*
url: https://leetcode.cn/problems/next-greater-node-in-linked-list/
参考: https://leetcode.cn/problems/next-greater-node-in-linked-list/solutions/2217563/tu-jie-dan-diao-zhan-liang-chong-fang-fa-v9ab/
标签: 【算法题单】单调栈
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

class Solution1019 {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        unordered_map<ListNode*, ListNode*> mp;
        stack<ListNode*> st;
        ListNode* node = head;
        while (node != nullptr) {
            while (!st.empty() && st.top()->val < node->val) {
                mp[st.top()] = node;
                st.pop();
            }
            st.push(node);
            node = node->next;
        }
        vector<int> ans;
        node = head;
        while (node != nullptr) {
            ans.push_back(mp.count(node) ? mp[node]->val : 0);
            node = node->next;
        }
        return ans;
    }

    // 参考灵茶题解，一次遍历。单调栈中存(节点值，节点下标)，然后优化，单调栈可以只存节点下标，把节点值暂存在ans里
    vector<int> nextLargerNodes_implementation2(ListNode* head) {
        vector<int> ans;
        stack<int> st;
        for (auto cur = head; cur; cur = cur->next) {
            while (!st.empty() && ans[st.top()] < cur->val) {
                ans[st.top()] = cur->val; // 可能ans[i]现在是i号节点的val，现在改成右侧第一个更大值，但是i号节点的val后面不会再用到，所以没问题
                st.pop();
            }
            st.push(ans.size()); // ans的size就是当前节点的编号
            ans.push_back(cur->val); // 每次循环ans的size变大1。ans暂存节点值，后面填成答案
        }
        // 栈中剩下的元素是右侧没有更大值的
        while (!st.empty()) {
            ans[st.top()] = 0;
            st.pop();
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1019 solu;

    ListNode* node2 = new ListNode(2);
    ListNode* node1 = new ListNode(1);
    ListNode* node5 = new ListNode(5);
    node2->next = node1;
    node1->next = node5;
    auto a = solu.nextLargerNodes(node2);

    return 0;
}
/*
url: https://leetcode.cn/problems/permutations/
LeetCode参考: https://leetcode.cn/problems/permutations/solutions/218275/quan-pai-lie-by-leetcode-solution-2/
相关: LeetCode3149. 找出分数最低的排列, LeetCode47. 全排列 II
标签: 全排列
*/

#include <bits/stdc++.h>

using namespace std;

class Solution46 {
public:
    /* 暴力法，为了找到第一个没被使用的需要遍历visited数组，这里分析时间复杂度应该类似记忆化搜索(不过搜不到重复状态)，
    时间复杂度 = 状态个数 * 单个状态计算时间 = n! * n = O(n * n!)。
    */
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        vector<char> visited(n, 0);
        vector<vector<int>> ans;
        vector<int> perm;

        function<void(int)> dfs = [&](int count) { // count为已选元素个数
            if (count == n) {
                ans.push_back(perm);
                return;
            }
            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    perm.push_back(nums[i]);
                    visited[i] = true;
                    dfs(count + 1);
                    perm.pop_back();
                    visited[i] = false;
                }
            }
        };

        dfs(0);

        return ans;
    }

    // 这样写也行，注意不能想着用一个vector作为set，选出元素时移出元素，递归完成时再放入末尾，这样会改变元素相对顺序。必须记好原位置放回。
    vector<vector<int>> permute_implementation2(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> perm;

        function<void(int)> dfs = [&](int count) { // count为已选元素个数
            if (count == n) {
                ans.push_back(perm);
                return;
            }
            int size = nums.size();
            for (int i = 0; i < size; i++) {
                int temp = nums[i];
                perm.push_back(nums[i]);
                nums.erase(nums.begin() + i);
                dfs(count + 1);
                perm.pop_back();
                nums.insert(nums.begin() + i, temp);
            }
        };

        dfs(0);

        return ans;
    }

    /* 官方题解的解法。不需要dfs()里的循环是n次，也不移除nums中的元素，这样dfs()里循环次数比permute()少，
    不需移除插入nums中元素，用时也比permute_implementation2()少，但是给出的结果非字典序。
    做法是元素访问之后与前面交换，将nums维持成前面是已访问的元素，后面是未访问的元素。
    为什么给出的结果非字典序？
    过程中，nums可能呈现这样的状态: [已访问][a b c]，当尝试选c为下一个访问时，算法会将c与a交换，
    然后递归b a，这改变了元素的相对顺序，再往下递归，结果会非字典序。
    */
    vector<vector<int>> permute_implementation3(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> perm;

        function<void(int)> dfs = [&](int first) { // first为第一个未访问元素位置，也是已选元素个数
            if (first == n) {
                ans.push_back(perm);
                return;
            }
            // first位置为第一个未访问元素
            for (int i = first; i < n; i++) {
                perm.push_back(nums[i]);
                swap(nums[i], nums[first]);
                dfs(first + 1);
                swap(nums[i], nums[first]);
                perm.pop_back();
            }
        };

        dfs(0);

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution46 solu;
    vector<int> nums = {1,2,3,4,5};
    solu.permute(nums);
    solu.permute_implementation2(nums);
    solu.permute_implementation3(nums);
    return 0;
}

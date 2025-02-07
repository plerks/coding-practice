/*
url: https://leetcode.cn/problems/contains-duplicate-iii/description/
参考: https://leetcode.cn/problems/contains-duplicate-iii/solutions/726619/cun-zai-zhong-fu-yuan-su-iii-by-leetcode-bbkt/
标签: 【题单】滑动窗口与双指针
*/

#include <bits/stdc++.h>

using namespace std;

class Solution220 {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        int n = nums.size();
        multiset<int> st;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            // 最后一个<=x
            auto it = st.upper_bound(x);
            if (it != st.begin()) {
                it--;
                // 到这里说明最后一个<=x的元素存在
                if (abs(*it - x) <= valueDiff) return true;
            }
            // 第一个>=x
            it = st.lower_bound(x);
            if (it != st.end() && abs(*it - x) <= valueDiff) return true;
            st.insert(x);
            if (i - indexDiff >= 0) {
                st.erase(nums[i - indexDiff]);
            }
        }
        return false;
    }

    /* 官方题解，用桶。
    为了快速判断是否有元素足够近(<=valueDiff，记为t)，把[0, t]放入一个桶，[t+1, 2t+1]放入一个桶...
    总之，每个桶的宽度为t+1，把每个元素值x表示成 (t+1) * a + b 的形式(进制表示法)。如果发现一个桶需要放入两个元素，那么
    就可以直接返回true，所以桶只需要记录一个元素就行，不用记录多个。
    如果元素在同一个桶，则一定<=t；如果在相邻桶，需要检查；如果在不相邻的桶，一定不合法
    这里有个问题，[0] [4]，然后3替换4，万一后面来个5变成 [0] [3] [5]，4在桶偏右的位置，和5足够近，但是替换导致不知道怎么办？
    3替换4的时候就知道要返回true了，所以，每个桶只记录一个元素没有问题。
    */
    bool containsNearbyAlmostDuplicate_implementation2(vector<int>& nums, int k, int t) {
        int n = nums.size();
        int mi = -1e9;
        unordered_map<int, int> mp;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            int a = (x - mi) / (t + 1);
            if (mp.count(a)) return true;
            if (mp.count(a - 1) && abs(x - mp[a - 1]) <= t) {
                return true;
            }
            if (mp.count(a + 1) && abs(x - mp[a + 1]) <= t) {
                return true;
            }
            mp[a] = x;
            if (i - k >= 0) mp.erase((nums[i - k] - mi) / (t + 1));
        }
        return false;
    }
};

int main(int argc, char const *argv[]) {
    Solution220 solu;
    cout << solu.containsNearbyAlmostDuplicate(*new vector<int>{1,2,3,1}, 3, 0) << endl;
    cout << solu.containsNearbyAlmostDuplicate(*new vector<int>{1,5,9,1,5,9}, 2, 3) << endl;
    cout << solu.containsNearbyAlmostDuplicate(*new vector<int>{2,2}, 2, 0) << endl;

    cout << solu.containsNearbyAlmostDuplicate_implementation2(*new vector<int>{1,2,3,1}, 3, 0) << endl;
    cout << solu.containsNearbyAlmostDuplicate_implementation2(*new vector<int>{1,5,9,1,5,9}, 2, 3) << endl;
    cout << solu.containsNearbyAlmostDuplicate_implementation2(*new vector<int>{2,2}, 2, 0) << endl;
    return 0;
}
/*
# 描述

nums数组的长度不大(例如 1e5)，但是 nums[i] 值域较大(例如 1e9)，离散化操作将各个元素重新编号，保持原有的全序关系并将编号大小压缩在数组长度范围内。
这样就能用全局数组作为 map 了。

总的来说就是按顺序重编号。

# 时间复杂度

O(nlogn)

# 参考

https://oi-wiki.org/misc/discrete/
*/
#include <bits/stdc++.h>

using namespace std;

vector<int> discrete(vector<int>& nums) {
    int n = nums.size();
    vector<int> temp(nums);
    sort(temp.begin(), temp.end());
    temp.erase(std::unique(temp.begin(), temp.end()), temp.end());
    for (int i = 0; i < n; i++) {
        nums[i] = std::lower_bound(temp.begin(), temp.end(), nums[i]) - temp.begin();
    }
    return nums;
}

int main(int argc, char const *argv[]) {
    vector<int> nums1 = {0, 1, 7, 3, 10, 6};
    auto a = discrete(nums1);
    return 0;
}
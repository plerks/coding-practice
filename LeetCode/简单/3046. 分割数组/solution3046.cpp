// https://leetcode.cn/problems/split-the-array/?envType=daily-question&envId=2024-12-28
#include <bits/stdc++.h>

using namespace std;

class Solution3046 {
public:
    bool isPossibleToSplit(vector<int>& nums) {
        unordered_map<int, int> map;
        for (int num : nums) map[num]++;
        for (auto& it : map) {
            if (it.second > 2) return false;
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    Solution3046 solu;
    vector<int> nums = {1,1,2,2,3,4};
    cout << solu.isPossibleToSplit(nums) << endl;
    return 0;
}

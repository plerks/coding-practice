// https://leetcode.cn/problems/first-unique-even-element/

#include <bits/stdc++.h>

using namespace std;

class Solution3866 {
public:
    int firstUniqueEven(vector<int>& nums) {
        unordered_map<int, int> freq;
        for (int x : nums) {
            if (x % 2 == 1) continue;
            freq[x]++;
        }
        int ans = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] % 2 == 0 && freq[nums[i]] == 1) {
                ans = i;
                break;
            }
        }
        return ans == -1 ? -1 : nums[ans];
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
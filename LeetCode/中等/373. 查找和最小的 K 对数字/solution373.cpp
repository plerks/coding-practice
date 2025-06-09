#include <bits/stdc++.h>

using namespace std;

class Solution373 {
public:
    // 与 ./solution373.rs k_smallest_pairs() 相同
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        auto check = [&](int x) {
            int i = 0;
            int j = nums2.size() - 1;
            long long cnt = 0;
            while (i < nums1.size()) {
                while (j >= 0 && nums1[i] + nums2[j] > x) {
                    j -= 1;
                }
                cnt += j + 1;
                i += 1;
            }
            return cnt >= k;
        };

        int left = nums1.front() + nums2.front();
        int right = nums1.back() + nums2.back();
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) { left = mid + 1; }
            else { right = mid - 1; }
        }
        int x = left;

        vector<vector<int>> ans;

        for (int i = 0; i < nums1.size(); i++) {
            for (int j = 0;  j < nums2.size(); j++) {
                if (nums1[i] + nums2[j] >= x) {
                    break;
                }
                ans.push_back(vector<int>{nums1[i], nums2[j]});
            }
        }
        
        for (int i = 0; i < nums1.size(); i++) {
            int index1 = lower_bound(nums2.begin(), nums2.end(), x - nums1[i] + 1) - nums2.begin();
            int index2 = lower_bound(nums2.begin(), nums2.end(), x - nums1[i]) - nums2.begin();
            for (int j = 0; j < index1 - index2; j++) {
                if (ans.size() == k) { return ans; }
                ans.push_back(vector<int>{nums1[i], x - nums1[i]});
            }
        }

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution373 solu;
    auto a = solu.kSmallestPairs(*new vector<int>{1,7,11}, *new vector<int>{2,4,6}, 3);
    auto b = solu.kSmallestPairs(*new vector<int>{1,1,2}, *new vector<int>{1,2,3}, 2);
    return 0;
}
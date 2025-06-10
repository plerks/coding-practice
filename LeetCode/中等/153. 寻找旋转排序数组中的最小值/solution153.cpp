#include <bits/stdc++.h>

using namespace std;

class Solution153 {
public:
    // 与 ./solution.rs find_min_implementation3() 相同，这里只是用c++写一下，去看 ./solution.rs
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!(nums[mid] < nums[0])) left = mid + 1;
            else right = mid - 1;
        }
        return left == n ? nums[0] : nums[left];
    }
};

int main(int argc, char const *argv[]) {
    Solution153 solu;
    cout << solu.findMin(*new vector<int>{3,1,2}) << endl;
    cout << solu.findMin(*new vector<int>{1,2,3}) << endl;
    return 0;
}
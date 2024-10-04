// https://leetcode.cn/problems/minimum-time-to-complete-trips/?envType=daily-question&envId=2024-10-05

#include <bits/stdc++.h>

using namespace std;

class Solution2187 {
public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        int n = time.size();
        int min = *min_element(time.begin(), time.end());
        int max = *max_element(time.begin(), time.end());
        long long left = totalTrips / min / n;
        long long right = (long long)max * ((totalTrips + n - 1) / n); // ⌊t/max⌋*n >= totalTrips
        while (left <= right) {
            long long mid = (left + right) / 2;
            long long cnt = 0;
            for (int t : time) cnt += mid / t;
            if (!(cnt >= totalTrips)) left = mid + 1;
            else right = mid - 1;
        }
        return left;
    }
};

int main(int argc, char const *argv[]) {
    Solution2187 solu;
    vector<int> time = {9,7,10,9,10,9,10};
    // cout << solu.minimumTime(time, 1) << endl;
    
    vector<int> time2 = {1935,5727103};
    cout << solu.minimumTime(time2, 6189436) << endl;
    return 0;
}

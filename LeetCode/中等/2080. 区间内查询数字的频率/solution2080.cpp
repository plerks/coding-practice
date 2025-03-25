/*
url: https://leetcode.cn/problems/range-frequency-queries/
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

class RangeFreqQuery {
public:
    unordered_map<int, vector<int>> mp;

    RangeFreqQuery(vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            mp[arr[i]].push_back(i); // 统计位置
        }
    }
    
    int query(int left, int right, int value) {
        if (!mp.count(value)) return 0;
        auto &vec = mp[value];
        // {<= right} - {<= left - 1}
        int r = upper_bound(vec.begin(), vec.end(), right) - vec.begin() - 1;
        int l = upper_bound(vec.begin(), vec.end(), left - 1) - vec.begin() - 1;
        return r - l;
    }
};

int main(int argc, char const *argv[]) {
    RangeFreqQuery rfq(*new vector<int>{12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56});
    cout << rfq.query(1,2,4) << endl;
    cout << rfq.query(0,11,33) << endl;
    return 0;
}
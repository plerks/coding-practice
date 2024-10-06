// https://leetcode.cn/problems/gas-station/description/?envType=daily-question&envId=2024-10-06

#include <bits/stdc++.h>

using namespace std;

class Solution134 {
public:
    int canCompleteCircuit(const vector<int>& gas, const vector<int>& cost) {
        /* 记diff[i] = gas[i] - cost[i]，则diff[i]表达了每走一个位置后，油量的差值变化，
        无论从什么位置开始，总的经历过的变化都是这些数。开始的点是0，油量变化过程构成一个折线图，diff[i]表示这段线的Δy
        要让油量始终>=0，则应该把最小值的点移到x轴上，也就是从最小值+1的位置出发。
        最终sum是否>=0就能表示出是否能够走一圈。
        */
        // 题目如何保证在sum>=0的情况下解唯一？让最小值只有一个位置取得，若把其它次小值放x轴上，则由于折线diff变化不会变，最小值处会<0。
        int n = gas.size();
        vector<int> diff(n, 0);
        for (int i = 0; i < n; i++) {
            diff[i] = gas[i] - cost[i];
        }
        int min = INT_MAX;
        int pos = -1;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += diff[i];
            if (sum < min) {
                min = sum;
                pos = i;
            }
        }
        if (sum < 0) return -1;
        return (pos + 1) % n;
    }
};

int main(int argc, char const *argv[]) {
    Solution134 solu;
    cout << solu.canCompleteCircuit({1,2,3,4,5}, {3,4,5,1,2}) << endl;
    return 0;
}

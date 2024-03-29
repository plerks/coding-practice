#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
    int n, m;
    int x, y;
    cin >> n >> m >> x >> y;
    int directions[8][2] = {{-1,-2},{-2,-1},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2}};
    unordered_set<int> set;
    const int D = 101;
    set.insert(x * D + y);
    for (auto& arr : directions) {
        set.insert((x + arr[0]) * D + y + arr[1]);
    }
    /* 这里写成全局数组更好，不过这题1 <= n,m <= 20，这个栈数组不会太大。
    C++全局数组值会初始化为0，局部数组值不确定，所以最好是放全局。
    */
    long long dp[n + 1][m + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 && j == 0) continue;
            if (set.count(i * D + j)) continue;
            dp[i][j] = (j - 1 >= 0 ? dp[i][j - 1] : 0) + (i - 1 >= 0 ? dp[i - 1][j] : 0);
        }
    }
    cout << dp[n][m];
}

// 一个用例：输入6 6 3 3，输出6

// 这题我用Java写用时360ms，内存17.92MB，C++写用时15ms，内存680.00KB，代码逻辑是差不多的
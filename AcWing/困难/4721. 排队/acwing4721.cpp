/*
url: https://www.acwing.com/problem/content/4724/
标签: 最远 < 自己的位置
*/
#include<bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        nums[i] = x;
    }
    vector<int> suf_min(n); // 后缀最小值
    int mi = INT_MAX;
    for (int i = n - 1; i >= 0; i--) {
        mi = min(mi, nums[i]);
        suf_min[i] = mi;
    }
    vector<int> ans(n); // ans[i]为nums[i]右侧最远的 < 自己的位置
    for (int i = 0; i < n; i++) {
        // 找suf_max[i]右侧最后一个 < nums[i] 的位置，如果没有则为i
        int index = lower_bound(suf_min.begin() + i + 1, suf_min.end(), nums[i]) - suf_min.begin() - 1;
        ans[i] = index;
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] > i) cout << ans[i] - i - 1 << ' ';
        else cout << -1 << ' ';
    }
    return 0;
}

/* 样例：
6
10 8 5 3 50 45
---
2 1 0 -1 0 -1
*/
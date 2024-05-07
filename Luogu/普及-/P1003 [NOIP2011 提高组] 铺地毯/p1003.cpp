// https://www.luogu.com.cn/problem/P1003

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
    int n;
    cin >> n;
    vector<vector<int>> arr(n, vector<int>(4));
    for (int i = 0; i < n; i++) {
        cin >> arr[i][0];
        cin >> arr[i][1];
        cin >> arr[i][2];
        cin >> arr[i][3];
    }
    int x, y;
    cin >> x >> y;
    int ans = -1;
    for (int i = 0; i < n; i++) {
        auto &rectangle = arr[i];
        int a = rectangle[0];
        int b = rectangle[1];
        int w = rectangle[2];
        int h = rectangle[3];
        if (a <= x && x <= a + w && b <= y && y <= b + y) {
            ans = i + 1;
        }
    }
    cout << ans << endl;
}

/*
一个用例
输入：
3
1 0 2 3
0 2 3 3
2 1 3 3
2 2
输出：
3
*/
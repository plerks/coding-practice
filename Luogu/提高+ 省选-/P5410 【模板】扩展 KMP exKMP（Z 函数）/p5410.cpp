/*
url: https://www.luogu.com.cn/problem/P5410
标签: 模板, Z函数
*/
#include <bits/stdc++.h>

using namespace std;

vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n, 0);
    z[0] = s.size();
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i + 1);
            // 若z[i - l] < r - i + 1，则z[i] = z[i - l]；若z[i - l] > r - i + 1，z[i]一定刚好是r - i + 1；只有等于的情况才需要用while去尝试延长
            if (z[i - l] != r - i + 1) continue;
        }
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main(int argc, char const *argv[]) {
    cin.tie(0)->sync_with_stdio(0);

    string a, b;
    cin >> a >> b;

    vector<int> z1 = z_function(b);
    long long xor_ = 0;
    for (long long i = 0; i < z1.size(); i++) xor_ ^= (i + 1) * (z1[i] + 1);
    cout << xor_ << '\n';

    string s = b + a;
    vector<int> z_s = z_function(s);
    vector<int> z2(a.size());
    for (int i = 0; i < a.size(); i++) {
        z2[i] = std::min((int)b.size(), z_s[b.size() + i]);
    }
    xor_ = 0;
    for (long long i = 0; i < z2.size(); i++) xor_ ^= (i + 1) * (z2[i] + 1);
    cout << xor_ << '\n';

    return 0;
}
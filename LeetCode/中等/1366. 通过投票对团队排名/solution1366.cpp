// https://leetcode.cn/problems/rank-teams-by-votes/description/?envType=daily-question&envId=2024-12-29

#include <bits/stdc++.h>

using namespace std;

class Solution1366 {
public:
    string rankTeams(vector<string>& votes) {
        int n = votes[0].size();
        vector<pair<char, vector<int>>> rank(26, make_pair('0', vector<int>(n)));
        for (int i = 0; i < 26; i++) {
            rank[i].first = 'A' + i;
        }
        vector<bool> exsist(26, false);
        for (string& s : votes) {
            for (int i = 0; i < s.size(); i++) {
                char c = s[i];
                rank[c - 'A'].second[i]++;
                exsist[c - 'A'] = true;
            }
        }

        auto comparator = [&](const pair<char, vector<int>>& x, const pair<char, vector<int>>& y) {
            if (x.second != y.second) {
                return x.second > y.second;
            }
            return x.first < y.first;
        };

        sort(rank.begin(), rank.end(), comparator);
        string ans;
        for (int i = 0; i < n; i++) {
            if (exsist[rank[i].first - 'A']) ans += rank[i].first;
        }
        return ans;
    }

    // 参考灵茶山艾府题解的写法，更简洁
    string rankTeams_implementation2(vector<string>& votes) {
        int n = votes[0].size();
        vector<vector<int>> counts(26, vector<int>(n));
        for (string& s : votes) {
            for (int i = 0; i < s.size(); i++) {
                char c = s[i];
                counts[c - 'A'][i]--; // 用相反数，这样投票数和队名字母比较的方向是一致的
            }
        }
        string ans = votes[0];
        auto comparator = [&](char x, char y) {
            return make_pair(counts[x - 'A'], x) < make_pair(counts[y - 'A'], y);
        };
        sort(ans.begin(), ans.end(), comparator);
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1366 solu;
    vector<string> votes = {"WXYZ","XYZW"};
    cout << solu.rankTeams(votes) << endl;
    cout << solu.rankTeams_implementation2(votes) << endl;
    return 0;
}

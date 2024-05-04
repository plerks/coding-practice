// https://leetcode.cn/problems/determine-the-winner-of-a-bowling-game/description/

#include <bits/stdc++.h>

using namespace std;

class Solution2660 {
public:
    int isWinner(const vector<int>& player1, const vector<int>& player2) {
        int score1 = calculateScore(player1);
        int score2 = calculateScore(player2);
        return score1 > score2 ? 1 : score1 < score2 ? 2 : 0;
    }

    int calculateScore(const vector<int>& player) {
        int lastTenPosition = player.size();
        int score = 0;
        for (int i = 0; i < player.size(); i++) {
            if (i - lastTenPosition > 0 && i - lastTenPosition <= 2) {
                score += player[i] << 1;
            }
            else score += player[i];
            if (player[i] == 10) lastTenPosition = i;
        }
        return score;
    }
};

int main(int argc, char const *argv[]) {
    Solution2660 solu;
    // cout << solu.isWinner({4,10,7,9}, {6,5,2,3}) << endl;
    cout << solu.isWinner({5,6,1,10}, {5,1,10,5}) << endl;
    return 0;
}

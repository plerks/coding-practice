#include <bits/stdc++.h>

using namespace std;

class Solution488 {
public:
    /* 参考官方题解，这题的剪枝条件有点多：
    1. 首先，hand中的球肯定是按类别来选，但是不用处理成unordered_set，只需开头排序一次，然后判断是否和前一个相等来实现按类别选的
    2. 枚举放置位置，只需考虑在连续相同颜色的段的开头放置，像 a (a) a / a a (a)  这种放法不需要枚举，和 (a) a a 一样，这样一来，
       只要 board[i - 1] = hand[j] ，就不用尝试
    3. 通过2后，还有一种情况我们可以排除，“「插入新球与插入位置两侧的球颜色均不相同，且插入位置两侧的球的颜色不同」”，即 a (b) c，插在这里
    没有意义，即使是像 WWRRBBWW -> WWRRBB(R)WW -> WWRRB(B)BRWW -> ""，这个 (R) 可以后面再插，不用重复枚举等价情况

        这个问题只关心能否把球完全消除，不关心不能完全消除的情况下的最小剩余数，所以，a (b) c 一定不值得尝试，(b) a 也一定不值得尝试（这里左边
        没有别的球，注意，手中的球不一定要用完，board = "", hand = "AAA"，直接就完成了，不需要放球下去），
        只有这两种情况需要尝试：
            ... (a) a 右侧有同色球，例如 (R) R R
            a (b) a 这种不明显，但是是为未来准备的，例如 WWRRBBRR -> WWRRBBR(W)R -> WWRR(B)BBR(W)R -> ""
    */
    int findMinStep(string board, string hand) {
        sort(hand.begin(), hand.end());

        struct State {
            string board;
            string hand;
            int step;
        };

        queue<State> q;
        unordered_set<string> vis;
        q.push({board, hand, 0});
        vis.insert(board + " " + hand);
        while (!q.empty()) {
            State stat = q.front(); q.pop();
            auto [board, hand, step] = stat;
            for (int i = 0; i < board.size(); i++) {
                for (int j = 0; j < hand.size(); j++) {
                    if (j > 0 && hand[j] == hand[j - 1]) continue; // 剪枝条件1：手里的球同类只需试一个

                    // 剪枝条件2：只需考虑在board同色段的开头插入，就是 board[i - 1] == hand[j] 时该把 j 插在 i - 1 位置
                    if (i - 1 >= 0 && board[i - 1] == hand[j]) { // board[i] 是否颜色相同，都是一样的结论，(a) a 和 a (a)，不用重复枚举等价情况
                        continue;
                    }

                    bool choose = false;
                    // (a) a
                    if (hand[j] == board[i]) {
                        choose = true;
                    }
                    // a (b) a
                    if (i - 1 >= 0 && board[i - 1] == board[i] && hand[j] != board[i]) {
                        choose = true;
                    }

                    if (choose) {
                        // 将 hand[j] 插到 board[i] 位置
                        string new_board = eliminate(board.substr(0, i) + hand[j] + board.substr(i));
                        string new_hand = hand.substr(0, j) + hand.substr(j + 1);
                        if (new_board == "") return step + 1;
                        if (!vis.count(new_board + " " + new_hand)) {
                            q.push({new_board, new_hand, step + 1});
                            vis.insert(new_board + " " + new_hand);
                        }
                    }
                }
            }
        }

        return -1;
    }

    string eliminate(const string& board) {
        // "WWBBBWW"，注意消除 BBB 后要等最后一个 W 进来才消，不然会剩一个 W
        // 也就是说，将要入栈的字符发现自己与栈顶不同，才能由它启动消除
        vector<pair<char, int>> st; // (字符, 字符连续个数)，这里当栈用的，由于后面要从栈底复原 board，所以用 vector 不用 stack
        for (char c : board) {
            // 消除，得写在这个 for 循环的前面而不能是后面
            while (!st.empty() && c != st.back().first && st.back().second >= 3) {
                st.pop_back();
            }

            if (!st.empty() && st.back().first == c) { // 合并
                st.back().second++;
            }
            else { // 创建新项目
                st.push_back({c, 1});
            }
        }

        // 要由 end() 再启动一次消除
        while (!st.empty() && st.back().second >= 3) {
            st.pop_back();
        }

        // 计算消除后的样子
        string new_board;
        for (auto [ch, cnt] : st) {
            new_board.insert(new_board.end(), cnt, ch);
        }
        return new_board;
    }

    /* 实际运行用时 1200+ ms，比较慢，
    这题 1 <= board.length <= 16，1 <= hand.length <= 5，board 和 hand 由字符 'R'、'Y'、'B'、'G' 和 'W' 组成，
    应该可以用位压缩来优化，避免用 string
    */

    /* 这篇[题解](https://leetcode.cn/problems/zuma-game/solutions/1092019/c-0ms-by-lucifer1004-ivwb/)
    的执行用时只有 36 ms 。
    
    [TODO] 以后再看吧，这个解法代码长且很复杂
    */
};

int main(int argc, char const *argv[]) {
    Solution488 solu;
    cout << solu.findMinStep("WWRRBBWW", "WRBRW") << endl;
    cout << solu.findMinStep("RBYYBBRRB", "YRBGB") << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/word-ladder/
参考: https://leetcode.cn/problems/word-ladder/solutions/473600/dan-ci-jie-long-by-leetcode-solution/
标签: 【题单】图论算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution127 {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // 题目给定 beginWord != endWord，如果 wordList 不包含 endWord 则无法转换
        bool contain = false;
        for (string word : wordList) if (endWord == word) contain = true;
        if (!contain) return 0;

        int n = wordList.size();
        unordered_map<string, int> mp; // wordList 每个 word 的编号，beginWord 编为 0
        for (int i = 0; i < n; i++) mp[wordList[i]] = i + 1;

        // beginWord 可能就在 wordList 中，不过没关系
        vector<vector<string>> convert(n + 1);

        for (int j = 0; j < beginWord.size(); j++) {
            for (int c = 0; c < 26; c++) {
                if (c + 'a' != beginWord[j]) {
                    string t = beginWord;
                    t[j] = c + 'a';
                    if (mp.count(t)) {
                        convert[0].push_back(t);
                    }
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            string s = wordList[i];
            // 枚举 s[j] 变成 26个小写字母
            for (int j = 0; j < s.size(); j++) {
                for (int c = 0; c < 26; c++) {
                    if (c + 'a' != s[j]) {
                        string t = s;
                        t[j] = c + 'a';
                        if (mp.count(t)) {
                            convert[i + 1].push_back(t);
                        }
                    }
                }
            }
        }

        // bfs
        queue<string> q;
        unordered_set<string> vis;
        q.push(beginWord);
        vis.insert(beginWord);
        int level = 1;
        // 题目给定 beginWord != endWord，所以不需要在这里判断 beginWord == endWord 的情况
        while (!q.empty()) {
            int sz = q.size();
            for (int _ = 0; _ < sz; _++) {
                string cur = q.front(); q.pop();
                int idx = mp[cur];
                for (string& next : convert[idx]) {
                    if (next == endWord) return level + 1; // 这题是返回路径点数
                    if (!vis.count(next)) {
                        q.push(next);
                        vis.insert(next);
                    }
                }
            }
            level++;
        }

        return 0; // 不能转换返回 0
    }

    // 官方题解的优化方法，双向bfs，终点和起点交替走来算距离，和 A* 的改进点有点像，不用 bfs 那么宽
    // 官方题解解法还有一个优化，走一步不是枚举 a-z ，而是用 * 来通配，走到 "...*..."，也就是相当于虚拟节点
    int ladderLength_implementation2(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, int> mp; // (string, 编号)
        vector<vector<int>> g;

        // 分配编号，扩展 g
        auto addWord = [&](string& word) {
            if (!mp.count(word)) {
                mp[word] = mp.size();
                g.emplace_back(); // 新节点，多一行，emplace_back() 可以不给参数默认构造
            }
        };

        auto add = [&](string& word) {
            addWord(word);
            int id1 = mp[word];

            // 增加边，这里只发生了创建真实节点到虚拟节点的边的创建，但是虚拟节点到真实节点的边会在后面被真实节点创建出来
            for (char& it : word) {
                // 官方题解这个解法能最大程度降低 string 的构造
                char tmp = it;
                it = '*';
                addWord(word);
                int id2 = mp[word];
                g[id1].push_back(id2);
                g[id2].push_back(id1);
                it = tmp;
            }
        };

        add(beginWord);
        for (string& word : wordList) add(word);
        if (!mp.count(endWord)) return 0;

        // 图中有虚拟节点"...*..."，相当于每条边现在拆成了两条边

        // 双向 bfs

        const int inf = 0x3f3f3f3f;

        // 从起点出发的
        queue<int> q1;
        vector<int> dis1(mp.size(), inf); // dis 可以替代 vis 的功能
        int id1 = mp[beginWord];
        q1.push(id1);
        dis1[id1] = 0;

        // 从终点出发的
        queue<int> q2;
        vector<int> dis2(mp.size(), inf);
        int id2 = mp[endWord];
        q2.push(id2);
        dis2[id2] = 0;

        // 只要一个方向遍历完了整个图就可以结束了
        while (!q1.empty() && !q2.empty()) {
            // 从上往下
            int sz1 = q1.size();
            for (int i = 0; i < sz1; i++) {
                int node = q1.front(); q1.pop();
                if (dis2[node] != inf) { // 走通了
                    return (dis1[node] + dis2[node]) / 2 + 1; // 除2是因为有虚拟节点，每条边变两条边了，+1是因为题目要返回节点数
                }
                for (int next : g[node]) {
                    if (dis1[next] == inf) {
                        q1.push(next);
                        dis1[next] = dis1[node] + 1;
                    }
                }
            }

            // 从下往上
            int sz2 = q2.size();
            for (int i = 0; i < sz2; i++) {
                int node = q2.front(); q2.pop();
                if (dis1[node] != inf) {
                    return (dis1[node] + dis2[node]) / 2 + 1;
                }
                for (int next : g[node]) {
                    if (dis2[next] == inf) {
                        q2.push(next);
                        dis2[next] = dis2[node] + 1;
                    }
                }
            }
        }

        return 0;
    }
};

int main(int argc, char const *argv[]) {
    Solution127 solu;
    cout << solu.ladderLength("hit", "cog", *new vector<string>{"hot","dot","dog","lot","log","cog"}) << endl;
    cout << solu.ladderLength_implementation2("hit", "cog", *new vector<string>{"hot","dot","dog","lot","log","cog"}) << endl;
    return 0;
}
/*
url: https://leetcode.cn/problems/find-the-child-who-has-the-ball-after-k-seconds/description/
参考: https://www.bilibili.com/video/BV1h7421R78s/
标签: LeetCode第401场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3178 {
public:
    // 周赛时的解法，直接模拟
    int numberOfChild(int n, int k) {
        int pos = 0;
        int direction = 1;
        for (int i = 0; i < k; i++) {
            if (direction == 1 && pos == n - 1 || direction == -1 && pos == 0) {
                direction = -direction;
            }
            pos += direction;
        }
        return pos;
    }

    // 灵茶山艾府视频讲解解法，先算出走的整次数，然后余下的部分决定位置
    int numberOfChild_implementation2(int n, int k) {
        int count = k / (n - 1); // 一次需要走n - 1步
        int rest = k % (n - 1);
        return count & 1 ?  n - 1 - rest : rest;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}

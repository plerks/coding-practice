/*
url: https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/?envType=daily-question&envId=2023-11-01
LeetCode参考: https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/solutions/1190222/can-jia-hui-yi-de-zui-duo-yuan-gong-shu-u8e8u/
              https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/solutions/2507559/gong-shui-san-xie-sha-shi-nei-xiang-wai-4ig79/
标签: 基环内向树, 基环树, 拓扑排序, 环, 座位问题
*/

import java.util.*;

public class Solution2127 {
    // 这题感觉是截止目前(2023/11/1)碰到的LeetCode困难题里难度最高的，基环树的背景性也很强
    public int maximumInvitations(int[] favorite) {
        int n = favorite.length;
        int[] indegrees = new int[n];
        for (int i = 0; i < n; i++) {
            indegrees[favorite[i]]++;
        }
        int[] f = new int[n]; // dp
        Arrays.fill(f, 1);
        boolean[] used = new boolean[n];
        Deque<Integer> q = new LinkedList<>();
        for (int i = 0; i < n; i++) {
            if (indegrees[i] == 0) {
                q.offer(i);
            }
        }
        while (!q.isEmpty()) {
            int u = q.poll();
            used[u] = true;
            int v = favorite[u];
            f[v] = Math.max(f[v], f[u] + 1);
            indegrees[v]--;
            if (indegrees[v] == 0) {
                q.offer(v);
            }
        }
        int ringLen = 0, pathTotal = 0; // ringLen和pathTotal对应官方题解中的最大环长度和双向游走路径长度
        // 拓扑排序结束后，剩余节点是环上的节点
        for (int u = 0; u < n; u++) {
            if (!used[u]) {
                int v = favorite[u];
                if (favorite[v] == u) { // 这俩互相喜欢，大小为2的环
                    pathTotal += f[u] + f[v]; // 多个双向游走路径都可以上桌开会
                    used[u] = used[v] = true;
                }
                // 不是大小为2的环，要求最大的环的长度
                else {
                    int count = 1;
                    int t = u;
                    while (favorite[t] != u) {
                        count++;
                        used[t] = true;
                        t = favorite[t];
                    }
                    ringLen = Math.max(ringLen, count);
                }
            }
        }
        return Math.max(ringLen, pathTotal);
    }

    public static void main(String[] args) {
        Solution2127 solu = new Solution2127();
        System.out.println(solu.maximumInvitations(new int[]{2,2,1,2}));
    }
}

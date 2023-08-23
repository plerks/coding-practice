/*
url: https://leetcode.cn/problems/count-pairs-of-nodes/
LeetCode参考: https://leetcode.cn/problems/count-pairs-of-nodes/solutions/2398562/tong-ji-dian-dui-de-shu-mu-by-leetcode-s-yxlv/
              https://leetcode.cn/problems/count-pairs-of-nodes/solutions/2400682/ji-bai-100cong-shuang-zhi-zhen-dao-zhong-yhze/
*/

import java.util.*;

public class Solution1782 {
    public int[] countPairs(int n, int[][] edges, int[] queries) {
        int[] degrees = new int[n];
        int[] ans = new int[queries.length];
        HashMap<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < edges.length; i++) {
            int u = edges[i][0] - 1;
            int v = edges[i][1] - 1;
            // 后续对点对排除只算(u,v)不计算(v,u)
            if (u > v) {
                int temp = u;
                u = v;
                v = temp;
            }
            degrees[u]++;
            degrees[v]++;
            // 这里u * n + v相当于n进制，u,v都是[0,n)之间的，所以不会出现(u1,v1) != (u2,v2)时u * n + v相等
            map.put(u * n + v, map.getOrDefault(u * n + v, 0) + 1);
        }
        int[] degrees2 = Arrays.copyOf(degrees, n);
        Arrays.sort(degrees2);
        for (int i = 0; i < queries.length; i++) {
            // 用排好序的degrees2尝试点对，但是若u,v间有边，u,v之间的边被算了两次，degrees2[j] + degrees2[k] > queries[i]的计算方式是多算了的
            // 这里j,k的大小不知道，但是因为是无向图，若j,k满足，k,j也会满足，同一点对只会算一次，即不会同时算j,k和k,j
            // 双指针
            int left = 0, right = n - 1;
            while (left < right) {
                if (degrees2[left] + degrees2[right] <= queries[i]) {
                    left++;
                }
                else {
                    ans[i] += right - left;
                    right--;
                }
            }
            for (Map.Entry<Integer, Integer> entry : map.entrySet()) {
                int key = entry.getKey();
                int u = key / n;
                int v = key % n;
                if (u > v) continue;
                if (degrees[u] + degrees[v] > queries[i] && degrees[u] + degrees[v] - entry.getValue() <= queries[i]) {
                    ans[i]--;
                }
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution1782 solu = new Solution1782();
        System.out.println(Arrays.toString(solu.countPairs(8, new int[][]{{2,5},{5,4},{4,3},{7,3},{5,8},{6,1},{7,5},{6,1},{7,5},{3,1},{6,4},{6,8},{6,5},{5,6},{8,1},{1,6},{1,3},{5,6},{8,3},{6,2}}, new int[]{2,5,4,3,0,4,4,3,3,2,3,1,5,7,5,1,6,18,14})));
    }
}
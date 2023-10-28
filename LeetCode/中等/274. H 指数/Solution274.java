/*
url: https://leetcode.cn/problems/h-index/submissions/?envType=daily-question&envId=2023-10-29
标签: h指数
*/
import java.util.*;

public class Solution274 {
    public int hIndex(int[] citations) {
        /* 记n = citations.length，h指数一定在0到n之间，因此可以枚举，且枚举仅仅花费O(n)时间，已属最优。
        将citations从大到小排序，若尝试h = x，则只需检查citations[x - 1]是否>=x即可
        */
        Arrays.sort(citations); // 当成从大到小排的来用
        int ans = 0;
        for (int i = 0; i < citations.length; i++) {
            int h = i + 1;
            if (citations[citations.length - h] >= h) {
                ans = h;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution274 solu = new Solution274();
        System.out.println(solu.hIndex(new int[]{11,15}));
    }
}

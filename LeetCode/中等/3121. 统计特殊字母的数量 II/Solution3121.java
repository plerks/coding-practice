/*
url: https://leetcode.cn/problems/count-the-number-of-special-characters-ii/description/
LeetCode参考: https://leetcode.cn/problems/count-the-number-of-special-characters-ii/solutions/2749235/zhuang-tai-ji-on-yi-ci-bian-li-pythonjav-ajaz/
相关: LeetCode3120. 统计特殊字母的数量 I
标签: LeetCode第394场周赛, 状态机
*/

import java.util.*;

public class Solution3121 {
    public int numberOfSpecialChars(String word) {
        int[] pos1 = new int[26]; // 记录最后一个小写的出现位置
        int[] pos2 = new int[26]; // 记录第一个大写的出现位置
        Arrays.fill(pos1, -1);
        Arrays.fill(pos2, -1);
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            if (c >= 'a' && c <= 'z') {
                pos1[c - 'a'] = i;
            }
            else {
                if (pos2[c - 'A'] == -1) {
                    pos2[c - 'A'] = i;
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < 26; i++) {
            if (pos1[i] >= 0 && pos2[i] >= 0 && pos1[i] < pos2[i]) {
                ans++;
            }
        }
        return ans;
    }

    /* 灵茶山艾府题解解法，用状态机，一次遍历即可。对每个字母，在遇到大写和遇到小写的过程中
    状态进行变化，-1是遇到大写然后遇到小写的状态，是非法状态。 */
    public int numberOfSpecialChars_implementation2(String word) {
        int[] state = new int[26];
        int ans = 0;
        for (char c : word.toCharArray()) {
            int x = (c & 31) - 1;
            if ((c & 32) > 0) { // 遇到小写字母
                if (state[x] == 0) {
                    state[x] = 1;
                }
                else if (state[x] == 2) {
                    state[x] = -1;
                    ans--; // 2变到1，ans减1
                }
                // 还有状态为1和-1的状态下遇到小写字母的情况，不过这两种情况自旋，不用做任何事
            }
            else { // 遇到大写字母
                if (state[x] == 0) {
                    state[x] = -1;
                }
                else if (state[x] == 1) {
                    state[x] = 2;
                    ans++; // 1变到2，ans加1
                }
            }
        }
        /* 可以在最后数一遍状态，如果状态是2则说明同时有小写和大写且最后一个小写在第一个大写之前，则ans++，
        这样总共要两次遍历。这里为了一次遍历，在循环过程中就计数，若1变到2，ans+1，若后面又遇到了小写，则说明
        是错的，ans再减掉1
        */
        return ans;
    }

    public static void main(String[] args) {
        Solution3121 solu = new Solution3121();
        System.out.println(solu.numberOfSpecialChars("aaAbcBC"));
        System.out.println(solu.numberOfSpecialChars_implementation2("aaAbcBC"));
    }
}

/*
url: https://leetcode.cn/problems/construct-string-with-repeat-limit/description/?envType=daily-question&envId=2024-01-13
LeetCode参考: https://leetcode.cn/problems/construct-string-with-repeat-limit/solutions/1300982/gou-zao-xian-zhi-zhong-fu-de-zi-fu-chuan-v02s/
标签: 双指针
*/

public class Solution2182 {
    public String repeatLimitedString(String s, int repeatLimit) {
        char repeatChar = '0';
        int repeatTime = 0;
        int[] times = new int[26];
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            times[c - 'a']++;
        }
        StringBuilder sb = new StringBuilder();
        while (true) {
            boolean haveCandidate = false;
            for (char c = 'z'; c >= 'a'; c--) {
                if (times[c - 'a'] == 0) continue;
                else {
                    if (repeatChar == c && repeatTime < repeatLimit) {
                        sb.append(c);
                        times[c - 'a']--;
                        repeatTime++;
                        haveCandidate = true;
                        break;
                    }
                    if (repeatChar != c) {
                        sb.append(c);
                        times[c - 'a']--;
                        repeatChar = c;
                        repeatTime = 1;
                        haveCandidate = true;
                        break;
                    }
                }
            }
            if (!haveCandidate) break;
        }
        return sb.toString();
    }

    // 参考题解的做法，用双指针避免每次都循环尝试z到a
    public String repeatLimitedString_implementation2(String s, int repeatLimit) {
        int repeatTime = 0;
        int[] times = new int[26];
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            times[c - 'a']++;
        }
        StringBuilder sb = new StringBuilder();
        for (int i = 25, j = 24; i >= 0 && j >= 0;) {
            if (times[i] == 0) {
                repeatTime = 0;
                i--;
            }
            else if (repeatTime < repeatLimit) {
                sb.append((char)('a' + i));
                times[i]--;
                repeatTime++;
            }
            // i有剩余但不可用
            else {
                while (j >= 0 && (j >= i || times[j] == 0)) j--;
                if (j >= 0) {
                    sb.append((char)('a' + j));
                    times[j]--;
                    repeatTime = 0; // 准备返回去用i
                }
            }
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        Solution2182 solu = new Solution2182();
        System.out.println(solu.repeatLimitedString("aababab", 2));
        System.out.println(solu.repeatLimitedString_implementation2("aababab", 2));
    }
}

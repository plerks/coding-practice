// https://leetcode.cn/problems/maximum-odd-binary-number/description/?envType=daily-question&envId=2024-03-13

public class Solution2864 {
    public String maximumOddBinaryNumber(String s) {
        int last1Index = -1; // s中至少包含一个'1'，记录最后一个'1'的位置
        int zeroCount = 0;
        StringBuilder sb = new StringBuilder();
        int n = s.length();
        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);
            if (c == '1') {
                sb.append('1');
                last1Index = sb.length() - 1;
            }
            else zeroCount++;
        }
        for (int i = 0; i < zeroCount; i++) {
            sb.append('0');
        }
        sb.setCharAt(last1Index, '0');
        sb.setCharAt(sb.length() - 1, '1');
        // 题目输出可以包含前导零
        return sb.toString();
    }

    public static void main(String[] args) {
        Solution2864 solu = new Solution2864();
        System.out.println(solu.maximumOddBinaryNumber("010"));
    }
}

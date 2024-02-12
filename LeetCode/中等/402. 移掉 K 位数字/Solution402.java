/*
url: https://leetcode.cn/problems/remove-k-digits/description/
标签: 单调栈
*/

import java.util.*;

public class Solution402 {
    public String removeKdigits(String num, int k) {
        /* 从左到右遍历num，若nums[j]比nums[i]大，则保留j删去i一定比保留i删去j优，
        若选择i,j都不保留，没有必要，后续j+1可能比j大，若选择i,j都保留，则后续遇到nums[j]>nums[j+1]时应该
        删去j，进一步应该删去i。即，为了让最终值更小，首位数应该选择从左到右遍历过程中遇到的最小的，一旦一位
        数发现自己比首位小，自己去抢首位总是更优的。从而单调栈。
        */
        Deque<Integer> stack = new LinkedList<>();
        for (int i = 0; i < num.length(); i++) {
            int digit = num.charAt(i) - '0';
            while (!stack.isEmpty() && stack.peek() > digit && k > 0) {
                stack.pop();
                k--;
            }
            stack.push(digit);
        }
        char[] arr = new char[stack.size()];
        int index = arr.length - 1;
        while (!stack.isEmpty()) {
            arr[index--] = (char)(stack.pop() + '0');
        }
        index = 0;
        while (index < arr.length && arr[index] == '0') index++;
        StringBuilder ans = new StringBuilder();
        for (int i = index; i < arr.length - k; i++) { // 删除次数没用完要从末尾删
            ans.append(arr[i]);
        }
        return ans.isEmpty() ? "0" : ans.toString();
    }

    public static void main(String[] args) {
        Solution402 solu = new Solution402();
        // System.out.println(solu.removeKdigits("1432219", 3));
        // System.out.println(solu.removeKdigits("10200", 1));
        // System.out.println(solu.removeKdigits("10", 2));
        System.out.println(solu.removeKdigits("9", 1));
    }
}

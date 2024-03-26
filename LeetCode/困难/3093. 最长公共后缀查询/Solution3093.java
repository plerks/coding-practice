/*
url: https://leetcode.cn/problems/longest-common-suffix-queries/description/
LeetCode参考: https://leetcode.cn/problems/longest-common-suffix-queries/solutions/2704763/zi-dian-shu-wei-hu-zui-duan-chang-du-he-r3h3j/
相关: LeetCode208. 实现 Trie (前缀树), 典型问题/字典树
标签: LeetCode第390场周赛, 字典树, 前缀树
*/

import java.util.*;

// 此题属于我参加的LeetCode第390场周赛
public class Solution3093 {
    // 周赛时的暴力做法，812 / 816 个通过的测试用例，超时
    public int[] stringIndices_exceed_time_limit(String[] wordsContainer, String[] wordsQuery) {
        int n = wordsQuery.length;
        int[] ans = new int[n];
        for (int i = 0; i < n; i++) {
            String word = wordsQuery[i];
            int maxCount = 0; // 最长长度
            int minLen = Integer.MAX_VALUE; // 选最短的字符串
            int index = 0;
            for (int j = 0; j < wordsContainer.length; j++) {
                String s = wordsContainer[j];
                int count = calc(s, word); // 计算最长公共后缀
                if (count > maxCount) {
                    maxCount = count;
                    minLen = s.length();
                    index = j;
                }
                else if (count == maxCount && s.length() < minLen) {
                    minLen = s.length();
                    index = j;
                }
            }
            ans[i] = index;
        }
        return ans;
    }

    private int calc(String s, String word) {
        int i = s.length() - 1, j = word.length() - 1;
        int maxSuffixLen = 0;
        while (i >= 0 && j >= 0 && s.charAt(i) == word.charAt(j)) {
            maxSuffixLen++;
            i--;
            j--;
        }
        return maxSuffixLen;
    }

    class Node {
        Node[] children = new Node[26];
        int minStringLen = Integer.MAX_VALUE; // 记录匹配到这个后缀的最短word长度
        int index = 0;
    }

    public int[] stringIndices(String[] wordsContainer, String[] wordsQuery) {
        Node root = new Node();
        // 建字典树
        for (int i = 0; i < wordsContainer.length; i++) {
            String word = wordsContainer[i];
            // 到达同一节点的后缀匹配长度是相同的
            Node node = root;
            if (word.length() < node.minStringLen) {
                node.minStringLen = word.length();
                node.index = i;
            }
            for (int j = word.length() - 1; j >= 0; j--) {
                char c = word.charAt(j);
                if (node.children[c - 'a'] == null) {
                    node.children[c - 'a'] = new Node();
                }
                node = node.children[c - 'a'];
                if (word.length() < node.minStringLen) { // 同公共后缀长度保留word长度更短的，由于从左到右遍历，同公共后缀长度同word长度保留更早的
                    node.minStringLen = word.length();
                    node.index = i;
                }
            }
        }
        int n = wordsQuery.length;
        int[] ans = new int[n];
        for (int i = 0; i < n; i++) {
            Node node = root;
            String query = wordsQuery[i];
            // 尽量沿着字典树走
            for (int j = query.length() - 1; j >= 0 && node.children[query.charAt(j) - 'a'] != null; j--) {
                node = node.children[query.charAt(j) - 'a'];
            }
            ans[i] = node.index;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution3093 solu = new Solution3093();
        System.out.println(Arrays.toString(solu.stringIndices(new String[]{"abcd","bcd","xbcd"}, new String[]{"cd","bcd","xyz"})));
    }
}

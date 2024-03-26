/*
url: https://leetcode.cn/problems/implement-trie-prefix-tree/description/
LeetCode参考: https://leetcode.cn/problems/implement-trie-prefix-tree/solutions/717239/shi-xian-trie-qian-zhui-shu-by-leetcode-ti500/
相关: LeetCode3093. 最长公共后缀查询, 典型问题/字典树
标签: 字典树, 前缀树
*/

// import java.util.*;

/* 我的解法，算是刚好猜出了前缀树的实现方式，能过，击败21.15%使用Java的用户，效率还行。从名字上来看是要组织成树，search()操作直接用一个set
就可以完成，startsWith()若暴力得将set中元素一个一个比对，于是想到把字符组织成树，然后调用startWith()时按树路径走。这里没有删除word的需求，
若有删除的需求可能每个节点记录一下count可能能行。
*/
/* public class Solution208 {
    TrieNode root;
    HashSet<String> set;

    // 粘贴到LeetCode上把这个方法改名为Trie
    public Solution208() {
        this.root = new TrieNode();
        this.set = new HashSet<>();
    }
    
    public void insert(String word) {
        set.add(word);
        TrieNode node = root;
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            if (node.children[c - 'a'] == null) {
                node.children[c - 'a'] = new TrieNode();
                node = node.children[c - 'a'];
            }
            else node = node.children[c - 'a'];
        }
    }
    
    public boolean search(String word) {
        return set.contains(word);
    }
    
    public boolean startsWith(String prefix) {
        TrieNode node = root;
        for (int i = 0; i < prefix.length(); i++) {
            char c = prefix.charAt(i);
            if (node.children[c - 'a'] == null) {
                return false;
            }
            node = node.children[c - 'a'];
        }
        return true;
    }

    public static void main(String[] args) {
        Solution208 solu = new Solution208();
        solu.insert("apple");
        System.out.println(solu.search("apple"));
        System.out.println(solu.search("app"));
        System.out.println(solu.startsWith("app"));
        solu.insert("app");
        System.out.println(solu.search("app"));
    }
}

class TrieNode {
    TrieNode[] children;

    public TrieNode() {
        this.children = new TrieNode[26]; // 这里word 和 prefix 仅由小写英文字母组成，26个就够长
    }
} */

/* 参考官方题解，和上面差不多，不过不用把Node节点单独定义出来，Trie直接就是Node节点，且不需要单独一个set存所有字符串，巧妙的是多了一个isEnd
属性表示当前节点是否是某个字符串的结尾(不是代表是否是叶子节点)，这样就相当于顶替了set。如果要支持删除操作应该是要在节点上有一个属性count，用来
记录字符串重在这个节点上的次数。
这里把Trie作为静态内部类用Solution208包裹一下是由于这题和`典型问题\字典树`的类名相同都是Trie，防止潜在问题。
*/
public class Solution208 {
    static class Trie {
        Trie[] children;
        boolean isEnd;
    
        public Trie() {
            this.children = new Trie[26]; // 这里word 和 prefix 仅由小写英文字母组成，26个就够长
            this.isEnd = false;
        }
        
        public void insert(String word) {
            Trie node = this;
            for (int i = 0; i < word.length(); i++) {
                char c = word.charAt(i);
                if (node.children[c - 'a'] == null) {
                    node.children[c - 'a'] = new Trie();
                }
                node = node.children[c - 'a'];
            }
            node.isEnd = true;
        }
        
        public boolean search(String word) {
            Trie node = this;
            for (int i = 0; i < word.length(); i++) {
                char c = word.charAt(i);
                if (node.children[c - 'a'] == null) {
                    return false;
                }
                node = node.children[c - 'a'];
            }
            return node.isEnd;
        }
        
        public boolean startsWith(String prefix) {
            Trie node = this;
            for (int i = 0; i < prefix.length(); i++) {
                char c = prefix.charAt(i);
                if (node.children[c - 'a'] == null) {
                    return false;
                }
                node = node.children[c - 'a'];
            }
            return true;
        }
    }

    public static void main(String[] args) {
        Trie trie = new Trie(); // trie为根节点
        trie.insert("apple");
        System.out.println(trie.search("apple"));
        System.out.println(trie.search("app"));
        System.out.println(trie.startsWith("app"));
        trie.insert("app");
        System.out.println(trie.search("app"));
    }
}

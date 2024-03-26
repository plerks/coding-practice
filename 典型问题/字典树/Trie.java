/*
描述: 字典树(也叫前缀树)，主要功能是向字典树中插入及查找字符串，以及查找字典树中是否存在一个字符串，其前缀是prefix
参考: https://oi-wiki.org/string/trie/
相关: LeetCode208. 实现 Trie (前缀树), LeetCode3093. 最长公共后缀查询
标签: 字典树, 前缀树
*/

// 这里假设只涉及小写字母
public class Trie {
    Trie[] children;
    boolean isEnd;

    public Trie() {
        this.children = new Trie[26]; // 这里假设只涉及小写字母，26个就够长
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

import java.util.Arrays;

public class KMP {
    public int[] buildNext(String p) {
        int[] next = new int[p.length()];
        next[0] = -1;
        int j = 0, t = -1; // t为next[j]
        // 从next[j]求next[j + 1]
        while (j < p.length() - 1) {
            if (t == -1 || p.charAt(j) == p.charAt(t)) {
                next[j + 1] = t + 1;
                j++;
                t++; // t变为新的next[j]
            }
            else {
                t = next[t];
            }
        }
        return next;
    }

    public int match(String s, String p) {
        int[] next = buildNext(p);
        int i = 0, j = 0;
        while (i < s.length() && j < p.length()) {
            if (j == -1 || s.charAt(i) == p.charAt(j)) {
                i++;
                j++;
            }
            else {
                j = next[j];
            }
        }
        return j == p.length() ? i - j : -1;
    }

    public int[] buildOptimizedNext(String p) {
        int[] next = new int[p.length()];
        next[0] = -1;
        int j = 0, t = -1;
        /* 假如已知next[j] == t，如何求next[j+1]?
        next[j] == t表示[0, j)的真前后缀匹配且p[j] != p[t]的最长匹配长度为t，
        但到了求next[j + 1]时，我们求[0, j + 1)的最长匹配长度，是要p[j] == p[t]的，
        所以为了求next[j + 1]，我们要检测一下是否p[j] == p[t]，
        1. 如果p[j] == p[t]，那么根据改进next表的策略，检查p[j + 1]是否等于p[t + 1]，
           如果不等，则next[j + 1]就是t + 1；
           如果相等，则next[j + 1]要更短，我们本来是要找[0, j + 1)的真前后缀匹配且p[j + 1] != p[t + 1]，现在p[j + 1] == p[t + 1]，
           说明p[0, t + 1] == p[j - t, j + 1]，则在[0, j + 1)中找max{t_x}使得真前后缀匹配且p[j + 1] != p[t_x + 1]完全
           等同于在[0, t + 1)中找max{t_x}使得真前后缀匹配且p[t + 1] != p[t_x + 1]，
           而这正是改进next[t + 1]的定义！于是next[j + 1]就是next[t + 1]
        2. 如果p[j] != p[t]，说明这个t不能把j处的字符接上，无法使得[0, j + 1)的真前后缀匹配，于是要更短一点的t' = next[t]，
           然后重新看能否p[j] == p[t']
        
        改进next[j] == t的定义不是p[j] != p[t]吗？那么不是会使得p[j] == p[t]注定失败吗？
        对j的一轮循环(j从刚开始取某个值到变为下一个值为一轮，这种写法，j的轮和while循环的轮不同步)，
        若开始时t == 改进next[j]，那么确实p[j] == p[t]一定失败，但是执行t = next[t]后就不一定了。

        t到底代表什么？
        对于build非改进next表，代码`next[j + 1] = t + 1;j++;t++;`，则下一轮j开始时一定有t == next[j]；
        但对于build改进next表，一轮j开始时，t是[0, j - 1]的最长真前后缀匹配长度，也即非改进next[j]，然后直到满足p[j] == p[t]，
        这时才求出了非改进next[j + 1] (t+1)，然后再通过判断p[j + 1] != p[t + 1]求出真正的改进next[j + 1]；
        也就是说t都是非改进next[j]！
        `t = next[t];` 这句，会把改进next[t + 1] 赋值给 t 重新尝试，那 t 还是 非改进next[j] 吗？
        是，求next[j]时，若p[t] != p[j]，那么下一个尝试的 p[t'] 应!= p[t] 才可能让 p[t'] = p[j]，也就是说，
        t = next[...next[t]] 这个过程用改进next表是比用非改进next表更快的，最后都会找到 j 的最长真前后缀匹配长度t，t的含义维持为非改进next[j]。
        
        关于非改进next表和改进next表的构造代码，看./KMP.cpp里的写法，更简洁。
        */
        while (j < p.length() - 1) {
            if (t == -1 || p.charAt(j) == p.charAt(t)) {
                next[j + 1] = (p.charAt(j + 1) != p.charAt(t + 1) ? t + 1 : next[t + 1]);
                j++;
                t++;
            }
            else {
                t = next[t];
            }
        }
        return next;
    }

    public int optimizedMatch(String s, String p) {
        int[] next = buildOptimizedNext(p);
        int i = 0, j = 0;
        while (i < s.length() && j < p.length()) {
            if (j == -1 || s.charAt(i) == p.charAt(j)) {
                i++;
                j++;
            }
            else {
                j = next[j];
            }
        }
        return j == p.length() ? i - j : -1;
    }

    public static void main(String[] args) {
        KMP kmp = new KMP();
        System.out.println(Arrays.toString(kmp.buildNext("CINCINNATI")));
        System.out.println(kmp.match("data structures and algorithms", "ta"));
        System.out.println(Arrays.toString(kmp.buildOptimizedNext("CINCINNATI")));
        System.out.println(kmp.optimizedMatch("data structures and algorithms", "ta"));
    }
}

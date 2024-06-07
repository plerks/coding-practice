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
        int j = 0, t = -1; // t为next[j]
        // 从next[j]求next[j + 1]
        while (j < p.length() - 1) {
            if (t == -1 || p.charAt(j) == p.charAt(t)) {
                next[j + 1] = (p.charAt(j + 1) != p.charAt(t + 1) ? t + 1 : next[t + 1]);
                j++;
                t++; // t变为新的next[j]
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

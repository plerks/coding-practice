// https://leetcode.cn/problems/remove-comments/

import java.util.ArrayList;
import java.util.List;

public class Solution722 {
    public List<String> removeComments(String[] source) {
        for (int i = 0; i < source.length; i++) {
            source[i] = source[i] + "\n";
        }
        for (int i = 0; i < source.length; i++) {
            String s = source[i];
            if (s.indexOf("//") == -1 && s.indexOf("/*") == -1) {
                continue;
            }
            else if (s.indexOf("//") >= 0 && (s.indexOf("/*") == -1 || s.indexOf("/*") > s.indexOf("//"))) {
                source[i] = s.substring(0, s.indexOf("//")) + "\n";
            }
            else if (s.indexOf("/*") >= 0 && s.indexOf("*/", s.indexOf("/*") + 2) >= 0) {
                source[i] = s.substring(0, s.indexOf("/*")) + s.substring(s.indexOf("*/", s.indexOf("/*") + 2) + "*/".length());
                i--; // 可能这行还有其它块注释
                continue;
            }
            else if (s.indexOf("/*") >= 0 && s.indexOf("*/", s.indexOf("/*") + 2) == -1) {
                source[i] = s.substring(0, s.indexOf("/*"));
                while (true) {
                    i++;
                    if (i >= source.length) {
                        break;
                    }
                    s = source[i];
                    if (s.indexOf("*/") == -1) {
                        source[i] = "";
                    }
                    else {
                        source[i] = s.substring(s.indexOf("*/") + "*/".length());
                        i--; // 可能这行还有其它块注释
                        break;
                    }
                }
            }
        }
        List<String> list = new ArrayList<>();
        boolean waitForConcat = false;
        int i = 0;
        while (source[i].equals("") || source[i].equals("\n")) {
            i++;
        }
        for (; i < source.length; i++) {
            if (source[i].equals("\n")) {
                waitForConcat = false;
                continue;
            }
            if (source[i].equals("")) {
                waitForConcat = true;
                continue;
            }
            else {
                if (waitForConcat) {
                    list.set(list.size() - 1, list.get(list.size() - 1).concat(source[i].replace("\n", "")));
                    waitForConcat = false;
                }
                else {
                    list.add(source[i].replace("\n", ""));
                }
            }
        }
        return list;
    }

    public static void main(String[] args) {
        Solution722 solu = new Solution722();
        // System.out.println(solu.removeComments(new String[]{"/*Test program */", "int main()", "{ ", "  // variable declaration ", "int a, b, c;", "/* This is a test", "   multiline  ", "   comment for ", "   testing */", "a = b + c;", "}"}));
        // System.out.println(solu.removeComments(new String[]{"a/*comment", "line", "more_comment*/b"}));
        // System.out.println(solu.removeComments(new String[]{"void func(int k) {", "// this function does nothing /*", "   k = k*2/4;", "   k = k/2;*/", "}"}));
        System.out.println(solu.removeComments(new String[]{"a/*/b//*c","blank","d//*e/*/f"}));
    }
}
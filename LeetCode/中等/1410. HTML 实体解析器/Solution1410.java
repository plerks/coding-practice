// https://leetcode.cn/problems/html-entity-parser/?envType=daily-question&envId=2023-11-23

public class Solution1410 {
    public String entityParser(String text) {
        StringBuilder sb = new StringBuilder();
        int i = 0;
        String[][] special = new String[][]{{"&quot;", "\""}, {"&apos;", "'"}, {"&amp;", "&"}, {"&gt;", ">"}, {"&lt;", "<"}, {"&frasl;", "/"}};
        while (i < text.length()) {
            if (text.charAt(i) != '&') sb.append(text.charAt(i++));
            else {
                boolean replaced = false;
                for (int j = 0; j < special.length; j++) {
                    if (text.substring(i, Math.min(text.length(), i + special[j][0].length())).equals(special[j][0])) {
                        sb.append(special[j][1]);
                        i += special[j][0].length();
                        replaced = true;
                        break;
                    }
                }
                if (!replaced) sb.append(text.charAt(i++));
            }
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        Solution1410 solu = new Solution1410();
        System.out.println(solu.entityParser("&quot; &gt; &gt;"));
    }
}

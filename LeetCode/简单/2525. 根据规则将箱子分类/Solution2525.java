// https://leetcode.cn/problems/categorize-box-according-to-criteria/?envType=daily-question&envId=2023-10-20

public class Solution2525 {
    public String categorizeBox(int length, int width, int height, int mass) {
        boolean bulky = length >= 10000 || width >= 10000 || height >= 10000 || (long)length * width* height >= Math.pow(10, 9);
        boolean heavy = mass >= 100;
        if (bulky && heavy) return "Both";
        if (!bulky && !heavy) return "Neither";
        if (bulky && !heavy) return "Bulky";
        return "Heavy";
    }

    public static void main(String[] args) {
        Solution2525 solu = new Solution2525();
        System.out.println(solu.categorizeBox(2909, 3968, 3272, 727));
    }
}

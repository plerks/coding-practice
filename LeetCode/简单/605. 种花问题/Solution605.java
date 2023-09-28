/*
url: https://leetcode.cn/problems/can-place-flowers/?envType=daily-question&envId=2023-09-29
标签: 贪心
*/

public class Solution605 {
    public boolean canPlaceFlowers(int[] flowerbed, int n) {
        int count = 0;
        for (int i = 0; i < flowerbed.length; i++) {
            if (flowerbed[i] == 1 || (i - 1 >= 0 && flowerbed[i - 1] == 1) || (i + 1 < flowerbed.length && flowerbed[i + 1] == 1)) {
                continue;
            }
            flowerbed[i] = 1;
            count++;
        }
        return count >= n;
    }

    public static void main(String[] args) {
        Solution605 solu = new Solution605();
        System.out.println(solu.canPlaceFlowers(new int[]{1,0,0,0,0,1}, 2));
    }
}
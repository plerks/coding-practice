/*
url: https://leetcode.cn/problems/filter-restaurants-by-vegan-friendly-price-and-distance/?envType=daily-question&envId=2023-09-27
标签: 多级条件排序写法
*/

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Solution1333 {
    public List<Integer> filterRestaurants(int[][] restaurants, int veganFriendly, int maxPrice, int maxDistance) {
        List<int[]> list;
        list = new ArrayList<>();
        for (int[] arr : restaurants) {
            if (veganFriendly == 1 && arr[2] == 1 && arr[3] <= maxPrice && arr[4] <= maxDistance) {
                list.add(arr);
            }
            if (veganFriendly == 0 && arr[3] <= maxPrice && arr[4] <= maxDistance) {
                list.add(arr);
            }
        }
        Collections.sort(list, (x, y) -> {
            if (x[1] != y[1]) {
                return y[1] - x[1];
            }
            if (x[0] != y[0]) {
                return y[0] - x[0];
            }
            return 0;
        });
        List<Integer> ans = new ArrayList<>();
        for (int[] arr : list) {
            ans.add(arr[0]);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution1333 solu = new Solution1333();
        System.out.println(solu.filterRestaurants(new int[][]{{1,4,1,40,10},{2,8,0,50,5},{3,8,1,30,4},{4,10,0,10,3},{5,1,1,15,1}}, 1, 50, 10));
    }
}
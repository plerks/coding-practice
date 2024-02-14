/*
描述: Java的多级条件排序的写法
相关: LeetCode1333. 餐厅过滤器, LeetCode2512. 奖励最顶尖的 K 名学生, LeetCode987. 二叉树的垂序遍历
*/

import java.util.*;

public class MultipleConditionSort {
    public static void main(String[] args) {
        List<Promotion> list = new ArrayList<>();
        list.add(new Promotion(5, 6, 1));
        list.add(new Promotion(3, 4, 0));
        list.add(new Promotion(1, 3, 2));
        Collections.sort(list, (x, y) -> {
            if (x.discount != y.discount) {
                return x.discount > y.discount ? -1 : 1;
            }
            if (x.endDate != y.endDate) {
                return x.endDate < y.endDate ? -1 : 1;
            }
            if (x.id != y.id) {
                return x.id < y.id ? -1 : 1;  // 直接写return x.id - y.id可能会有Integer.MIN_VALUE - 1 > 0导致排序错误的问题，若数据范围能确保不溢出写成x.id - y.id也可
            }
            return 0;
        });
        for (Promotion promotion : list) {
            System.out.println(String.format("discount: %s, endDate: %s, id: %s", promotion.discount, promotion.endDate, promotion.id));
        }
    }
}

class Promotion {
    int discount;
    int endDate;
    int id;

    public Promotion(int discount, int endDate, int id) {
        this.discount = discount;
        this.endDate = endDate;
        this.id = id;
    }
}
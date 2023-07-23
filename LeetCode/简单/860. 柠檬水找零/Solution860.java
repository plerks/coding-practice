import java.util.ArrayList;
import java.util.Map;

public class Solution860 {
    public boolean lemonadeChange(int[] bills) {
        // 每张钱有多少张
        int five = 0; int ten = 0;
        for (int bill : bills) {
            if (bill == 5) {
                five++;
            }
            if (bill == 10) {
                ten++;
                five--;
            }
            else if (bill == 20) {
                if (ten > 0) {
                    ten--;
                    five--;
                }
                else five -= 3;
            }
            // 可以只判断是否five<0，最终都会尝试5元的
            if (five < 0 || ten < 0) return false;
        }
        return true;
    }

    public static void main(String[] args) {
        Solution860 solu = new Solution860();
        System.out.println(solu.lemonadeChange(new int[]{5,5,5,10,20}));
    }
}
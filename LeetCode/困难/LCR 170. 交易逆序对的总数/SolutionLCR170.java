/*
url: https://leetcode.cn/problems/shu-zu-zhong-de-ni-xu-dui-lcof/description/
LeetCode参考: https://leetcode.cn/problems/shu-zu-zhong-de-ni-xu-dui-lcof/solutions/216984/shu-zu-zhong-de-ni-xu-dui-by-leetcode-solution/
相关: LeetCode493. 翻转对
标签: 逆序对数, 归并排序, 树状数组
*/

public class SolutionLCR170 {
    int ans = 0;
    int[] temp;

    public int reversePairs(int[] record) {
        if (record.length == 0) return 0;
        this.temp = new int[record.length / 2]; // 用作merge的数组
        mergeSort(record, 0, record.length);
        return ans;
    }

    private void mergeSort(int[] record, int left, int right) {
        if (right - left == 1) return;
        int mid = (left + right) / 2;
        mergeSort(record, left, mid);
        mergeSort(record, mid, right);
        merge(record, left, mid, right);
    }

    private void merge(int[] record, int left, int mid, int right) {
        for (int i = left; i < mid; i++) {
            temp[i - left] = record[i];
        }
        int p1 = 0, p2 = mid, p = left;
        // (mid - left)为前半段长度
        while (p1 < (mid - left) && p2 < right) {
            if (temp[p1] <= record[p2]) {
                record[p++] = temp[p1++];
            }
            else {
                ans += (mid - left) - p1; // 此时temp[p1]及右边的元素全部大于record[p2]，构成逆序对
                record[p++] = record[p2++];
            }
        }
        while (p1 < (mid - left)) {
            record[p++] = temp[p1++];
        }
    }

    public static void main(String[] args) {
        SolutionLCR170 solu = new SolutionLCR170();
        System.out.println(solu.reversePairs(new int[]{9, 7, 5, 4, 6}));
    }
}

#include <bits/stdc++.h>

using namespace std;

class SolutionLCR170 {
public:
    int ans = 0;
    vector<int> temp; // 用作归并的数组

    /* 把线性的结构树化，用归并排序或者认为是线段树的分治思路。
    若对A B两个子向量归并的一步选A，则没有逆序对，若选B，则B的这个头能与|A|都形成逆序对，直接计数，不用反复比较
    */
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        temp.resize(n / 2);
        merge_sort(nums, 0, n);
        return ans;
    }

    void merge_sort(vector<int>& nums, int left, int right) {
        if (right - left <= 1) return;
        int mid = (left + right) >> 1;
        merge_sort(nums, left, mid);
        merge_sort(nums, mid, right);
        merge(nums, left, mid, right);
    }

    void merge(vector<int>& nums, int left, int mid, int right) {
        for (int i = left; i < mid; i++) temp[i - left] = nums[i];

        int i = 0, j = mid, k = left;
        while (i < mid - left && j < right) {
            // 选左边
            if (temp[i] <= nums[j]) {
                nums[k++] = temp[i++];
            }
            // 选右边
            else {
                ans += mid - left - i;
                nums[k++] = nums[j++];
            }
        }
        // 处理剩余的左部。剩余的右部不用处理
        while (i < mid - left) {
            nums[k++] = temp[i++];
        }
    }
};

int main(int argc, char const *argv[]) {
    SolutionLCR170 solu;
    cout << solu.reversePairs(*new vector<int>{9, 7, 5, 4, 6}) << endl;
    return 0;
}
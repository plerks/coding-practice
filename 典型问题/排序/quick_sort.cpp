#include <bits/stdc++.h>

using namespace std;

int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[left]; // 这里没有随机选一个位置的值作为pivot，简便起见直接选了arr[left]
    while (left < right) {
        while (left < right && arr[right] > pivot) right--;
        if (left < right) arr[left++] = arr[right]; // 当left == right时，该退出循环把pivot写进来了，这里和下面的对应位置都要判断left < right才执行
        while (left < right && arr[left] < pivot) left++;
        if (left < right) arr[right--] = arr[left];
    }
    arr[left] = pivot;
    return left;
}

void quick_sort(vector<int>& arr, int left, int right) { // 对arr[left, right)排序
    if (left + 1 >= right) {
        return;
    }
    int mid = partition(arr, left, right - 1); // 这里转成闭区间
    quick_sort(arr, left, mid);
    quick_sort(arr, mid + 1, right);
}

int main(int argc, char const *argv[]) {
    vector<int> arr = {797, 925, 498, 191, 208, 626, 665, 999};
    quick_sort(arr, 0, arr.size());
    for (int x : arr) cout << x << " ";
    return 0;
}
import java.util.Arrays;

public class Sort {
    public static void main(String[] args) {
        Sort sort = new Sort();
        int[] arr = new int[]{797, 925, 498, 191, 208, 626, 665, 999};

        // 只写了插入排序，归并排序，快排。

        int[] arr1 = arr.clone();
        sort.insertionSort(arr1);
        System.out.println(Arrays.toString(arr1));

        int[] arr2 = arr.clone();
        sort.mergeSort(arr2, 0, arr2.length);
        System.out.println(Arrays.toString(arr2));

        int[] arr3 = arr.clone();
        sort.quickSort(arr3, 0, arr3.length);
        System.out.println(Arrays.toString(arr3));
    }

    public void insertionSort(int[] arr) {
        for (int i = 1; i < arr.length - 1; i++) {
            for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--) {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }

    public void mergeSort(int[] arr, int left, int right) { // 对arr[left, right)排序
        if (left + 1 >= right) {
            return;
        }
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid, right);
        merge(arr, left, right);
    }

    public void merge(int[] arr, int left, int right) {
        int mid = (left + right) / 2;
        int[] temp = new int[mid - left]; // 归并需要额外空间
        for (int i = 0; i < temp.length; i++) {
            temp[i] = arr[left + i];
        }
        int i = 0, j = mid, k = left;
        while (i < temp.length && j < right) {
            if (temp[i] <= arr[j]) {
                arr[k++] = temp[i++];
            }
            else {
                arr[k++] = arr[j++];
            }
        }
        // 若前一半有剩余，把前一半剩余的全部写回。若后一半有剩余，则后一半本身已就位
        while (i < temp.length) {
            arr[k++] = temp[i++];
        }
    }

    public void quickSort(int[] arr, int left, int right) { // 对arr[left, right)排序
        if (left + 1 >= right) {
            return;
        }
        int mid = partition(arr, left, right - 1); // 这里转成闭区间
        quickSort(arr, left, mid);
        quickSort(arr, mid + 1, right);
    }

    public int partition(int[] arr, int left, int right) {
        int pivot = arr[left]; // 这里没有随机选一个位置的值作为pivot，简便起见直接选了arr[left]
        while (left < right) {
            while (left < right) {
                if (arr[right] > pivot) {
                    right--;
                }
                else {
                    arr[left++] = arr[right];
                    break;
                }
            }
            while (left < right) {
                if (arr[left] < pivot) {
                    left++;
                }
                else {
                    arr[right--] = arr[left];
                    break;
                }
            }
        }
        arr[left] = pivot;
        return left;
    }
}

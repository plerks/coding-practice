import java.util.Arrays;

class ArraySortIntArray {
    public static void main(String[] args) {
        int n = 7;
        int[] arr1 = new int[n];
        for (int i = 0; i < n; i++) {
            arr1[i] = i;
        }
        /* 这里会报错找不到匹配的方法，参考https://stackoverflow.com/questions/12654600/sorting-an-int-array-in-descending-order-is-giving-method-not-applicable-for-ar，
        sort(T[] a, Comparator<? super T> c)，这里int[]无法和T[]对应上，需要变成对象数组，所以要换成Integer[] */
        /* Arrays.sort(arr1, (x ,y) -> {
            return x * (x - 5) - y * (y - 5);
        }); */
        
        Integer[] arr2 = new Integer[n];
        for (int i = 0; i < n; i++) {
            arr2[i] = i;
        }
        Arrays.sort(arr2, (x ,y) -> {
            return x * (x - 6) - y * (y - 6);
        });
        System.out.println(Arrays.toString(arr2));
    }
}
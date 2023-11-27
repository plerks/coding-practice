// https://leetcode.cn/problems/design-front-middle-back-queue/?envType=daily-question&envId=2023-11-28

import java.util.ArrayList;
import java.util.List;

/* 只在头尾及中部操作，用链表应该好一些，避免用ArrayList的扩容/缩容，对于中部操作，维护一个指针指向中部元素。
最简单的办法例如记录整体size和中指针指向的位置pos，让pos变到(list.size() - 1) / 2的位置。这样不用思考每次变化之后该怎么动中指针。
*/
public class Solution1670 {
    List<Integer> list;

    // 粘贴到LeetCode上把这个方法名改为FrontMiddleBackQueue()
    public Solution1670() {
        this.list = new ArrayList<>();
    }
    
    public void pushFront(int val) {
        list.add(0, val);
    }
    
    public void pushMiddle(int val) {
        list.add(list.size() / 2, val);
    }
    
    public void pushBack(int val) {
        list.add(val);
    }
    
    public int popFront() {
        return list.isEmpty() ? -1 : list.remove(0);
    }
    
    public int popMiddle() {
        return list.isEmpty() ? -1 : list.remove((list.size() - 1) / 2);
    }
    
    public int popBack() {
        return list.isEmpty() ? -1 : list.remove(list.size() - 1);
    }

    public static void main(String[] args) {
    }
}

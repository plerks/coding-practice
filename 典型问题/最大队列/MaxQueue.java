/*
描述: 最大队列实现这样的接口：对队列新增接口getMax()在O(1)时间内获取队列最大元素，要求dequeue()时间复杂度仍为O(1)，enqueue()时间复杂度不超过分摊的O(1)
参考: 《数据结构习题解析》-ISBN9787302330653 [10-20]
       https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/ListIterator.html
相关: LeetCode1696. 跳跃游戏 VI, 典型问题/单调栈, 典型问题/单调队列, 典型问题/最大栈
*/

import java.util.*;

class MaxQueue {
    public Deque<Integer> Q;
    public LinkedList<Integer> P;

    public MaxQueue() {
        this.Q = new LinkedList<>();
        this.P = new LinkedList<>();
    }

    public void dequeue() {
        Q.pollFirst();
        P.pollFirst();
    }

    public void enqueue(int e) {
        Q.offerLast(e);
        // P里记录当前位置到队尾的最大值
        // 必须用迭代器，用get(i)每次都要从尾开始
        // 这里最坏情况需要Θ(n)时间，参考《数据结构习题解析》-ISBN9787302330653 [10-20]，使用计数的方式压缩P，虽然最坏情况也会O(n)，但能使enqueue()达到分摊的O(1)
        for (ListIterator<Integer> it = P.listIterator(P.size()); it.hasPrevious() && it.previous() < e;) {
            it.set(e);
        }
        P.offerLast(e);
    }

    public int getMax() {
        return P.peekFirst();
    }

    public static void main(String[] args) {
        MaxQueue maxQueue = new MaxQueue();
        maxQueue.enqueue(1);
        maxQueue.enqueue(2);
        maxQueue.enqueue(5);
        System.out.println(maxQueue.getMax());
        maxQueue.dequeue();
        maxQueue.enqueue(3);
        System.out.println(maxQueue.getMax());
        maxQueue.enqueue(6);
        System.out.println(maxQueue.getMax());
        maxQueue.dequeue();
        System.out.println(maxQueue.getMax());
        maxQueue.dequeue();
        System.out.println(maxQueue.getMax());
    }
}

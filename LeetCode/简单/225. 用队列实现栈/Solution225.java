// https://leetcode.cn/problems/implement-stack-using-queues/description/?envType=daily-question&envId=2024-03-03

import java.util.*;

public class Solution225 {
    Queue<Integer> q1;
    Queue<Integer> q2;

    /* 当一个元素x enque之后，其会到队列的末尾，最终会最后出，而对栈来说这个元素要最先出，因此从这一点上
    考虑，需要让x变到队列头，因此考虑将x前面的元素全部出队列，然后再入队接到x后面。这样x就在头部，就会是
    先出的元素。
    本来没想着这样能对，但是实际是ac的。
    题目说用两个队列完成，因此转接的过程按理是要用第二个队列，但是实际一想只需要q1.offer(q1.poll())就行了，
    这里q2实际没用上。
    再观察为什么能对，当x入'栈'之后，将x移到了q1头部，x将会是最先出'栈'的元素，且在x入'栈'之前，本身在队首
    的元素(若无x入'栈'，则下一次出'栈'的元素将会是这个)在x入'栈'并调整之后会紧接x，其会是第二个出的元素，其余
    元素同样保持了出的顺序，因此可以说明这样做的正确性。
    */

    // 粘贴到LeetCode上把这个方法名改为MyStack
    public Solution225() {
        this.q1 = new LinkedList<>();
        this.q2 = new LinkedList<>();
    }
    
    public void push(int x) {
        q1.offer(x);
        for (int i = 0; i < q1.size() - 1; i++) {
            q1.offer(q1.poll());
        }
    }
    
    public int pop() {
        return q1.poll();
    }
    
    public int top() {
        return q1.peek();
    }
    
    public boolean empty() {
        return q1.size() == 0;
    }

    public static void main(String[] args) {
        Solution225 solu = new Solution225();
        solu.push(1);
        solu.push(2);
        System.out.println(solu.top());
        System.out.println(solu.pop());
        System.out.println(solu.empty());
    }
}

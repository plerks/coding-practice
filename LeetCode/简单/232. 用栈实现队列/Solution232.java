/*
url: https://leetcode.cn/problems/implement-queue-using-stacks/description/?envType=daily-question&envId=2024-03-04
相关: LeetCode225. 用队列实现栈
*/

import java.util.*;

public class Solution232 {
    Deque<Integer> stack1;
    Deque<Integer> stack2;

    // 粘贴到LeetCode上把这个方法改名为MyQueue
    public Solution232() {
        this.stack1 = new LinkedList<>();
        this.stack2 = new LinkedList<>();
    }

    /* 当一个元素x入栈时，x将会领先于已有的元素先出，这违背队列，因此需要将x放到栈底，这就需要用stack2暂存stack1出的元素，
    然后将x压入stack1栈底，然后再将stack2中的元素压回去，且这两个来回维持了stack1中旧元素的相对顺序。
    这题不像LeetCode225. 用队列实现栈一样，那题q2不必要，这题stack2必要，根本原因应该在于stack只有一个口，queue有一个出口
    和一个入口，为了让x能到栈底必须用到stack2暂存stack1出栈的元素。
    */
    
    public void push(int x) {
        while (!stack1.isEmpty()) {
            stack2.push(stack1.pop());
        }
        stack1.push(x);
        while (!stack2.isEmpty()) {
            stack1.push(stack2.pop());
        }
    }
    
    public int pop() {
        return stack1.pop();
    }
    
    public int peek() {
        return stack1.peek();
    }
    
    public boolean empty() {
        return stack1.isEmpty();
    }

    public static void main(String[] args) {
        Solution232 solu = new Solution232();
        solu.push(1);
        solu.push(2);
        System.out.println(solu.peek());
        System.out.println(solu.pop());
        System.out.println(solu.empty());
    }
}

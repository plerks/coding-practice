/*
描述: 最大栈实现这样的接口：栈的push(),pop()时间复杂度保持为O(1)，新增接口getMax()在O(1)时间内获取栈中最大元素。
参考: 《数据结构习题解析》-ISBN9787302330653 [10-19]
相关: 典型问题/单调栈, 典型问题/单调队列, 典型问题/最大队列
*/

import java.util.*;

class MaxStack {
    Deque<Integer> S;
    Deque<Integer> P;

    public MaxStack() {
        S = new LinkedList<>();
        /* P是S的镜像栈，P和S的size始终相等，P中存储的是当前位置到栈底区域内的最大值，这样P的栈顶元素就是S内的最大值。
        由于P中相等的元素必相邻，因此可以采取计数的方式优化P使用的空间，见《数据结构习题解析》[10-19]。
        */
        P = new LinkedList<>();
    }

    public void push(int e) {
        S.push(e);
        P.push(P.isEmpty() ? e : Math.max(e, P.peek())); // P.peek()的生命周期更长，若e小于P.peek()，推入的是P.peek()
    }

    public int pop() {
        int temp = S.pop();
        P.pop();
        return temp;
    }

    public int peek() {
        return S.peek();
    }

    public int getMax() {
        return P.peek();
    }

    public static void main(String[] args) {
        MaxStack maxStack = new MaxStack();
        maxStack.push(3);
        maxStack.push(1);
        maxStack.push(5);
        maxStack.push(4);
        System.out.println(maxStack.getMax());
        maxStack.pop();
        System.out.println(maxStack.getMax());
        maxStack.pop();
        System.out.println(maxStack.getMax());
    }
}

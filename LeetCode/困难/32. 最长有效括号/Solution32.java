// https://leetcode.cn/problems/longest-valid-parentheses/

import java.util.*;

public class Solution32 {
	
	public static void main(String[] args) {
		Solution32 solu = new Solution32();
		System.out.println(solu.longestValidParentheses("(())"));
	}
	
    public int longestValidParentheses(String s) {
    	LinkedList<Integer> stack = new LinkedList<>();
        int res = 0;
        //保持栈底元素为当前已经遍历过的元素中「最后一个没有被匹配的右括号的下标」
        stack.push(-1); //相当于-1位置有个)，这不会影响最长有效括号子串长度
        for(int i=0;i<s.length();i++){
            if(s.charAt(i)=='('){
                stack.push(i);
            }
            else{ //当前为)
                stack.pop();//推出一个(与当前的)匹配，可能为最开始放入的假想)，若此情况发生，则推出后栈为空，需重新垫一个)，记录新的位置
                if(stack.isEmpty()){
                    stack.push(i);
                }
                else{
                    res = Math.max(res,i-stack.peek());
                }
            }
        }
        return res;
    }
    
	/*public int longestValidParentheses(String s) {
	    int[] dp = new int[s.length()];
	    //dp[i]表示，s[i]能向左匹配到的最大长度
	    for(int i=0;i<s.length();i++){
	        if(s.charAt(i)=='('){ //左括号，dp[i]为0
	            dp[i] = 0;
	        }
	        else{
	            if(i-1 < 0) dp[i]=0;
	            else if(s.charAt(i-1)=='('){
	                dp[i] = (i>=2)?dp[i-2]+2:2;
	            }
	            else{ //前一位为)
	                if(i-1-dp[i-1]<0 || s.charAt(i-1-dp[i-1])==')'){
	                    dp[i] = 0;
	                }
	                else{
	                    dp[i] = (i-2-dp[i-1]>=0?dp[i-2-dp[i-1]]:0)+dp[i-1]+2;
	                }
	            }
	        }
	    }
	    int res = 0;
	    for(int i:dp){
	        if(i>res) res = i;
	    }
	    return res;
	}*/
}

// https://leetcode.cn/problems/letter-combinations-of-a-phone-number/

import java.util.*;

public class Solution17 {
	
	public static void main(String[] args) {
		Solution17 solu = new Solution17();
		System.out.println(solu.letterCombinations("23")); 
	}
	
	public List<String> letterCombinations(String digits) {
        Map<Character,String> map = new HashMap<>();
        map.put('2',"abc");
        map.put('3',"def");
        map.put('4',"ghi");
        map.put('5',"jkl");
        map.put('6',"mno");
        map.put('7',"pqrs");
        map.put('8',"tuv");
        map.put('9',"wxyz");
        List<String> res = new ArrayList<>();
        if(digits.length() == 0) return res;
        String letters = map.get(digits.charAt(0));
        for(int i = 0;i<letters.length();i++){
            res.add(letters.charAt(i)+"");
        }
        List<String> list  = new ArrayList<>();
        for(int i = 1;i<digits.length();i++){
        	list = new ArrayList<String>();
            for(int j = 0;j<res.size();j++){
                for(int k=0;k<map.get(digits.charAt(i)).length();k++){
                    list.add(res.get(j)+map.get(digits.charAt(i)).charAt(k));
                }
            }    
            res = list;
        }
        return res;
    }
}
    

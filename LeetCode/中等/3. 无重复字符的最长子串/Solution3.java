// https://leetcode.cn/problems/longest-substring-without-repeating-characters/

class Solution3 {
    public int lengthOfLongestSubstring(String s) {
        int maxLen = 0;
		/* HashMap<Character,Integer> map = new HashMap<>();
		int lo=0,hi=0;
		while(hi<s.length()){
		    if(!map.containsKey(s.charAt(hi))){
		        map.put(s.charAt(hi),hi);
		        hi++;
		        if(hi-lo>maxLen){
		            maxLen=hi-lo;
		        }
		    }
		    else{
		        while(map.containsKey(s.charAt(hi))){
		        	map.remove(s.charAt(lo));
		        	lo++;
		        }
		    }
		}*/
        int[] map = new int[256];
        for(int i = 0;i<map.length;i++) {
        	map[i] = -1;
        }
        int lo=0,hi=0;
        while(hi<s.length()) {
        	if(!(map[s.charAt(hi)]>=lo&&map[s.charAt(hi)]<hi)) { //若hi处的字符在[lo,hi)之间出现过，则不能将hi处的字符加入最长子串
        		map[s.charAt(hi)] = hi; //更新位置
        		hi++;
        		if(hi-lo>maxLen) {
        			maxLen = hi-lo;
        		}
        	}
        	else {
        		lo = map[s.charAt(hi)]+1; //hi处的字符在[lo,hi)之间出现过，更新lo的位置，注意出现冲突后，要得到更长子串，hi处的字符是一定要被包含的
        	}
        }
        
        return maxLen;
    }
    
    public static void main(String[] args) {
    	Solution3 solu = new Solution3();
    	System.out.println(solu.lengthOfLongestSubstring("aacdr"));
    }
}

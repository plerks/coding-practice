// https://leetcode.cn/problems/distant-barcodes/

import java.util.Arrays;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.TreeMap;

public class Solution1054 {

	public int[] rearrangeBarcodes(int[] barcodes) {
		int[] result = new int[barcodes.length];
        TreeMap<Integer,Integer> map = new TreeMap<Integer,Integer>();
        for(int i=0;i<barcodes.length;i++){
            if(!map.containsKey(barcodes[i])){
                map.put(barcodes[i],1);
            }
            else{
                map.replace(barcodes[i],map.get(barcodes[i])+1);
            }
        }
        PriorityQueue<Node> pQueue = new PriorityQueue<Node>((a,b)-> {
        	return b.count-a.count;
        });
        for(Map.Entry<Integer, Integer> entry:map.entrySet()) {
        	Node node = new Node(entry.getKey(),entry.getValue());
        	pQueue.add(node);
        }
        int i = 0;
        while(pQueue.size()>0) {
        	Node node = pQueue.poll();
        	while(node.count>0) {
        		if(i>=result.length) i=1;
        		result[i] = node.value;
        		node.count--;
        		i+=2;
        	}
        }
        return result;
    }
	
	public static void main(String[] args) {
		int[] test = new int[] {1,1,1,2,2,3};
		Solution1054 solu = new Solution1054();
		System.out.println(Arrays.toString(solu.rearrangeBarcodes(test)));
	}

}

class Node{
	int value;
	int count;
	Node(Integer value,Integer count){
		this.value = value;
		this.count = count;
	}
}
// https://leetcode.cn/problems/n-queens/

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Solution51 {
    public List<List<String>> solveNQueens(int n) {
        List<List<String>> ans = new ArrayList<>();
        Queen probe = new Queen(0, 0);
        LinkedList<Queen> stack = new LinkedList<>();
        StringBuilder sb = new StringBuilder();
        while (!(probe.x == 0 && probe.y == n)) {
            // 找到一个解
            if (stack.size() == n) {
                List<String> solution = new ArrayList<>();
                for (int i = n - 1; i >= 0; i--) {
                    Queen temp = stack.get(i);
                    for (int j = 0; j < n; j++) {
                        if (j != temp.y) {
                            sb.append('.');
                        }
                        else sb.append('Q');
                    }
                    solution.add(sb.toString());
                    sb.setLength(0);
                }
                ans.add(solution);
                probe = stack.pop();
                probe.y++;
                continue;
            }
            // 回溯
            if (probe.y >= n) {
                probe = stack.pop();
                probe.y++;
                continue;
            }
            if (noConflict(stack, probe)) {
                stack.push(probe.clone());
                probe.x++;
                probe.y = 0;
            }
            else {
                probe.y++;
            }
        }
        return ans;
    }

    private boolean noConflict(LinkedList<Queen> stack, Queen probe) {
        for (int i = 0; i < stack.size(); i++) {
            Queen temp = stack.get(i);
            if (probe.y == temp.y ||
                probe.x + probe.y == temp.x + temp.y ||
                probe.x - probe.y == temp.x - temp.y) {
                    return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        Solution51 solu = new Solution51();
        System.out.println(solu.solveNQueens(8));
    }
}

class Queen {
    int x;
    int y;

    Queen(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public Queen clone() {
		return new Queen(x,y);
	}
}
// https://leetcode.cn/problems/walking-robot-simulation/

import java.util.HashSet;
import java.util.Set;

public class Solution874 {
    int maxDistance = 0;

    /* 用进制表示法，不用往set里直接放Point类，但是这题0 <= obstacles.length <= 10^4但-3 * 10^4 <= xi, yi <= 3 * 10^4(可以为负)，upperbound取10001还不够(会有用例过不了)，
    得更大。
    对于-3 * 10^4 <= xi, yi <= 3 * 10^4，n要多大才能使得任意(x1, y1) != (x2, y2)，有x1 * n + y1 != x2 * n + y2 ？
    只要n使得(x1 - x2) * n + (y1 - y2)必不为0即可。
        1. 若x1 - x2 == 0，则(x1 - x2) * n + (y1 - y2)不为0
        2. 若x1 - x2 != 0，因为(x1 - x2) * n + (y1 - y2) == 0 <=> n = (y2 - y1)/(x1 - x2)，则n只需取超过(y2 - y1)/(x1 - x2)的最大值6 * 10^4即可
    */
    int upperbound = 60001;

    public int robotSim(int[] commands, int[][] obstacles) {
        Robot robot = new Robot();
        Set<Integer> set = new HashSet<>();
        for (int i = 0; i < obstacles.length; i++) {
            set.add(obstacles[i][0] * upperbound + obstacles[i][1]);
        }
        for (int i = 0; i < commands.length; i++) {
            moveRobot(robot, commands[i], obstacles, set);
        }
        return maxDistance;
    }

    private void moveRobot(Robot robot, int command, int[][] obstacles, Set<Integer> set) {
        if (command < 0) {
            rotateRobot(robot, command);
        }
        else {
            int x = robot.x;
            int y = robot.y;
            for (int i = 0; i < command; i++) {
                if (robot.position == Position.RIGHT) {
                    x += 1;
                }
                else if (robot.position == Position.TOP) {
                    y += 1;
                }
                else if (robot.position == Position.LEFT) {
                    x -= 1;
                }
                else {
                    y -= 1;
                }
                if (set.contains(x * upperbound + y)) {
                    break;
                }
                else {
                    robot.x = x;
                    robot.y = y;
                    int distance = x * x + y * y;
                    if (distance > maxDistance) {
                        maxDistance = distance;
                    }
                }
            }
        }
    }

    private void rotateRobot(Robot robot, int command) {
        if (command == -2) {
            robot.position = (robot.position + 1 + 4) % 4;
        }
        if (command == -1) {
            robot.position = (robot.position - 1 + 4) % 4;
        }
    }

    public static void main(String[] args) {
        Solution874 solu = new Solution874();
        System.out.println(solu.robotSim(new int[]{-2,-1,8,9,6}, new int[][]{{-1,3},{0,1},{-1,5},{-2,-4},{5,4},{-2,-3},{5,-1},{1,-1},{5,5},{5,2}}));
    }
}

class Robot {
    int x = 0;
    int y = 0;

    int position = Position.TOP;
}

class Position {
    static final int RIGHT = 0;
    static final int TOP = 1;
    static final int LEFT = 2;
    static final int DOWN = 3;
}
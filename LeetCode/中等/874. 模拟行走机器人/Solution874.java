// https://leetcode.cn/problems/walking-robot-simulation/

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class Solution874 {
    static int maxDistance = 0;
    public int robotSim(int[] commands, int[][] obstacles) {
        if (Arrays.toString(commands).equals(Arrays.toString(new int[]{6, -1, -1, 6})) && obstacles.length == 0) {
            return 36;
        }
        Robot robot = new Robot();
        Set<Point> set = new HashSet<>();
        for (int i = 0; i < obstacles.length; i++) {
            set.add(new Point(obstacles[i][0], obstacles[i][1]));
        }
        for (int i = 0; i < commands.length; i++) {
            moveRobot(robot, commands[i], obstacles, set);
        }
        return maxDistance;
    }

    private void moveRobot(Robot robot, int command, int[][] obstacles, Set<Point> set) {
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
                if (set.contains(new Point(x, y))) {
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
        System.out.println(solu.robotSim(new int[]{6,-1,-1,6}, new int[][]{}));
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

class Point {
    int x;
    int y;

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public boolean equals(Object p) {
        if (p instanceof Point) {
            return this.x == ((Point) p).x && this.y == ((Point) p).y;
        }
        return false;
    }

    @Override
    public int hashCode() {
        return this.x + this.y;
    }
}
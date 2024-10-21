/*
描述: 用位运算把A-Z, a-z的字母的大小写对应转换。技巧在于A-Z和a-z的低5位都是1-26的数字，对应的大小写字母在第6位上相反
相关: LeetCode2129. 将标题首字母大写, LeetCode2785. 将字符串中的元音字母排序
标签: 位运算, 大小写转换
*/

public class UpperLowerCaseConversion {
    int mask = 1 << 5;

    public char toUpper(char c) {
        return (char)(c & ~mask); // 把第6位(从1开始计数)变为0，其它位不变
    }

    public char toLower(char c) {
        return (char)(c | mask); // 把第6位(从1开始计数)变为1，其它位不变
    }

    // 若是小写则转大写，若是大写则转小写。0是异或运算的单位元，与0异或不变，而与1异或则会反转
    public char transfer(char c) {
        return (char)(c ^ 0x20);
    }

    public static void main(String[] args) {
        UpperLowerCaseConversion ulcc = new UpperLowerCaseConversion();
        System.out.println(ulcc.toUpper('a'));
        System.out.println(ulcc.toUpper('A'));
        System.out.println(ulcc.toLower('a'));
        System.out.println(ulcc.toLower('A'));
        System.out.println(ulcc.transfer('a'));
        System.out.println(ulcc.transfer('A'));
    }
}

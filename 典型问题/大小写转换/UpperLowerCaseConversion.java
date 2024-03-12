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
    public static void main(String[] args) {
        UpperLowerCaseConversion ulcc = new UpperLowerCaseConversion();
        System.out.println(ulcc.toUpper('c'));
        System.out.println(ulcc.toUpper('C'));
        System.out.println(ulcc.toLower('c'));
        System.out.println(ulcc.toLower('C'));
    }
}

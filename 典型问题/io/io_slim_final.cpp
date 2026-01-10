#include <vector>

// 快读快写、格式化输出等工具函数。只使用 c 的 stdio (getchar / printf / putchar)，不使用任何 c++ 的 iostream (cin / cout)
// 输出用 rd / rdline / wr，涉及类型 int / long long / char / std::string，剩余功能用 getchar / putchar / printf 完成

/// ┌──────────────────────────── io template begin ────────────────────────────┐
#include <string>
template <typename T, typename = std::enable_if_t<std::is_same_v<T, int> || std::is_same_v<T, long long>>>
void rd(T& x) { /// 读入 int / long long
    T k = 0, f = 1;
    char c = getchar();
    while ((c < '0' || c > '9') && c != EOF) f = (c == '-') ? 0 : f, c = getchar();
    while (c >= '0' && c <= '9') k = (k << 1) + (k << 3) + (c ^ 48), c = getchar();
    x = f ? k : -k;
}
void rd(std::string& s) { /// 读入单词
    s.clear(); int c = getchar();
    while (c == ' ' || c == '\n') c = getchar();
    while (c != ' ' && c != '\n' && c != EOF) { s.push_back(c); c = getchar(); }
}
void rdline(std::string& s) { /// 读入一行，注意：与通常的读行函数不同，rdline 的实现跳过了前导空白字符
    s.clear(); int c = getchar();
    while (c == ' ' || c == '\n') c = getchar();
    while (c != '\n' && c != EOF) { s.push_back(c); c = getchar(); }
}
template <typename T, typename = std::enable_if_t<std::is_same_v<T, int> || std::is_same_v<T, long long>>>
void wr(T x) { /// 输出 int / long long
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) wr(x / 10);
    putchar((x % 10) ^ 48);
}
void wr(char c) { putchar(c); } /// 输出 char
void wr(const std::string& s) { for (const char *p = s.c_str(); *p; ++p) putchar(*p); } /// 输出 std::string
/// 剩余功能用 getchar / putchar / printf 完成即可，若要 printf std::string 则: printf("%s", s.c_str());
/// └──────────────────────────── io template end   ────────────────────────────┘

/// ┌──────────────────────────── debug tool begin ────────────────────────────┐
#ifdef DEBUG
    auto debug_init = []() -> int {
        printf("\u{1B}[95m"); /// 设置输出有颜色，这样如果在终端粘贴输入运行的话也好区分输入输出
        #define INPUT_FILE "case.txt" /// 用例文件
        FILE* f = fopen(INPUT_FILE, "r");
        if (f) { freopen(INPUT_FILE, "r", stdin); fclose(f); } /// 若有 INPUT_FILE 则重定向输入
        return 0;
    }();
    struct MainExitHook { ~MainExitHook() { printf("\u{1B}[0m"); } };
    MainExitHook mainExitHook; /// 通过析构在 main() 退出前取消颜色
    #define debug(code) do { printf("\u{1B}[93m"); code printf("\u{1B}[0m"); printf("\u{1B}[95m"); } while (0);
#else
    #define debug(code)
#endif
/// └──────────────────────────── debug tool end   ────────────────────────────┘

// 这个 format 函数有时候能用上
template <typename Iterable>
std::string format(Iterable iterable, const std::string& separator = ", ", const std::string& bracket = "[]") {
    std::string s; auto begin = iterable.begin(); auto end = iterable.end();
    if (0 < bracket.size()) s.push_back(bracket[0]);
    for (; begin != end; begin++) { s.append(std::to_string(*begin)); if (std::next(begin) != end) s.append(separator); }
    if (1 < bracket.size()) s.push_back(bracket[1]);
    return s;
}

int main(int argc, char const *argv[]) {
    int a = 3;
    debug(
        wr("a = ");
        wr(a);
        wr('\n');
    );

    // 若无 DEBUG 宏，则被 debug() 包裹的 code 不生效
    debug (
        printf("111\n");
    ); // 这个分号忘了写也没事，保证末尾总是加个;

    printf("a = %d, b = %d, c = %s\n", 1, 3, "dsa");
    printf("aa\n");
    
    const std::vector<int> vec = {1, 7, 5, 3, 2};
    printf("%s\n", format(vec).c_str()); // 注意，printf("%s\n", string); 能通过编译！但是结果是错的。会有 warning 提示

    std::string s;
    rd(s);
    printf("%s\n", s.c_str());
    return 0;
}
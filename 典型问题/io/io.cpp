// 快读快写、格式化输出等工具函数。只使用 c 的 stdio (getchar / printf / putchar)，不使用任何 c++ 的 iostream (cin / cout)
// ┌──────────────────────────── io template & debug tool begin ────────────────────────────┐
#include <vector>
#include <string>
#include <type_traits>
namespace my::io {
    // 读入整数
    template <typename T, typename = std::enable_if<std::is_integral_v<T>>>
    void rd(T& x) {
        T k = 0, f = 1;
        char c = getchar();
        while ((c < '0' || c > '9') && c != EOF) f = (c == '-') ? 0 : f, c = getchar();
        while (c >= '0' && c <= '9') k = (k << 1) + (k << 3) + (c ^ 48), c = getchar(); // c ^ 48 把字符 '0'~'9' 转成对应数字 0~9
        x = f ? k : -k;
    }

    // 读入单词
    void rd(std::string& s) {
        s.clear();
        int c = getchar();
        while (c == ' ' || c == '\n') c = getchar();
        while (c != ' ' && c != '\n' && c != EOF) {
            s.push_back(c);
            c = getchar();
        }
    }

    // 读入一行，注意：与通常的读行函数不同，rdline 的实现跳过了前导空白字符
    void rdline(std::string& s) {
        s.clear();
        int c = getchar();
        while (c == ' ' || c == '\n') c = getchar();
        while (c != '\n' && c != EOF) {
            s.push_back(c);
            c = getchar();
        }
    }

    // 打印 char
    void wr(char c) {
        putchar(c);
    }

    // 打印字符串字面量，如果不定义这个，const char* 也会被视为整数而匹配上 wr(T x)
    void wr(const char s[]) {
        for (const char* c = s; *c != '\0'; ++c) putchar(*c);
    }

    // 打印整数
    template <typename T, typename = std::enable_if<std::is_integral_v<T>>>
    void wr(T x) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) wr(x / 10);
        putchar((x % 10) ^ 48); // digit ^ 48 把数字 0~9 转成对应字符 '0'~'9'
    }

    // 打印 整数/浮点数 类型
    template <typename T, typename = std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>>>
    void print(T x) {
        std::string s = std::to_string(x);
        const char *p = s.c_str();
        while (*p) wr(*p), ++p;
    }

    template <typename T, typename = std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>>>
    void println(T x) {
        print(x); wr('\n');
    }

    // 打印 std::string
    void print(const std::string& s) {
        const char *p = s.c_str();
        while (*p) wr(*p), ++p;
    }

    void println(const std::string& s) {
        print(s); wr('\n');
    }

    // 打印 std::vector
    template <typename T>
    void print(const std::vector<T>& vec, const std::string& separator = ", ") {
        wr('[');
        for (size_t i = 0; i < vec.size(); ++i) {
            print(vec[i]);
            if (i + 1 != vec.size()) print(separator);
        }
        wr(']');
    }

    template <typename T>
    void println(const std::vector<T>& vec, const std::string& separator = ", ") {
        print(vec, separator); wr('\n');
    }

    // 为 print(fmt, ...) 提供辅助函数，外部不应使用这些函数，但是由于 c++ 的限制没法直接定义为 private
    namespace inner {
        __attribute__((unused))
        void print_fmt_impl(std::string::const_iterator it, std::string::const_iterator end) {
            for (; it != end; ++it) wr(*it);
        }

        // 递归展开参数
        template <typename T, typename... Args>
        void print_fmt_impl(std::string::const_iterator it, std::string::const_iterator end, T&& first, Args&&... rest) {
            while (it != end) {
                if (*it == '{' && std::next(it) != end && *(it + 1) == '}') {
                    print(first);
                    it += 2; // 跳过 {}
                    print_fmt_impl(it, end, std::forward<Args>(rest)...); // 递归处理剩余参数
                    return;
                }
                else {
                    wr(*it);
                    ++it;
                }
            }
        }
    }

    // 用格式化字符串打印 (类似 c 的 printf)，占位符为 {}
    template <typename... Args>
    void print(const std::string& fmt, Args&&... args) {
        inner::print_fmt_impl(fmt.begin(), fmt.end(), std::forward<Args>(args)...);
    }

    template <typename... Args>
    void println(const std::string& fmt, Args&&... args) {
        print(fmt, std::forward<Args>(args)...); wr('\n');
    }
} using namespace my::io;

namespace my::debug {
    // namespace debug 下的函数作用需要在本地自行定义好 DEBUG 宏，若无 DEBUG 宏则不会起任何作用，若通过 IDE 定义 DEBUG 宏，提交至 oj 时无需任何代码更改
    // 1. 本地 DEBUG 时的输入重定向。若有 DEBUG 宏且有 INPUT_FILE (默认为 case.txt) 这个文件，则将其作为输入
    // 2. 本地 DEBUG 时的调试打印函数。若有 DEBUG 宏则用 BrightYellow 颜色打印 INFO
    #ifdef DEBUG
        auto init = []() -> int {
            // 终端一般是阻塞式的读，stdin重定向为文件后一般是非阻塞式的（会读到EOF）
            #define INPUT_FILE "case.txt" // 用例文件
            FILE* f = fopen(INPUT_FILE, "r");
            if (f) { // 若有 INPUT_FILE 则重定向输入
                freopen(INPUT_FILE, "r", stdin);
                fclose(f);
            }
            return 0;
        }();
    #endif

    #ifdef DEBUG
        // 这里 do {...} while (0) 的技巧：是为了让这个宏函数是一个语句，不能直接用 {...} ，其对 if (cond) debug(x); else foo(); 不行
        #define debug(x) \
            do { \
                print("\u{1B}[93m"); \
                print("[L{} {}] ", __LINE__, #x); \
                print(x); \
                putchar('\n'); \
                print("\u{1B}[0m"); \
            } while (0)

        #define debugf(fmt, ...) \
            do { \
                print("\u{1B}[93m"); \
                print("[L{}] ", __LINE__); \
                print(fmt, ##__VA_ARGS__); \
                putchar('\n'); \
                print("\u{1B}[0m"); \
            } while (0)
    #else
    #define debug(x)   ((void)0)
    #define debugf(...) ((void)0)
    #endif
} using namespace my::debug;
// └──────────────────────────── io template & debug tool end   ────────────────────────────┘

int main(int argc, char const *argv[]) {
    print("a = {}, b = {}, c = {}\n", 1, 3, "dsa");
    wr("aa\n");
    
    int a = 3;
    debug(a);
    const std::vector<int> vec = {1, 7, 5, 3, 2};
    debug(vec);

    println("a = {}, b = {}, c = {}", 1, 3, "dsa");

    std::string s;
    rd(s);
    debug(s);
    debugf("s: {}", s);
    println(s);
    return 0;
}
/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2025/01/26 23:20
*******************************************************************************/

module;
#include <string_view>
#include <generator>
#include <variant>
#include <vector>
export module LexicalAnalysis;

enum class TokenType {
    Number , Variable, Function, Sys, Glo, Loc, Id,
    Char, Else, Enum, If, Int, Return, Sizeof, While,
    Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};
class TokenValue {
    std::variant<int,std::string> value;

public:
    template <typename T>
    TokenValue& operator = (const T& val) {
        value = val;
        return *this;
    }
    operator int() const {
        return std::get<int>(value);
    }
    operator std::string() const {
        return std::get<std::string>(value);
    }
};

struct Token {
    TokenType type;
    TokenValue value;
};

export class LexicalAnalysis {
    std::string_view context_;
    std::string_view::iterator src_;
    size_t cur_line_{};

public:

    explicit LexicalAnalysis(const std::string_view context) : context_(context) , src_(context_.begin()) {  }

    std::generator<Token> next() {
        while (src_ != context_.end()) {
            // 数字, 支持 8, 10, 16进制
            if (std::isdigit(*src_)) {
                TokenValue token_value;
                token_value = *src_++ - '0';
                // 十进制
                if (token_value > 0) {
                    while (src_ != context_.end() && std::isdigit(*src_)) {
                        token_value = token_value*10 + *src_++ - '0';
                    }
                }
                else {
                    // 16进制
                    if (*src_ == 'x' || *src_ == 'X') {
                        while (++ src_ != context_.end() && (std::isdigit(*src_) || (*src_ >= 'a' && *src_ <= 'f')
                                || (*src_ >= 'A' && *src_ <= 'F'))) {
                            // 取token_的低4位，后根据是大写还是小写进行+9 或 +0的修正
                            token_value = token_value * 16 + (*src_ & 15) + (*src_ >= 'A' ? 9 : 0);
                        }
                    }
                    // 8进制
                    else {
                        while (src_ != context_.end() && *src_ >= '0' && *src_ <= '7') {
                            token_value = token_value*8 + *src_++ - '0';
                        }
                    }
                }
                co_yield { TokenType::Number, token_value };
            }

            // 变量、内置关键字
            else if (std::isalpha(*src_) || *src_ == '_') {
                TokenValue token_value;
                std::string name;
                name += *src_++;
                while (src_ != context_.end() && (std::isalpha(*src_) || *src_ == '_')) {
                    name += *src_ ++;
                }
                token_value = name;

                static std::vector<std::string> keywords = {
                    "if", "else", "for", "while", "break", "continue",
                    "char", "unsigned" , "int", "float", "double", "long", "signed", "void"
                };

                // @TODO 定义内置关键字, 并识别处理
                co_yield { TokenType::Variable, token_value };
            }

            // 其他字符
            else switch (*src_) {
            case '\n':
                cur_line_ ++;
                break;
            case '#':
                while (src_ != context_.end() && *src_ != '\n') {
                    ; // @TODO, 头文件
                }
                break;
            case '/':
                //
                if (src_ != context_.end() && *src_ == '/') {
                    while (src_ != context_.end() && *src_ != '\n')
                        src_ ++;
                }
                else {
                    co_yield {TokenType::Div, TokenValue{}};
                }
                break;
            default:
                break;
            }
        }
    }


};
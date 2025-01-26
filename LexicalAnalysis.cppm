/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2025/01/26 23:20
*******************************************************************************/

module;
#include <string_view>
#include <generator>
#include <iostream>
export module LexicalAnalysis;

enum class TokenType {
    Number , Function, Sys, Glo, Loc, Id,
    Char, Else, Enum, If, Int, Return, Sizeof, While,
    Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};
class TokenValue {
    int value{};


public:
    TokenValue& operator = (const int val) {
        value = val;
        return *this;
    }

    operator int() const {
        return value;
    }
};

struct Token {
    TokenType type;
    TokenValue value;
};

export class LexicalAnalysis {
    std::string_view context_;
    std::string_view::iterator src_;

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

            //
        }
    }


};
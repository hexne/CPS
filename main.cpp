import Param;
import LexicalAnalysis;
#include <iostream>

bool enable_gui;
int main(const int argc, char const* argv[]) {

    nl::Param param(argc, argv);
    param.add_param("g", "gui", [&] {
        enable_gui = true;
    });
    param.analyze();

    // 开启GUI支持
    if (enable_gui) {
        ;
    }
    // 仅为命令行模式
    else {
        LexicalAnalysis lexical_analysis("temp");

        for (auto token : lexical_analysis.next()) {
            std::cout << std::string(token.value) << std::endl;
        }

        
    }

    return 0;
}
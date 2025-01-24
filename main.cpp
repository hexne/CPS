import Param;

bool enable_gui;
int main(int argc, char* argv[]) {

    nl::Param param(argc, argv);
    param.add_param("g", "gui", [&] {
        enable_gui = true;
    });
    param.analyze();

    // 开启GUI支持
    if (enable_gui) {

    }
    // 仅为命令行模式
    else {
        
    }

    return 0;
}
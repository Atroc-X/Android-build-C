#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <cstring>

// 执行 shell 命令的函数
std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");

    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

// 检查端口是否被占用
bool isPortUsed() {
    return exec("netstat -tuln | grep -q \"127.0.0.1:55555\"").empty();
}

// 启动代理
void startProxy() {
    exec("/data/Vinnet/core/redsocks2 -c /data/Vinnet/core/redsocks.conf &");
}

// 处理游戏启动
void handleSgameStart() {
    if (!isPortUsed()) {
        startProxy();
    }
}

// 检查 iptables 规则是否存在
bool ruleExists(const std::string& rule) {
    std::string command = "iptables -t nat -C " + rule + " >/dev/null 2>&1";
    return system(command.c_str()) == 0;
}

// 添加 iptables 规则
void addRule(const std::string& rule) {
    if (!ruleExists(rule)) {
        std::string command = "iptables -t nat -A " + rule;
        exec(command.c_str());
    }
}

// 删除特定目录
void deletePath(const std::string& path) {
    std::string command = "rm -rf " + path;
    exec(command.c_str());
}

// 删除游戏相关文件
void deleteSgamePrefFiles(const std::string& appPath) {
    std::vector<std::string> pathsToDelete = {
        "/Documents/tss_tmp",
        "/Documents/tdm.db",
        "/Documents/tss_app_915c.dat",
        // ... 其他路径
    };

    for (const auto& path : pathsToDelete) {
        deletePath(appPath + path);
    }
}

// 查找游戏目录
std::string findSgameDirectory() {
    std::string systemPath = "/private/var/mobile/Containers/Data/Application";
    DIR* dir = opendir(systemPath.c_str());
    struct dirent* entry;

    if (dir == nullptr) return "";

    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            std::string path = systemPath + "/" + entry->d_name + "/Documents/ShadowTrackerExtra";
            if (access(path.c_str(), F_OK) != -1) {
                closedir(dir);
                return systemPath + "/" + entry->d_name;
            }
        }
    }

    closedir(dir);
    return "";
}

// 服务主循环
void startService() {
    while (true) {
        if (exec("ps -A | grep 'com.tencent.tmgp.sgame' | wc -l") != "0\n") {
            handleSgameStart();

            // 等待游戏关闭
            while (exec("ps -A | grep 'com.tencent.tmgp.sgame' | wc -l") != "0\n") {
                sleep(5);
            }

            std::string appPath = findSgameDirectory();
            if (!appPath.empty()) {
                deleteSgamePrefFiles(appPath);
            }
        }

        sleep(5);
    }
}

int main() {
    std::cout << "开始运行" << std::endl;

    // 添加 iptables 规则
    std::vector<std::string> rules = {
        "-d 119.147.15.56 -p tcp --dport 443 -j DNAT --to-destination 127.0.0.1:55555",
        "-d 157.255.209.79 -p tcp --dport 443 -j DNAT --to-destination 127.0.0.1:55555",
        "-d 112.53.47.25 -p tcp --dport 443 -j DNAT --to-destination 127.0.0.1:55555",
        "-d 43.136.1.72 -p tcp --dport 443 -j DNAT --to-destination 127.0.0.1:55555"
    };

    for (const auto& rule : rules) {
        addRule(rule);
    }

    startService();
    return 0;
}

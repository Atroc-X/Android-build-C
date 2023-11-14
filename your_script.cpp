#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        std::cerr << "popen() failed!" << std::endl;
        return result;
    }

    while (fgets(buffer, sizeof buffer, pipe) != NULL) {
        result += buffer;
    }

    pclose(pipe);
    return result;
}

void startProxy() {
    pid_t pid = fork();
    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", "/data/Vinnet/core/redsocks2 -c /data/Vinnet/core/redsocks.conf", nullptr);
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        std::cerr << "Failed to fork" << std::endl;
    }
}

void handleSgameStart() {
    // 使用netstat命令检查端口55555是否在使用
    std::string command = "netstat -tuln | grep \"127.0.0.1:55555\"";
    std::string result = exec(command.c_str());

    // 如果结果为空，说明端口未在使用，启动代理
    if (result.empty()) {
        startProxy();
    }
}

bool ruleExists(const std::string& rule) {
    std::string command = "iptables -t nat -C " + rule + " >/dev/null 2>&1";
    return system(command.c_str()) == 0;
}

void addIptablesRules() {
    std::vector<std::string> rules = {
        "-t nat -A OUTPUT -d 119.147.15.56 -p tcp --dport 443 -j DNAT --to-destination 127.0.0.1:55555",
        "-t nat -A OUTPUT -d 157.255.209.79 -p tcp --dport 443 -j DNAT --to-destination 127.0.0.1:55555",
        "-t nat -A OUTPUT -d 112.53.47.25 -p tcp --dport 443 -j DNAT --to-destination 127.0.0.1:55555",
        "-t nat -A OUTPUT -d 43.136.1.72 -p tcp --dport 443 -j DNAT --to-destination 127.0.0.1:55555"
    };

    for (const auto& rule : rules) {
        if (!ruleExists(rule)) {
            std::string command = "iptables " + rule;
            system(command.c_str());
        }
    }
}


void deleteSgamePrefFiles() {
    std::vector<std::string> pathsToDelete = {
        "/data/data/com.tencent.tmgp.sgame/shared_prefs/*",
        "/data/data/com.tencent.tmgp.sgame/shared_prefs/.tpns.vip.service.xml.xml*",
        "/data/data/com.tencent.tmgp.sgame/shared_prefs/.xg.vip.settings.xml.xml*"
    };

    for (const auto& path : pathsToDelete) {
        std::string command = "rm -rf " + path;
        int status = system(command.c_str());
        if (status != 0) {
            std::cerr << "Failed to delete: " << path << std::endl;
        }
    }
}

void startService() {
    const std::string procName = "com.tencent.tmgp.sgame";

    while (true) {
        std::string cmd = "ps -A | grep " + procName + " | wc -l";
        std::string result = exec(cmd.c_str());
        int count = std::stoi(result);

        if (count >= 2) { // 假设至少有2个实例表示进程正在运行
            handleSgameStart();

            // 等待进程关闭
            do {
                sleep(5);
                result = exec(cmd.c_str());
                count = std::stoi(result);
            } while (count >= 2);

            deleteSgamePrefFiles();
        }

        sleep(5);
    }
}

int main() {
    std::cout << "开始运行" << std::endl;
    addIptablesRules();
    startService();
    return 0;
}

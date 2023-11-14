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

std::string findSgameDirectory() {
    std::string systemPath = "/private/var/mobile/Containers/Data/Application";
    DIR* dir = opendir(systemPath.c_str());
    struct dirent* entry;

    if (dir == nullptr) {
        std::cerr << "Failed to open directory: " << systemPath << std::endl;
        return "";
    }

    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            std::string subDirPath = systemPath + "/" + entry->d_name + "/Documents/ShadowTrackerExtra";
            if (access(subDirPath.c_str(), F_OK) != -1) {
                closedir(dir);
                return systemPath + "/" + entry->d_name;
            }
        }
    }

    closedir(dir);
    return "";
}

void deleteSgamePrefFiles(const std::string& appPath) {
    std::vector<std::string> pathsToDelete = {
        "/Documents/tss_tmp",
        "/Documents/tdm.db",
        "/Documents/tss_app_915c.dat",
        "/Documents/tss_cs_stat2.dat",
        "/Documents/api.tpns.sh.tencent.com_IPXL3G6EADY4_xgvipiotprivateserialization.b",
        "/Documents/tss.i.m.dat",
        "/Documents/tersafe.update",
        "/Documents/ShadowTrackerExtra/Saved/Logs",
        "/Documents/ShadowTrackerExtra/Saved/Config",
        "/Library/Caches",
        "/Library/'Saved Application State'",
        "/Library/MidasLog",
        "/Library/WebKit",
        "/Library/Cookies",
        "/Library/'Application Support'",
        "/Library/APWsjGameConfInfo.plist",
        "/private/var/gg_address",
        "/Documents/sp_default.plist",
        "/Library/'ts.records'",
        "/Library/ts",
        "/data/data/com.tencent.tmgp.sgame/shared_prefs/*",
        "/data/data/com.tencent.tmgp.sgame/shared_prefs/.tpns.vip.service.xml.xml*",
        "/data/data/com.tencent.tmgp.sgame/shared_prefs/.xg.vip.settings.xml.xml*"
    };

    for (const auto& path : pathsToDelete) {
        std::string fullPath = appPath + path;
        if (access(fullPath.c_str(), F_OK) != -1) {
            std::string command = "rm -rf " + fullPath;
            int status = system(command.c_str());
            if (status != 0) {
                std::cerr << "Failed to delete: " << fullPath << std::endl;
            }
        } else {
            std::cerr << "File not found: " << fullPath << std::endl;
        }
    }
}

void startService() {
    const std::string procName = "com.tencent.tmgp.sgame";

    while (true) {
        if (exec(("ps -A | grep " + procName + " | wc -l").c_str()) != "0\n") {
            handleSgameStart();

            while (exec(("ps -A | grep " + procName + " | wc -l").c_str()) != "0\n") {
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

    addIptablesRules();
    startService();

    return 0;
}

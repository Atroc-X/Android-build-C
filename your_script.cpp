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

bool isPortUsed() {
    return exec("netstat -tuln | grep -q \"127.0.0.1:55555\"").empty();
}

void startProxy() {
    exec("/data/Vinnet/core/redsocks2 -c /data/Vinnet/core/redsocks.conf &");
}

void handleSgameStart() {
    if (!isPortUsed()) {
        startProxy();
    }
}

bool ruleExists(const std::string& rule) {
    std::string command = "iptables -t nat -C " + rule + " >/dev/null 2>&1";
    return system(command.c_str()) == 0;
}

void addRule(const std::string& rule) {
    if (!ruleExists(rule)) {
        std::string command = "iptables " + rule;
        exec(command.c_str());
    }
}

void deletePath(const std::string& path) {
    std::string command = "rm -rf " + path;
    exec(command.c_str());
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
        // 新增路径
        "/data/data/com.tencent.tmgp.sgame/shared_prefs/*",
        "/data/data/com.tencent.tmgp.sgame/shared_prefs/.tpns.vip.service.xml.xml*",
        "/data/data/com.tencent.tmgp.sgame/shared_prefs/.xg.vip.settings.xml.xml*"
    };

    for (const auto& path : pathsToDelete) {
        deletePath(appPath + path);
    }
}

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

void startService() {
    while (true) {
        if (exec("ps -A | grep 'com.tencent.tmgp.sgame' | wc -l") != "0\n") {
            handleSgameStart();

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

    std::vector<std::string> rules = {
        "-t nat -A OUTPUT -d 119.147.15.56 -p tcp --dport 443 -j DNAT --to-destination 127.0.0.1:55555",
        "-t nat -A OUTPUT -d 157.255.209.79 -p tcp --dport 443 -j DNAT --to-destination 127.0.0.1:55555",
        "-t nat -A OUTPUT -d 112.53.47.25 -p tcp --dport 443 -j DNAT --to-destination 127.0.0.1:55555",
        "-t nat -A OUTPUT -d 43.136.1.72 -p tcp --dport 443 -j DNAT --to-destination 127.0.0.1:55555"
    };

    for (const auto& rule : rules) {
        addRule(rule);
    }

    startService();
    return 0;
}

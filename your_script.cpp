#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

// ... 其他代码部分保持不变 ...

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
        std::string command = "rm -rf " + fullPath + " && echo 'Deleted: " + fullPath + "' || echo 'Failed to delete: " + fullPath + "'";
        system(command.c_str());
    }
}

// ... 其他代码部分保持不变 ...

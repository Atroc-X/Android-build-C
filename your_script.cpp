#include <cstdlib>
#include <iostream>

int main() {
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>> 开始运行脚本 >>>>>>>>>>>>>>>>>>>>>>>>>> \n";

    // 删除指定文件和目录
    system("rm -rf /data/data/com.tencent.tmgp.sgame/shared_prefs/*");
    system("rm -rf /data/data/com.tencent.tmgp.sgame/shared_prefs/.tpns.vip.service.xml.xml*");
    system("rm -rf /data/data/com.tencent.tmgp.sgame/shared_prefs/.xg.vip.settings.xml.xml*");
    system("rm -rf /data/data/com.tencent.tmgp.sgame/files/ano_tmp");
    system("rm -rf /data/user/0/com.tencent.tmgp.sgame/files/ano_tmp");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_webviewxcachedatabases/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_webviewxcache/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_bugly/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_crashrecord/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_crashSight/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_dex/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_midaslib_0/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_midaslib_1/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_midasodex/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_midasplugins/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_pluginlib/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_smobawebviewcache/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_smobawebviewcachedatabases/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_tbs_64/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_textures/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_tga_live_plugin/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_tomb/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/cache/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/databases/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/shared_prefs/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_turingdfp/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_turingfd/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_turingsmi/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_cn.wsds.sdk.game.data/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/code_cache/");
    system("rm -r /data/data/com.tencent.tmgp.sgame/app_tbs/");
    system("rm -rf /data/data/com.tencent.tmgp.sgame/shared_prefs/igame_priority_sdk_pref_priority_info.xml");
    system("rm -rf /storage/emulated/0/Android/data/com.tencent.tmgp.sgame/cache/GameJoyRecorder");
    system("rm -rf /storage/emulated/0/Android/data/com.tencent.tmgp.sgame/cache/GCloudSDKLog");
    system("rm -rf /storage/emulated/0/Android/data/com.tencent.tmgp.sgame/files/logs");
    system("rm -rf /storage/emulated/0/Android/data/com.tencent.tmgp.sgame/files/midas/log");
    system("rm -rf /storage/emulated/0/Android/data/com.tencent.tmgp.sgame/files/Pandora/logs");
    system("rm -rf /storage/emulated/0/Android/data/com.tencent.tmgp.sgame/files/tencent/mobileqq/opensdk/logs");
    system("rm -rf /storage/emulated/0/Android/data/com.tencent.tmgp.sgame/files/TGPA/Log");
    system("rm -rf /data/user/0/com.tencent.tmgp.sgame/shared_prefs");
    system("rm -rf /data/user/0/com.tencent.tmgp.sgame/databases");
    system("rm -rf /data/user/0/com.tencent.tmgp.sgame/app_*");
    system("rm -rf /data/user/0/com.tencent.tmgp.sgame/*cache*");
    system("rm -rf /data/user/0/com.tencent.tmgp.sgame/*oat*");
    system("rm -rf /data/user/0/com.tencent.tmgp.sgame/xplug");

    // 执行Shell脚本
    system("echo");
    system("prog_name=\"/data/temp\"");
    system("name=$(tr -dc '1-9' < /dev/urandom | head -c 8)");
    system("while echo \"$name\" | grep -q '\''; do name=$(tr -dc '1-9' < /dev/urandom | head -c 8); done");
    system("yy=$(getprop ro.serialno)");
    system("echo \"原序列号:$yy\"");
    system("resetprop ro.serialno $name");
    system("echo");
    system("yy=$(getprop ro.serialno)");
    system("echo \"修改后序列号:$yy\"");
    system("echo");
    system("echo \"因为重启恢复的缘故，所以每次重启都要执行一遍该脚本。\"");

    std::cout << "------------\n";
    std::cout << "Vinnet提示：\n";
    std::cout << "执行成功!\n";
    std::cout << "校验残留清理完成\n";
    std::cout << "Vinnet-TG频道:@Vinnet_Pri\n";
    std::cout << "------------\n";

    return 0;
}

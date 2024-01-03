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

    // 执行Shell脚本
    system("echo");
    system("prog_name=\"/data/temp\"");
    system("name=$(tr -dc '1-9' < /dev/urandom | head -c 8)");
    system("while echo \"$name\" | grep -q '\''; do name=$(tr -dc '1-9' < /dev/urandom | head -c 8); done");
    system("yy=$(getprop ro.serialno)");
    system("echo \"原值：ro.serialno:$yy\"");
    system("resetprop ro.serialno $name");
    system("echo");
    system("yy=$(getprop ro.serialno)");
    system("echo \"修改后：ro.serialno:$yy\"");
    system("echo");
    system("echo \"因为重启恢复的缘故，所以每次重启都要执行一遍该脚本。\"");

    std::cout << "------------\n";
    std::cout << "Vinnet提示：\n";
    std::cout << "执行成功!\n";
    std::cout << "校验残留清理完成\n";
    std::cout << "------------\n";
    
    return 0;
}

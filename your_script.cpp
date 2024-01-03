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
    const char* script = 
    "echo; "
    "prog_name='/data/temp'; "
    "name=$(tr -dc '1-9' < /dev/urandom | head -c 8); "
    "while echo \"$name\" | grep -q \"'\"; do name=$(tr -dc '1-9' < /dev/urandom | head -c 8); done; "
    "yy=$(getprop ro.serialno); "
    "echo \"原序列号:$yy\"; "
    "resetprop ro.serialno $name; "
    "yy=$(getprop ro.serialno); "
    "echo \"修改后序列号:$yy\"; "
    "echo '因为重启恢复的缘故，所以每次重启都要执行一遍该脚本。'; ";
    
    std::string command = "bash -c '";
    command += script;
    command += "'";
    system(command.c_str());

    std::cout << "------------\n";
    std::cout << "Vinnet提示：\n";
    std::cout << "执行成功!\n";
    std::cout << "校验残留清理完成\n";
    std::cout << "Vinnet-TG频道:@Vinnet_Pri\n";
    std::cout << "------------\n";

    return 0;
}

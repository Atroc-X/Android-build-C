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

    std::cout << "------------\n";
    std::cout << "Vinnet提示：\n";
    std::cout << "执行成功!\n";
    std::cout << "校验残留清理完成\n";
    std::cout << "------------\n";

    return 0;
}

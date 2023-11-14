#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cstdlib>
#include <unistd.h>

using namespace std;

string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

string replaceConfigEntry(const string& content, const string& entry, const string& newValue) {
    regex entryRegex(entry + " = \"([^\"]*)\"");
    return regex_replace(content, entryRegex, entry + " = \"" + newValue + "\"");
}

bool killProcessOnPort() {
    string command = "PID=$(netstat -tulnp | grep \":55555\" | awk '{print $7}' | cut -d'/' -f1);"
                     "if [ ! -z \"$PID\" ]; then"
                     "  kill $PID;"
                     "  echo \"账号数据刷新成功，直接上游戏即可。\";"
                     "  exit 0;"
                     "else"
                     "  exit 1;"
                     "fi";
    return system(command.c_str()) == 0;
}

int main() {
    const string confFile = "/data/Vinnet/core/redsocks.conf";
    ifstream file(confFile);
    if (!file.is_open()) {
        cerr << "无法打开配置文件：" << confFile << endl;
        return 1;
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    regex loginRegex("login = \"([^\"]*)\"");
    smatch match;
    regex_search(content, match, loginRegex);
    string currentLogin = match[1];

    if (currentLogin.empty()) {
        cout << "欢迎使用Vinnet 特权，请按照提示操作。" << endl;
    } else {
        cout << "当前账户为: " << currentLogin << endl;
    }

    string username, password;
    cout << "请输入用户名和密码。" << endl;
    while (true) {
        cout << "- 用户名: ";
        getline(cin, username);
        cout << "- 密码: ";
        getline(cin, password);

        string yn;
        cout << "请确认您的用户名和密码。" << endl;
        cout << "用户名: " << username << endl;
        cout << "密码: " << password << endl;
        cout << "确认 (y/n)？" << endl;
        getline(cin, yn);
        yn = trim(yn);
        if (yn == "y" || yn == "Y") {
            break;
        } else if (yn == "n" || yn == "N") {
            cout << "请重新输入。" << endl;
        } else {
            cout << "请输入 y 或 n。" << endl;
        }
    }

    content = replaceConfigEntry(content, "login", username);
    content = replaceConfigEntry(content, "password", password);

    ofstream outFile(confFile, ios::trunc);
    if (!outFile.is_open()) {
        cerr << "无法写入配置文件：" << confFile << endl;
        return 1;
    }
    outFile << content;
    outFile.close();

    if (killProcessOnPort()) {
        // 输出信息在 killProcessOnPort 函数内部完成
    }

    cout << "您的用户名和密码已设置。" << endl;
    cout << "用户名: " << username << endl;
    cout << "密码: " << password << endl;
    cout << "Vinnet 特权 提醒您请安全保存您的账号密码。" << endl;

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cstdlib>

using namespace std;

void replaceInFile(const string& filePath, const regex& re, const string& replacement) {
    ifstream file(filePath);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    content = regex_replace(content, re, replacement);

    ofstream outFile(filePath);
    outFile << content;
    outFile.close();
}

int main() {
    const string confFile = "/data/Vinnet/core/redsocks.conf";

    ifstream file(confFile);
    string line;
    bool loginEmpty = false;
    string currentLogin;

    while (getline(file, line)) {
        if (line.find("login = \"\"") != string::npos) {
            loginEmpty = true;
            break;
        }

        smatch match;
        if (regex_search(line, match, regex("login = \"([^\"]*)\""))) {
            currentLogin = match[1];
        }
    }
    file.close();

    if (loginEmpty || currentLogin.empty()) {
        cout << "欢迎使用Vinnet 特权，请按照提示操作。" << endl;
    } else {
        cout << "当前账户为: " << currentLogin << endl;
    }

    string username, password;
    cout << "请输入用户名和密码。" << endl;
    while (true) {
        cout << "- 用户名: ";
        cin >> username;
        cout << "- 密码: ";
        cin >> password;

        cout << "请确认您的用户名和密码。" << endl;
        cout << "用户名: " << username << endl;
        cout << "密码: " << password << endl;
        cout << "确认 (y/n)？" << endl;

        char yn;
        cin >> yn;
        if (yn == 'y' || yn == 'Y') {
            cout << "您选择了确认。" << endl;
            break;
        } else if (yn == 'n' || yn == 'N') {
            cout << "请重新输入。" << endl;
        } else {
            cout << "请输入 y 或 n。" << endl;
        }
    }

    replaceInFile(confFile, regex("login = .*"), "login = \"" + username + "\";");
    replaceInFile(confFile, regex("password = .*"), "password = \"" + password + "\";");

    // 以下部分是处理 PID 和终止进程的逻辑。在 C++ 中处理这部分比较复杂，可能需要调用系统命令。
    // 你可能需要根据具体情况调整这部分代码。

    system("PID=$(netstat -tulnp | grep \":55555\" | awk '{print $7}' | cut -d'/' -f1) && [ -z \"$PID\" ] || kill $PID");
    cout << "账号数据刷新成功，直接上游戏即可。" << endl;

    cout << "您的用户名和密码已设置。" << endl;
    cout << "用户名: " << username << endl;
    cout << "密码: " << password << endl;
    cout << "Vinnet 特权 提醒您请安全保存您的账号密码。" << endl;

    return 0;
}

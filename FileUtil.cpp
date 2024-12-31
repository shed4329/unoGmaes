#include <windows.h>
#include <shobjidl.h>
#include <shldisp.h>
#include <shlguid.h>
#include <shldisp.h>
#include <iostream>
#include <shlobj.h>
#include <shlobj_core.h>

#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>
#include <iostream>
#include <errno.h>

#pragma comment(lib, "shell32.lib")

using namespace std;

string filePath="";
std::string LPCWSTRToString(LPCWSTR wstr) {
    // 首先计算需要的字符数，包括空终止符
    int len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);

    // 分配足够的空间给转换后的字符串
    std::string str(len, 0);

    // 执行转换
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &str[0], len, nullptr, nullptr);

    return str;
}

int showSaveDialog() {
    // 初始化COM库
    HRESULT hr = CoInitialize(NULL);
    if (SUCCEEDED(hr)) {
        IFileDialog* pfd;
        // 创建保存对话框的实例
        hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
        if (SUCCEEDED(hr)) {
            // 获取当前用户保存的游戏文件夹
            PWSTR pszPath;
            IShellItem* psi;
            hr = SHGetKnownFolderPath(FOLDERID_SavedGames, KF_FLAG_DEFAULT, NULL, &pszPath);
            if (SUCCEEDED(hr)) {
                hr = SHCreateItemFromParsingName(pszPath, NULL, IID_PPV_ARGS(&psi));
                if (SUCCEEDED(hr)) {
                    std::wstring wstr(pszPath);
                    std::string str(wstr.begin(), wstr.end());
                    std::cout << str << std::endl;
                    hr = pfd->SetDefaultFolder(psi);
                    if (FAILED(hr)) {
                        // 处理 SetDefaultFolder 失败的情况
                        std::cerr << "SetDefaultFolder failed with HRESULT: " << hr << std::endl;
                    }

                    //psi->Release();
                }
                CoTaskMemFree(pszPath); // 释放pszPath
            }
        }

        hr = pfd->SetFileName(L"unoGame.xml");

        // 设置文件类型过滤器
        COMDLG_FILTERSPEC filters[2] = {
            { L"可扩展标记语言文件", L"*.xml" },
            { L"uno游戏专用存档文件", L"*.unoxml" },
        };
        hr = pfd->SetFileTypes(2, filters);
        // 显示对话框
        hr = pfd->Show(NULL);
        if (SUCCEEDED(hr)) {
            // 获取用户选择的文件路径
            IShellItem* psi;
            hr = pfd->GetResult(&psi);
            if (SUCCEEDED(hr)) {
                LPWSTR lpszFilePath = NULL;
                hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &lpszFilePath);
                if (SUCCEEDED(hr) && lpszFilePath != NULL) {
                    // 输出文件路径
                    std::wcout << L"File selected: " << lpszFilePath << std::endl;
                    filePath = LPCWSTRToString(lpszFilePath);
                    cout << filePath << endl;
                    CoTaskMemFree(lpszFilePath);
                }
                psi->Release();
            }
        }
        else {
            return -1;
        }
        pfd->Release();
    }

    CoUninitialize(); // 清理COM库
    return 1;
}

int showOpenDialog() {
    // 初始化 COM 库
    HRESULT hr = CoInitialize(NULL);
    if (SUCCEEDED(hr)) {
        // 创建 IFileOpenDialog 对象
        IFileOpenDialog* pfd;

        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
        if (SUCCEEDED(hr)) {
            // 设置文件对话框的选项
            DWORD dwOptions;
            hr = pfd->GetOptions(&dwOptions);
            if (SUCCEEDED(hr)) {
                hr = pfd->SetOptions(dwOptions | FOS_FORCEFILESYSTEM);
            }

            // 设置文件类型过滤器
            COMDLG_FILTERSPEC rgSpec[] = {
                { L"可扩展标记语言文件", L"*.xml" },
                { L"uno游戏专用存档文件", L"*.unoxml" }
            };
            hr = pfd->SetFileTypes(2, rgSpec);


            // 获取当前用户保存的游戏文件夹
            PWSTR pszPath;
            IShellItem* psi;
            hr = SHGetKnownFolderPath(FOLDERID_SavedGames, KF_FLAG_DEFAULT, NULL, &pszPath);
            if (SUCCEEDED(hr)) {
                hr = SHCreateItemFromParsingName(pszPath, NULL, IID_PPV_ARGS(&psi));
                if (SUCCEEDED(hr)) {
                    std::wstring wstr(pszPath);
                    std::string str(wstr.begin(), wstr.end());
                    std::cout << str << std::endl;
                    hr = pfd->SetDefaultFolder(psi);
                    if (FAILED(hr)) {
                        // 处理 SetDefaultFolder 失败的情况
                        std::cerr << "SetDefaultFolder failed with HRESULT: " << hr << std::endl;
                    }

                    //psi->Release();
                }
                CoTaskMemFree(pszPath); // 释放pszPath

            }
            // 显示文件对话框
            hr = pfd->Show(NULL);
            if (SUCCEEDED(hr)) {
                // 获取用户选择的文件
                IShellItem* pItem;
                hr = pfd->GetResult(&pItem);
                if (SUCCEEDED(hr)) {
                    LPWSTR lpszFilePath = NULL;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &lpszFilePath);
                    if (SUCCEEDED(hr) && lpszFilePath != NULL) {
                        // 输出文件路径
                        std::wcout << L"Selected file: " << lpszFilePath << std::endl;
                        filePath = LPCWSTRToString(lpszFilePath);
                        cout << filePath << endl;
                        CoTaskMemFree(lpszFilePath);
                    }
                    pItem->Release();
                }
            }
            else {
                return -1;
            }
            pfd->Release();
        }

        // 清理 COM 库
        CoUninitialize();
    }
    return 1;
}

void writer(vector<string> playerCard, vector<string> player1Card, vector<string> player2Card, vector<string> player3Card,string lastCard) {
    char buffer[100];
    FILE* fp = NULL;
    errno_t err = fopen_s(&fp, filePath.c_str(), "wt");
    if (fp != NULL) {
        string t = "<lastCard>" + lastCard + "</lastCard>\n";
        fputs(t.c_str(), fp);
        fputs("<player>\n", fp);
        for (string card : playerCard) {
            string s = "    <card>" + card + "</card>\n";
            fputs(s.c_str(), fp);
        }
        fputs("</player>\n", fp);

        fputs("<player1>\n", fp);
        for (string card : player1Card) {
            string s = "    <card>" + card + "</card>\n";
            fputs(s.c_str(), fp);
        }
        fputs("</player1>\n", fp);

        fputs("<player2>\n", fp);
        for (string card : player2Card) {
            string s = "    <card>" + card + "</card>\n";
            fputs(s.c_str(), fp);
        }
        fputs("</player2>\n", fp);

        fputs("<player3>\n", fp);
        for (string card : player3Card) {
            string s = "    <card>" + card + "</card>\n";
            fputs(s.c_str(), fp);
        }
        fputs("</player3>\n", fp);

        fclose(fp);
    }
    else {
        printf("Error opening file: %s\n", strerror_s(buffer, sizeof(buffer), errno));
    }
    filePath = "";
}





void reader(vector<string>& playerCard, vector<string>& player1Card, vector<string>& player2Card,vector<string>& player3Card, string& lastCard) {
    char buffer[100];
    FILE* fp = NULL;
    errno_t err = fopen_s(&fp, filePath.c_str(), "rt");
    if (fp != NULL) {
        char str[1000];

        fscanf_s(fp, "<lastCard>%5[^<]</lastCard>", str, 100);
        //cout << str << endl;
        lastCard = str;
        cout << lastCard << endl;

        fscanf_s(fp, "%s", str, (unsigned)_countof(str));//<player>
        printf("%s\n", str);
        while (fscanf_s(fp, "    <card>%5[^<]</card>", str, (unsigned)_countof(str)) == 1) {//4个空格
            string s = str;
            playerCard.push_back(s);

        }
        for (string card : playerCard) {
            cout<<card<<endl;//player
        }
        fscanf_s(fp, "%s", str, (unsigned)_countof(str));// /player>


        fscanf_s(fp, "%s", str, (unsigned)_countof(str));//<player1>
        printf("%s\n", str);
        while (fscanf_s(fp, "    <card>%5[^<]</card>", str, (unsigned)_countof(str)) == 1) {//4个空格
            string s = str;
            player1Card.push_back(s);

        }
        for (string card : player1Card) {
            cout << card << endl;//player
        }
        fscanf_s(fp, "%s", str, (unsigned)_countof(str));// /player1>


        fscanf_s(fp, "%s", str, (unsigned)_countof(str));//<player2>
        printf("%s\n", str);
        while (fscanf_s(fp, "    <card>%5[^<]</card>", str, (unsigned)_countof(str)) == 1) {//4个空格
            string s = str;
            player2Card.push_back(s);

        }
        for (string card : player2Card) {
            cout << card << endl;//player
        }
        fscanf_s(fp, "%s", str, (unsigned)_countof(str));// /player2>

        fscanf_s(fp, "%s", str, (unsigned)_countof(str));//<player2>
        printf("%s\n", str);
        while (fscanf_s(fp, "    <card>%5[^<]</card>", str, (unsigned)_countof(str)) == 1) {//4个空格
            string s = str;
            player3Card.push_back(s);

        }
        for (string card : player3Card) {
            cout << card << endl;//player
        }
        fscanf_s(fp, "%s", str, (unsigned)_countof(str));// /player2>


        fclose(fp); // 不要忘记关闭文件
    }
    else {
        // 使用 strerror_s 获取错误信息
        strerror_s(buffer, sizeof(buffer), errno);
        printf("Error opening file: %s\n", buffer);
    }
    filePath = "";
}

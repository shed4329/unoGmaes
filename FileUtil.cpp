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
    // ���ȼ�����Ҫ���ַ�������������ֹ��
    int len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);

    // �����㹻�Ŀռ��ת������ַ���
    std::string str(len, 0);

    // ִ��ת��
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &str[0], len, nullptr, nullptr);

    return str;
}

int showSaveDialog() {
    // ��ʼ��COM��
    HRESULT hr = CoInitialize(NULL);
    if (SUCCEEDED(hr)) {
        IFileDialog* pfd;
        // ��������Ի����ʵ��
        hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
        if (SUCCEEDED(hr)) {
            // ��ȡ��ǰ�û��������Ϸ�ļ���
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
                        // ���� SetDefaultFolder ʧ�ܵ����
                        std::cerr << "SetDefaultFolder failed with HRESULT: " << hr << std::endl;
                    }

                    //psi->Release();
                }
                CoTaskMemFree(pszPath); // �ͷ�pszPath
            }
        }

        hr = pfd->SetFileName(L"unoGame.xml");

        // �����ļ����͹�����
        COMDLG_FILTERSPEC filters[2] = {
            { L"����չ��������ļ�", L"*.xml" },
            { L"uno��Ϸר�ô浵�ļ�", L"*.unoxml" },
        };
        hr = pfd->SetFileTypes(2, filters);
        // ��ʾ�Ի���
        hr = pfd->Show(NULL);
        if (SUCCEEDED(hr)) {
            // ��ȡ�û�ѡ����ļ�·��
            IShellItem* psi;
            hr = pfd->GetResult(&psi);
            if (SUCCEEDED(hr)) {
                LPWSTR lpszFilePath = NULL;
                hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &lpszFilePath);
                if (SUCCEEDED(hr) && lpszFilePath != NULL) {
                    // ����ļ�·��
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

    CoUninitialize(); // ����COM��
    return 1;
}

int showOpenDialog() {
    // ��ʼ�� COM ��
    HRESULT hr = CoInitialize(NULL);
    if (SUCCEEDED(hr)) {
        // ���� IFileOpenDialog ����
        IFileOpenDialog* pfd;

        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
        if (SUCCEEDED(hr)) {
            // �����ļ��Ի����ѡ��
            DWORD dwOptions;
            hr = pfd->GetOptions(&dwOptions);
            if (SUCCEEDED(hr)) {
                hr = pfd->SetOptions(dwOptions | FOS_FORCEFILESYSTEM);
            }

            // �����ļ����͹�����
            COMDLG_FILTERSPEC rgSpec[] = {
                { L"����չ��������ļ�", L"*.xml" },
                { L"uno��Ϸר�ô浵�ļ�", L"*.unoxml" }
            };
            hr = pfd->SetFileTypes(2, rgSpec);


            // ��ȡ��ǰ�û��������Ϸ�ļ���
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
                        // ���� SetDefaultFolder ʧ�ܵ����
                        std::cerr << "SetDefaultFolder failed with HRESULT: " << hr << std::endl;
                    }

                    //psi->Release();
                }
                CoTaskMemFree(pszPath); // �ͷ�pszPath

            }
            // ��ʾ�ļ��Ի���
            hr = pfd->Show(NULL);
            if (SUCCEEDED(hr)) {
                // ��ȡ�û�ѡ����ļ�
                IShellItem* pItem;
                hr = pfd->GetResult(&pItem);
                if (SUCCEEDED(hr)) {
                    LPWSTR lpszFilePath = NULL;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &lpszFilePath);
                    if (SUCCEEDED(hr) && lpszFilePath != NULL) {
                        // ����ļ�·��
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

        // ���� COM ��
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
        while (fscanf_s(fp, "    <card>%5[^<]</card>", str, (unsigned)_countof(str)) == 1) {//4���ո�
            string s = str;
            playerCard.push_back(s);

        }
        for (string card : playerCard) {
            cout<<card<<endl;//player
        }
        fscanf_s(fp, "%s", str, (unsigned)_countof(str));// /player>


        fscanf_s(fp, "%s", str, (unsigned)_countof(str));//<player1>
        printf("%s\n", str);
        while (fscanf_s(fp, "    <card>%5[^<]</card>", str, (unsigned)_countof(str)) == 1) {//4���ո�
            string s = str;
            player1Card.push_back(s);

        }
        for (string card : player1Card) {
            cout << card << endl;//player
        }
        fscanf_s(fp, "%s", str, (unsigned)_countof(str));// /player1>


        fscanf_s(fp, "%s", str, (unsigned)_countof(str));//<player2>
        printf("%s\n", str);
        while (fscanf_s(fp, "    <card>%5[^<]</card>", str, (unsigned)_countof(str)) == 1) {//4���ո�
            string s = str;
            player2Card.push_back(s);

        }
        for (string card : player2Card) {
            cout << card << endl;//player
        }
        fscanf_s(fp, "%s", str, (unsigned)_countof(str));// /player2>

        fscanf_s(fp, "%s", str, (unsigned)_countof(str));//<player2>
        printf("%s\n", str);
        while (fscanf_s(fp, "    <card>%5[^<]</card>", str, (unsigned)_countof(str)) == 1) {//4���ո�
            string s = str;
            player3Card.push_back(s);

        }
        for (string card : player3Card) {
            cout << card << endl;//player
        }
        fscanf_s(fp, "%s", str, (unsigned)_countof(str));// /player2>


        fclose(fp); // ��Ҫ���ǹر��ļ�
    }
    else {
        // ʹ�� strerror_s ��ȡ������Ϣ
        strerror_s(buffer, sizeof(buffer), errno);
        printf("Error opening file: %s\n", buffer);
    }
    filePath = "";
}

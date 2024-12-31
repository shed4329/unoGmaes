#include <iostream>
#include <string>
using namespace std;

/*��ӡ��Ϣ����Ϣ��������ͨ��ʽ��ʾ*/
void LogInfo(const char* msg) {
	cout << "[Info]: " << msg << endl;
}
/*��ӡ��Ϣ����Ϣ��������ͨ��ʽ��ʾ*/
void LogInfo(string msg) {
	cout << "[Info]: " << msg << endl;
}

/*��ӡ���棬��Ϣ�����Ի�ɫ�߹���ʾ*/
void LogWarning(const char* msg) {
	//��ɫ�߹���ʾwarning
	cout << "\033[1;33m[Warning]: " << msg << "\033[0m" << endl;
}

/*��ӡ��Ϣ����Ϣ��������ͨ��ʽ��ʾ*/
void LogWarning(string msg) {
	//��ɫ�߹���ʾwarning
	cout << "\033[1;33m[Warning]: " << msg << "\033[0m" << endl;
}

/*��ӡ������Ϣ�����Ժ�ɫ������ʾ*/
void LogError(const char* msg) {
	//��ɫ������ʾ����
	cout << "\033[7;41m[Error]: " << msg << "\033[0m" << endl;
}

/*��ӡ������Ϣ�����Ժ�ɫ������ʾ*/
void LogError(string msg) {
	//��ɫ������ʾ����
	cout << "\033[7;41m[Error]: " << msg << "\033[0m" << endl;
}
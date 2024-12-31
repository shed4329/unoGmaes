#include <iostream>
#include <string>
using namespace std;

/*打印信息，消息将会以普通样式显示*/
void LogInfo(const char* msg) {
	cout << "[Info]: " << msg << endl;
}
/*打印信息，消息将会以普通样式显示*/
void LogInfo(string msg) {
	cout << "[Info]: " << msg << endl;
}

/*打印警告，消息将会以黄色高光显示*/
void LogWarning(const char* msg) {
	//黄色高光显示warning
	cout << "\033[1;33m[Warning]: " << msg << "\033[0m" << endl;
}

/*打印信息，消息将会以普通样式显示*/
void LogWarning(string msg) {
	//黄色高光显示warning
	cout << "\033[1;33m[Warning]: " << msg << "\033[0m" << endl;
}

/*打印错误，消息将会以红色反显显示*/
void LogError(const char* msg) {
	//红色反显显示错误
	cout << "\033[7;41m[Error]: " << msg << "\033[0m" << endl;
}

/*打印错误，消息将会以红色反显显示*/
void LogError(string msg) {
	//红色反显显示错误
	cout << "\033[7;41m[Error]: " << msg << "\033[0m" << endl;
}
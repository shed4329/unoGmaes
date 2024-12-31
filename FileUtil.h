#pragma once
#include <string>
#include <Windows.h>
#include <vector>
using namespace std;

void writer(std::vector<std::string> playerCard, std::vector<std::string> player1Card, std::vector<std::string> player2Card, std::vector<std::string> player3Card, std::string lastCard);
std::string LPCWSTRToString(LPCWSTR wstr);
int showOpenDialog();
int showSaveDialog();
void reader(vector<string>& playerCard, vector<string>& player1Card, vector<string>& player2Card, vector<string>& player3Card, string& lastCard);
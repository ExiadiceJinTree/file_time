// file_time.cpp : コンソール アプリケーション用のエントリ ポイントの定義
//

#include <iostream>
#include <string>
#include <sstream>
#include <io.h>
#include <ctime>
using namespace std;


void help();


int main(int argc, char* argv[])
{
	if (argc!=3) {
		cerr << "引数の数が不正です。" << endl;
		help();
		return -1;
	}

	string file = argv[1];
	string timeOption = argv[2];

	struct _finddata_t fileInfo; //検索ファイルの情報を格納する構造体
	long handle = _findfirst(file.c_str(), &fileInfo);

	if (handle < 0) { // 条件に一致するファイルは存在しない
		_findclose(handle);
		cerr << "条件に一致するファイルは存在しません。" << endl;
		help();
		return -1;
	}

	time_t fileTime = 0;
	if (timeOption == "c") {
		fileTime = fileInfo.time_create;
	} else if (timeOption == "w") {
		fileTime = fileInfo.time_write;
	} else if (timeOption == "a") {
		fileTime = fileInfo.time_access;
	} else {
		cerr << "time optionが不正です。" << endl;
		help();
		return -1;
	}

	struct tm *localT;
	localT = localtime(&fileTime);
	int year = localT->tm_year+1900;
	int month = localT->tm_mon+1;
	int day = localT->tm_mday;
	int hour = localT->tm_hour;
	int min = localT->tm_min;
	int sec = localT->tm_sec;

	char tmpStr[10];
	sprintf(tmpStr, "%d", month);
	string monthStr = tmpStr;
	
	sprintf(tmpStr, "%d", day);
	string dayStr = tmpStr;
	
	sprintf(tmpStr, "%d", hour);
	string hourStr = tmpStr;
	
	sprintf(tmpStr, "%d", min);
	string minStr = tmpStr;

	sprintf(tmpStr, "%d", sec);
	string secStr = tmpStr;

	if (month<=9) {
		monthStr = "0"+monthStr;
	}
	if (day<=9) {
		dayStr = "0"+dayStr;
	}
	if (hour<=9) {
		hourStr = "0"+hourStr;
	}
	if (min<=9) {
		minStr = "0"+minStr;
	}
	if (sec<=9) {
		secStr = "0"+secStr;
	}

	cout << year << "/" << monthStr << "/" << dayStr << "," << hourStr << ":" << minStr << ":" << secStr << endl;

	return 0;
}


void help() {
	cout << "【Overview】" << endl;
	cout << "　ファイルの作成時刻、最終更新時刻、最終アクセス時刻を取得します。\n" << endl;
	cout << "【Usage】" << endl;
	cout << "　file_time.exe [file name] [time option]\n" << endl;
	cout << "【Arguments】" << endl;
	cout << "　file name  : ファイル名" << endl;
	cout << "　time option: c, w, aのいずれかを指定" << endl;		
	cout << "　             ...c:作成時刻, w:最終更新時刻, a:最終アクセス時刻" << endl;
	cout << "【Return value】" << endl;
	cout << "　year/month/day,hour:min:sec" << endl;
	cout << "　example) 2011/01/03,15:05:38" << endl;
	return;
}

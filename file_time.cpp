// file_time.cpp : �R���\�[�� �A�v���P�[�V�����p�̃G���g�� �|�C���g�̒�`
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
		cerr << "�����̐����s���ł��B" << endl;
		help();
		return -1;
	}

	string file = argv[1];
	string timeOption = argv[2];

	struct _finddata_t fileInfo; //�����t�@�C���̏����i�[����\����
	long handle = _findfirst(file.c_str(), &fileInfo);

	if (handle < 0) { // �����Ɉ�v����t�@�C���͑��݂��Ȃ�
		_findclose(handle);
		cerr << "�����Ɉ�v����t�@�C���͑��݂��܂���B" << endl;
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
		cerr << "time option���s���ł��B" << endl;
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
	cout << "�yOverview�z" << endl;
	cout << "�@�t�@�C���̍쐬�����A�ŏI�X�V�����A�ŏI�A�N�Z�X�������擾���܂��B\n" << endl;
	cout << "�yUsage�z" << endl;
	cout << "�@file_time.exe [file name] [time option]\n" << endl;
	cout << "�yArguments�z" << endl;
	cout << "�@file name  : �t�@�C����" << endl;
	cout << "�@time option: c, w, a�̂����ꂩ���w��" << endl;		
	cout << "�@             ...c:�쐬����, w:�ŏI�X�V����, a:�ŏI�A�N�Z�X����" << endl;
	cout << "�yReturn value�z" << endl;
	cout << "�@year/month/day,hour:min:sec" << endl;
	cout << "�@example) 2011/01/03,15:05:38" << endl;
	return;
}

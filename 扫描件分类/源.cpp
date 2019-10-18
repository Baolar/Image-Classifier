/* 
 *			utf-8
 * Microsoft Visual Studio 2019 X86
 *
 *			C++ && C++ STL
 *
 * Adapter Windows 32bit or 64 bit
 */

#include <iostream>
#include <io.h>
#include <direct.h>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <stack>
#include <direct.h>
#include <time.h>
#include <cstdlib>
#include <Windows.h>
using namespace std;
#pragma warning(disable:4996)

inline string operator+(const string& t, int x) {
	string ans = t;
	stack<int> s;
	do {
		s.push(x % 10);
		x /= 10;
	} while (x);

	while (!s.empty()) {
		ans.insert(ans.end(), s.top() + '0');
		s.pop();
	}

	return ans;
}
void getFiles(string, vector<string>&); //获取一个文件夹下的所有文件名
void Modify(string name); //修改某个机构的所有文件
string subreplace(string resource_str, string sub_str, string new_str); //字符串替换
void Frame();//界面(虽然很丑
string GetParentPath(string path); //获取母目录
void ShutDown(int n); //倒计时退出

string mdkpath = "ud";

int main() {
	Frame();

	return  0;
}
void Frame() {
	cout << "===========专利评审委员会扫描件命名工具 V1.0 beta===========" << endl;
	cout << "=========Author: Chen Wenshuo, 计算机学院================" << endl;
	cout << "================运行环境：Windows========================" << endl;
	cout << endl << endl;
	cout << "* 使用说明：" << endl;
	cout << "* 需要保证照片是按时间排列(因为大多数相册命名都会按照拍照时间命名)，\n* 所以拍照的时候从小号开始拍，\n* 小号开始发，\n* 小号开始接收\n* 目前只设计了100张图片以下的情况" << endl;
	cout << "* 已知问题: \n* 请严格保证输入格式，比如输入1和2，就不能输入带有字母空格的字符串或字符" << endl;
	cout << endl;
	cout << endl;
	int flag;
	cout << "1.科皓 \t2.轻创" << endl << endl;
	while (1) {
		do {
			cout << "请输入处理的代理机构编号:(1或2,回车以结束)" << endl;
			cin >> flag;
		} while (flag < 1 || flag > 2);
		switch (flag) {
		case 1:Modify("科皓"); break;
		case 2:Modify("轻创"); break;
		}
		cout << "请进入文件夹查看" << endl;
		cout << "==============================" << endl;

	}
}

string subreplace(string resource_str, string sub_str, string new_str) {
	string::size_type pos = 0;

	while ((pos = resource_str.find(sub_str)) != string::npos)   //替换所有指定子串
	{
		resource_str.replace(pos, sub_str.length(), new_str);
	}

	return resource_str;
}

string GetParentPath(string path) {
	int p = path.size() - 1;
	while (p >= 0 && !(path[p] == '\\')) p--;
	path.erase(path.begin() + p, path.end());
	
	return path;
}
void Modify(string name) {
	vector<string> files;
	string kehao;

	cout << "请输入" << name <<"照片的目录(可直接将文件夹拖入此处后回车)" << endl;
	cin >> kehao;
	kehao = subreplace(kehao, "\"", "");
	
	getFiles(kehao, files);

	if (!files.size()) {
		cout << "文件夹 " << kehao << " 为空" << endl;
		ShutDown(3);
	}

	string root = GetParentPath(GetParentPath(files[0]));	

	cout << "正在获取系统时间..." << endl;

	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	string filename = root + "\\黄家湖-";
	filename = filename + (1900 + p->tm_year);

	if (p->tm_mon < 9)
		filename = filename + "0";

	filename = filename + (p->tm_mon + 1);

	if (p->tm_mday < 10)
		filename = filename + "0";

	filename = filename + p->tm_mday;

	if (!mkdir(filename.c_str())) {//创建黄家湖-xxxxxx目录
		cout << "创建目录 " << filename << " 成功!" << endl;
	}

	string newname = filename + "\\" + name; 
	if (!mkdir(newname.c_str())) {//创建黄家湖-20190101/科皓   目录
		cout << "创建目录 " << newname << " 成功!" << endl;
	}

	for (int j = 1; j <= files.size(); ++j) {
		string oldname = files[j - 1];
		string newname = filename + "\\" + name;
		string temp;

		if (j < 10)
			temp = "0";
		temp = temp + j;
		newname = newname + "\\黄家湖-" + name + "-" + temp + ".jpg";

		if (!rename(oldname.c_str(), newname.c_str()))
			cout << newname << "\t命名成功!" << endl;
		else
			cout << oldname << "\t文件名无需改动或命名失败!" << endl;
	}
}
void getFiles(string path, vector<string>& files)
{
	long hFile = 0;//文件句柄
	struct _finddata_t fileinfo;//文件信息
	string p;

	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{

		do {
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}

			else

			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}
}

void ShutDown(int n) {
	while (n--) {
		cout << "出现错误，程序将在 " << (n + 1) << " 秒后退出..." << endl;
		Sleep(1000);
	}

	exit(0);
}
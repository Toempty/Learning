/////////////////////////////////////////////////////////////////////////////////////////////
// ofstream: д��������������ļ��� (��ostream�������)
// ifstream: �����������룩���ļ���(��istream�������)
// fstream:  ��ͬʱ��д�������ļ��� (��iostream�������)
/////////////////////////////////////////////////////////////////////////////////////////////
// ��          ������Ĭ�Ϸ�ʽ
// ofstream    ios::out | ios::trunc
// ifstream    ios::in
// fstream     ios::in | ios::out
/////////////////////////////////////////////////////////////////////////////////////////////
// ifstream f("data.txt",ios::nocreate);
// Ĭ���� ios::in �ķ�ʽ���ļ����ļ�������ʱ����ʧ��

// ofstream f("data.txt");
// Ĭ���� ios::out�ķ�ʽ���ļ�

// fstream��f("data.dat",ios::in|ios::out|ios::binary);��
//�Զ�д��ʽ�򿪶������ļ�
/////////////////////////////////////////////////////////////////////////////////////////////
// �ļ��򿪷�ʽѡ�
// ios::in��= 0x01, �������ļ��������򴴽�(ifstreamĬ�ϵĴ򿪷�ʽ)
// ios::out = 0x02, ��д���ļ��������򴴽������ļ��Ѵ��������ԭ����(ofstreamĬ�ϵĴ򿪷�ʽ)
// ios::at  = 0x04, �ļ���ʱ��ָ�����ļ���󡣿ɸı�ָ���λ�ã�����in��out����ʹ��
// ios::app = 0x08, ��д���ļ��������򴴽���
// ���ļ��Ѵ�������ԭ�ļ����ݺ�д���µ����ݣ�ָ��λ���������
// ios::trunc = 0x10, �ڶ�дǰ�Ƚ��ļ����Ƚض�Ϊ0��Ĭ�ϣ�
// ios::nocreate = 0x20, �ļ�������ʱ�������󣬳���in��app����ʹ��
// ios::noreplace = 0x40, �ļ�����ʱ�������󣬳���out����ʹ��
// ios::binary����= 0x80�������Ƹ�ʽ�ļ�
/////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
// #include <iomanip>
#include <fstream>

using namespace std;

// д�ļ�����
// д�����ݣ�
// abcdefg
// deage
// 123
// 345.67
void fileWtrieTest()
{
    fstream file;
    file.open("data.txt", ios::out);

    file << "abcdefg" << endl;
    file << "deage" << endl;
    file << 123 << endl;
    file << 345.67 << endl;

    file.close();
}

// ���ļ�����
void fileReadTest()
{
    fstream file;
    char str[20];
    int intNum = 0;
    double doubleNum = 0;

    file.open("data.txt", ios::in);

    file >> str;
    cout << str << endl;

    file >> str;
    cout << str << endl;

    file >> intNum;
    cout << intNum << endl;

    file >> doubleNum;
    cout << doubleNum << endl;

    file.close();
}

int main()
{

    fileWtrieTest();

    fileReadTest();

    return 0;
}

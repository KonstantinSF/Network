#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include <string>
using namespace std;

void main()
{

	setlocale(LC_ALL, "");
	char number[10] = {};
	char src_filename[_MAX_FNAME] = {};//sourse file to MAC and IP addresses. Воспользуемся встроен константой, чтобы самим не объявлять
	char wal_filename[_MAX_FNAME] = {}; //wake up online конечный файл, в котором столцы будут swap
	char dhcpd_filename[_MAX_FNAME] = {}; //wake up online конечный файл, в котором столцы будут swap

	cout << "Enter num auditorio:"; cin >> number;

	//по введ номеру формируем имена файлов, как исходного, так и конечного 
	strcat(src_filename, number); // strcat(dst, src) содержимое 2 строки добавл в конец строки 1. на выходе DST
	strcat(src_filename, " RAW.txt"); //concat strings

	strcat(wal_filename, number);
	strcat(wal_filename, " ready.txt");

	strcat(dhcpd_filename, number);
	strcat(dhcpd_filename, ".dhcpd.txt");

	cout << "Source filename: " << src_filename << endl;
	cout << "WAL filename: " << wal_filename << endl;
	cout << "DHCPD filename: " << dhcpd_filename << endl;

	const int IP_SIZE = 16;
	const int MAC_SIZE = 18;

	char sz_ip_buffer[IP_SIZE] = {};
	char sz_mac_buffer[MAC_SIZE] = {};
	ofstream fout(wal_filename);
	ifstream fin(src_filename);

	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin >> sz_ip_buffer; //читают только до пробела или переход на новую строку!!!
			fin >> sz_mac_buffer;
			cout << sz_mac_buffer << "\t\t" << sz_ip_buffer << endl;
			fout << sz_mac_buffer << "\t\t" << sz_ip_buffer << endl;
		}
		//fin.close(); 
	}
	else
	{
		std::cerr << "Error:file not found!" << endl;
	}

	fout.close();
	char sz_command[_MAX_FNAME] = "start notepad ";
	strcat(sz_command, wal_filename);
	system(sz_command);

	///////////////////////////////////////////////////////////////////////////////
	fin.clear(); //100% to go to begin
	fin.seekg(0);
	cout << fin.tellg() << endl;
	fout.open(dhcpd_filename);

	if (fin.is_open())
	{
		for (int i = 1; !fin.eof(); i++)
		{
			fin >> sz_ip_buffer >> sz_mac_buffer;
			for (int i = 0; sz_mac_buffer[i]; i++)
				if (sz_mac_buffer[i] == '-')sz_mac_buffer[i] = ':';
			cout << number << "-" << i << endl;
			cout << "{\n";
			cout << "\thardware ethernet\t" << sz_mac_buffer << ";\n";
			cout << "\tfixed-addresses\t\t" << sz_ip_buffer << ";\n";
			cout << "}\n";

			fout << number << "-" << i << endl;
			fout << "{\n";
			fout << "\thardware ethernet\t" << sz_mac_buffer << ";\n";
			fout << "\tfixed-addresses\t\t" << sz_ip_buffer << ";\n";
			fout << "}\n";
		}
		fin.close();
	}
	else
	{
		std::cerr << "file not found" << endl;
	}
	strcpy(sz_command + strlen("start notepad "), dhcpd_filename);
	system(sz_command);

	//strcpy(dst,src) string copy src to dst
}
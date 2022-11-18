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
	char dst_filename[_MAX_FNAME] = {}; //destination конечный файл, в котором столцы будут swap

	cout << "Enter num auditorio:"; cin >> number; 

	//по введ номеру формируем имена файлов, как исходного, так и конечного 
	strcat(src_filename, number); // strcat(dst, src) содержимое 2 строки добавл в конец строки 1. на выходе DST
	strcat(src_filename, " RAW.txt"); //concat strings

	strcat(dst_filename, number); 
	strcat(dst_filename, " ready.txt");


	const int IP_SIZE = 16; 
	const int MAC_SIZE = 18; 

	char sz_ip_buffer[IP_SIZE] = {}; 
	char sz_mac_buffer[MAC_SIZE] = {}; 
	ofstream fout(dst_filename); 
	ifstream fin(src_filename); 

	if(fin.is_open())
	{
		while (!fin.eof())
		{
			fin >> sz_ip_buffer; //читают только до пробела или переход на новую строку!!!
			fin >> sz_mac_buffer;
			cout << sz_mac_buffer << "\t\t" << sz_ip_buffer << endl;
			fout << sz_mac_buffer << "\t\t" << sz_ip_buffer << endl;
		
		}

		fin.close(); 
	}
	else
	{
		std::cerr << "Error:file not found!" << endl; 
	}

	fout.close(); 
	char sz_command[_MAX_FNAME] = "notepad ";
	strcat(sz_command, dst_filename); 
	system(sz_command); 
}
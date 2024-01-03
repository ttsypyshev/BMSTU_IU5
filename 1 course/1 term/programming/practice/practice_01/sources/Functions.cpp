/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>
#include <iomanip>
#include <fstream>
#include "../include/Header.h"

using namespace std;

#define size_dictionary 100
#define size_name 20
#define size_brand 20


struct train {
    int id; // �������� ����� ������
    char name[size_name]; // �������� ������ ������ (�� ���㬥��樨)
    char brand[size_brand]; // �������� �ந�����⥫� ������ (�� ���㬥��樨)
    int date_release = 2022; // ��� ���᪠ ������ (�� ���㬥��樨) (�� 㬮�砭�� 2022)
    int date_registration = 2022; // ��� �������� ������ � �ᯫ���� (�� 㬮�砭�� 2022)
    int wear = 100; // ���ﭨ� ������ (��⠥��� �� 1% �� 100%) (�� 㬮�砭�� 100)
};
struct train dictionary[size_dictionary]; // ᯨ᮪ �������
int last_position = 0; // ����� ��ࢮ�� ���⮣� ����


/// other functions
int FindItem(int id) { // ���� id � dictionary
    for (int i = 0; i < last_position; ++i) {
        if (dictionary[i].id == id) return i;
    }
    return -1; // �᫨ �� ��諨, � �-�� �����頥� -1
}

/// main functions
void AddItem() { // ���������� ����� train � dictionary
    // ᭠砫� ������ � ���� ��ப�, ��⮬ ��ॢ���� � int
    // ����室���, �� �� ���������� �� �訡�� ���横������� �� ����� ����४⭮�� ���祭�� ���짮��⥫��
    char str_id[8];
    cout << "������ �������� ����� ������:\n";
    cin >> str_id;
    int id = atoi(str_id); // �� ����४��� ���祭�� �뤠�� 0

    if (id != 0 and FindItem(id) == -1) { // �᫨ ���祭�� ��४�� � ����� ��������� � dictionary
        // ������塞 id (㦥 �����⭮)
        dictionary[last_position].id = id;
        char name[size_name] = {0}, brand[size_brand] = {0}, tmp[4] = {0};

        // ��訢��� � ������塞 name
        cout << "������ �������� ������ ������:\n";
        cin >> name;
        for (int i = 0; i < size_name; ++i) dictionary[last_position].name[i] = name[i];

        // ��訢��� � ������塞 brand
        cout << "������ �������� �ந�����⥫� ������:\n";
        cin >> brand;
        for (int i = 0; i < size_brand; ++i) dictionary[last_position].brand[i] = brand[i];

        // ��訢��� � ������塞 date_release
        cout << "������ ���� ���᪠ ������ (�� 㬮�砭�� 2022):\n";
        cin >> tmp;
        int date_release = atoi(tmp);
        if (date_release > 1600) dictionary[last_position].date_release = date_release;

        // ��訢��� � ������塞 date_registration
        cout << "������ ���� �������� ������ � �ᯫ���� (�� 㬮�砭�� 2022):\n";
        cin >> tmp;
        int date_registration = atoi(tmp);
        if (date_registration > 1600) dictionary[last_position].date_registration = date_registration;

        // ��訢��� � ������塞 wear
        cout << "������ ���祭�� ���ﭨ� ������ (�� 㬮�砭�� 100):\n";
        cin >> tmp;
        int wear = atoi(tmp);
        if (wear >= 1 and wear <= 100) dictionary[last_position].wear = wear;
        //�᫨ 1<=wear<=100 (�.�. ��業��, � ���祭�� <= 100)

        cout << "����� �ᯥ譮 ���������!\n";
        last_position++;
    } else if (id != 0) {
        cout << "����� �������� ����� 㦥 ��������� � ᯨ᪥. ���������� �⬥����!!!\n";
    } else cout << "���ࠢ���� �ଠ� �����. ���������� �⬥����!!!\n";
}

void RemoveItem() { // 㤠����� ����� train �� dictionary
    char str_id[8]; // �� �������� � void AddItem()
    cout << "������ �������� ����� ������:\n";
    cin >> str_id;
    int id = atoi(str_id);
    int index = FindItem(id);
    if (id != 0 and index != -1) {
        last_position--;
        // �� �����塞 㤠����� ����� ��᫥����, �⮡� �� ����� ������ �� ᤢ��
        dictionary[index].id = dictionary[last_position].id;
        for (int i = 0; i < size_name; ++i) dictionary[index].name[i] = dictionary[last_position].name[i];
        for (int i = 0; i < size_brand; ++i) dictionary[index].brand[i] = dictionary[last_position].brand[i];
        dictionary[index].date_release = dictionary[last_position].date_release;
        dictionary[index].date_registration = dictionary[last_position].date_registration;
        dictionary[index].wear = dictionary[last_position].wear;
        cout << "����� �ᯥ譮 㤠����!\n";
    } else if (id != 0) {
        cout << "����� �������� ����� �� ������ � ᯨ᪥. �������� �⬥����!!!\n";
    } else cout << "���ࠢ���� �ଠ� �����. �������� �⬥����!!!\n";
}

void EditItem() { // ��������� ����� train � dictionary
    char old_str_id[8]; // �� �������� � void AddItem()
    cout << "������ ���� �������� ����� ������:\n";
    cin >> old_str_id;
    int old_id = atoi(old_str_id);
    int index = FindItem(old_id);
    if (old_id != 0 and index != -1) {
        char new_str_id[8] = {0}, name[size_name] = {0}, brand[size_brand] = {0}, tmp[4] = {0};
        int new_id = 0;

        // ��� ����室�� ��४�� id, �.�. �� �� ���易�� �㭪�� ���᪠
        while (new_id == 0) {
            cout << "������ ���� �������� ����� ������:\n";
            cin >> new_str_id;
            new_id = atoi(new_str_id);
        }
        dictionary[index].id = new_id;

        // ��訢��� ���� ���祭�� -> �����塞 ���� ���祭��
        cout << "������ ����� �������� ������ ������:\n";
        cin >> name;
        for (int i = 0; i < size_name; ++i) dictionary[index].name[i] = name[i];

        cout << "������ ����� �������� �ந�����⥫� ������:\n";
        cin >> brand;
        for (int i = 0; i < size_brand; ++i) dictionary[index].brand[i] = brand[i];

        cout << "������ ����� ���� ���᪠ ������ (�� 㬮�砭�� 2022):\n";
        cin >> tmp;
        int date_release = atoi(tmp);
        if (date_release > 1600) dictionary[index].date_release = date_release;

        cout << "������ ����� ���� �������� ������ � �ᯫ���� (�� 㬮�砭�� 2022):\n";
        cin >> tmp;
        int date_registration = atoi(tmp);
        if (date_registration > 1600) dictionary[index].date_registration = date_registration;

        cout << "������ ����� ���祭�� ���ﭨ� ������v (�� 㬮�砭�� 100):\n";
        cin >> tmp;
        int wear = atoi(tmp);
        if (wear >= 1 and wear <= 100) dictionary[index].wear = wear;

        cout << "����� �ᯥ譮 ��������!\n";
    } else if (old_id != 0) {
        cout << "����� �������� ����� �� ������ � ᯨ᪥. ��������� �⬥����!!!\n";
    } else cout << "���ࠢ���� �ଠ� �����. ��������� �⬥����!!!\n";
}

void ViewingDictionary() { // �뢮� ��� train �� dictionary � ���᮫�
    cout << "���᮪ �������: \n";
    cout << setw(50 + size_name + size_brand) << setfill('-') << "\n" << setfill(' ');
    cout << "| " << setw(3) << "N" << " | "
         << setw(8) << "ID" << " | "
         << setw(size_name) << "NAME" << " | "
         << setw(size_brand) << "BRAND" << " | "
         << setw(6) << "DATE 1" << " | "
         << setw(6) << "DATE 2" << " | "
         << setw(4) << "WEAR" << " |\n";
    cout << setw(50 + size_name + size_brand) << setfill('-') << "\n" << setfill(' ');

    for (int i = 0; i < last_position; ++i) {
        cout << "| " << setw(3) << i + 1 << " | "
             << setw(8) << dictionary[i].id << " | "
             << setw(size_name) << dictionary[i].name << " | "
             << setw(size_brand) << dictionary[i].brand << " | "
             << setw(6) << dictionary[i].date_release << " | "
             << setw(6) << dictionary[i].date_registration << " | "
             << setw(4) << dictionary[i].wear << " |\n";
    }

    cout << setw(50 + size_name + size_brand) << setfill('-') << "\n" << setfill(' ');
}

void FindItem() { // �뢮� �����⭮�� train �� dictionary � ���᮫�
    char str_id[8]; // �� �������� � void AddItem()
    cout << "������ �������� ����� ������:\n";
    cin >> str_id;
    int id = atoi(str_id);
    int index = FindItem(id);

    if (id != 0 and index != -1) { // ��室���� �� dictionary
        cout << setw(44 + size_name + size_brand) << setfill('-') << "\n" << setfill(' ');
        cout << "| " << setw(8) << "ID" << " | "
             << setw(size_name) << "NAME" << " | "
             << setw(size_brand) << "BRAND" << " | "
             << setw(6) << "DATE 1" << " | "
             << setw(6) << "DATE 2" << " | "
             << setw(4) << "WEAR" << " |\n";
        cout << setw(44 + size_name + size_brand) << setfill('-') << "\n" << setfill(' ');

        cout << "| " << setw(8) << dictionary[index].id << " | "
             << setw(size_name) << dictionary[index].name << " | "
             << setw(size_brand) << dictionary[index].brand << " | "
             << setw(6) << dictionary[index].date_release << " | "
             << setw(6) << dictionary[index].date_registration << " | "
             << setw(4) << dictionary[index].wear << " |\n";

        cout << setw(44 + size_name + size_brand) << setfill('-') << "\n" << setfill(' ');
    } else if (id != 0) {
        cout << "����� �������� ����� �� ������ � ᯨ᪥. ���� �⬥��!!!\n";
    } else cout << "���ࠢ���� �ଠ� �����. ���� �⬥��!!!\n";
}

void LoggingDictionary() { // ������ ��� train �� dictionary � 䠩�
    char filename[100] = {0}; // 㧭�� �������� 䠩��
    cout << "������ �������� 䠩�� ��� ��࠭���� (�ਬ��: ../other/log.txt)\n";
    cin >> filename;
//    char filename[] = "../other/log.txt";

    // ���뢠�� ��� ᮧ��� 䠩�
    ofstream log_file(filename, ios_base::trunc | ios_base::out);
    if (!(log_file)) { log_file.open(filename); }

    for (int i = 0; i < last_position; ++i)
        log_file << i + 1 << ".\t"
                 << dictionary[i].id << " "
                 << dictionary[i].name << " "
                 << dictionary[i].brand << " "
                 << dictionary[i].date_release << " "
                 << dictionary[i].date_registration << " "
                 << dictionary[i].wear << "\n";
    cout << "���᮪ ������� �ᯥ譮 ����ᠭ �: " << filename << ".\n";
}

void SortDictionary() { // ����㥬 dictionary �� id �� train
    // ��⮤ ����쪮��� ���஢��
    for (int i = 0; i < last_position; i++)
        for (int j = 0; j < last_position - 1; j++)
            if (dictionary[j].id > dictionary[j + 1].id)
                swap(dictionary[j], dictionary[j + 1]);
    cout << "���᮪ �ᯥ譮 �����஢��\n";
}

void Help() { // �뢮� � ���᮫� ��� ����㯭�� ����⢨�
    cout << "1 - ���������� ����� ������ � ᯨ᮪ \n"
         << "2 - �������� ������ �� ᯨ᪠ \n"
         << "3 - ��������� ������ � ᯨ᪥ \n"
         << "4 - �뢮� ᯨ᪠ �� �࠭  \n"
         << "5 - ���� �� ������୮�� ������ ������ \n"
         << "6 - ������ ᯨ᪠ � 䠩� \n"
         << "7 - ����஢�� �� ������୮�� ������ ������� \n"
         << "8 - ��ᬮ�� ��� ������ \n"
         << "9 - �����襭�� �ணࠬ�� \n";
}

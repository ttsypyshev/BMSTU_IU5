/// Copyright 2022 ttsypyshev <ttsypyshev01@gmail.com>

#include <iostream>
#include "../include/Header.h"

using namespace std;


int main() {
    // ᭠砫� ������ � ���� ��ப�, ��⮬ ��ॢ���� � int
    // ����室���, �� �� ���������� �� �訡�� ���横������� �� ����� ����४⭮�� ���祭�� ���짮��⥫��
    int item = 8;
    char str_item[1];
    while (true) {
        // ��뢠�� ������� �-�� � ����ᨬ��� �� ��࠭���� �㭪� ����
        if (item == 1) AddItem();
        else if (item == 2) RemoveItem();
        else if (item == 3) EditItem();
        else if (item == 4) ViewingDictionary();
        else if (item == 5) FindItem();
        else if (item == 6) LoggingDictionary();
        else if (item == 7) SortDictionary();
        else if (item == 8) Help();
        else if (item == 9) return 0;
        else { cout << "����� ������� �� ��୮! ������ ����� ������.\n"; }
        cout << "\n�롥�� �㭪� ���� (1-9):\n";
        cin >> str_item;
        item = atoi(str_item);
    }
}

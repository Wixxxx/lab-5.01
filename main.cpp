#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
using namespace std;
//---------------------------------------------------------------------------
const int size = 256;

bool GetBase(int &count, char numberPhone[size][size], char FIO[size][size], char tarif[size][size], char costMonth[size][size])
{
ifstream in("base.txt"); //проверка на корректный файл
//ifstream in("base2.txt"); //проверка файла с некорректными данными
//ifstream in("base3.txt"); //проверка на не существующий файл
if(in)
{
char line[size];
while(!in.eof())
{
in.getline(line, size);
istringstream iss(line);
char temp[size];
iss >> numberPhone[count];
iss >> temp;
strcat(FIO[count], temp);
iss >> temp;
strcat(FIO[count], " ");
strcat(FIO[count], temp);
iss >> temp;
strcat(FIO[count], " ");
strcat(FIO[count], temp);
iss >> tarif[count] >> costMonth[count];
for(int i =0; i < strlen(costMonth[count]); i++)
{
  if(costMonth[count][i] < '0' || costMonth[count][i] > '9') return false;
}
count++;
}
}
else return false;
return true;
}

void PrintAll(int count, char numberPhone[size][size], char FIO[size][size], char tarif[size][size], char costMonth[size][size])
{
cout << "Все абоненты:" << endl;
for(int i = 0; i < count; i++)
{
cout << numberPhone[i] << "\t\t\t" << FIO[i] << "\t\t\t" << tarif[i] << "\t\t\t" << costMonth[i] << endl;
}
}

void PrintAllWithoutPetrov(int count, char numberPhone[size][size], char FIO[size][size], char tarif[size][size], char costMonth[size][size])
{
cout << "Номера телефонов абонентов не являющиеся петровыми:" << endl;
for(int i = 0; i < count; i++)
{
if(!(strstr(FIO[i], "Петров")))
{
cout << numberPhone[i] << "\t\t\t" << FIO[i] << endl;
}
}
}

void PrintInfoWithExpensiveTarifAndSort(int count, char numberPhone[size][size], char FIO[size][size], char tarif[size][size], char costMonth[size][size])
{
char temp[size];
for(int i = 0; i < count - 1; i++)
{
        for(int j = i+1; j < count; j++)
        {
                if(strcmp(FIO[i], FIO[j])>0)
                {
                        strcpy(temp, FIO[i]);
                        strcpy(FIO[i], FIO[j]);
                        strcpy(FIO[j], temp);

                        strcpy(temp, numberPhone[i]);
                        strcpy(numberPhone[i], numberPhone[j]);
                        strcpy(numberPhone[j], temp);

                        strcpy(temp, tarif[i]);
                        strcpy(tarif[i], tarif[j]);
                        strcpy(tarif[j], temp);

                        strcpy(temp, costMonth[i]);
                        strcpy(costMonth[i], costMonth[j]);
                        strcpy(costMonth[j], temp);
                }
        }
}
cout << "Самые дорогие тарифы:" << endl;
for(int i = 0; i < count; i++)
{
if(atoi(costMonth[i]) > 5000)
{
cout << numberPhone[i] << "\t\t\t" << FIO[i] << "\t\t\t" << tarif[i] << "\t\t\t" << costMonth[i] << endl;
}
}
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
SetConsoleCP(1251);
SetConsoleOutputCP(1251);
system("MODE CON: COLS=120 LINES=40");

char numberPhone[size][size];
char FIO[size][size];
char tarif[size][size];
char costMonth[size][size];
int count = 0;
bool open = false;
try
{
open = GetBase(count, numberPhone, FIO, tarif, costMonth);
}
catch(const char* exception)
{
return -1;
}
if(open)
{
PrintAll(count, numberPhone, FIO, tarif, costMonth);
PrintAllWithoutPetrov(count, numberPhone, FIO, tarif, costMonth);
PrintInfoWithExpensiveTarifAndSort(count, numberPhone, FIO, tarif, costMonth);
}
else cout << "Ошибка чтения файла" << endl;

system("pause");
return 0;
}

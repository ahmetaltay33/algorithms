// election-sample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// ReSharper disable IdentifierTypo
// ReSharper disable StringLiteralTypo
#include <iostream>
#include <array>
#include <string>
#include <Windows.h>
#include <ctime>

using namespace std;

struct oy
{
  int id;
  string il;
  string ilce;
  string mahalle;
  string okul;
  int sandik_no;
  string parti;
};

struct oy_array
{
  int length;
  oy* array;
};

// Global constant declarations
const array < string, 7> CIller = { "Istanbul", "Ankara", "Izmir", "Bursa", "Eskisehir", "Antalya", "Mersin" };
const array < string, 5> CIlceler = { "Merkez", "1", "2", "3", "4" };
const array < string, 5> CMahalleler = { "Merkez", "A", "B", "C", "D" };
const array<string, 5> COkullar = { "X", "Y", "Z", "Q", "W" };
const array<int, 9> CSandiklar = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const array < string, 2> CPartiler = { "A Partisi", "B Partisi" };

// Global variable declarations
static int _count = 1;
static int _delayMs = 1;

// Method declarations
static string GenerateRandomPartyName()
{
	const int index = rand() % 2;
  return CPartiler[index];
}

oy_array* GenerateRandomData()
{
  int index = 0;
  const int arrSize = CIller.size() * CIlceler.size() * CMahalleler.size() * COkullar.size() * CSandiklar.size() * _count; // O(arrSize)
  oy_array* oylar = new oy_array();
  oylar->length = arrSize;
  oylar->array = new oy[arrSize];
  for (int i = 0; i < CIller.size(); i++)
  {
    for (int j = 0; j < CIlceler.size(); j++)
    {
      for (int k = 0; k < CMahalleler.size(); k++)
      {
        for (int l = 0; l < COkullar.size(); l++)
        {
          for (int m = 0; m < CSandiklar.size(); m++)
          {
            for (int n = 0; n < _count; n++)
            {
              oy* oy = new ::oy();
              oy->id = index + 1;
              oy->il = CIller[i];
              oy->ilce = CIlceler[j];
              oy->mahalle = CMahalleler[k];
              oy->okul = COkullar[l];
              oy->sandik_no = CSandiklar[m];
              oy->parti = GenerateRandomPartyName();
              Sleep(_delayMs);
              oylar->array[index] = *oy;
              index++;
            }
          }
        }
      }
    }
  }

  return oylar;
}

int main()
{
  cout << "Secim Sistemi Paralel Hesaplama Ornegi!\n\n";
  cout << "Sirali hesaplama algoritmasi calistiriliyor...!\n";
	clock_t seqTimeBegin = clock();
  oy_array* oylar = GenerateRandomData();
  clock_t seqTimeEnd = clock();
  const int elapsedTime = (double(seqTimeEnd - seqTimeBegin) / CLOCKS_PER_SEC);
  printf("Kayit sayisi: %d, Gecen sure: %dsn\n", oylar->length, elapsedTime);
  delete[] oylar->array;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

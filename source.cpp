#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Zakres_1(int zmienna)
{
	if ((zmienna < 1) || (zmienna > 140000))
	{
		cout << "BLAD!!! Liczba okreslajaca ilosc liczb w zestawie jest poza zakresem (zakres od 0 do 140 000). \n Nastapi zamkniecie programu." << endl;
		system("pause");
		exit(0);
	}
}

void Zakres_2(unsigned long zmienna)
{
	if ((zmienna < 0) || (zmienna > 3000000000))
	{
		cout << "BLAD!!! Liczba w zestawie jest poza zakresem (zakres od 0 do 3 000 000 000). \nNastapi zamkniecie programu." << endl;
		system("pause");
		exit(0);
	}
}

int main()
{
	ofstream plik_zapis;
	ifstream plik_odczyt;
	string nazwa;
	int  m, n;
	unsigned long *tab1, *tab2, *tab_wyniki;
	plik_zapis.open("odpowiedz.txt");

	//Otwieranie pliku do odczytu
	int proba = 0;
	do
	{
		cout << "Podaj nazwe pliku do odczytu: ";
		cin >> nazwa;
		plik_odczyt.open(nazwa);
		proba++;
	} while (plik_odczyt.good() == false && proba < 3);

	//Zestaw I
	plik_odczyt >> m;
	Zakres_1(m);	//Funkcja zakres_1
	tab1 = new unsigned long [m];
	unsigned long *wskaznik1 = tab1;
	for (int i = 0; i < m; i++)
	{
		plik_odczyt >> *wskaznik1;
		Zakres_2(*wskaznik1);	//Funkcja zakres_2
		wskaznik1++;
	}

	//Zestaw II
	plik_odczyt >> n;
	Zakres_1(n);	//Funkcja zakres_1
	tab2 = new unsigned long [n];
	unsigned long *wskaznik2 = tab2;
	for (int i = 0; i < n; i++)
	{
		plik_odczyt >> *wskaznik2;
		Zakres_2(*wskaznik2);	//Funkcja zakres_2
		wskaznik2++;
	}

	//Tablica dla wynikow
	int rozmiar = 0;
	tab_wyniki = new unsigned long[rozmiar];

	//Program
	for (int i = 0; i < m; i++)	//petla sterujaca tab1[]
	{
		for (int j = 0; j < n; j++) //petla sterujaca tab2[]
		{
			if (tab1[i] == tab2[j]) //warunek
			{
				//////////////////////////////////////////////////
				//Sprawdzanie powtarzania sie liczb w wynikach////
				//////////////////////////////////////////////////
				bool powtarza = false;
				for (int k = 0; k < rozmiar; k++) //petla sterujaca tab_wyniki[]
				{
					if (tab_wyniki[k] == tab1[i]) //sprawdzanie czy w wynikach powtarza sie liczba
					{
						powtarza = true;
					}
				}

				if (!powtarza) //jesli nie wystpepuje to zapisywane do tab_wyniki[]
				{
					tab_wyniki[rozmiar] = tab1[i];
					rozmiar++;
				}
				//////////////////////////////////////////////////
				//////////////////////////////////////////////////
			}
		}
	}

	//Zapis wynikow do pliku odpowiedz.txt
	plik_zapis << rozmiar << endl;
	for (int i = 0; i < rozmiar; i++)
	{
		plik_zapis << tab_wyniki[i] << endl;
	}

	delete[] tab1;
	delete[] tab2;
	delete[] tab_wyniki;

	plik_odczyt.close();
	plik_zapis.close();
	system("pause");
	return 0;
}

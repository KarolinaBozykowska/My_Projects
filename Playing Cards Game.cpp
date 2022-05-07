// POP 2015-12-17 projekt 1 Bozykowska Karolina EiT 1 160279
// Code::Blocks 13.12 GNU CPP Compiler

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

void generowanie_kart(char karty[52][2]);
void zerowania_planszy(char plansza[21][7][2]);
void losowanie_kart(char plansza[7][7][2], char karty[52][2], char karty_do_losowania[24][2]);
void generowanie_planszy(char macierz_pomocnicza[7][7][2], char karty_do_losowania[24][2]);
void nanoszenie_kart(char plansza[21][7][2], char macierz_pomocnicza[7][7][2]);
void wyswietlanie_planszy(char plansza[21][7][2], char ABCD[4][2], char karty_do_losowania[24][2]);
void komendy(string wczytany_znak, char plansza[21][7][2], char ABCD[4][2], char karty_do_losowania[24][2], char macierz_pomocnicza[7][7][2],int ile_kart_przekladac);
bool czy_mozna_przeniesc_karte(int komenda[2], char plansza[21][7][2], char ABCD[4][2], char karty_do_losowania[24][2]);
void przenoszenie_karty(int komenda[2], char plansza[21][7][2], char ABCD[4][2], char karty_do_losowania[24][2], char macierz_pomocnicza[7][7][2]);
void wyswietl_instrukcje();
bool czy_wygrane(char ABCD[4][2]);
bool sprawdzanie_przegranej(char plansza[21][7][2], char ABCD[4][2], char karty_do_losowania[24][2]);

int main(){

	char plansza[21][7][2];
	char macierz_pomocnicza[7][7][2];
	char karty_do_losowania[24][2];
	char ABCD[4][2];
	for (int i = 0; i < 4; i++){
		ABCD[i][0] = '-';
		ABCD[i][1] = '-';
	}

	generowanie_planszy(macierz_pomocnicza, karty_do_losowania);  //generowanie talii i ustalanie które leżą na stole a które w talii
	zerowania_planszy(plansza);		// wstawianie spacji a później zmienianie ich na macier trójkątna
	nanoszenie_kart(plansza, macierz_pomocnicza);	// odkrywanie pierwdzych kart na macierzy ( po przekątnej)

	string wczytany_znak;	//komendy jakie wczytujemy
	string komendy_historia = ""; // zapamiętywanie wykonanych ruchów
	while(1){

		int ile_kart_przekladac = 0;
		wyswietlanie_planszy(plansza, ABCD, karty_do_losowania);

		if (sprawdzanie_przegranej(plansza, ABCD, karty_do_losowania));
		else {
			cout << "NIE MASZ JUZ RUCHOW!, PRZEGRALES" << endl;
			system("pause");
			exit(1);
		}
		cin.sync();	// usuwanie znaku końca linii z poprzedniego wczytywania, żeby za każdym wczytaniem zaczynał od nowa
		getline(cin, wczytany_znak);
		if (wczytany_znak.size() == 0)continue;
		if (wczytany_znak == "com"){
			int licznik = 0;
			for (int i = 0; i<komendy_historia.size(); i++){
				cout << komendy_historia[i];
				licznik++;
				if (licznik > 15 && komendy_historia[i] == ' '){	// przerzucanie reszty komend na drugą stronę żeby nie wyświetlały się w jednej linii
					cout << endl;
				}
			}
			cout << endl;
			system("pause");
			continue;
		}
		if (wczytany_znak == "help"){
			wyswietl_instrukcje();
			system("pause");
			continue;
		}
		if (wczytany_znak[0] == '*'){
			char pomocnicza[2];
			if (wczytany_znak.size() == 6 && wczytany_znak[1] == '1' && (int)wczytany_znak[2] >= 48 && (int)wczytany_znak[2] <= 51){
				pomocnicza[0] = wczytany_znak[4];
				pomocnicza[1] = wczytany_znak[5];
				ile_kart_przekladac += 10;
				ile_kart_przekladac += ((int)wczytany_znak[2] - 48);
				wczytany_znak = "";		//zapamiętanie i wyzerowanie komendy ile kart przekładać i zostawienie tylko informacji z jakiej kolumny przekładamy kartę
				wczytany_znak += pomocnicza[0];
				wczytany_znak += pomocnicza[1];
			}
			else if (wczytany_znak.size() == 5 && (int)wczytany_znak[1] > 48 && (int)wczytany_znak[1] <= 58){
				pomocnicza[0] = wczytany_znak[3];
				pomocnicza[1] = wczytany_znak[4];
				ile_kart_przekladac = (int)wczytany_znak[1] - 48;
				wczytany_znak = "";
				wczytany_znak += pomocnicza[0];
				wczytany_znak += pomocnicza[1];
			}
			else {
				cout << "Niepoprawna komenda!" << endl;
				system("pause");
				continue;
			}

		}

		komendy_historia += " ";
		komendy_historia += wczytany_znak;

		if (wczytany_znak.size() > 2){
			cout << "Nieodpowiednia dlugosc komendy" << endl;
			system("pause");
			continue;
		}
		if (wczytany_znak.size() == 1)wczytany_znak += ' ';

		wczytany_znak[0] = tolower(wczytany_znak[0]);
		wczytany_znak[1] = tolower(wczytany_znak[1]);

		komendy(wczytany_znak, plansza, ABCD, karty_do_losowania,macierz_pomocnicza, ile_kart_przekladac);

		if (czy_wygrane(ABCD)){
			system("cls");
			cout << "BRAWO, WYGRALES GRE!" << endl;
			system("pause");
			exit(1);
		}

	}

	system("pause");
	return 0;
}

void generowanie_planszy(char macierz_pomocnicza[7][7][2], char karty_do_losowania[24][2]){

	char karty[52][2];
	generowanie_kart(karty);
	losowanie_kart(macierz_pomocnicza, karty, karty_do_losowania);

}

void generowanie_kart(char karty[52][2]){

	for (int i = 0; i < 13; i++){
		if (i<10)karty[i][0] = char(48 + i);
		else karty[i][0] = char(65 + i - 10);
		karty[i][1] = 'x';
	}

	for (int i = 13; i < 26; i++){
		if(i<23)karty[i][0] = char(48 + i - 13);
		else karty[i][0] = char(65 + i - 23);
		karty[i][1] = 'X';
	}

	for (int i = 26; i < 39; i++){
		if (i<36)karty[i][0] = char(48 + i - 26);
		else karty[i][0] = char(65 + i - 36);
		karty[i][1] = 'y';
	}

	for (int i = 39; i < 52; i++){
		if (i<49)karty[i][0] = char(48 + i - 39);
		else karty[i][0] = char(65 + i - 49);
		karty[i][1] = 'Y';
	}

}

void losowanie_kart(char macierz_pomocnicza[7][7][2], char karty[52][2], char karty_do_losowania[24][2]){

	int liczba_dostepnych_kart = 52;

	srand(time(NULL));

	for (int i = 0; i < 7; i++){
		for (int j = 6; j>=0; j--){
			int liczba_pomocnicza = rand() % liczba_dostepnych_kart;
			macierz_pomocnicza[i][j][0] = karty[liczba_pomocnicza][0];
			macierz_pomocnicza[i][j][1] = karty[liczba_pomocnicza][1];


			char karta_na_koniec[2];
			karta_na_koniec[0] = karty[liczba_pomocnicza][0]; // zapamiętuje którą kartę ma przerzucić na koniec
			karta_na_koniec[1] = karty[liczba_pomocnicza][1];



			for (int s = liczba_pomocnicza; s < liczba_dostepnych_kart - 1; s++){ //wylosowaną karte przesuwa na koniec a resztę art zsuwa o 1 w lewo
				karty[s][0] = karty[s + 1][0];
				karty[s][1] = karty[s + 1][1];
			}

			karty[liczba_dostepnych_kart - 1][0] = karta_na_koniec[0];
			karty[liczba_dostepnych_kart - 1][1] = karta_na_koniec[1];  // przypisanie ostatniej karty
			liczba_dostepnych_kart--;
			if (i - j == 0 && i >0)break; // i jest większe od zera żeby program ułożył kartę w punkcie [0,0]
		}
	}

	for (int i = 0; i < 24; i++){
		karty_do_losowania[i][0] = karty[i][0];   // przypisanie pozostałych kart do losowania z talii
		karty_do_losowania[i][1] = karty[i][1];
	}

}

void zerowania_planszy(char plansza[21][7][2]){

	for (int i = 0; i < 21; i++){			// tworzenie planszy złożonej ze spacji
		for (int j = 0; j < 7; j++){
			plansza[i][j][0] = ' ';
			plansza[i][j][1] = ' ';
		}
	}

	for (int i = 0; i < 7; i++){      // tworzenie macierzy trójkątnej górnej
		for (int j = 0; j < 7; j++){
			if (j - i < 0)continue;
			plansza[i][j][0] = '-';
			plansza[i][j][1] = '-';

		}
	}

}

void nanoszenie_kart(char plansza[21][7][2], char macierz_pomocnicza[7][7][2]){

	for (int i = 0, j = 0; i < 7; i++, j++){
		plansza[i][j][0] = macierz_pomocnicza[i][j][0];  // wstawia pierwsze karty wyświetlane na macierzy
		plansza[i][j][1] = macierz_pomocnicza[i][j][1];
	}

}

void wyswietlanie_planszy(char plansza[21][7][2], char ABCD[4][2], char karty_do_losowania[24][2]){

	int max_wyswietlania = 0;
	for (int i = 0; i < 7; i++){   // sprawdzenie długości kolumn i zapamiętywanie dł najdłuższej kolumny ; uzależnienie miejsca w którym zaczyna wczytywanie
		for (int j = 20; j >= 0; j--){
			if (plansza[j][i][0] != ' ' && j > max_wyswietlania){
				max_wyswietlania = j;
			}
		}
	}


	system("cls");
	cout << "E  A  B  C  D  " << endl;
	cout << karty_do_losowania[0][0] << karty_do_losowania[0][1] << " "
		<< ABCD[0][0] << ABCD[0][1] << " "
		<< ABCD[1][0] << ABCD[1][1] << " "
		<< ABCD[2][0] << ABCD[2][1] << " "
		<< ABCD[3][0] << ABCD[3][1] << " " << endl;

	cout << "1  2  3  4  5  6  7  " << endl;
	for (int i = 0; i <= max_wyswietlania; i++){
		for (int j = 0; j < 7; j++){
			cout << plansza[i][j][0] << plansza[i][j][1] << " ";
		}
		cout << endl;
	}

}

void komendy(string wczytany_znak, char plansza[21][7][2], char ABCD[4][2], char karty_do_losowania[24][2], char macierz_pomocnicza[7][7][2], int ile_kart_przekladac){

	if (wczytany_znak[0] == 'e' && wczytany_znak[1] == ' '){
		char pomocnicza[2];
		pomocnicza[0] = karty_do_losowania[0][0];
		pomocnicza[1] = karty_do_losowania[0][1];
		for (int i = 0; i < 23; i++){
			if (i == 22 && karty_do_losowania[i + 1][0] != '-'){
				karty_do_losowania[i][0] = karty_do_losowania[i + 1][0];	// kończy pracę pętli jeżeli dojdzie do końca kart które ma do wylosowania i przypisze pierwszą kartę jako ostatnią
				karty_do_losowania[i][1] = karty_do_losowania[i + 1][1];
				karty_do_losowania[i + 1][0] = pomocnicza[0];
				karty_do_losowania[i + 1][1] = pomocnicza[1];
				break;
			}
			else if (karty_do_losowania[i + 1][0] != '-'){ 					// przerzuca kolejną karte w miejsce poprzedniej
				karty_do_losowania[i][0] = karty_do_losowania[i + 1][0];
				karty_do_losowania[i][1] = karty_do_losowania[i + 1][1];
			}
			else{
				karty_do_losowania[i][0] = pomocnicza[0];  	// kończy pracę pętli jeżeli napotka na sytuację że kolejna karta to kreski i wraca do wartości pierwszej karty którą poprzednio zapisał w pomocniczej
				karty_do_losowania[i][1] = pomocnicza[1];
				break;
			}
		}

	}
	else{
		int komenda[2];
		komenda[0] = (int)wczytany_znak[0] - 48;
		komenda[1] = (int)wczytany_znak[1] - 48;
		string karty_tymczasowe = "";
		if (ile_kart_przekladac != 0){
			int licznik = 0;
			for (int i = 20; i >= 0; i--){
				if (plansza[i][komenda[0] - 1][0] != ' ' && plansza[i][komenda[0] - 1][0] != '-'){
					licznik++;
				}
			}
			if (licznik >= ile_kart_przekladac){
				licznik = ile_kart_przekladac - 1; // -1 ponieważ przy przekłądaniu 4 kart żeby je przełożyć musi najpierw zdjąć 3 karty
				for (int i = 20; i > 0; i--){
					if (plansza[i][komenda[0] - 1][0] != ' ' && plansza[i][komenda[0] - 1][0] != '-'){
						karty_tymczasowe += plansza[i][komenda[0] - 1][1]; // zapisanie w pamięci koloru kart przenoszonych
						karty_tymczasowe += plansza[i][komenda[0] - 1][0]; //zapisanie w pamięci numeru kart przenoszonych
						plansza[i][komenda[0] - 1][0] = ' '; //zerowanie kart występujących przed karta którą chcemy przerzucić żeby komuter ich nie wiedizał
						plansza[i][komenda[0] - 1][1] = ' ';
						licznik--;
					}
					if (licznik == 0)break; // licznik - ilość kart które zdejmujemy
				}
			}
			else{
				cout << "Nie mozna wykonac takiej komendy" << endl;
				system("pause");
				return;
			}
		}
		if (czy_mozna_przeniesc_karte(komenda, plansza, ABCD, karty_do_losowania))	// sprawdzanie gdzie leży przeniesiona karta i ile kart mamy w pamięci jeszcze do przeniesienia
		{
			przenoszenie_karty(komenda, plansza, ABCD, karty_do_losowania, macierz_pomocnicza);
			if (ile_kart_przekladac != 0){
				int licznik = ile_kart_przekladac - 1;
				int pomocnicza = karty_tymczasowe.size()-1;
				for (int i = 0; i < 21; i++){
					if (plansza[i][komenda[1] - 1][0] == ' '){
						plansza[i][komenda[1] - 1][0] = karty_tymczasowe[pomocnicza];
						pomocnicza--;
						plansza[i][komenda[1] - 1][1] = karty_tymczasowe[pomocnicza];
						pomocnicza--;
						licznik--;
					}
					if (licznik == 0)break;
				}
			}

		}
		else {
			if (ile_kart_przekladac != 0){		//jeżeli nie można przenieść kart sprawdza miejsce z którego pobraliśmy karty i odkłada je na miejsce
				int licznik = ile_kart_przekladac - 1;
				int pomocnicza = karty_tymczasowe.size() - 1;
				for (int i = 0; i < 21; i++){
					if (plansza[i][komenda[0] - 1][0] == ' '){
						plansza[i][komenda[0] - 1][0] = karty_tymczasowe[pomocnicza];
						pomocnicza--;
						plansza[i][komenda[0] - 1][1] = karty_tymczasowe[pomocnicza];
						pomocnicza--;
						licznik--;
					}
					if (licznik == 0)break;
				}
			}
		}
	}
}

bool czy_mozna_przeniesc_karte(int komenda[2], char plansza[21][7][2], char ABCD[4][2], char karty_do_losowania[24][2]){

	char karta_do_przeniesienia[2];
	switch (komenda[0]){
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		for (int i = 20; i >= 0; i--){
			if (plansza[i][komenda[0] - 1][0] != ' ' && plansza[i][komenda[0] - 1][0] != '-'){ 	//pobranie karty którą będzie przerzucać
				karta_do_przeniesienia[0] = plansza[i][komenda[0] - 1][0];
				karta_do_przeniesienia[1] = plansza[i][komenda[0] - 1][1];
				break;
			}
			else if (i == 0){
				cout << "Nie mozna wykonac takiego ruchu!" << endl;
				system("pause");
				return false;
			}
		}
		break;
	case 53:
		if (karty_do_losowania[0][0] == '-'){	// dla wartości "e"
			cout << "Nie mozna wykonac tego ruchu, poniewaz nie masz juz kart!" << endl;
			system("pause");
			return false;
		}
		else{
			karta_do_przeniesienia[0] = karty_do_losowania[0][0];
			karta_do_przeniesienia[1] = karty_do_losowania[0][1];
		}
		break;
	default:
		cout << "Komenda jest niepoprawna!" << endl;
		system("pause");
		return false;
	}
	//-------------------------------------------------------------------------------
	switch (komenda[1]){
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		for (int i = 20; i > 0; i--){
			if (plansza[i - 1][komenda[1] - 1][0] != ' ' && plansza[i - 1][komenda[1] - 1][0] != '-'){
				if ((int)plansza[i - 1][komenda[1] - 1][0] == (int)karta_do_przeniesienia[0] + 1){	//sprawdzanie czy kolejna karta jesdt o 1 większa od poprzedniej
					if (((int)plansza[i - 1][komenda[1] - 1][1] % 2) != ((int)karta_do_przeniesienia[1] % 2 )){ // sprawdzanie czy reszta z dzielenia jest równa 0 czy coś innego, X oraz x mają parzyste wartości w tablicy Ascii, Y oraz y mają wartości nieparzyste
						break;
					}
					else{
						cout << "Kolory kart nie zgadzaja sie!" << endl;
						system("pause");
						return false;
					}
				}
				else if ((int)plansza[i - 1][komenda[1] - 1][0] == 65 && ((int)karta_do_przeniesienia[0] == 57)){
					if ((int)plansza[i - 1][komenda[1] - 1][1] % 2 != (int)karta_do_przeniesienia[1] % 2){
						break;
					}
					else{
						cout << "Kolory kart nie zgadzaja sie!" << endl;
						system("pause");
						return false;
					}

				}
				else{
					cout << "Nie mozesz wykonac takiego ruchu!" << endl;
					system("pause");
					return false;
				}

			}
			else if (i == 1 && plansza[i - 1][komenda[1] - 1][0] == '-'
				&& plansza[i][komenda[1] - 1][0] == ' ' && (int)karta_do_przeniesienia[0] == 'C'){
				break;
			}
			else if (i == 1){
				cout << "Nie mozna przeniesc tej karty we wskazane miejsce!" << endl;
				system("pause");
				return false;
			}

		}
		break;
	case 49:   // wartości A,B,C,D w tabeli Ascii
	case 50:
	case 51:
	case 52:
		if (ABCD[komenda[1] - 49][0] == '-' && karta_do_przeniesienia[0] == '0');
		else if ((int)ABCD[komenda[1] - 49][0] == (int)karta_do_przeniesienia[0] - 1 && (int)ABCD[komenda[1] - 49][1] == (int)karta_do_przeniesienia[1]); // przy przerzucaniu 0-9
		else if (ABCD[komenda[1] - 49][0] == '9' && (int)karta_do_przeniesienia[0] == 65 && (int)ABCD[komenda[1] - 49][1] == (int)karta_do_przeniesienia[1]); //przy przerzucaniu ABCD
		else {
			cout << "Nie mozna wykonac danej komendy, poniewaz karty sie nie zgadzaja!" << endl;
			system("pause");
			return false;
		}
		break;
	default:
		cout << "Komenda jest niepoprawna!" << endl;
		system("pause");
		return false;
	}


	return true;
}

void przenoszenie_karty(int komenda[2], char plansza[21][7][2], char ABCD[4][2], char karty_do_losowania[24][2], char macierz_pomocnicza[7][7][2]){

	char karta_do_przeniesienia[2];
	switch (komenda[0]){
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		for (int i = 20; i >= 0; i--){
			if (plansza[i][komenda[0] - 1][0] != ' ' && plansza[i][komenda[0] - 1][0] != '-'){
				karta_do_przeniesienia[0] = plansza[i][komenda[0] - 1][0];
				karta_do_przeniesienia[1] = plansza[i][komenda[0] - 1][1];
				plansza[i][komenda[0] - 1][0] = ' ';
				plansza[i][komenda[0] - 1][1] = ' ';
				if (i != 0 && plansza[i - 1][komenda[0] - 1][0] == '-'){
					plansza[i - 1][komenda[0] - 1][0] = macierz_pomocnicza[i - 1][komenda[0] - 1][0];
					plansza[i - 1][komenda[0] - 1][1] = macierz_pomocnicza[i - 1][komenda[0] - 1][1];
				}
				if (i == 0){
					plansza[i][komenda[0] - 1][0] = '-';
					plansza[i][komenda[0] - 1][1] = '-';
				}
				break;
			}
		}
		break;
	case 53:
		karta_do_przeniesienia[0] = karty_do_losowania[0][0];
		karta_do_przeniesienia[1] = karty_do_losowania[0][1];
		for (int i = 0; i < 23; i++){
			if (karty_do_losowania[i + 1][0] != '-' && i != 22){
				karty_do_losowania[i][0] = karty_do_losowania[i + 1][0];
				karty_do_losowania[i][1] = karty_do_losowania[i + 1][1];
			}
			else if (karty_do_losowania[i + 1][0] == '-'){
				karty_do_losowania[i][0] = '-';
				karty_do_losowania[i][1] = '-';
			}
			else {
				karty_do_losowania[i][0] = karty_do_losowania[i + 1][0];
				karty_do_losowania[i][1] = karty_do_losowania[i + 1][1];
				karty_do_losowania[i + 1][0] = '-';
				karty_do_losowania[i + 1][1] = '-';
			}
		}

		break;
	}
	//-------------------------------------------------------------------------------------------------------------------
	switch (komenda[1]){
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		for (int i = 20; i > 0; i--){
			if (plansza[i - 1][komenda[1] - 1][0] != ' ' && plansza[i - 1][komenda[1] - 1][0] != '-'){
				plansza[i][komenda[1] - 1][0] = karta_do_przeniesienia[0];
				plansza[i][komenda[1] - 1][1] = karta_do_przeniesienia[1];
				break;
			}
			else if (plansza[i - 1][komenda[1] - 1][0] == '-'){
				plansza[i-1][komenda[1] - 1][0] = karta_do_przeniesienia[0];
				plansza[i-1][komenda[1] - 1][1] = karta_do_przeniesienia[1];
			}
		}break;
	case 49:
	case 50:
	case 51:
	case 52:
		ABCD[komenda[1] - 49][0] = karta_do_przeniesienia[0];
		ABCD[komenda[1] - 49][1] = karta_do_przeniesienia[1];
		break;
	}

}

void wyswietl_instrukcje(){

	system("cls");
	cout << "-----INSTRUKCJA-----" << endl;
	cout << "Aby przeniesc pojedyncza karte nalezy" << endl;
	cout << "wpisac komende skladajaca sie z dwoch znakow." << endl;
	cout << "Pierwsza litera odpowiada za miejsce skad chcemy" << endl;
	cout << "pobrac karte, a druga za miejsce gdzie chcemy ja polozyc." << endl;
	cout << "Wciskajac jedynie litere \"e\" mozemy przewijac karty" << endl;
	cout << "ktore sa w talii do naszej dyspozycji. Aby je podniesc" << endl;
	cout << "nalezy wpisac np \"e1\" i wtedy pierwsza karte z talii," << endl;
	cout << "przerzucimy na pierwsza kolumne. Aby sciagnac caly segment" << endl;
	cout << "nalezy uzyc nastepujaca kombinacje. Np \"*3 23\". kombinacja" << endl;
	cout << "ta sprawi, ze pobierzemy 3 pierwsze karty z kolumny 2 i " << endl;
	cout << "i przelozymy je na kolumne numer 3. Oczywiscie jesli bedzie" << endl;
	cout << "to zgodne z przepisami. Komenda \"com\" mozemy podejrzec swoje" << endl;
	cout << "wczesniejsze wpisane komendy. POWODZENIA!" << endl;
};

bool czy_wygrane(char ABCD[4][2]){

	if (ABCD[0][0] == 'C' &&ABCD[1][0] == 'C' && ABCD[2][0] == 'C' && ABCD[3][0] == 'C') return true;
	else return false;
}

bool sprawdzanie_przegranej(char plansza[21][7][2], char ABCD[4][2], char karty_do_losowania[24][2]){

	char karta_do_sprawdzenia[2];
	for (int i = 0; i < 7; i++){
		for (int k = 20; k>=1; k--){
			if (plansza[k][i][0] != ' ' && plansza[k][i][0] != '-' && plansza[k - 1][i][0] == '-'){
				karta_do_sprawdzenia[0] = plansza[k][i][0];
				karta_do_sprawdzenia[1] = plansza[k][i][1];
				break;
			}
			else if (k == 1 && plansza[k][i][0] == ' ' && plansza[k - 1][i][0] != '-'){
				karta_do_sprawdzenia[0] = plansza[k - 1][i][0];
				karta_do_sprawdzenia[1] = plansza[k - 1][i][1];
			}
			else continue;
		}
		for (int j = 0; j < 7; j++){
			if (j == i)continue;
			for (int k = 20; k>=1; k--){
				if (plansza[k][j][0] == ' ' && plansza[k - 1][j][0] == char((int)karta_do_sprawdzenia[0] + 1)
					&& (int)plansza[k - 1][j][1]%2 != (int)karta_do_sprawdzenia[1]%2){
					return true;
				}
				else if (plansza[k][j][0] == ' ' && plansza[k - 1][j][0] == 'A' && karta_do_sprawdzenia[0] == '9'
					&& (int)plansza[k - 1][j][1] % 2 != (int)karta_do_sprawdzenia[1] % 2){
					return true;
				}
				else if (k == 1 && karta_do_sprawdzenia[0] == 'C' && plansza[k - 1][j][0] == '-' && plansza[k][j][0] == ' '){
					return true;
				}
			}
		}
	}

	for (int i = 0; i < 24; i++){
		if (karty_do_losowania[i][0] == '-')break;
		karta_do_sprawdzenia[0] = karty_do_losowania[i][0];
		karta_do_sprawdzenia[1] = karty_do_losowania[i][1];
		for (int j = 0; j < 7; j++){
			for (int k = 20; k >= 1; k--){
				if (plansza[k][j][0] == ' ' && plansza[k - 1][j][0] == char((int)karta_do_sprawdzenia[0] + 1)
					&& (int)plansza[k - 1][j][1] % 2 != (int)karta_do_sprawdzenia[1] % 2){
					return true;
				}
				else if (plansza[k][j][0] == ' ' && plansza[k - 1][j][0] == char(65) && karta_do_sprawdzenia[0] == '9'
					&& (int)plansza[k - 1][j][1] % 2 != (int)karta_do_sprawdzenia[1] % 2){
					return true;
				}
				else if (k == 1 && karta_do_sprawdzenia[0] == 'C' && plansza[k - 1][j][0] == '-' && plansza[k][j][0] == ' '){
					return true;
				}
			}
		}
		for (int j = 0; j < 4; j++){
			if (ABCD[j][0] == char((int)karta_do_sprawdzenia[0] - 1) && ABCD[j][1] == karta_do_sprawdzenia[1]){
				return true;
			}
			else if (ABCD[j][0] == '9' && karta_do_sprawdzenia[0] == 'A' && ABCD[j][1] == karta_do_sprawdzenia[1]){
				return true;
			}
		}
	}

	for (int i = 0; i < 7; i++){
		for (int k = 20; k >= 1; k--){
			if (plansza[k][i][0] == ' ' && plansza[k - 1][i][0] != ' ' && plansza[k - 1][i][0] != '-'){
				karta_do_sprawdzenia[0] = plansza[k - 1][i][0];
				karta_do_sprawdzenia[1] = plansza[k - 1][i][1];
				break;
			}
		}
		for (int j = 0; j < 4; j++){
			if (ABCD[j][0] == char((int)karta_do_sprawdzenia[0] - 1) && ABCD[j][1] == karta_do_sprawdzenia[1]){
				return true;
			}
			else if (ABCD[j][0] == '9' && karta_do_sprawdzenia[0] == 'A' && ABCD[j][1] == karta_do_sprawdzenia[1]){
				return true;
			}
		}
	}
	return false;
}

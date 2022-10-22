#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <Windows.h>
#include <bitset>
using namespace std;

void MyEncryption(char Ins[64], unsigned short OutCoding[64]);

enum  ConsoleColor : unsigned int
{							//0000 IRGB  
	Black = 0x00,			//0000 0000
	Blue = 0x01,			//0000 0001
	Green = 0x02,			//0000 0010
	Cyan = 0x03,			//0000 0011
	Red = 0x04,				//0000 0100
	Magenta = 0x05,			//0000 0101
	Brown = 0x06,			//0000 0110
	LightGray = 0x07,		//0000 0111 
	DarkGray = 0x08,		//0000 1000
	LightBlue = 0x09,		//0000 1001
	LightGreen = 0x0a,		//0000 1010
	LightCyan = 0x0b,		//0000 1011
	LightRed = 0x0c,		//0000 1100
	LightMagenta = 0x0d,	//0000 1101
	Yellow = 0x0e,			//0000 1110
	White = 0x0f,			//0000 1111
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Console, (WORD)((background << 4) | text));
}

void InputColor()
{
	int kText, kBackground;
	do {
		cout << "Select the text and background color:\n";
		cout << "0.	Black		\n"
			<< "1.	Blue		\n"
			<< "2.	Green		\n"
			<< "3.	Cyan		\n"
			<< "4.	Red			\n"
			<< "5.	Magenta		\n"
			<< "6.	Brown		\n"
			<< "7.	LightGray	\n"
			<< "8.	DarkGray	\n"
			<< "9.	LightBlue	\n"
			<< "10.LightGreen	\n"
			<< "11.LightCyan	\n"
			<< "12.LightRed	\n"
			<< "13.LightMagen	\n"
			<< "14.Yellow		\n"
			<< "15.White		\n";

		cin >> kText >> kBackground;
		if (kText <= 15 || kBackground <= 15)
			SetColor(ConsoleColor(kText), ConsoleColor(kBackground));
		else
			cout << "Uncorrect value(es)";
	} while (kText > 15 || kBackground > 15);
	cin.get();

}

void MenuExamples() {

	cout << "    Examples   \n";
	cout << "    1.  Expression calculation using bitwise operations \n";
	cout << "    2.  Encryption\n";
	cout << "    3.	 Encryption structure \n";
	cout << "    4.	 Optional - Bit image 8x8 \n";
	cout << "    5.  Change the text and background color\n";
	cout << "    6.  Exit \n";

}

void Example1()
{
	system("chcp 1251");
	cout << " Обчислення виразів з використанням побітових операцій  \n";
	int a, b, c, d, x, y;
	cout << "Вираз : " << endl <<
		"            x = 33 * b + ((d*15 + 12*a)/512) - 65*c + d*14" << endl <<
		"            x = b + (b << 5) + (((d << 4) - d + (a << 3) + (a << 2)) >> 9) - (c << 6) - c + ((d << 4) - (d << 1 ))" << endl;

	cout << " Введiть a b c d " << endl;
	cin >> a >> b >> c >> d;
	cout << endl;
	auto st = cin.rdstate();
	if (st != cin.goodbit) { cin.clear(); cout << " error \n"; cin.get(); cin.get(); return; }

	x = b + (b << 5) + (((d << 4) - d + (a << 3) + (a << 2)) >> 9) - (c << 6) - c + ((d << 4) - (d << 1));
	y = b * 33 + ((d * 15 + 12 * a) / 512) - c * 65 + d * 14;

	cout << " a= " << a << "  b= " << b << " c= " << c << " d= " << d << endl;
	cout << "  x1(побітові операції)= " << x << endl << "  x2(перевірка)= " << y << endl;
	cin.get();
}

void decimalToBinary(unsigned short OutCoding[128], int index) {
	char out[17];
	int i, in, ix, n = 0;
	double x;

	in = OutCoding[index];
	auto st = cin.rdstate();
	if (st != cin.goodbit) { cin.clear(); cout << " error \n"; cin.get(); cin.get(); return; }

	if (in != 0) {
		x = in;
		do {
			x = x / 2.;
			ix = (int)x;
			if ((x - ix) != 0) out[n] = '1';
			else out[n] = '0';
			n++;
			x = ix;
		} while (x >= 1);
	}

	for (i = n - 1; i >= 0; i--)
		cout << out[i];
	cout << endl;
	cin.get();
}

void decimalToBinarySt(unsigned short elem) {
	char out[17];
	int i, in, ix, n = 0;
	double x;

	in = elem;
	auto st = cin.rdstate();
	if (st != cin.goodbit) { cin.clear(); cout << " error \n"; cin.get(); cin.get(); return; }

	if (in != 0) {
		x = in;
		do {
			x = x / 2.;
			ix = (int)x;
			if ((x - ix) != 0) out[n] = '1';
			else out[n] = '0';
			n++;
			x = ix;
		} while (x >= 1);
	}

	for (i = n - 1; i >= 0; i--)
		cout << out[i];
	cout << endl;
	cin.get();
}

/*
6. Задано текст до 128 символів.Доповнити пробілами до 128 символів.Шифрувати тексти
таким чином, щоб кожний символ тексту записувався у два байта.Два байта мають таку
структуру :
0 біт – біт парності(1 біт)
у бітах 1 - 8 ASCII - код букви(8 біт),
у бітах 9 - 15 позиція букви у рядку(7 біти),
*/

void MyEncryption(char InS[128], unsigned short OutCoding[128])
{
	unsigned char c;
	unsigned short r, t, i, b, l;
	short j;
	for (i = 0; i < 128; i++)            //розглянемо для прикладу 5 ітерацію циклу, тобто маємо 5 символ, наприклад хай це буде символ 's' 
	{
		r = 0;							// 0000 0000 0000 0000
		c = InS[i];                     // s - 0x73 = 0111 0011
		t = c;
		r |= c << 1;					// 0000 0000 1110 0110
		r |= i << 9;					// 0000 1010 1110 0110	if i=5 -> 0000 0000 0000 0101

		t = 1;
		b = 0;
		for (int j = 0; j < 16; j++)         // обчислення біта парності
		{
			if (r & t) {
				if (b == 0) b = 1; else b = 0;
			}
			t <<= 1;
		}
		r |= b;							// 0000 1010 1110 0111	if i=5 -> 0000 0000 0000 0101


		OutCoding[i] = r;
	}
}

void Example2()
{
	unsigned short OutCoding[128];
	string string_text;

	cout << "Enter text: ";
	getline(cin, string_text);

	char char_text[128];
	for (int i = 0; i < string_text.length(); i++)
	{
		char_text[i] = string_text[i];
		cout << char_text[i];
	}
	cout << "\n";
	if (string_text.length() != 128)  // доповним нулями
	{
		for (int i = string_text.length(); i < 128; i++)
		{
			char_text[i] = ' ';
		}
	}

	MyEncryption(char_text, OutCoding);
	cout << "\n Encription elements : ";
	for (size_t i = 0; i < string_text.length(); i++)
	{
		cout << i << " --> ";
		decimalToBinary(OutCoding, 5);
		cout << endl;
	}

}


struct TextCode {
	unsigned short kb : 8;
	unsigned short posrow : 7;
	unsigned short bitp : 1;
};

unsigned char pbit(unsigned char c)
{
	unsigned char t = 1, b = 0;
	for (int j = 0; j < 8; j++)         // обчислення біта парності
	{
		if (c & t) {
			if (b == 0) b = 1; else b = 0;
		}
		t <<= 1;
	}
	return b;
}

/*
6. Задано текст до 128 символів.Доповнити пробілами до 128 символів.Шифрувати тексти
таким чином, щоб кожний символ тексту записувався у два байта.Два байта мають таку
структуру :
0 біт – біт парності(1 біт)
у бітах 1 - 8 ASCII - код букви(8 біт),
у бітах 9 - 15 позиція букви у рядку(7 біти),
*/

void MyEncryptionS(char InS[128], TextCode OutCoding[128])
{
	unsigned char c;
	unsigned short r, t, i;
	short j;
	for (i = 0; i < 128; i++)            //
	{
		c = InS[i];                     // s - 0x73 = 0111 0011
		OutCoding[i].posrow = i;        //	позиція букви в рядку
		OutCoding[i].kb = c;			//	код букви

		r = pbit(c);
		t = pbit(static_cast<unsigned char>(i));
		OutCoding[i].bitp = r ^ t;		//	біт парності

	}
}


void Example3() {
	TextCode OutCoding[128];
	string string_text;

	cout << "Enter text: ";

	getline(cin, string_text);

	char char_text[128];
	//	strcpy(char_text, text.c_str());
	for (int i = 0; i < string_text.length(); i++)
	{
		char_text[i] = string_text[i];
		cout << char_text[i];
	}
	cout << "\n";
	if (string_text.length() != 128)			// доповним нулями
	{
		for (int i = string_text.length(); i < 128; i++)
		{
			char_text[i] = ' ';
		}
	}

	MyEncryptionS(char_text, OutCoding);
	cout << "\n Encription elements : \n";
	for (size_t i = 0; i < string_text.length(); i++)
	{
		cout << i << " -->  bit parnosti = ";
		decimalToBinarySt(OutCoding[i].bitp);
		cout << "; kod bukwu = ";
		decimalToBinarySt(OutCoding[i].kb);
		cout << "; pos riadka = ";
		decimalToBinarySt(OutCoding[i].posrow);

		cout << endl;
	}
}


// 4 ЗАВДАННЯ!

/*	Бітовий образ 8х8 задається вісьмома байтами, кожен з яких задає одну скан - лінію з 8 точок
(0 - 7 біти) : нульовий біт – біла точка, одиничний – чорна.За вказаними користувачем
вісьмома байтами вивести на екран(у текстовому режимі) відповідне йому зображення.Для
відображення білих точок використати символ “пробіл”, для відображення чорних – символ
“О”
*/

struct bipMap {
	byte bit0 : 1;
	byte bit1 : 1;
	byte bit2 : 1;
	byte bit3 : 1;
	byte bit4 : 1;
	byte bit5 : 1;
	byte bit6 : 1;
	byte bit7 : 1;
};

void optional()
{
	short unsigned b[8];
	bipMap image[8];
	short unsigned t = 0;
	short unsigned mask = 1;
	cout << "Enter 8 bytes to form the image (input only numbers):";
	for (size_t i = 0; i < 8; i++)
	{
		cin >> b[i];
	}
	for (size_t i = 0; i < 8; i++)
	{
		image[i].bit0 = (b[i] & mask);
		b[i] = b[i] >> 1;
		image[i].bit1 = (b[i] & mask);
		b[i] = b[i] >> 1;
		image[i].bit2 = (b[i] & mask);
		b[i] = b[i] >> 1;
		image[i].bit3 = (b[i] & mask);
		b[i] = b[i] >> 1;
		image[i].bit4 = (b[i] & mask);
		b[i] = b[i] >> 1;
		image[i].bit5 = (b[i] & mask);
		b[i] = b[i] >> 1;
		image[i].bit6 = (b[i] & mask);
		b[i] = b[i] >> 1;
		image[i].bit7 = (b[i] & mask);
	}

	for (size_t i = 0; i < 8; i++)
	{
		if (image[i].bit0 == 1)
			cout << "O";
		else
			cout << " ";

		if (image[i].bit1 == 1)
			cout << "O";
		else
			cout << " ";

		if (image[i].bit2 == 1)
			cout << "O";
		else
			cout << " ";

		if (image[i].bit3 == 1)
			cout << "O";
		else
			cout << " ";

		if (image[i].bit4 == 1)
			cout << "O";
		else
			cout << " ";

		if (image[i].bit5 == 1)
			cout << "O";
		else
			cout << " ";

		if (image[i].bit6 == 1)
			cout << "O";
		else
			cout << " ";

		if (image[i].bit7 == 1)
			cout << "O";
		else
			cout << " ";

		cout << endl;
	}
}


void Examples() {
	char ch = '5';
	do {
		MenuExamples();

		ch = cin.get();
		cin.get();

		switch (ch) {
		case '1':
			Example1();
			break;
		case '2':
		{
			Example2();
			cin.get();
			break;
		}
		case '3':
			Example3();
			cin.get();
			break;
		case '4':
			optional();
			cin.get();
			break;

		case '5':
			InputColor();
			break;

		case '6': cout << "end...";
		}


	} while (ch != '6');
}




int main() {

	Examples();

}
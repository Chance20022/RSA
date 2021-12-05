#include <iostream>
#include <string>

long int openCipher(long int);
long int takeSimpleNumber(long int, long int);
long int revModule(long int, long int);
int publicCipher(int, long int, long int);
int privateCipher(int, long int, long int);

int main()
{
	long int p = 0, q = 0;

	std::cout << "Enter p: "; 
	std::cin >> p;
	std::cout << "Enter q: "; 
	std::cin >> q;

	// приготовление ключей
	
	long int n = p * q;
	long int Ailer = (p - 1) * (q - 1);

	std::cout << "n = " << n << " formula Ailer: f(n) = " << Ailer << std::endl << std::endl;	

	long int e = openCipher(Ailer); // Вычисление открытого ключа
	if (e == -1) {
		std::cout << "Wrong with open cipher!" << std::endl;
		return 0;
	}

	long int d = revModule(e, Ailer);
	if (d == -1) {
		std::cout << "Wrong with reverse module!";
		return 0;
	}

	std::cout << "Your keys:" << std::endl << "public key: [ n = " << n << ", e = " << e << " ]" << std::endl << "private key: [ n = " << n << ", d = " << d << " ]" << std::endl << std::endl;

	// зашифровка

	std::cout << "Enter your massage: ";
	std::string massage = "";
	std::cin.ignore();
	std::getline(std::cin, massage);

	for (int i = 0; i < massage.length(); i++) {
		int chNum = publicCipher(massage[i], e, n);
		massage[i] = chNum;
	}

	std::cout << "Your cippher text: " << massage << std::endl;

	// расшифрока

	for (int i = 0; i < massage.length(); i++) {
		massage[i] = privateCipher(massage[i], d, n);
	}

	std::cout << "Your original text: " << massage;
}

long int openCipher(long int f) {
	for (long int e = 3; e < f-1; e++) {
		if (takeSimpleNumber(e, f) == 1)
		{
			return e;
		}
	}

	return -1;
}

long int takeSimpleNumber(long int e, long int f) {

	long int myTemp = e;

	while (e > 0)
	{
		myTemp = e;
		e = f % e;
		f = myTemp;
	}

	return f;
}

long int revModule( long int e, long int f) {
	long int x = 0;
	for (int i = 0; i < f; i++) {
		x = (e*i) % f;
		if (x == 1) return i;
	}
	return -1;
}

int publicCipher(int ch, long int e, long int n) {
	int m = ch - 97;
	int answer = 1;
	for (int i = 0; i < e; i++) {
		answer = answer * m;
		answer = m % n;
	}
	return answer;
}

int privateCipher(int ch, long int d, long int n) {
	int m = ch;
	int answer = 1;
	for (int i = 0; i < d; i++) {
		answer = answer * m;
		answer = m % n;
	}
	return answer+97;
}
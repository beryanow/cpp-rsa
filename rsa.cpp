#include <iostream>
#include <cmath>
#include <string>
#include <vector>

bool isPrime(long number);
long evaluateCoprimeExponent(long eulerFunctionResult);
long evaluateGreatestCommonDivisor(long firstNumber, long secondNumber);
long evaluateModularMultiplicativeInverse(long number, long modulus, long congruentToValue);
long encrypt(long messageToEncrypt, long e, long n);
long decrypt(long messageToDecrypt, long d, long n);

int main() {
    long p, q;
    long t;
    long e, d, n;

    std::vector<long> encryptedText = std::vector<long>();
    std::vector<long> decryptedText = std::vector<long>();

    std::cout << "Добро пожаловать в мир RSA!" << std::endl << std::endl;

    // Шаг 1. Выбираются два различных простых числа p и q заданного размера.
    bool isPrimeFlag;

    do {
        std::cout << "Введите простое число p:" << std::endl;
        std::cin >> p;

        isPrimeFlag = isPrime(p);

        if (!isPrimeFlag) {
            std::cout << "Введённое число p не является простым" << std::endl;
        }
    } while (!isPrimeFlag);

    do {
        std::cout << "Введите простое число q:" << std::endl;
        std::cin >> q;

        isPrimeFlag = isPrime(q);

        if (!isPrimeFlag) {
            std::cout << "Введённое число q не является простым" << std::endl;
        }
    } while (!isPrimeFlag);

    // Шаг 2. Вычисляется произведение n = p ⋅ q, которое называется модулем.
    n = p * q;
    std::cout << "Результат произведения p * q = " << n << std::endl;

    // Шаг 3. Вычисляется значение функции Эйлера t(n) = (p − 1) * (q − 1) от числа n.
    t = (p - 1) * (q - 1);
    std::cout << "Результат вычисления функции Эйлера (p − 1) * (q − 1) = " << t << std::endl;

    // Шаг 4. Вычисляется целое число e (1 < e < φ(n)), взаимно простое со значением функции Эйлера φ(n), которое называется открытой экспонентой.
    e = evaluateCoprimeExponent(t);

    // Шаг 5. Вычисляется число d, мультипликативно обратное к числу e по модулю φ(n), то есть удовлетворяющее сравнению d * e ≡ 1 (mod φ(n)).
    d = evaluateModularMultiplicativeInverse(e, t, 1);

    // Шаг 6. Пара (e, n) публикуется в качестве открытого ключа RSA.
    std::cout << "Публичный ключ RSA -> (e = " << e << ", n = " << n << ")" << std::endl;

    // Шаг 7. Пара (d, n) играет роль закрытого ключа RSA и держится в секрете.
    std::cout << "Приватный ключ RSA -> (d = " << d << ", n = " << n << ")" << std::endl;

    // Шаг 8. Шифрование сообщения.
    std::cout << "Введите сообщение для шифрования:" << std::endl;
    std::cin.ignore();

    std::string message;
    std::getline(std::cin, message);

    std::cout << "Введённое сообщение: " << message << std::endl;

    for (char messageCharacter : message) {
        encryptedText.push_back(encrypt(messageCharacter, e, n));
    }

    std::cout << "Зашифрованное сообщение: ";

    for (long encryptedCharacter : encryptedText) {
        std::cout << (char) encryptedCharacter;
    }

    std::cout << std::endl;

    // Шаг 9. Дешифрование сообщения.

    for (long encryptedCharacter : encryptedText) {
        decryptedText.push_back(decrypt(encryptedCharacter, d, n));
    }

    std::cout << "Дешифрованное сообщение: ";

    for (long decryptedCharacter : decryptedText) {
        std::cout << (char) decryptedCharacter;
    }

    std::cout << std::endl;

    return 0;
}

bool isPrime(long number) {
    long numberSquareRoot = (long) sqrt((long double) number);

    for (long probableDivisor = 2; probableDivisor <= numberSquareRoot; probableDivisor++) {
        if (number % probableDivisor == 0) {
            return false;
        }
    }

    return true;
}

long int evaluateCoprimeExponent(long eulerFunctionResult) {
    for (long coprimeExponent = 2; coprimeExponent < eulerFunctionResult; coprimeExponent++) {
        if (evaluateGreatestCommonDivisor(coprimeExponent, eulerFunctionResult) == 1) {
            return coprimeExponent;
        }
    }

    return -1;
}

long int evaluateGreatestCommonDivisor(long firstNumber, long secondNumber) {
    while (firstNumber > 0) {
        long temp = firstNumber;
        firstNumber = secondNumber % firstNumber;
        secondNumber = temp;
    }

    return secondNumber;
}

long int evaluateModularMultiplicativeInverse(long number, long modulus, long congruentToValue) {
    long relevantMultiplicationResult = congruentToValue;

    while (true) {
        relevantMultiplicationResult += modulus;

        if (relevantMultiplicationResult % number == 0) {
            return relevantMultiplicationResult / number;
        }
    }
}

long encrypt(long messageToEncrypt, long e, long n) {
    long encryptedMessage = 1;

    for (long powTime = 0; powTime < e; powTime++) {
        encryptedMessage *= messageToEncrypt;
        encryptedMessage %= n;
    }

    return encryptedMessage;
}

long decrypt(long messageToDecrypt, long d, long n) {
    long decryptedMessage = 1;

    for (long powTime = 0; powTime < d; powTime++) {
        decryptedMessage *= messageToDecrypt;
        decryptedMessage %= n;
    }

    return decryptedMessage;
}


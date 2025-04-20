#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int celFahr(int T);
int fahrCel(int T);
double usdBrl(int n);
double brlUsd(int n);
int horaMinuto(int t);
int minutoSegundo(int t);

int main() {
    while (true) {
        cout << "--- Conversor de Unidades ---" << '\n';
        cout << "Escolha o tipo de conversão: " << '\n';
        cout << "1. Temperatura\n" << "2. Moeda\n" << "3. Tempo\n" << "4. Sair\n";
        cout << "Opção: ";
        int opt, n;
        cin >> opt;

        if (opt == 1) {
            cout << "--- Conversor de Temperatura ---\n";
            cout << "1. Celsius -> Fahrenheit\n" << "2. Fahrenheit -> Celsius\n";
            cout << "Opção: ";
            cin >> opt;
            switch (opt) {
                case 1:
                    cout << "Digite o valor em Celsius: ";
                    cin >> n;
                    cout << "Resultado: " << celFahr(n) << "°F" << '\n';
                    break;
                case 2:
                    cout << "Digite o valor em Fahrenheit: ";
                    cin >> n;
                    cout << "Resultado: " << fahrCel(n) << "°C" << '\n';
                    break;
            }
        } else if (opt == 2) {
            cout << "--- Conversor de Moeda ---\n";
            cout << "1. Dólar -> Real\n" << "2. Real -> Dólar\n";
            cout << "Opção: ";
            cin >> opt;
            switch (opt) {
                case 1:
                    cout << "Valor em Dólar: ";
                    cin >> n;
                    cout << "Resultado: R$" << usdBrl(n) << '\n';
                    break;
                case 2:
                    cout << "Valor em Real: ";
                    cin >> n;
                    cout << "Resultado: US$" << brlUsd(n) << '\n';
                    break;
            }
        } else if (opt == 3) {
            cout << "1. Hora(s) -> Minuto(s)\n" << "2. Minuto(s) -> Segundo(s)\n";
            cout << "Opção: ";
            cin >> opt;
            switch (opt) {
                case 1:
                    cout << "Hora(s): ";
                    cin >> n;
                    cout << "Resultado: " << n * 60 << " Minuto(s)\n";
                    break;
                case 2:
                    cout << "Minuto(s): ";
                    cin >> n;
                    cout << "Resultado: " << n * 60 << " Segundo(s)\n";
                    break;
            }
        } else if (opt == 4) {
            cout << "Saindo..." << '\n';
            return 0;
        }
        cout << '\n';
    }
}

int celFahr(int T) {
    return T * 9/5 + 32;
}
int fahrCel(int T) {
    return (T - 32) /9 * 5;
}

double getExchange() {
    system("python exchange.py");

    string line;
    ifstream file ("exchange.txt");
    double cotacao = 0;
    if (file.is_open()) {
        getline(file, line);
        cotacao = stod(line);
        file.close();

    } else {
        cout << "Unable to open exchange.txt";
    }
    return cotacao;
}

double usdBrl(int n) {
    double cotacao = getExchange();
    return n * cotacao;
}
double brlUsd(int n) {
    double cotacao = getExchange();
    return n / cotacao;
}

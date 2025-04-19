#include <iostream>

using namespace std;

double calcSomar(double a, double b);
double calcSubtrair(double a, double b);
double calcMultiplicar(double a, double b);
double calcDividir(double a, double b);

int main() {
    while (true) {
        int opt = 0;

        cout << "--- Calculadora Simples ---" << '\n';
        cout << "Escolha uma operação: " << '\n';
        cout << "1. Soma" << '\n' << "2. Subtração" << '\n' << "3. Multiplicação" << '\n' << "4. Divisão" << '\n' << "5. Sair" << '\n';
        cout << '\n' << "Opção: ";
        cin >> opt;

        if (opt == 5) {
            cout << "Saindo..." << '\n';
            return 0;
        }

        double a, b;
        cout << "Digite o primeiro número: ";
        cin >> a;
        cout << "Digite o segundo número: ";
        cin >> b;

        double res;
        switch (opt) {
            case 1:
                res = calcSomar(a, b);
                break;
            case 2:
                res = calcSubtrair(a, b);
                break;
            case 3:
                res = calcMultiplicar(a, b);
                break;
            case 4:
                if (b == 0) {
                    cout << "b não pode ser igual a zero!" << '\n';
                    return 1;
                }
                res = calcDividir(a, b);
        }
        cout << "Resultado: " << res << "\n\n";
    }
}

double calcSomar(double a, double b) {
    return a + b;
}
double calcSubtrair(double a, double b) {
    return a - b;
}
double calcMultiplicar(double a, double b) {
    return a * b;
}
double calcDividir(double a, double b) {
    return a / b;
}

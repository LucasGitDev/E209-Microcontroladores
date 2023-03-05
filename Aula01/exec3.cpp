#include <iostream>

using namespace std;

int main() {
    int n, i, j, num, par, impar, positivo, negativo;

    cin >> n;

    for (i = 0; i < n; i++) {
        par = 0;
        impar = 0;
        positivo = 0;
        negativo = 0;

        for (j = 0; j < 5; j++) {
            cin >> num;

            if (num % 2 == 0) {
                par++;
            } else {
                impar++;
            }

            if (num > 0) { // no caso de 0, ele não é positivo nem negativo. O exemplo utiliza 0 como positivo, para isso basta trocar o sinal do if para num >= 0
                positivo++;
            } else if (num < 0) {
                negativo++;
            }
        }

        cout << "Quantidade de numeros pares: " << par << endl;
        cout << "Quantidade de numeros impares: " << impar << endl;
        cout << "Quantidade de numeros positivos: " << positivo << endl;
        cout << "Quantidade de numeros negativos: " << negativo << endl;
        cout << endl;
    }
    return 0;
}
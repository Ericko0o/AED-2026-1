#include <iostream>
#include <ctime>
#include <cctype>

using namespace std;

// ----------- ESTRUCTURA TIPO RETRO (pero con otro nombre) -------------
template<class T>
class retroceder {
private:
    T* arr;
    int inicio;
    int fin;
    int num_eleme;

public:
    int nelem;

    retroceder(int cap = 10) {
        num_eleme = cap;
        arr = new T[num_eleme];
        inicio = 0;
        fin = 0;
        nelem = 0;
    }

    void push_back(T elem) {
        arr[fin] = elem;
        fin = (fin + 1) % num_eleme;

        if (nelem < num_eleme) {
            nelem++;
        }
        else {
            inicio = (inicio + 1) % num_eleme; // sobrescribe
        }
    }

    T pop_back() {
        if (nelem == 0) return 0;

        fin = (fin - 1 + num_eleme) % num_eleme;
        T temp = arr[fin];
        nelem--;

        return temp;
    }

    T operator[](int i) {
        if (i >= nelem) return 0;
        return arr[(inicio + i) % num_eleme];
    }

    ~retroceder() {
        delete[] arr;
    }
};

// ----------- JUEGO AHORCADO -------------
class ahorcadox {
private:
    retroceder<char> memo;       // historial (10 estados)
    retroceder<char> memoequi;   // letras incorrectas

    char palabras[10][30] = {
    "programacion",
    "computadora",
    "desarrollo",
    "arquitectura",
    "inteligencia",
    "algoritmo",
    "estructura",
    "compilador",
    "microprocesador",
    "sistemas"
    };

    char (*plb)[30] = palabras;
    char* p;

    int numero_letras;
    int vidas;

    char* palabra_oculta;
    char letra_ingresada;

public:
    ahorcadox() : memo(10), memoequi(10) {
        srand(time(0));
        p = *(plb + (rand() % 10));

        numero_letras = 0;
        while (p[numero_letras] != '\0') numero_letras++;

        palabra_oculta = new char[numero_letras];

        for (int i = 0; i < numero_letras; i++) {
            palabra_oculta[i] = '_';
        }

        vidas = 15;
    }

    void verifica_letra(char letra_ingresada) {
        memo.push_back(letra_ingresada);

        bool cambio = false;

        for (int i = 0; i < numero_letras; i++) {
            if (p[i] == letra_ingresada) {
                palabra_oculta[i] = letra_ingresada;
                cambio = true;
            }
        }

        if (!cambio && letra_ingresada != '*') {
            vidas--;
            memoequi.push_back(letra_ingresada);
        }
    }

    void imprimir_plb() {
        for (int i = 0; i < numero_letras; i++) {
            cout << palabra_oculta[i] << " ";
        }
        cout << endl;

        cout << "Incorrectas: ";
        for (int i = 0; i < memoequi.nelem; i++) {
            cout << memoequi[i] << " ";
        }
        cout << endl;
    }

    void deshacer() {
        if (memo.nelem == 0) {
            cout << "Nada que deshacer\n";
            return;
        }

        char letra = memo.pop_back();
        bool cambio = false;

        for (int i = 0; i < numero_letras; i++) {
            if (p[i] == letra) {
                palabra_oculta[i] = '_';
                cambio = true;
            }
        }

        if (!cambio) {
            vidas++;
            memoequi.pop_back();
        }
    }

    bool jugar() {
        cout << "\n---------------------------\n";
        cout << "Vidas: " << vidas << endl;

        imprimir_plb();

        // verificar victoria
        bool ganaste = true;
        for (int i = 0; i < numero_letras; i++) {
            if (palabra_oculta[i] != p[i]) {
                ganaste = false;
                break;
            }
        }

        if (ganaste) {
            cout << "Ganaste \n";
            return true;
        }

        if (vidas == 0) {
            cout << "Perdiste \n";
            cout << "La palabra era: " << p << endl;
            return true;
        }

        cout << "Ingresa letra (* para deshacer): ";
        cin >> letra_ingresada;
        letra_ingresada = tolower(letra_ingresada);

        if (letra_ingresada == '*') {
            deshacer();
        }
        else {
            verifica_letra(letra_ingresada);
        }

        return false;
    }

    ~ahorcadox() {
        delete[] palabra_oculta;
    }
};

int main() {
    ahorcadox juego;

    bool fin = false;
    while (!fin) {
        fin = juego.jugar();
    }

    return 0;
}
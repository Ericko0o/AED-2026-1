#include<iostream>
#include <ctime>

using namespace std;


template<class t>
class retro {
    t* arr;
    t* heal;
    t* tail;
    int num_eleme = 10;

public:
    int nelem = 0;
    retro() {
        arr = new t[num_eleme];
        heal = arr;
        tail = arr;
    };

    //--------cambiar tamaño de memoria-------
    retro(int x) {
        num_eleme = x;
        arr = new t[num_eleme];
        heal = arr;
        tail = arr;
    };

    t ultimoelemento() {
        if (nelem == 0) {
            return 0; // o lanzar error
        }

        if (tail > arr) {
            return *(tail - 1);
        }
        else {
            return *(arr + num_eleme - 1);
        }
        //return *tail;
    }

    t operator[](int i) {
        if (i < nelem) {
            t* pos = heal + i;

            if (pos >= arr + num_eleme) {
                pos -= num_eleme; // wrap
            }

            return *pos;
        }
        return 0;
    }

    t pop_back() {

        if (nelem == 0) {
            return 0;
        }
        if (tail > arr) {
            tail--;
        }
        else {
            tail = arr + num_eleme - 1;
        }

        nelem--;


        t tem = *tail;
        return tem;
    };
    void push_back(t elem) {
        *tail = elem;

        if (tail < arr + num_eleme - 1) {
            tail++;
        }
        else {
            tail = arr;
        }
        if (nelem < num_eleme) {
            nelem++;
        }
        if (tail == heal) {
            if (heal == arr + num_eleme - 1) {
                heal = arr;
            }
            else {
                heal++;
            }
        }
    };
    ~retro() {
        delete[] arr;
    };
};


class ahorcado {
    retro<char> memo;

    retro<char> memoequi;

    char palabras[10][30] = {
        "programacion",
        "computadora",
        "desarrollo",
        "arquitectura",
        "inteligencia",
        "electromagnetismo",
        "responsabilidad",
        "caracteristicas",
        "internacionalizacion",
        "hipopotomonstrosesqu" };

    char (*plb)[30] = palabras;

    char* p;
    int numero_letras = 0;

    int vidas = 15;

    char* palabra_oculta;

    char letra_ingresada;





public:

    ahorcado() {
        srand(time(0));
        p = *(plb + (rand() % 10));
        char* t = p;
        while (*t != '\0') {
            numero_letras++;
            t++;
        }

        palabra_oculta = new char[numero_letras];
        for (char* t = palabra_oculta;t < palabra_oculta + numero_letras;t++) {
            *t = '_';
        }
    };
    void verifica_letra(char letra_ingresada) {

        memo.push_back(letra_ingresada);// ingresa palabra en memoria 
        bool cambio = false;
        char* p_po = palabra_oculta;

        for (char* t = p;t < p + numero_letras;t++) {

            //puntero a palabra oculta
            if (letra_ingresada == *t) {
                *p_po = letra_ingresada;
                cambio = true;
            }
            p_po++;

            // si la letra coinside con  alguna de la palabra oculta la pone 
        }
        if (!cambio && (letra_ingresada != '-')) {
            vidas--;
            memoequi.push_back(letra_ingresada);

            //si no coincide te resta una vida y aumenta una letra en palabras equivocadas 
        }


    }
    void imprimir_plb() {

        //imprime palabra con cambios o sin cambios 
        for (char* t = palabra_oculta;t < palabra_oculta + numero_letras;t++) {
            cout << *t << " ";
        }
        cout << endl;
        for (int i = 0;i < memoequi.nelem;i++) {
            cout << memoequi[i] << " ";
        }
        cout << endl;
        //imprime palabras equipocadas 


    }

    void controlz() {

        if (memo.nelem == 0) {
            cout << "Nada que deshacer" << endl;
            return;
        }
        char i = memo.pop_back();
        bool cambio = false;

        char* p_po = palabra_oculta;
        for (char* t = p;t < p + numero_letras;t++) {

            //puntero a palabra oculta
            if (i == *t) {
                *p_po = '_';
                cambio = true;
            }
            p_po++;
        }
        if (!cambio) {
            vidas++;
            memoequi.pop_back();
        }


    }


    bool jugar() {

        cout << "--------------------------------------------" << endl;
        cout << "numero de vida actuales = " << vidas << endl;

        imprimir_plb();


        bool ganaste = true;

        for (int i = 0; i < numero_letras; i++) {
            if (*(palabra_oculta + i) != *(p + i)) {
                ganaste = false;
                break;
            }
        }

        if (ganaste) {
            cout << "descubliste la palabra" << endl;
            cout << "GANASTE!!!" << endl;
            return true;
        }
        if (vidas == 0) {
            cout << "PERDISTE !!! te quedaste si vidas" << endl;
            return true;
        }


        cout << "introduce una letra : ";
        cin >> letra_ingresada;
        if (letra_ingresada == '-') {
            controlz();
        }
        else {
            verifica_letra(letra_ingresada);
        }
        cout << "--------------------------------------------" << endl;
        return false;


    };
    ~ahorcado() {
        delete[] palabra_oculta;
    }
};

int main() {

    ahorcado juego;
    bool t = false;
    while (!t) {
        t = juego.jugar();

    }

}
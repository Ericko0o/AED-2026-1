#include <iostream>
using namespace std;

// Deque char

struct NodoD {
    char dato;
    NodoD* ant;
    NodoD* sig;
};

class DequeChar {
    NodoD* ini;
    NodoD* fin;

public:
    DequeChar() {
        ini = fin = 0;
    }

    bool vacio() {
        return ini == 0;
    }

    void push_back(char x) {
        NodoD* n = new NodoD;
        n->dato = x;
        n->sig = 0;
        n->ant = fin;

        if (vacio()) {
            ini = fin = n;
        }
        else {
            fin->sig = n;
            fin = n;
        }
    }

    void push_front(char x) {
        NodoD* n = new NodoD;
        n->dato = x;
        n->ant = 0;
        n->sig = ini;

        if (vacio()) {
            ini = fin = n;
        }
        else {
            ini->ant = n;
            ini = n;
        }
    }

    void pop_back() {
        if (fin) {
            NodoD* t = fin;
            fin = fin->ant;

            if (fin) fin->sig = 0;
            else ini = 0;

            delete t;
        }
    }

    void pop_front() {
        if (ini) {
            NodoD* t = ini;
            ini = ini->sig;

            if (ini) ini->ant = 0;
            else fin = 0;

            delete t;
        }
    }

    char back() {
        if (fin) return fin->dato;
        return 0;
    }

    char front() {
        if (ini) return ini->dato;
        return 0;
    }
};

// Pila de enteros

struct NodoI {
    int dato;
    NodoI* sig;
};

class PilaInt {
    NodoI* top;
public:
    PilaInt() {
        top = 0;
    }

    bool vacia() {
        return top == 0;
    }

    void push(int x) {
        NodoI* n = new NodoI;
        n->dato = x;
        n->sig = top;
        top = n;
    }

    void pop() {
        if (top) {
            NodoI* t = top;
            top = top->sig;
            delete t;
        }
    }

    int cima() {
        if (top) return top->dato;
        return 0;
    }
};

// Prioridad

int prioridad(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infija_postfija(char exp[], char res[]) {

    DequeChar dq;

    int i = 0, j = 0;

    while (exp[i] != '\0') {

        char c = exp[i];

        if (c == ' ') {
            // ignorar espacios
        }

        else if (c >= '0' && c <= '9') {
            res[j++] = c;
            res[j++] = ' ';
        }

        else if (c == '(') {
            dq.push_back(c);
        }

        else if (c == ')') {

            while (!dq.vacio() && dq.back() != '(') {
                res[j++] = dq.back();
                res[j++] = ' ';
                dq.pop_back();
            }

            dq.pop_back(); // para elminiar (
        }

        else { // operador

            while (!dq.vacio() &&
                prioridad(dq.back()) >= prioridad(c)) {

                res[j++] = dq.back();
                res[j++] = ' ';
                dq.pop_back();
            }

            dq.push_back(c);
        }

        i++;
    }

    while (!dq.vacio()) {
        res[j++] = dq.back();
        res[j++] = ' ';
        dq.pop_back();
    }

    res[j] = '\0';
}

// evaluar postfija

int evaluar_postfija(char post[]) {

    PilaInt pila;
    int i = 0;

    while (post[i] != '\0') {

        char c = post[i];

        if (c >= '0' && c <= '9') {
            pila.push(c - '0');
        }

        else if (c == ' ') {
            // ignorar espacios
        }

        else {
            int b = pila.cima(); pila.pop();
            int a = pila.cima(); pila.pop();

            if (c == '+') pila.push(a + b);
            if (c == '-') pila.push(a - b);
            if (c == '*') pila.push(a * b);
            if (c == '/') pila.push(a / b);
        }

        i++;
    }

    return pila.cima();
}


int main() {

    char exp[50] = "9*(2+3)/5";
    char post[100];

    cout << "Expresion infija: " << exp << endl;

    infija_postfija(exp, post);

    cout << "Postfija: " << post << endl;

    cout << "Resultado: " << evaluar_postfija(post) << endl;

    return 0;
}
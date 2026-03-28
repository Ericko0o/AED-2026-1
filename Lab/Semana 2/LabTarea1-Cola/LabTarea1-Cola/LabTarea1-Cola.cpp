#include <iostream>
using namespace std;

template <class T, int N = 10>
struct Cola
{
    T* arr;
    T* head;
    T* tail;
    int n_elem;

    Cola();
    ~Cola();
    bool vacio();
    bool lleno();
    bool push(T val);
    bool pop(T& val);
    void imprimir();
};

// constructor
template <class T, int N>
Cola<T, N>::Cola()
{
    n_elem = N;
    arr = new T[n_elem];
    head = nullptr;
    tail = nullptr;
}

template <class T, int N>
bool Cola<T, N>::vacio()
{
    return head == nullptr;
}

template <class T, int N>
bool Cola<T, N>::lleno()
{
    return tail == arr + n_elem - 1;
}

template <class T, int N>
bool Cola<T, N>::push(T val)
{
    if (lleno())
        return false;

    if (vacio())
    {
        head = tail = arr;
    }
    else
    {
        tail++;
    }

    *tail = val;
    return true;
}

template <class T, int N>
bool Cola<T, N>::pop(T& val)
{
    if (vacio())
        return false;

    val = *head;
    head++;

    if (head > tail)
    {
        head = nullptr;
        tail = nullptr;
    }

    return true;
}


template <class T, int N>
void Cola<T, N>::imprimir()
{
    for (int i = 0; i < n_elem; i++)
    {
        if (head != nullptr && tail != nullptr &&
            arr + i >= head && arr + i <= tail)
        {
            cout << "[" << arr[i] << "]";
        }
        else
        {
            cout << "[ ]";
        }
    }
    cout << endl;

    if (head != nullptr)
        cout << "H: " << (head - arr) << endl;
    else
        cout << "H: NULL" << endl;

    if (tail != nullptr)
        cout << "T: " << (tail - arr) << endl;
    else
        cout << "T: NULL" << endl;

    cout << "----------------------" << endl;
}

// destructor
template <class T, int N>
Cola<T, N>::~Cola()
{
    delete[] arr;
}

int main()
{
    Cola<int, 10> c;

    c.imprimir();

    c.push(10);
    c.imprimir();

    c.push(20);
    c.imprimir();

    c.push(30);
    c.imprimir();

    int x;

    c.pop(x);
    cout << "Sale: " << x << endl;
    c.imprimir();

    c.pop(x);
    cout << "Sale: " << x << endl;
    c.imprimir();

    c.pop(x);
    cout << "Sale: " << x << endl;
    c.imprimir();

    return 0;
}
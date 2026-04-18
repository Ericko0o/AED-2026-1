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
    if (vacio()) return false;

    T* next = (tail == arr + n_elem - 1) ? arr : tail + 1;
    return next == head;
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
        if (tail == arr + n_elem - 1)
            tail = arr;
        else
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

    if (head == tail)
    {
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        if (head == arr + n_elem - 1)
            head = arr;
        else
            head++;
    }

    return true;
}


template <class T, int N>
void Cola<T, N>::imprimir()
{
    for (int i = 0; i < n_elem; i++)
    {
        if (head != nullptr)
        {
            int pos = i;
            int h = head - arr;
            int t = tail - arr;

            if (
                (h <= t && pos >= h && pos <= t) ||
                (h > t && (pos >= h || pos <= t))
                )
            {
                cout << "[" << arr[i] << "]";
            }
            else
            {
                cout << "[ ]";
            }
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

    int x;

    c.imprimir();

    
    c.push(10); c.imprimir();
    c.push(20); c.imprimir();
    c.push(30); c.imprimir();
    c.push(40); c.imprimir();
    c.push(50); c.imprimir();
    c.push(60); c.imprimir();
    c.push(70); c.imprimir();
    c.push(80); c.imprimir();
    c.push(90); c.imprimir();
    c.push(100); c.imprimir();

    
    c.push(110);
    c.imprimir();

    
    c.pop(x); cout << "Sale: " << x << endl; c.imprimir();
    c.pop(x); cout << "Sale: " << x << endl; c.imprimir();
    c.pop(x); cout << "Sale: " << x << endl; c.imprimir();
    c.pop(x); cout << "Sale: " << x << endl; c.imprimir();
    c.pop(x); cout << "Sale: " << x << endl; c.imprimir();

    
    c.push(200); c.imprimir();
    c.push(300); c.imprimir();

    
    while (c.pop(x))
    {
        cout << "Sale: " << x << endl;
        c.imprimir();
    }

    
    c.pop(x);
    c.imprimir();

    c.push(10); c.imprimir();
    c.push(20); c.imprimir();
    c.push(30); c.imprimir();
    c.push(40); c.imprimir();

    return 0;
}
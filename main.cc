#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VVC;

void imprimirTablero(const VVC& Tablero) {
    for (int i = 0; i < Tablero.size(); ++i) {
        for (int j = 0; j <= 2*Tablero[0].size(); ++j) {
            cout <<  '-';
        }
        cout << endl;
        for (int j = 0; j < Tablero[0].size(); ++j) {
            cout <<  '|' << Tablero[i][j];
        }
        cout << '|' << endl;
    }
    for (int i = 0; i <= 2*Tablero[0].size(); ++i) {
        cout <<  '-';
    }
    cout << endl;
}

// Funcion de busqueda generalizada 
// Pre: aux puede valer 1, -1 o 0
bool buscar(const VVC& Tablero, int i, int j, int aux1, int aux2) {
    int n = Tablero.size();
    int m = Tablero[0].size();

    int k = 1;
    while (i + k*aux1 < n and j + k*aux2 < m and i + k*aux1 >= 0 and j + k*aux2 >= 0 and 
    Tablero[i + k*aux1][j + k*aux2] == Tablero[i][j]) {
        ++k;
        if (k == 4) return true;
    }
    return false;
}

bool quatroEnRaya(VVC& Tablero, int i, int j) {
    if (buscar(Tablero, i, j, 0, 1)) return true;
    if (buscar(Tablero, i, j, 0, -1)) return true;
    if (buscar(Tablero, i, j, 1, 0)) return true;
    if (buscar(Tablero, i, j, -1, 0)) return true;
    if (buscar(Tablero, i, j, 1, 1)) return true;
    if (buscar(Tablero, i, j, 1, -1)) return true;
    if (buscar(Tablero, i, j, -1, 1)) return true;
    if (buscar(Tablero, i, j, -1, -1)) return true;

    return false;
}

int introducirFicha(VVC& Tablero, int columna, int turno) {
    // Busca posiciones validas de abajo a arriba de la columna
    for (int i = Tablero.size() - 1; i >= 0; --i) {
        if (Tablero[i][columna] == ' ') {
            if (turno == 0) Tablero[i][columna] = 'X';
            else if (turno == 1) Tablero[i][columna] = 'O';
            return i;
        }
    }
    cout << "Columna llena" << endl;
    return -1;
}

int main() {
    VVC Tablero(6, VC(7, ' '));
    imprimirTablero(Tablero);
    
    int turno = 0;
    int columna;
    while (cin >> columna) {
        --columna; // Para no tener columna 0
        if (columna < Tablero[0].size() and columna >= 0) {
            // Guarda la fila donde introduce la ficha
            int fila = introducirFicha(Tablero, columna, turno);

            imprimirTablero(Tablero);

            if (quatroEnRaya(Tablero, fila, columna)) {
                if (turno == 0) cout << "¡Ganan las X!" << endl;
                else if (turno == 1) cout << "¡Ganan las O!" << endl;
                break;
            }
            // Si introduces fichas fuera del limite no cambia el turno
            if (fila < Tablero.size()) turno = 1 - turno;
        }
        else cout << "Columna inexistente" << endl;
    }
}
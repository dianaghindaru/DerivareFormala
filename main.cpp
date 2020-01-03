#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**
1. Diff(C) = 0;
2. Diff(X) = 1;
3. Diff(F + G) = (Diff(F) + Diff(G))
4. Diff(F - G) = (Diff(F) - Diff(G))
5. Diff(F * G) = ((F * Diff(G)) * (Diff(F) * G))
6. Diff(F / G) = (((G * Diff(F)) - (F * Diff(G))) / (G ^ 2))
7. Diff(F ^ G) = ((G * (F ^ (G - 1))) * Diff(F))

UNDE:
C = "0123456789" (multimea de constante)
later edit: mi-am dat seama ca sunt toate numerele, inclusiv
cele cu doua sau mai multe cifre
X - multimea de variabile in functie de care derivam
(poate fi si Y, Z sau orice altceva)
F - corespunde pt subarborele din stanga
G - corespunde pt subarborele din dreapta
*/

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
    string text;
    while (fin >> text) {
        cout << text;
    }
}

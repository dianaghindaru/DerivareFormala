#include <iostream>
#include <string>
#include <limits>
#include <ctime> /// time_t, difftime, time
using namespace std;

int alegere = 0;

struct nodLista
{
    string text;
    nodLista* next;
};

typedef nodLista* Lista;

nodLista* elementLista, * ultimulElementLista;
Lista lista = NULL;

struct nodArbore
{
    string text;
    nodArbore* stanga, * dreapta;
};

typedef nodArbore* Arbore;

nodArbore* elementArbore, * elementArbore1, * elementArbore2, * elementArbore3, * f_x, * g_x;
Arbore arbore = NULL, p;

bool FormulaCorecta = true;
string Formula;

void emptyArbore(Arbore& arbore)
{
    arbore = NULL;
}

void insertElementArbore(Arbore& p)
{
    elementArbore = new nodArbore;
    elementArbore->text = elementLista->text;
    elementLista = elementLista->next;
    p = elementArbore;
    if (elementArbore->text == "+" || elementArbore->text == "-" || elementArbore->text == "*" || elementArbore->text == "/" || elementArbore->text == "^" || elementArbore->text == "log")
    {
        insertElementArbore(p->stanga);
        insertElementArbore(p->dreapta);
    }
    else if (elementArbore->text == "sin" || elementArbore->text == "cos" || elementArbore->text == "tg" || elementArbore->text == "ctg" || elementArbore->text == "arcsin" || elementArbore->text == "arccos" || elementArbore->text == "arctg" || elementArbore->text == "arcctg" || elementArbore->text == "ln" || elementArbore->text == "sqrt")
    {
        insertElementArbore(p->stanga);
        p->dreapta = NULL;
    }
    else
        p->stanga = p->dreapta = NULL;
}

void afisareArbore(Arbore arbore)
{
    if (arbore->text == "+" || arbore->text == "-" || arbore->text == "*" || arbore->text == "/" || arbore->text == "^")
    {
        if (arbore->text == "-" && arbore->stanga->text == "0")
        {
            cout << "(" << arbore->text;
            afisareArbore(arbore->dreapta);
            cout << ")";
        }
        else if(arbore->text == "/" || arbore->text == "^")
        {
            cout << "(";
            afisareArbore(arbore->stanga);
            cout << ")" << arbore->text << "(";
            afisareArbore(arbore->dreapta);
            cout << ")";
        }
        else
        {
            afisareArbore(arbore->stanga);
            cout << arbore->text;
            afisareArbore(arbore->dreapta);
        }
        /*cout << "(";
        if (!(arbore->text == "-" && arbore->stanga->text == "0"))
            afisareArbore(arbore->stanga);
        cout << arbore->text;
        afisareArbore(arbore->dreapta);
        cout << */
    }
    else if (arbore->text == "sin" || arbore->text == "cos" || arbore->text == "tg" || arbore->text == "ctg" || arbore->text == "arcsin" || arbore->text == "arccos" || arbore->text == "arctg" || arbore->text == "arcctg" || arbore->text == "ln" || arbore->text == "sqrt")
    {
        cout << arbore->text << "(";
        afisareArbore(arbore->stanga);
        cout << ")";
    }
    else if (arbore->text == "log")
    {
        cout << "log(";
        afisareArbore(arbore->dreapta);
        cout << ",";
        afisareArbore(arbore->stanga);
        cout << ")";
    }
    else
        cout << arbore->text;
}

void deleteArbore(Arbore& arbore)
{
    if (arbore->stanga != NULL)
        deleteArbore(arbore->stanga);
    if (arbore->dreapta != NULL)
        deleteArbore(arbore->dreapta);
    delete arbore;
}

void resetArbore(Arbore& arbore)
{
    deleteArbore(arbore);
    emptyArbore(arbore);
}

void copyArbore(Arbore& copiedToArbore, Arbore copiedFromArbore)
{
    elementArbore = new nodArbore;
    elementArbore->text = copiedFromArbore->text;

    copiedToArbore = elementArbore;

    if (copiedFromArbore->stanga != NULL)
        copyArbore(copiedToArbore->stanga, copiedFromArbore->stanga);
    else
        copiedToArbore->stanga = NULL;

    if (copiedFromArbore->dreapta != NULL)
        copyArbore(copiedToArbore->dreapta, copiedFromArbore->dreapta);
    else
        copiedToArbore->dreapta = NULL;
}

void emptyList(Lista& lista)
{
    lista = NULL;
}

void insertElementLista(Lista& lista, string text)
{
    elementLista = new nodLista;
    elementLista->text = text;
    elementLista->next = NULL;
    if (lista == NULL)
    {
        lista = elementLista;
        ultimulElementLista = lista;
    }
    else
    {
        ultimulElementLista->next = elementLista;
        ultimulElementLista = elementLista;
    }
}

void showList(Lista lista)
{
    for (nodLista* i = lista; i != NULL; i = i->next)
        cout << i->text << "  ";
}

void deleteList(Lista& lista)
{
    if (lista->next != NULL)
        deleteList(lista->next);
    delete lista;
}

void resetList(Lista& lista)
{
    deleteList(lista);
    emptyList(lista);
}

bool VerificareFormule(string Formula)
{
    /// Verifica daca este <parametru> <semn> <parametru> si daca da, returneaza false
    for (int i = 0; i < Formula.size(); i++)
        if (Formula[i] == '+' || Formula[i] == '-' || Formula[i] == '*' || Formula[i] == '/' || Formula[i] == '^' || Formula.substr(0, 3) == "sin" || Formula.substr(0, 3) == "cos" || Formula.substr(0, 2) == "tg" || Formula.substr(0, 3) == "ctg" || Formula.substr(0, 6) == "arcsin" || Formula.substr(0, 6) == "arccos" || Formula.substr(0, 5) == "arctg" || Formula.substr(0, 6) == "arcctg" || Formula.substr(0, 2) == "ln" || Formula.substr(0, 4) == "sqrt" || Formula.substr(0, 3) == "log")
            return false;
    return true;
}

bool VerificareParanteza(string Formula)
{
    /// Verifica daca formula are forma <paranteza deschisa> <formula> <paranteza inchisa>
    if (Formula[0] == '(' && Formula[Formula.size() - 1] == ')')
    {
        int j = 0;
        for (int i = 0; i < Formula.size(); i++)
            if (Formula[i] == '(')
                j++;
            else if (Formula[i] == ')')
                j--;
            else if (j == 0 && i != Formula.size() - 1)
                return false;
        return true;
    }
    return false;
}

int CoordonateSemnPlusMinus(string Formula)
{
    int pozitiaSemn = -1, indiceParanteza = 0;
    bool AmGasitSemnul = 0;
    /** Cauta semnele [+] sau [-] */
    for (int i = 0; i < Formula.size() && AmGasitSemnul == 0; i++)
        if (Formula[i] == '(')
            indiceParanteza++;
        else if (Formula[i] == ')')
            indiceParanteza--;
        else if ((Formula[i] == '+' || Formula[i] == '-') && indiceParanteza == 0)
        {
            pozitiaSemn = i;
            AmGasitSemnul = 1;
        }
    return pozitiaSemn;
}

int CoordonateSemnInmultire(string Formula)
{
    int pozitiaSemn = -1, indiceParanteza = 0;
    bool AmGasitSemnul = 0;
    /** Cauta semnul [*] */
    for (int i = 0; i < Formula.size() && AmGasitSemnul == 0; i++)
        if (Formula[i] == '(')
            indiceParanteza++;
        else if (Formula[i] == ')')
            indiceParanteza--;
        else if ((Formula[i] == '*') && indiceParanteza == 0)
        {
            pozitiaSemn = i;
            AmGasitSemnul = 1;
        }
    return pozitiaSemn;
}

int CoordonateSemnImpartire(string Formula)
{
    int pozitiaSemn = -1, indiceParanteza = 0;
    bool AmGasitSemnul = 0;
    /** Cauta semnul [/] */
    for (int i = 0; i < Formula.size() && AmGasitSemnul == 0; i++)
        if (Formula[i] == '(')
            indiceParanteza++;
        else if (Formula[i] == ')')
            indiceParanteza--;
        else if ((Formula[i] == '/') && indiceParanteza == 0)
        {
            pozitiaSemn = i;
            AmGasitSemnul = 1;
        }
    return pozitiaSemn;
}

int CoordonateSemnPutere(string Formula)
{
    int pozitiaSemn = -1, indiceParanteza = 0;
    bool AmGasitSemnul = 0;
    /** Cauta semnul [^] */
    for (int i = 0; i < Formula.size() && AmGasitSemnul == 0; i++)
        if (Formula[i] == '(')
            indiceParanteza++;
        else if (Formula[i] == ')')
            indiceParanteza--;
        else if ((Formula[i] == '^') && indiceParanteza == 0)
        {
            pozitiaSemn = i;
            AmGasitSemnul = 1;
        }

    return pozitiaSemn;
}

int CoordonateSemn(string Formula)
{
    int pozitiaSemn = CoordonateSemnPlusMinus(Formula);

    if (pozitiaSemn == -1)
        pozitiaSemn = CoordonateSemnInmultire(Formula);

    if (pozitiaSemn == -1)
        pozitiaSemn = CoordonateSemnImpartire(Formula);

    if (pozitiaSemn == -1)
        pozitiaSemn = CoordonateSemnPutere(Formula);

    return pozitiaSemn;
}

int CoordonateSinus(string Formula)
{
    if (Formula.substr(0, 3) == "sin")
        return 0;
    else if (Formula.substr(0, 3) == "cos")
        return 1;
    else if (Formula.substr(0, 2) == "tg" /** || s.substr(0,3) == "tan" */)
        return 2;
    else if (Formula.substr(0, 3) == "ctg" /** || s.substr(0,3) == "cot" */)
        return 3;
    else if (Formula.substr(0, 6) == "arcsin" /** || s.substr(0,4) == "asin" */)
        return 4;
    else if (Formula.substr(0, 6) == "arccos" /** || s.substr(0,4) == "acos" */)
        return 5;
    else if (Formula.substr(0, 5) == "arctg" /** || s.substr(0,4) == "atan" */)
        return 6;
    else if (Formula.substr(0, 6) == "arcctg" /** || s.substr(0,4) == "acot" */)
        return 7;
    else if (Formula.substr(0, 2) == "ln")
        return 8;
    else if (Formula.substr(0, 4) == "sqrt")
        return 9;
    else if (Formula.substr(0, 3) == "log")
        return 10;
    else
        return -1;
}

int logBaza(string s)
{
    for (int i = 0; i < s.size(); i++)
        if (s[i] == ',')
            return i;
    return -1;
}

void convertireInLista(string s)
{
    while (VerificareParanteza(s))
    {
        s.erase(0, 1);
        s.erase(s.size() - 1, 1);
    }

    /// Verifica daca are formule
    if (VerificareFormule(s))
    {
        insertElementLista(lista, s);
        return;
    }

    int pozitiaSemn = CoordonateSemn(s);

    if (pozitiaSemn == -1)
    {
        pozitiaSemn = CoordonateSinus(s);
        if (pozitiaSemn != -1)
            switch (pozitiaSemn)
            {
            case 0:
                insertElementLista(lista, "sin");
                convertireInLista(s.substr(3));
                break;
            case 1:
                insertElementLista(lista, "cos");
                convertireInLista(s.substr(3));
                break;
            case 2:
                insertElementLista(lista, "tg");
                convertireInLista(s.substr(2));
                break;
            case 3:
                insertElementLista(lista, "ctg");
                convertireInLista(s.substr(3));
                break;
            case 4:
                insertElementLista(lista, "arcsin");
                convertireInLista(s.substr(6));
                break;
            case 5:
                insertElementLista(lista, "arccos");
                convertireInLista(s.substr(6));
                break;
            case 6:
                insertElementLista(lista, "arctg");
                convertireInLista(s.substr(5));
                break;
            case 7:
                insertElementLista(lista, "arcctg");
                convertireInLista(s.substr(6));
                break;
            case 8:
                insertElementLista(lista, "ln");
                convertireInLista(s.substr(2));
                break;
            case 9:
                insertElementLista(lista, "sqrt");
                convertireInLista(s.substr(4));
                break;
            case 10:
                ///<!>
                pozitiaSemn = logBaza(s.substr(3));
                if (pozitiaSemn != -1)
                {
                    insertElementLista(lista, "log");
                    convertireInLista(s.substr(3 + pozitiaSemn + 1, s.size() - pozitiaSemn - 5));
                    convertireInLista(s.substr(3 + 1, pozitiaSemn - 1));
                }
                else
                {
                    insertElementLista(lista, "ln");
                    convertireInLista(s.substr(3));
                }
                break;
            }
        return;
    }
    if (pozitiaSemn == 0)
    {
        if (s[pozitiaSemn] == '+')
            convertireInLista(s.substr(1));
        else if (s[pozitiaSemn] == '-')
        {
            insertElementLista(lista, s.substr(pozitiaSemn, 1));
            convertireInLista("0");
            convertireInLista(s.substr(pozitiaSemn + 1, s.size() - (pozitiaSemn + 1)));
        }
        else
            FormulaCorecta = false;
    }
    else if (pozitiaSemn == s.size() - 1)
        FormulaCorecta = false;
    else if (FormulaCorecta)
    {
        insertElementLista(lista, s.substr(pozitiaSemn, 1));
        convertireInLista(s.substr(0, pozitiaSemn));
        convertireInLista(s.substr(pozitiaSemn + 1, s.size() - (pozitiaSemn + 1)));
    }
}

/**
1. derivare(C) = 0;
2. derivare(x) = 1;
3. derivare(f_x + g_x) = (dx(f_x) + dx(g_x))
4. derivare(f_x - g_x) = (dx(f_x) - dx(g_x))
5. derivare(f_x * g_x) = ((dx(f_x) * g_x) * (f_x * dx(g_x)))
6. derivare(f_x / g_x) = (((dx(f_x) * g_x) * (f_x * dx(g_x))) / (g_x ^ 2))
7. derivare(f_x ^ g_x) = (g_x *(f_x ^ (g_x - 1)) * dx(f_x) + f_x * (log(f_x ) * dx(g_x)))
UNDE:
C = multimea de constante
x - multimea de variabile in functie de care derivam
(poate fi si Y, Z sau orice altceva)
*/

void derivare(Arbore& arbore)
{
    /// Reguli de derivare
    if (arbore->text == "+" || arbore->text == "-")
    {
        /** Reprezentare arbore derivat pentru adunare / scadere:
                 (+)       sau      (-)
                /   \              /   \
              f(x)' g(x)'        f(x)' g(x)'

        */

        derivare(arbore->stanga);
        derivare(arbore->dreapta);
    }
    else if (arbore->text == "*")
    {
        /** Reprezentare arbore derivat pentru inmultire:
                             (+)
                         /          \
                      (*)            (*)
                     /   \          /   \
                  f(x)'  g(x)     f(x)  g(x)'
        */

        copyArbore(f_x, arbore->stanga);
        copyArbore(g_x, arbore->dreapta);

        arbore->text = "+";

        elementArbore1 = new nodArbore;
        elementArbore1->text = "*";
        copyArbore(elementArbore1->stanga, f_x);
        copyArbore(elementArbore1->dreapta, g_x);

        arbore->stanga = elementArbore1;

        elementArbore1 = new nodArbore;
        elementArbore1->text = "*";
        copyArbore(elementArbore1->stanga, f_x);
        copyArbore(elementArbore1->dreapta, g_x);

        arbore->dreapta = elementArbore1;

        resetArbore(f_x);
        resetArbore(g_x);

        /// Derivare
        derivare(arbore->stanga->stanga);
        derivare(arbore->dreapta->dreapta);
    }
    else if (arbore->text == "/")
    {
        /** Reprezentare arbore derivat pentru impartire:
                             (/)
                        /             \
                      (-)             (^)
                    /     \          /   \
                  (*)     (*)      g(x)   2
                 /   \   /   \
             f(x)' g(x) f(x) g(x)'
        */

        copyArbore(f_x, arbore->stanga);
        copyArbore(g_x, arbore->dreapta);

        /// Ramura Stanga
        elementArbore1 = new nodArbore;
        elementArbore1->text = "*";
        copyArbore(elementArbore1->stanga, f_x);
        copyArbore(elementArbore1->dreapta, g_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "-";
        elementArbore2->stanga = elementArbore1;

        elementArbore1 = new nodArbore;
        elementArbore1->text = "*";
        copyArbore(elementArbore1->stanga, f_x);
        copyArbore(elementArbore1->dreapta, g_x);
        elementArbore2->dreapta = elementArbore1;

        arbore->stanga = elementArbore2;

        /// Ramura Dreapta
        elementArbore1 = new nodArbore;
        elementArbore1->text = "2";
        elementArbore1->stanga = elementArbore1->dreapta = NULL;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "^";
        elementArbore2->dreapta = elementArbore1;
        copyArbore(elementArbore2->stanga, g_x);

        arbore->dreapta = elementArbore2;

        resetArbore(f_x);
        resetArbore(g_x);

        /// Derivare
        derivare(arbore->stanga->stanga->stanga);
        derivare(arbore->stanga->dreapta->dreapta);
    }
    else if (arbore->text == "^")
    {
        /** Reprezentare arbore derivat pentru ridicarea la putere:
                                  (+)
                        /                     \
                     (*)                       (*)
                    /   \                 /           \
                  g(x)  (*)            (^)              (*)
                       /   \          /   \            /   \
                     (^)   f(x)'    f(x)  g(x)      (ln)   g(x)'
                    /   \                          /   \
                  f(x)  (-)                     f(x)    []
                       /   \
                     g(x)   1

        */

        arbore->text = "+";

        copyArbore(f_x, arbore->stanga);
        copyArbore(g_x, arbore->dreapta);

        /// Ramura stanga
        elementArbore1 = new nodArbore;
        elementArbore1->text = "1";
        elementArbore1->stanga = elementArbore1->dreapta = NULL;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "-";
        elementArbore2->dreapta = elementArbore1;
        copyArbore(elementArbore2->stanga, g_x);

        elementArbore1 = new nodArbore;
        elementArbore1->text = "^";
        elementArbore1->dreapta = elementArbore2;
        copyArbore(elementArbore1->stanga, f_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        elementArbore2->stanga = elementArbore1;
        copyArbore(elementArbore2->dreapta, f_x);

        elementArbore1 = new nodArbore;
        elementArbore1->text = "*";
        elementArbore1->dreapta = elementArbore2;
        copyArbore(elementArbore1->stanga, g_x);

        arbore->stanga = elementArbore1;

        /// Ramura dreapta
        elementArbore1 = new nodArbore;
        elementArbore1->text = "ln";
        elementArbore1->dreapta = NULL;
        copyArbore(elementArbore1->stanga, f_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        elementArbore2->stanga = elementArbore1;
        copyArbore(elementArbore2->dreapta, g_x);

        elementArbore1 = new nodArbore;
        elementArbore1->text = "*";
        elementArbore1->dreapta = elementArbore2;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "^";
        copyArbore(elementArbore2->stanga, f_x);
        copyArbore(elementArbore2->dreapta, g_x);

        elementArbore1->stanga = elementArbore2;

        arbore->dreapta = elementArbore1;

        resetArbore(f_x);
        resetArbore(g_x);

        ///Derivare
        derivare(arbore->stanga->dreapta->dreapta);
        derivare(arbore->dreapta->dreapta->dreapta);
    }
    /// Derivate
    else if (arbore->text == "sin")
    {
        /// Reprezentare pentru derivarea lui sin(f(x))
        ///              (*)
        ///           /       \
        ///         cos       f_x'
        ///        /   \
        ///      f_x  NULL

        arbore->text = "*";

        copyArbore(f_x, arbore->stanga);

        ///  Ramura stanga
        elementArbore1 = new nodArbore;
        elementArbore1->text = "cos";
        elementArbore1->dreapta = NULL;
        copyArbore(elementArbore1->stanga, f_x);

        arbore->stanga = elementArbore1;

        /// Ramura dreapta
        copyArbore(arbore->dreapta, f_x);

        resetArbore(f_x);

        ///Derivare
        derivare(arbore->dreapta);
    }
    else if (arbore->text == "cos")
    {
        /// Reprezentare pentru derivarea lui cos(f(x)):
        ///              (-)
        ///           /       \
        ///          0        (*)
        ///                 /     \
        ///               sin     f_x'
        ///              /   \
        ///            f_x  NULL

        arbore->text = "-";

        copyArbore(f_x, arbore->stanga);

        ///  Ramura stanga
        elementArbore1 = new nodArbore;
        elementArbore1->text = "0";

        arbore->stanga = elementArbore1;

        /// Ramura dreapta
        elementArbore1 = new nodArbore;
        elementArbore1->text = "sin";
        elementArbore1->dreapta = NULL;
        copyArbore(elementArbore1->stanga, f_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        elementArbore2->stanga = elementArbore1;

        elementArbore1 = new nodArbore;
        copyArbore(elementArbore1, f_x);
        elementArbore2->dreapta = elementArbore1;

        arbore->dreapta = elementArbore2;

        resetArbore(f_x);

        ///Derivare
        derivare(arbore->dreapta->dreapta);
    }
    else if (arbore->text == "tg")
    {
        /// Reprezentare pentru derivarea lui tg(f(x))
        ///              (/)
        ///           /       \
        ///         f_x'      (^)
        ///               /         \
        ///             cos          2
        ///            /   \
        ///          f_x   NULL

        arbore->text = "/";

        copyArbore(f_x, arbore->stanga);

        /// Ramura dreapta
        elementArbore1 = new nodArbore;
        elementArbore1->text = "cos";
        elementArbore1->dreapta = NULL;
        copyArbore(elementArbore1->stanga, f_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "^";
        elementArbore2->stanga = elementArbore1;

        elementArbore1 = new nodArbore;
        elementArbore1->text = "2";
        elementArbore1->dreapta = elementArbore1->stanga = NULL;
        elementArbore2->dreapta = elementArbore1;

        arbore->dreapta = elementArbore2;

        resetArbore(f_x);

        ///Derivare
        derivare(arbore->stanga);
    }
    else if (arbore->text == "ctg")
    {
        /// Reprezentare pentru derivarea lui ctg(f(x))
        ///            (-)
        ///      /             \
        ///     0              (/)
        ///                 /       \
        ///               f_x'      (*)
        ///                     /         \
        ///                   sin         sin
        ///                  /   \       /   \
        ///                f_x   NULL  f_x  NULL

        arbore->text = "-";

        copyArbore(f_x, arbore->stanga);

        ///  Ramura stanga
        elementArbore1 = new nodArbore;
        elementArbore1->text = "0";
        elementArbore1->stanga = elementArbore1->dreapta = NULL;

        arbore->stanga = elementArbore1;

        /// Ramura dreapta
        elementArbore1 = new nodArbore;
        elementArbore1->text = "sin";
        elementArbore1->dreapta = NULL;
        copyArbore(elementArbore1->stanga, f_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "^";
        elementArbore2->stanga = elementArbore1;

        elementArbore1 = new nodArbore;
        elementArbore1->text = "2";
        elementArbore1->dreapta = elementArbore1->stanga = NULL;
        elementArbore2->dreapta = elementArbore1;

        elementArbore1 = new nodArbore;
        elementArbore1->text = "/";
        elementArbore1->dreapta = elementArbore2;
        copyArbore(elementArbore1->stanga, f_x);

        arbore->dreapta = elementArbore1;

        resetArbore(f_x);

        ///Derivare
        derivare(arbore->dreapta->stanga);
    }
    else if (arbore->text == "arcsin")
    {
        /// Reprezentare pentru derivarea lui arcsin(f(x))
        ///        (/)
        ///      /    \
        ///    f_x'  sqrt
        ///          /   \
        ///        (-)   NULL
        ///       /   \
        ///      1    (^)
        ///          /   \
        ///        f_x    2

        arbore->text = "/";

        copyArbore(f_x, arbore->stanga);

        /// Ramura dreapta
        elementArbore1 = new nodArbore;
        elementArbore1->text = "^";
        copyArbore(elementArbore1->stanga, f_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "2";
        elementArbore2->stanga = elementArbore2->dreapta = NULL;
        elementArbore1->dreapta = elementArbore2;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "-";
        elementArbore2->dreapta = elementArbore1;

        elementArbore1 = new nodArbore;
        elementArbore1->text = "1";
        elementArbore1->stanga = elementArbore1->dreapta = NULL;
        elementArbore2->stanga = elementArbore1;

        elementArbore1 = new nodArbore;
        elementArbore1->text = "sqrt";
        elementArbore1->dreapta = NULL;
        elementArbore1->stanga = elementArbore2;

        arbore->dreapta = elementArbore1;

        resetArbore(f_x);

        /// Derivarea
        derivare(arbore->stanga);
    }
    else if (arbore->text == "arccos")
    {
        /// Reprezentare pentru derivarea lui arccos(f(x))
        ///         (-)
        ///      /        \
        ///     0         (/)
        ///             /     \
        ///           f_x'   sqrt
        ///                  /   \
        ///                (-)   NULL
        ///               /   \
        ///              1    (^)
        ///                  /   \
        ///                f_x    2

        arbore->text = "-";

        copyArbore(f_x, arbore->stanga);

        ///  Ramura stanga
        elementArbore1 = new nodArbore;
        elementArbore1->text = "0";
        elementArbore1->stanga = elementArbore1->dreapta = NULL;

        arbore->stanga = elementArbore1;

        /// Ramura dreapta
        elementArbore1 = new nodArbore;
        elementArbore1->text = "^";
        copyArbore(elementArbore1->stanga, f_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "2";
        elementArbore2->dreapta = elementArbore2->stanga = NULL;
        elementArbore1->dreapta = elementArbore2;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "-";
        elementArbore2->dreapta = elementArbore1;

        elementArbore1 = new nodArbore;
        elementArbore1->text = "1";
        elementArbore1->stanga = elementArbore1->dreapta = NULL;
        elementArbore2->stanga = elementArbore1;

        elementArbore1 = new nodArbore;
        elementArbore1->text = "sqrt";
        elementArbore1->dreapta = NULL;
        elementArbore1->stanga = elementArbore2;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "/";
        elementArbore2->dreapta = elementArbore1;
        copyArbore(elementArbore2->stanga, f_x);

        arbore->dreapta = elementArbore2;

        resetArbore(f_x);

        /// Derivarea
        derivare(arbore->dreapta->stanga);
    }
    else if (arbore->text == "arctg")
    {
        /// Reprezentare pentru derivarea lui arctg(f(x))
        ///       (/)
        ///     /     \
        ///   f_x'    (+)
        ///          /   \
        ///        (^)    1
        ///       /   \
        ///     f(x)   2

        arbore->text = "/";

        copyArbore(f_x, arbore->stanga);

        /// Ramura stanga
        copyArbore(arbore->stanga, f_x);

        /// Ramura dreapta
        elementArbore1 = new nodArbore;
        elementArbore1->text = "2";
        elementArbore1->stanga = elementArbore1->dreapta = NULL;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "^";
        elementArbore2->dreapta = elementArbore1;
        copyArbore(elementArbore2->stanga, f_x);

        elementArbore1 = new nodArbore;
        elementArbore1->text = "+";
        elementArbore1->stanga = elementArbore2;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "1";
        elementArbore2->stanga = elementArbore2->dreapta = NULL;
        elementArbore1->dreapta = elementArbore2;

        arbore->dreapta = elementArbore1;

        resetArbore(f_x);

        /// Derivarea
        derivare(arbore->stanga);
    }
    else if (arbore->text == "arcctg")
    {
        /// Reprezentare pentru derivarea lui arcctg(f(x))
        ///        (-)
        ///     /       \
        ///    0        (/)
        ///           /     \
        ///         f_x'    (+)
        ///                /   \
        ///              (^)    1
        ///             /   \
        ///           f(x)   2

        arbore->text = "-";

        copyArbore(f_x, arbore->stanga);

        ///  Ramura stanga
        elementArbore1 = new nodArbore;
        elementArbore1->text = "0";
        elementArbore1->stanga = elementArbore1->dreapta = NULL;

        arbore->stanga = elementArbore1;

        /// Ramura dreapta
        elementArbore1 = new nodArbore;
        elementArbore1->text = "2";
        elementArbore1->stanga = elementArbore1->dreapta = NULL;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "^";
        elementArbore2->dreapta = elementArbore1;
        copyArbore(elementArbore2->stanga, f_x);

        elementArbore1 = new nodArbore;
        elementArbore1->text = "+";
        elementArbore1->stanga = elementArbore2;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "1";
        elementArbore2->stanga = elementArbore1->dreapta = NULL;
        elementArbore1->dreapta = elementArbore2;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "/";
        elementArbore2->dreapta = elementArbore1;
        copyArbore(elementArbore2->stanga, f_x);

        arbore->dreapta = elementArbore2;

        resetArbore(f_x);

        /// Derivare
        derivare(arbore->dreapta->stanga);
    }
    else if (arbore->text == "sqrt")
    {
        /// Reprezentare pentru derivarea radicalului
        ///         (/)
        ///       /     \
        ///     f(x)'   (*)
        ///           /     \
        ///          2    (sqrt)
        ///              /      \
        ///            f(x)    NULL

        arbore->text = "/";

        copyArbore(f_x, arbore->stanga);

        ///  Ramura dreapta
        elementArbore1 = new nodArbore;
        elementArbore1->text = "sqrt";
        elementArbore1->dreapta = NULL;
        copyArbore(elementArbore1->stanga, f_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        elementArbore2->dreapta = elementArbore1;

        elementArbore1 = new nodArbore;
        elementArbore1->text = "2";
        elementArbore1->stanga = elementArbore1->dreapta = NULL;
        elementArbore2->stanga = elementArbore1;

        arbore->dreapta = elementArbore2;

        resetArbore(f_x);

        /// Derivare
        derivare(arbore->stanga);
    }
    else if (arbore->text == "log")
    {
        /// Reprezentarea pentru derivarea logaritmului:
        ///                                       (/)
        ///                         /                             \
        ///                       (-)                             (*)
        ///             /                      \                /      \
        ///           (*)                      (*)            f_x      (*)
        ///       /         \              /         \              /       \
        ///     (*)          ln          (*)          ln          g_x       (*)
        ///    /   \       /    \       /   \       /     \            /            \
        ///  f_x'  g_x   g_x    NULL  g_x'  f_x   f_x    NULL         ln             ln
        ///                                                         /    \         /    \
        ///                                                        g_x    NULL   g_x   NULL

        arbore->text = "/";

        copyArbore(f_x, arbore->stanga);
        copyArbore(g_x, arbore->dreapta);

        /// Ramura stanga
        elementArbore1 = new nodArbore;
        elementArbore1->text = "ln";
        elementArbore1->dreapta = NULL;
        copyArbore(elementArbore1->stanga, g_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        elementArbore2->dreapta = elementArbore1;

        elementArbore1 = new nodArbore;
        elementArbore1->text = "*";
        copyArbore(elementArbore1->stanga, f_x);
        copyArbore(elementArbore1->dreapta, g_x);
        elementArbore2->stanga = elementArbore1;

        elementArbore1 = new nodArbore;
        elementArbore1->text = "-";
        elementArbore1->stanga = elementArbore2;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "ln";
        elementArbore2->dreapta = NULL;
        copyArbore(elementArbore2->stanga, f_x);

        elementArbore3 = new nodArbore;
        elementArbore3->text = "*";
        elementArbore3->dreapta = elementArbore2;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        copyArbore(elementArbore2->stanga, g_x);
        copyArbore(elementArbore2->dreapta, f_x);
        elementArbore3->stanga = elementArbore2;
        elementArbore1->dreapta = elementArbore3;

        arbore->stanga = elementArbore1;

        /// Ramura dreapta
        elementArbore1 = new nodArbore;
        elementArbore1->text = "ln";
        elementArbore1->dreapta = NULL;
        copyArbore(elementArbore1->stanga, g_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        elementArbore2->stanga = elementArbore1;

        elementArbore1 = new nodArbore;
        elementArbore1->text = "ln";
        elementArbore1->dreapta = NULL;
        copyArbore(elementArbore1->stanga, g_x);
        elementArbore2->dreapta = elementArbore1;

        elementArbore1 = new nodArbore;
        elementArbore1->text = "*";
        elementArbore1->dreapta = elementArbore2;
        copyArbore(elementArbore1->stanga, g_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        elementArbore2->dreapta = elementArbore1;
        copyArbore(elementArbore2->stanga, f_x);

        arbore->dreapta = elementArbore2;

        resetArbore(f_x);
        resetArbore(g_x);

        ///Derivare
        derivare(arbore->stanga->stanga->stanga->stanga);
        derivare(arbore->stanga->dreapta->stanga->stanga);
    }
    else if (arbore->text == "ln")
    {
        /// Reprezentare pentru derivarea logaritmului natural:
        ///       (/)
        ///     /     \
        ///   f_x'   f_x

        arbore->text = "/";
        copyArbore(f_x, arbore->stanga);
        copyArbore(arbore->stanga, f_x);
        copyArbore(arbore->dreapta, f_x);

        resetArbore(f_x);

        /// Derivare
        derivare(arbore->stanga);
    }
    else if (arbore->text == "x")
    {
        arbore->text = "1";
    }
    else
        arbore->text = "0";
}

void simplificare(Arbore& arbore)
{
    if(arbore->stanga != NULL) simplificare(arbore->stanga);
    if(arbore->dreapta != NULL) simplificare(arbore->dreapta);

    if (arbore->stanga != NULL /*&& arbore->dreapta != NULL*/)
    {
        /// simplificare pentru adunare
        if (arbore->text == "+")
        {
            /// se verifica cazurile in care intr-o adunare apare elementul neutru "0"

            if (arbore->stanga->text == "0")
            {
                if (arbore->dreapta->stanga == NULL)
                {
                    arbore->text = arbore->dreapta->text;
                    arbore->stanga = NULL;
                    arbore->dreapta = NULL;
                }
                else
                {
                    copyArbore(arbore, arbore->dreapta);
                    simplificare(arbore);
                }
            }
            else if (arbore->dreapta->text == "0")
            {
                if (arbore->stanga->stanga == NULL)
                {
                    arbore->text = arbore->stanga->text;
                    arbore->stanga = NULL;
                    arbore->dreapta = NULL;
                }
                else
                {
                    copyArbore(arbore, arbore->stanga);
                    simplificare(arbore);
                }
            }
        }

        /// simplificare pentru scadere
        else if (arbore->text == "-")
        {
            /// verificam cazul in care la o scadere apare elementul neutru "0"(scazatorul)

            if (arbore->dreapta->text == "0")
            {
                if (arbore->stanga->stanga == NULL)
                {
                    arbore->text = arbore->stanga->text;
                    arbore->stanga = NULL;
                    arbore->dreapta = NULL;
                }
                else
                {
                    copyArbore(arbore, arbore->stanga);
                    simplificare(arbore);
                }
            }
        }

        /// simplificare pentru inmultire
        else if (arbore->text == "*")
        {
            ///la inmultire verificam doua cazuri: cazul inmultirii cu elementul neutru "1" si cazul inmultirii cu 0

            if (arbore->stanga->text == "1")
            {
                if (arbore->dreapta->stanga == NULL)
                {
                    arbore->text = arbore->dreapta->text;
                    arbore->stanga = NULL;
                    arbore->dreapta = NULL;
                }
                else
                {
                    copyArbore(arbore, arbore->dreapta);
                    simplificare(arbore);
                }
            }
            else if (arbore->dreapta->text == "1")
            {
                if (arbore->stanga->stanga == NULL)
                {
                    arbore->text = arbore->stanga->text;
                    arbore->stanga = NULL;
                    arbore->dreapta = NULL;
                }
                else
                {
                    copyArbore(arbore, arbore->stanga);
                    simplificare(arbore);
                }
            }
            else if (arbore->stanga->text == "0" || arbore->dreapta->text == "0")
            {
                arbore->text = "0";
                arbore->stanga = NULL;
                arbore->dreapta = NULL;
            }

        }

        /// simplificare pentru impartire
        else if (arbore->text == "/")
        {
            ///verificam cazurile in care deimpartitul este 0 si impartitorul diferit de 0, in care impartitorul este 0(eroare), si impartirea la 1

            if (arbore->stanga->text == "0" && arbore->dreapta->text != "0")
            {
                arbore->text = "0";
                arbore->stanga = NULL;
                arbore->dreapta = NULL;
            }
            else if (arbore->dreapta->text == "0")
            {
                cout << "eroare";
                return;
            }
            else if(arbore->dreapta->text == "1")
                if(arbore->stanga->stanga == NULL)
            {
                arbore->text = arbore->stanga->text;
                arbore->stanga = NULL;
                arbore->dreapta = NULL;
            }
            else
            {
                copyArbore(arbore, arbore->stanga);
                simplificare(arbore->stanga);
            }
        }

        /// simplificare pentru ridicare la putere
        else if (arbore->text == "^")
        {
            ///verificam cazurile ridicarii la putere cu 1, cu 0, ridicarii lui 1 la orice putere, ridicarii lui 0 la orice putere si
            ///ridicarii lui 0 la puterea 0(eroare)

            if (arbore->dreapta->text == "1" && arbore->stanga->text != "0")
            {
                if (arbore->stanga->stanga == NULL)
                {
                    arbore->text = arbore->stanga->text;
                    arbore->stanga = NULL;
                    arbore->dreapta = NULL;
                }
                else
                {
                    copyArbore(arbore, arbore->stanga);
                    simplificare(arbore);
                }
            }
            else if (arbore->dreapta->text == "0" && arbore->stanga->text != "0")
            {
                arbore->text = "1";
                arbore->stanga = NULL;
                arbore->dreapta = NULL;
            }
            else if (arbore->stanga->text == "0" && arbore->dreapta->text != "0")
            {
                arbore->text = "0";
                arbore->stanga = NULL;
                arbore->dreapta = NULL;
            }
            else if (arbore->stanga->text == "0" && arbore->dreapta->text == "0")
            {
                cout << "eroare";
                return;
            }
            else if (arbore->stanga->text == "1")
            {
                arbore->text = "1";
                arbore->stanga = NULL;
                arbore->dreapta = NULL;
            }
        }

        else if (arbore->text == "log")
        {
            ///verificam cazul logaritmului in oricare baza din 1

            if (arbore->stanga->text == "1")
            {
                arbore->text = "0";
                arbore->stanga = NULL;
                arbore->dreapta = NULL;
            }
        }

        else if (arbore->text == "ln")
        {
            ///verificam cazul logaritmului natural din e

            if (arbore->stanga->text == "e")
            {
                arbore->text = "1";
                arbore->stanga = NULL;
                arbore->dreapta = NULL;
            }
        }

        else if (arbore->text == "sqrt")
        {
            ///verificam cazurile radicalului din 1 si radicalului din 0

            if (arbore->stanga->text == "1")
            {
                arbore->text = "1";
                arbore->stanga = NULL;
                arbore->dreapta = NULL;
            }
            else if (arbore->stanga->text == "0")
            {
                arbore->text = "0";
                arbore->stanga = NULL;
                arbore->dreapta = NULL;
            }
        }
    }
}

int main()
{
    cout << "Apasa 'Enter' || Press 'Enter' || Appuyez sur 'Enter'." << "\n";

    time_t startTime = time(NULL);
    time_t currentTime;
    double seconds;
    cin.ignore(numeric_limits <streamsize>::max(), '\n');

revenire:
    int salt = 1;
    int limba;
    cout << "==============================================================" << "\n";
    cout << "| Alege limba || Choose language || Choisissez votre langue: |" << "\n";
    cout << "| Apasa '1' pentru 'Romana'.                                 |" << "\n";
    cout << "| Press '2' for 'English'.                                   |" << "\n";
    cout << "| Appuyez sur '3' pour le 'Francais'.                        |" << "\n";
    cout << "==============================================================" << "\n";
    cout << "\n";
    cout << "Alegere ta || Your choice || Votre choix: ";
    cin >> limba;
    cout << "\n";
    switch (limba)
    {
    case 1:
        cout << "============================================================" << "\n";
        cout << "|                       Meniu principal.                   |" << "\n";
        cout << "============================================================" << "\n";
        cout << "|                        Bine ai venit!                    |" << "\n";
        cout << "============================================================" << "\n";
        while (1)
        {
            cout << "Apasa '1' pentru a intra in program." << "\n";
            cout << "Apasa '2' pentru a intra in sectiunea de 'Credite'." << "\n";
            cout << "Apasa '3' pentru a alege alta limba." << "\n";
            cout << "Apasa '4' pentru a vedea cat timp a trecut de cand ai pornit programul." << "\n";
            cout << "Apasa '5' pentru a iesi din program." << "\n";
            cout << "Alegere: ";
            alegere = 0;
            while (alegere <= 0 || alegere > 5)
                cin >> alegere;
            cout << "\n";
            switch (alegere)
            {
            case 1:
            {
                FormulaCorecta = true;
                string Formula;
                cout << "Scrie formula pe care doresti sa o derivezi: ";
                cin >> Formula;
                cout << "\n";
                cout << "Formula initiala: " << Formula << "\n";
                cout << "\n";
                convertireInLista(Formula);
                if (FormulaCorecta)
                {
                    elementLista = lista;
                    insertElementArbore(arbore);
                    resetList(lista);
                    cout << "Arborele binar: ";
                    afisareArbore(arbore);
                    cout << "\n";
                    cout << "\n";
                    derivare(arbore);
                    cout << "Arborele derivat: ";
                    afisareArbore(arbore);
                    cout << "\n";
                    cout << "\n";
                    cout << "Varianta simplificata: ";
                    simplificare(arbore);
                    afisareArbore(arbore);
                    cout << "\n";
                    cout << "\n";
                    resetArbore(arbore);
                }
                else
                {
                    resetList(lista);
                    cout << "Formula este Gresita!" << "\n";
                    cout << "\n";
                    cout << "Apasa '1' pentru a scrie o alta formula." << "\n";
                    cout << "Alegere: ";
                    alegere = 0;
                    while (alegere != 1)
                        cin >> alegere;
                    cout << "\n";
                    break;
                }
            }
            break;
            case 2:
                cout << "============================================================" << "\n";
                cout << "|                         'Credite'                        |" << "\n";
                cout << "============================================================" << "\n";
                cout << "Acest proiect a fost realizat de: " << "\n";
                cout << "Bordea Ion" << "\n";
                cout << "Diana Ghindaru" << "\n";
                cout << "Ciobotariu Andrei" << "\n";
                cout << "\n";
                cout << "Apasa '1' pentru a iesi din sectiunea de 'Credite'." << "\n";
                cout << "Alegere: ";
                alegere = 0;
                while (alegere != 1)
                    cin >> alegere;
                cout << "\n";
                break;
            case 3:
                if (salt == 1)
                    goto revenire;
                break;
            case 4:
                time(&currentTime);
                seconds = difftime(currentTime, startTime);
                cout << "Au trecut " << seconds << " secunde de cand ai pornit programul.\n";
                cout << "\n";
                cout << "Apasa '1' pentru a reveni la meniul principal." << "\n";
                cout << "Alegere: ";
                alegere = 0;
                while (alegere != 1)
                    cin >> alegere;
                cout << "\n";
                break;
            case 5:
                return 0;
            }

        }
    case 2:
        cout << "============================================================" << "\n";
        cout << "|                          Main menu.                      |" << "\n";
        cout << "============================================================" << "\n";
        cout << "|                           Welcome!                       |" << "\n";
        cout << "============================================================" << "\n";
        while (1)
        {
            cout << "Press '1' to start the program." << "\n";
            cout << "Press '2' for the 'Credits' section." << "\n";
            cout << "Press '3' to choose another language." << "\n";
            cout << "Press '4' to see how long you have been in the program." << "\n";
            cout << "Press '5' to exit the program." << "\n";
            cout << "Your choice: ";

            alegere = 0;
            while (alegere <= 0 || alegere > 5)
                cin >> alegere;
            cout << "\n";
            switch (alegere)
            {
            case 1:
            {
                FormulaCorecta = true;
                string Formula;
                cout << "Write the formula you want to derive: ";
                cin >> Formula;
                cout << "\n";
                cout << "The initial formula: " << Formula << "\n";
                cout << "\n";
                convertireInLista(Formula);
                if (FormulaCorecta)
                {
                    elementLista = lista;
                    insertElementArbore(arbore);
                    resetList(lista);
                    cout << "The binary tree: ";
                    afisareArbore(arbore);
                    cout << "\n";
                    cout << "\n";
                    derivare(arbore);
                    cout << "The derived tree: ";
                    afisareArbore(arbore);
                    cout << "\n";
                    cout << "\n";
                    cout << "Simplified version: ";
                    simplificare(arbore);
                    afisareArbore(arbore);
                    cout << "\n";
                    cout << "\n";
                    resetArbore(arbore);
                }
                else
                {
                    resetList(lista);
                    cout << "The formula is wrong!" << "\n";
                    cout << "\n";
                    cout << "Press '1' to write another formula: " << "\n";
                    cout << "Your choice: ";
                    alegere = 0;
                    while (alegere != 1)
                        cin >> alegere;
                    cout << "\n";
                    break;
                }
            }
            break;
            case 2:
                cout << "============================================================" << "\n";
                cout << "|                         'Credits'                        |" << "\n";
                cout << "============================================================" << "\n";
                cout << "This project was realized by: " << "\n";
                cout << "Bordea Ion" << "\n";
                cout << "Diana Ghindaru" << "\n";
                cout << "Ciobotariu Andrei" << "\n";
                cout << "\n";
                cout << "Press '1' to exit the 'Credits' section." << "\n";
                cout << "Your choice: ";
                alegere = 0;
                while (alegere != 1)
                    cin >> alegere;
                cout << "\n";
                break;
            case 3:
                if (salt == 1)
                    goto revenire;
                break;
            case 4:
                time(&currentTime);
                seconds = difftime(currentTime, startTime);
                cout << "It has now been " << seconds << " seconds since you started the program.\n";
                cout << "\n";
                cout << "Press '1' to return to the main menu." << "\n";
                cout << "Your choice: ";
                alegere = 0;
                while (alegere != 1)
                    cin >> alegere;
                cout << "\n";
                break;
            case 5:
                return 0;
            }
        }
    case 3:
        cout << "============================================================" << "\n";
        cout << "|                       Menu principal.                    |" << "\n";
        cout << "============================================================" << "\n";
        cout << "|                         Bienvenue!                       |" << "\n";
        cout << "============================================================" << "\n";
        while (1)
        {
            cout << "Appuyez sur '1' pour acceder au programme." << "\n";
            cout << "Appuyez sur '2' pour acceder a la section 'Credits'." << "\n";
            cout << "Appuyez sur '3' pour choisir une autre langue." << "\n";
            cout << "Appuyez sur '4' pour voir combien de temps il s'est ecoule depuis le demarrage du programme." << "\n";
            cout << "Appuyez sur '5' pour quitter le programme." << "\n";
            cout << "Votre choix: ";
            alegere = 0;
            while (alegere <= 0 || alegere > 5)
                cin >> alegere;
            cout << "\n";
            switch (alegere)
            {
            case 1:
            {
                FormulaCorecta = true;
                string Formula;
                cout << "Ecrivez la formule que vous souhaitez deriver: ";
                cin >> Formula;
                cout << "\n";
                cout << "Formule initiale: " << Formula << "\n";
                cout << "\n";
                convertireInLista(Formula);
                if (FormulaCorecta)
                {
                    elementLista = lista;
                    insertElementArbore(arbore);
                    resetList(lista);
                    cout << "Arbre binaire: ";
                    afisareArbore(arbore);
                    cout << "\n";
                    cout << "\n";
                    derivare(arbore);
                    cout << "Arbre derive: ";
                    afisareArbore(arbore);
                    cout << "\n";
                    cout << "\n";
                    cout << "Version simplifiee: ";
                    simplificare(arbore);
                    afisareArbore(arbore);
                    cout << "\n";
                    cout << "\n";
                    resetArbore(arbore);
                }
                else
                {
                    resetList(lista);
                    cout << "La formule est fausse!" << "\n";
                    cout << "\n";
                    cout << "Appuyez sur '1' pour ecrire une autre formule." << "\n";
                    cout << "Votre choix: ";
                    alegere = 0;
                    while (alegere != 1)
                        cin >> alegere;
                    cout << "\n";
                    break;
                }
            }
            break;
            case 2:
                cout << "============================================================" << "\n";
                cout << "|                         'Credits'                        |" << "\n";
                cout << "============================================================" << "\n";
                cout << "Ce projet a ete realise par: " << "\n";
                cout << "Bordea Ion" << "\n";
                cout << "Diana Ghindaru" << "\n";
                cout << "Ciobotariu Andrei" << "\n";
                cout << "\n";
                cout << "Appuyez sur '1' pour quitter la section 'Credits'." << "\n";
                cout << "Votre choix: ";
                alegere = 0;
                while (alegere != 1)
                    cin >> alegere;
                cout << "\n";
                break;
            case 3:
                if (salt == 1)
                    goto revenire;
                break;
            case 4:
                time(&currentTime);
                seconds = difftime(currentTime, startTime);
                cout << "Cela fait " << seconds << " que vous avez commence le programme.\n";
                cout << "\n";
                cout << "Appuyez sur '1' pour revenir au menu principal." << "\n";
                cout << "Votre choix: ";
                alegere = 0;
                while (alegere != 1)
                    cin >> alegere;
                cout << "\n";
                break;
            case 5:
                return 0;
            }
        }
    }
}


/** Backup putere
        ///Ramura Stanga
        elementArbore1 = new nodArbore;
        elementArbore1->text = "1";
        elementArbore1->stanga = elementArbore1->dreapta = NULL;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "-";
        elementArbore2->dreapta = elementArbore1;
        elementArbore1 = elementArbore2;
        copyArbore(elementArbore1->stanga, g_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "^";
        elementArbore2->dreapta = elementArbore1;
        elementArbore1 = elementArbore2;
        copyArbore(elementArbore1->stanga, f_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        elementArbore2->stanga = elementArbore1;
        elementArbore1 = elementArbore2;
        copyArbore(elementArbore1->dreapta, f_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        elementArbore2->dreapta = elementArbore1;
        elementArbore1 = elementArbore2;
        copyArbore(elementArbore1->stanga, g_x);

        arbore->stanga = elementArbore1;

        ///Ramura Dreapta
        elementArbore1 = new nodArbore;
        elementArbore1->text = "ln";
        elementArbore1->dreapta = NULL;
        copyArbore(elementArbore1->stanga, f_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        elementArbore2->stanga = elementArbore1;
        elementArbore1 = elementArbore2;
        copyArbore(elementArbore1->dreapta, g_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        elementArbore2->dreapta = elementArbore1;
        elementArbore1 = elementArbore2;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "^";
        copyArbore(elementArbore2->stanga, f_x);
        copyArbore(elementArbore2->dreapta, g_x);
        elementArbore1->stanga = elementArbore2;

        arbore->dreapta = elementArbore1;
*/

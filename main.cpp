#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/**                           !!!Manifest!!!                           */
/**Baieti eu propun ca formula sa fie scrisa canonic, fara ambiguitati,*/
/**fiindca este destul de complicat de implementat asta.               */

ifstream fin("input.txt");
ofstream fout("output.txt");

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
    nodArbore *stanga, *dreapta;
};

typedef nodArbore* Arbore;

nodArbore* elementArbore, * elementArbore1, * elementArbore2, * f_x, * g_x;
Arbore arbore = NULL, p;

bool FormulaCorecta = true;
string Formula;

void emptyArbore(Arbore &arbore)
{
    arbore = NULL;
}

void insertElementArbore(Arbore &p)
{
    elementArbore = new nodArbore;
    elementArbore->text = elementLista->text;
    elementLista = elementLista->next;
    p = elementArbore;
    if(elementArbore->text == "+" || elementArbore->text == "-" || elementArbore->text == "*" || elementArbore->text == "/" || elementArbore->text == "^")
    {
        insertElementArbore(p->stanga);
        insertElementArbore(p->dreapta);
    }
    else if(elementArbore->text == "sin" || elementArbore->text == "cos" || elementArbore->text == "tg" || elementArbore->text == "ctg" || elementArbore->text == "arcsin" || elementArbore->text == "arccos" || elementArbore->text == "arctg" || elementArbore->text == "arcctg")
    {
        insertElementArbore(p->stanga);
        p->dreapta = NULL;
    }
    else
        p->stanga = p->dreapta = NULL;
}

void afisareArbore(Arbore arbore)
{
    if(arbore->text == "+" || arbore->text == "-" || arbore->text == "*" || arbore->text == "/" || arbore->text == "^")
    {
        fout << "(";
        afisareArbore(arbore->stanga);
        fout << arbore->text;
        afisareArbore(arbore->dreapta);
        fout << ")";
    }
    else if(arbore->text == "sin" || arbore->text == "cos" || arbore->text == "tg" || arbore->text == "ctg" || arbore->text == "arcsin" || arbore->text == "arccos" || arbore->text == "arctg" || arbore->text == "arcctg" || arbore->text == "log")
    {
        fout << arbore->text << "(";
        afisareArbore(arbore->stanga);
        fout << ")";
    }
    else
        fout << arbore->text;
}

void deleteArbore(Arbore &arbore)
{
    if(arbore->stanga != NULL)
        deleteArbore(arbore->stanga);
    if(arbore->dreapta)
        deleteArbore(arbore->dreapta);
    delete arbore;
}

void resetArbore(Arbore &arbore)
{
    deleteArbore(arbore);
    emptyArbore(arbore);
}

void copyArbore(Arbore &copiedToArbore, Arbore copiedFromArbore)
{
    elementArbore = new nodArbore;
    elementArbore->text = copiedFromArbore->text;

    copiedToArbore = elementArbore;

    if(copiedFromArbore->stanga != NULL)
        copyArbore(copiedToArbore->stanga, copiedFromArbore->stanga);
    else
        copiedToArbore->stanga = NULL;

    if(copiedFromArbore->dreapta != NULL)
        copyArbore(copiedToArbore->dreapta, copiedFromArbore->dreapta);
    else
        copiedToArbore->dreapta = NULL;
}

void emptyList(Lista &lista)
{
    lista = NULL;
}

void insertElementLista(Lista &lista, string text)
{
    elementLista = new nodLista;
    elementLista->text = text;
    elementLista->next = NULL;
    if(lista == NULL)
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
    for(nodLista *i = lista; i != NULL; i = i->next)
        fout << i->text << " ";
}

void deleteList(Lista &lista)
{
    if(lista->next != NULL)
        deleteList(lista->next);
    delete lista;
}

void resetList(Lista &lista)
{
    deleteList(lista);
    emptyList(lista);
}

bool VerificareFormule(string Formula)
{
    ///Verifica daca este <parametru> <semn> <parametru> si daca da returneaza false
    for(int i = 0; i<Formula.size(); i++)
        if(Formula[i] == '+' || Formula[i] == '-' || Formula[i] == '*' || Formula[i] == '/' || Formula[i] == '^' || Formula.substr(0,3) == "sin" || Formula.substr(0,3) == "cos" || Formula.substr(0,2) == "tg" || Formula.substr(0,3) == "ctg" || Formula.substr(0,6) == "arcsin" || Formula.substr(0,6) == "arccos" || Formula.substr(0,5) == "arctg" || Formula.substr(0,6) == "arcctg")
            return false;

    return true;
}

bool VerificareParanteza(string Formula)
{
    ///Verificare daca formula are forma <paranteza deschisa> <formula> <paranteza inchisa>
    if(Formula[0] == '(' && Formula[Formula.size() - 1] == ')')
    {
        int j = 0;
        for(int i = 0; i < Formula.size(); i++)
            if(Formula[i] == '(')
                j++;
            else if(Formula[i] == ')')
                j--;
            else if(j == 0 && i != Formula.size()-1)
                return false;
        return true;
    }
    return false;
}

int CoordonateSemnPlusMinus(string Formula)
{
    int pozitiaSemn = -1, indiceParanteza = 0;
    bool AmGasitSemnul = 0;
    /**Cautam semnele [+] sau [-]*/
    for(int i = 0; i < Formula.size() && AmGasitSemnul == 0; i++)
        if(Formula[i] == '(')
            indiceParanteza++;
        else if(Formula[i] == ')')
            indiceParanteza--;
        else if((Formula[i] == '+' || Formula[i] == '-') && indiceParanteza == 0)
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
    /**Cautam semnul [*]*/
    for(int i = 0; i < Formula.size() && AmGasitSemnul == 0; i++)
        if(Formula[i] == '(')
            indiceParanteza++;
        else if(Formula[i] == ')')
            indiceParanteza--;
        else if((Formula[i] == '*') && indiceParanteza == 0)
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
    /**Cautam semnul [/]*/
    for(int i = 0; i < Formula.size() && AmGasitSemnul == 0; i++)
        if(Formula[i] == '(')
            indiceParanteza++;
        else if(Formula[i] == ')')
            indiceParanteza--;
        else if((Formula[i] == '/') && indiceParanteza == 0)
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
    /**Cautam semnul [^]*/
    for(int i = 0; i < Formula.size() && AmGasitSemnul == 0; i++)
        if(Formula[i] == '(')
            indiceParanteza++;
        else if(Formula[i] == ')')
            indiceParanteza--;
        else if((Formula[i] == '^') && indiceParanteza == 0)
        {
            pozitiaSemn = i;
            AmGasitSemnul = 1;
        }
    return pozitiaSemn;
}

int CoordonateSemn(string Formula)
{
    int pozitiaSemn = CoordonateSemnPlusMinus(Formula);

    if(pozitiaSemn == -1)
        pozitiaSemn = CoordonateSemnInmultire(Formula);

    if(pozitiaSemn == -1)
        pozitiaSemn = CoordonateSemnImpartire(Formula);

    if(pozitiaSemn == -1)
        pozitiaSemn = CoordonateSemnPutere(Formula);

    return pozitiaSemn;
}

int CoordonateSinus(string Formula)
{
    if(Formula.substr(0,3) == "sin")
        return 0;
    else if(Formula.substr(0,3) == "cos")
        return 1;
    else if(Formula.substr(0,2) == "tg"/** || s.substr(0,3) == "tan"*/)
        return 2;
    else if(Formula.substr(0,3) == "ctg"/** || s.substr(0,3) == "cot"*/)
        return 3;
    else if(Formula.substr(0,6) == "arcsin"/** || s.substr(0,4) == "asin"*/)
        return 4;
    else if(Formula.substr(0,6) == "arccos"/** || s.substr(0,4) == "acos"*/)
        return 5;
    else if(Formula.substr(0,5) == "arctg"/** || s.substr(0,4) == "atan"*/)
        return 6;
    else if(Formula.substr(0,6) == "arcctg"/** || s.substr(0,4) == "acot"*/)
        return 7;
    else if(Formula.substr(0,3) == "log")
        return 8;
    else
        return -1;
}

int CoordonateParanteza(string s)
{
    /**<!>*/
    int pozitiaSemn = -1;
    for(int i = 0; i< s.size(); i++)
        if(1)
            return 0;
}

void convertireInLista(string s)
{
    while(VerificareParanteza(s))
    {
        s.erase(0,1);
        s.erase(s.size()-1,1);
    }

    ///Verificarea daca are formule
    if(VerificareFormule(s))
    {
        insertElementLista(lista, s);
        return;
    }
    ///trebuie de modificat

    int pozitiaSemn = CoordonateSemn(s);

    if(pozitiaSemn == -1)
    {
        pozitiaSemn = CoordonateSinus(s);
        if(pozitiaSemn != -1)
            switch(pozitiaSemn)
            {
            /**<?> - trebuie de intrebat profesorul despre care forma vom lua.*/
            /**Pentru ca sunt diferite forme a tangentei si cotangentei       */
            /**     ========================================                 */
            /**      |             tg <=> tan               |                 */
            /**      |                                      |                 */
            /**      |             ctg <=> cot              |                 */
            /**      ========================================                 */
            /**                                                               */

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
                insertElementLista(lista, "log");
                convertireInLista(s.substr(3));
                break;
            }
        return;
    }

    if(pozitiaSemn == 0)
        if(s[pozitiaSemn] == '+')
            convertireInLista(s.substr(1));
        else if(s[pozitiaSemn] == '-')
        {
            insertElementLista(lista, s.substr(pozitiaSemn,1));
            convertireInLista("0");
            convertireInLista(s.substr(pozitiaSemn+1,s.size()-(pozitiaSemn+1)));
        }
        else
            FormulaCorecta = false;

    else if (pozitiaSemn == s.size()-1)
        FormulaCorecta = false;

    else if(FormulaCorecta)
    {
        insertElementLista(lista, s.substr(pozitiaSemn,1));
        convertireInLista(s.substr(0,pozitiaSemn));
        convertireInLista(s.substr(pozitiaSemn+1,s.size()-(pozitiaSemn+1)));
    }
}

/**
1. dx(C) = 0;
2. dx(x) = 1;
3. dx(f_x + g_x) = (dx(f_x) + dx(g_x))
4. dx(f_x - g_x) = (dx(f_x) - dx(g_x))
5. dx(f_x * g_x) = ((dx(f_x) * g_x) * (f_x * dx(g_x)))
6. dx(f_x / g_x) = (((dx(f_x) * g_x) * (f_x * dx(g_x))) / (g_x ^ 2))
7. dx(f_x ^ g_x) = (g_x *(f_x ^ (g_x - 1)) * dx(f_x) + f_x * (log(f_x ) * dx( g_x)))

UNDE:
C = multimea de constante
x - multimea de variabile in functie de care derivam
(poate fi si Y, Z sau orice altceva)
*/

void dx(Arbore &arbore)
{
    if(arbore->text == "+" || arbore->text == "-")
    {
        /**
        Aici arborele are forma
                 (+)
                /   \
              f(x)  g(x)
        Programul va deriva fiul stang si fiul drept aparte
        */

        dx(arbore->stanga);
        dx(arbore->dreapta);
    }
    else if(arbore->text == "*")
    {
        if(arbore->text == "*")
            arbore->text = "+";

        /**
        Pentru cazul cu inmultire:
                 (*)
                /   \
              f(x)  g(x)
          derivata trebuie sa arate in felul urmator
                     (+)
                /            \
              (*)            (*)
             /   \          /   \
          f(x)'  g(x)     f(x)  g(x)'
        Cream elementArbore1 si elementArbore2
                               (*)
                              /   \
                             []   []
          !!!Atentie!!! Trebuie creata o copie a fiului stang cat si a fiului drept, deoarece avem nevoie de ele nemodificate (in formula f(x) si g(x) raman asa cum sunt)

          <1> - in aceasta parte este exemplificat cum a fost copiat fiul stanga al arborelui

          Dupa ce am stabilit care sunt fii va trebui sa modificam semnul principal al expresiei (din (*) -> (+)),
          iar pentru cei doi fii semnele corespunzatoare regulii de derivare
          arbore:           (+)
                       /            \
                     (*)            (*)
                    /   \          /   \
                 f(x)   g(x)     f(x)  g(x)
          Dupa ce am modificat nodul radacina, va trebui sa derivam cel mai din stanga fiu[arbore->stanga->stanga] si cel mai din dreapta fiu[arbore->dreapta->dreapta]
          arbore:            (+)
                         /          \
                      (*)            (*)
                     /   \          /   \
                  f(x)'  g(x)     f(x)  g(x)'
        */

        elementArbore1 = new nodArbore;
        elementArbore1->text = "*";
        copyArbore(elementArbore1->stanga,arbore->stanga); /**<1>*/

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        copyArbore(elementArbore2->dreapta,arbore->dreapta);

        elementArbore1->dreapta = arbore->dreapta;
        elementArbore2->stanga = arbore->stanga;

        arbore->stanga = elementArbore1;
        arbore->dreapta = elementArbore2;

        dx(arbore->stanga->stanga);
        dx(arbore->dreapta->dreapta);
    }
    else if(arbore->text == "/")
    {
        /** Regula de derivare pentru impartire:
        dx(f_x / g_x) = (((dx(f_x) * g_x) * (f_x * dx(g_x))) / (g_x ^ 2))

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

        ///Ramura Stanga


        ///Ramura Dreapta
        elementArbore1 = new nodArbore;
        elementArbore1->text = "2";

        elementArbore2 = new nodArbore;
        elementArbore2->text = "^";
        elementArbore2->stanga = elementArbore1;
        elementArbore1 = elementArbore2;
        copyArbore(elementArbore1->stanga,g_x);

        arbore->dreapta = elementArbore1;

        resetArbore(f_x);
        resetArbore(g_x);

        ///Derivarea
        dx(arbore->stanga->dreapta->dreapta);
        dx(arbore->dreapta->dreapta->dreapta);

    }
    else if(arbore->text == "^")
    {
        /**
          ( f(x)^g(x) )' = g(x)*( f(x)^( g(x)-1 ) )*( f(x) )' + f(x)*log( f(x) )*( g(x) )'
          Aceasta este formula generala a derivatei operatiei de ridicare la putere:

          Arbore:
                  (^)
                 /   \
               f(x)  g(x)

          Arbore Modificat:
                                  (+)
                        /                     \
                     (*)                       (*)
                    /   \                 /           \
                  g(x)  (*)            (^)              (*)
                       /   \          /   \            /   \
                     (^)   f(x)'    f(x)  g(x)     (log)   g(x)'
                    /   \                          /   \
                  f(x)  (-)                     f(x)    []
                       /   \
                     g(x)   1

        */
        arbore->text = "+";
        copyArbore(f_x, arbore->stanga);
        copyArbore(g_x, arbore->dreapta);

        ///Ramura Stanga
        elementArbore1 = new nodArbore;
        elementArbore1->text = "1";

        elementArbore2 = new nodArbore;
        elementArbore2->text = "-";
        elementArbore2->dreapta = elementArbore1;
        elementArbore1 = elementArbore2;
        copyArbore(elementArbore1->stanga,g_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "^";
        elementArbore2->dreapta = elementArbore1;
        elementArbore1 = elementArbore2;
        copyArbore(elementArbore1->stanga,f_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        elementArbore2->stanga = elementArbore1;
        elementArbore1 = elementArbore2;
        copyArbore(elementArbore1->dreapta,f_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        elementArbore2->dreapta = elementArbore1;
        elementArbore1 = elementArbore2;
        copyArbore(elementArbore1->stanga,g_x);

        arbore->stanga = elementArbore1;

        ///Ramura Dreapta
        elementArbore1 = new nodArbore;
        elementArbore1->text = "log";
        elementArbore1->dreapta = NULL;
        copyArbore(elementArbore1->stanga,f_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        elementArbore2->stanga = elementArbore1;
        elementArbore1 = elementArbore2;
        copyArbore(elementArbore1->dreapta,g_x);

        elementArbore2 = new nodArbore;
        elementArbore2->text = "*";
        elementArbore2->dreapta = elementArbore1;
        elementArbore1 = elementArbore2;

        elementArbore2 = new nodArbore;
        elementArbore2->text = "^";
        copyArbore(elementArbore2->stanga,f_x);
        copyArbore(elementArbore2->dreapta,g_x);
        elementArbore1->stanga = elementArbore2;

        arbore->dreapta = elementArbore1;

        resetArbore(f_x);
        resetArbore(g_x);

        ///Derivarea
        dx(arbore->stanga->dreapta->dreapta);
        dx(arbore->dreapta->dreapta->dreapta);
    }
    else if(arbore->text == "x")
    {
        arbore->text = "1";
    }
    else
        arbore->text = "0";
}

int main()
{
    fin >> Formula;
    convertireInLista(Formula);
    if(FormulaCorecta)
    {
        elementLista = lista;
        insertElementArbore(arbore);

        resetList(lista);

        afisareArbore(arbore);

        fout << endl;
        dx(arbore);
        afisareArbore(arbore);

        resetArbore(arbore);
    }
    else
        fout << "Formula este Gresita";
    return 0;
}

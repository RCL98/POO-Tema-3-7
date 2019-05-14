#include <iostream>
#include <fstream>
#include "Harta.h"

using namespace std;


int main()
{
    ifstream f1,f2,f3,f4,f5;
    ofstream g1;
    f1.open("harta_europa");
    f2.open("harta_australia");
    f3.open("harta_africa");
    f4.open("harta_asia");
    f5.open("harta_america");
    g1.open("harta_america.out");

    General_graph g;
    f1 >> g;
    cout << g;
    cout << "Drumul minim de la Madrid la Berlin e: " << g.calculeaza_drum_minim("Madrid","Berlin") << endl;

    Tree_graph t;
    f2 >> t;
    cout << t;
    cout << "Drumul minim de la Sydney la Darwin e: " << t.calculeaza_drum_minim("Sydney","Darwin") << endl;

    DAG_graph d;
    f3 >> d;
    cout << d;
    cout << "Drumul minim de la Cairo la Mogadishu e: " << d.calculeaza_drum_minim("Cairo","Mogadishu") << endl;

    Linear_graph l;
    f4 >> l;
    cout << l;
    cout << "Drumul minim de la Beijing la Baghdad e: " << l.calculeaza_drum_minim("Beijing","Baghdad") << endl;

    Complet_graph c;
    f5 >> c;
    cout << c;
    cout << "Drumul minim de la New York la Los Angeles e: " << c.calculeaza_drum_minim("New York","Los Angeles") << endl;

    Harta <Complet_graph> America("Nr.1");
    America.aduaga_regiune(c);
    g1 << America;
    f1.close();
    f2.close();
    f3.close();
    f4.close();
    f5.close();
    return 0;
}

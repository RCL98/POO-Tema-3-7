#ifndef HARTA_H_INCLUDED
#define HARTA_H_INCLUDED
#pragma once
#include "Graf_regiune.h"

template <class T>
class Harta
{
    std :: string nume_harta;
    static unsigned id_harta;
    std :: vector <T> regiuni;
    public:
        Harta<T>(){id_harta++;}
        Harta<T>(const std :: string nume){nume_harta = nume; id_harta++;}
        ~Harta<T>(){id_harta--;}
        void aduaga_regiune(T &reg)
        {
            regiuni.push_back(reg);
        }
        void sterge_regiune(const std :: string nume)
        {
             typename std :: vector <T> :: iterator it;
             for(it = regiuni.begin(); it != regiuni.end(); ++it)
             if(it->nume_regiune == nume)
             {
                regiuni.erase(it);
                break;
             }
        }
        template <typename X>
        friend std :: istream & operator>>(std :: istream &in, Harta<X> &h)
        {
            int nr_regiuni;
            in >> nr_regiuni;
            X gr;
            for(int i = 0; i < nr_regiuni; i++)
            {
                in >> gr;
                h.regiuni.push_back(gr);
            }
            return in;
        }
        template <typename X>
        friend std :: ostream & operator<<(std :: ostream &out, const Harta<X> &h)
        {
            out << "Harta " << h.nume_harta << " are regiunile: ";
            for(auto x : h.regiuni)
                out << x;
            return out;
        }
};

template<typename T>
unsigned Harta<T> :: id_harta = 0;


#endif // HARTA_H_INCLUDED

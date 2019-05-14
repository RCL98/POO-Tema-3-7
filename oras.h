#ifndef ORAS_H_INCLUDED
#define ORAS_H_INCLUDED
#include <string>
#include <iostream>
#include <math.h>
#pragma once

class Linear_graph;
class Tree_graph;
class DAG_graph;
class General_graph;
class Complet_graph;
template<class T>
class Graph_regiune;

class oras
{
    std :: string nume;
    int id_oras;
    double x;
    double y;
    public:
        double distanta_euclid(const oras &) const;
        friend std :: istream & operator>>(std :: istream &, oras &);
        friend std :: ostream & operator<<(std:: ostream &, const oras &);
        friend class Linear_graph;
        friend class Tree_graph;
        friend class DAG_graph;
        friend class General_graph;
        friend class Complet_graph;
        template<typename T>
        friend class Graph_regiune;
};

inline double oras :: distanta_euclid(const oras &a) const
{
    return sqrt(pow((a.x - x),2) + pow((a.y - y),2));
}


inline std :: istream & operator>>(std :: istream &in, oras &o)
{
    in.ignore(1,'\n');
    getline(in,o.nume);
    if(o.nume[o.nume.length()-1]=='\r')
        o.nume.erase(o.nume.begin()+o.nume.length()-1);
    in >> o.x;
    in >> o.y;
    return in;
}

inline std :: ostream & operator<<(std :: ostream &out, const oras &o)
{
    out << "Oras: " << o.nume << std :: endl;
    out << "Oras id: " << o.id_oras <<std :: endl;
    out << "Coordonate oras: (" << o.x << ", " << o.y << ") " << std :: endl;
    out << std :: endl;
    return out;
}

#endif // ORAS_H_INCLUDED

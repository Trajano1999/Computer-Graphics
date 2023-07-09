// *********************************************************************
// ** 
// ** Nombre    : Juan Manuel
// ** Apellidos : Mateos Pérez
// ** DNI       : 77555876Z 
// ** Informática Gráfica - curso 2021-22
// ** Doble Grado Informática y Matemáticas
// **
// *********************************************************************

#ifndef LATAPEONES_H
#define LATAPEONES_H

#include "grafo-escena.h"

// ---------------------------------------------------------------------
// PEONES
// ---------------------------------------------------------------------

class PeonMadera : public NodoGrafoEscena{
    public:
        PeonMadera();
};

class PeonBlanco : public NodoGrafoEscena{
    public:
        PeonBlanco();
};

class PeonNegro : public NodoGrafoEscena{
    public:
        PeonNegro();
};

// ---------------------------------------------------------------------
// ELEMENTOS LATAS
// ---------------------------------------------------------------------

class TapaSuperiorLata : public NodoGrafoEscena{
    public:
        TapaSuperiorLata();
};

class TapaInferiorLata : public NodoGrafoEscena{
    public:
        TapaInferiorLata();
};

class CuerpoLataCola : public NodoGrafoEscena{
    public:
        CuerpoLataCola();
};

class CuerpoLataPepsi : public NodoGrafoEscena{
    public:
        CuerpoLataPepsi();
};

class CuerpoLataUGR : public NodoGrafoEscena{
    public:
        CuerpoLataUGR();
};

// ---------------------------------------------------------------------
// LATAS
// ---------------------------------------------------------------------

class LataCola : public NodoGrafoEscena{
    public:
        LataCola();
};

class LataPepsi : public NodoGrafoEscena{
    public:
        LataPepsi();
};

class LataUGR : public NodoGrafoEscena{
    public:
        LataUGR();
};

// ---------------------------------------------------------------------
// LATAPEONES
// ---------------------------------------------------------------------

class LataPeones : public NodoGrafoEscena{
    public: 
        LataPeones();
};

// ---------------------------------------------------------------------
// VARIASLATASPEONES
// ---------------------------------------------------------------------

class VariasLatasPeones : public NodoGrafoEscena{
    public:
        VariasLatasPeones();
};

#endif

// *********************************************************************
// ** 
// ** Nombre    : Juan Manuel
// ** Apellidos : Mateos Pérez
// ** DNI       : 77555876Z 
// ** Informática Gráfica - curso 2021-22
// ** Doble Grado Informática y Matemáticas
// **
// *********************************************************************

#ifndef MRPOTATO_HPP
#define MRPOTATO_HPP

#include "grafo-escena.h"

class MrPotato : public NodoGrafoEscena{
    protected:
        Matriz4f * pm_traslacion_cejas = nullptr;
        Matriz4f * pm_rotacion_cuerpo  = nullptr;
        Matriz4f * pm_rotacion_brazos  = nullptr;

    public:
        MrPotato();

        void setTraslacionCejas( const float nueva_traslacion_cejas );
        void setRotacionCuerpo( const float nueva_rotacion_cuerpo );
        void setRotacionBrazos( const float nueva_rotacion_brazos );
        
        unsigned leerNumParametros() const;                                                    
        void actualizarEstadoParametro( const unsigned iParam, const float t_sec );
};

class Pie : public NodoGrafoEscena{
    public:
        Pie();
};

class Cuerpo : public NodoGrafoEscena{
    public:
        Cuerpo();
};

class Ojo : public NodoGrafoEscena{
    public:
        Ojo();
};

class Pupila : public NodoGrafoEscena{
    public:
        Pupila();
};

class Nariz : public NodoGrafoEscena{
    public:
        Nariz();
};

class Oreja : public NodoGrafoEscena{
    public:
        Oreja();
};

class Sombrero : public NodoGrafoEscena{
    public:
        Sombrero();
};

class Bigote : public NodoGrafoEscena{
    public:
        Bigote();
};

class Boca : public NodoGrafoEscena{
    public:
        Boca();
};

class Sonrisa : public NodoGrafoEscena{
    public:
        Sonrisa();
};

class Brazo : public NodoGrafoEscena{
    public:
        Brazo( Matriz4f * &rotacion_brazos );
};

class Mano : public NodoGrafoEscena{
    public:
        Mano();
};

class Ceja : public NodoGrafoEscena{
    public:
        Ceja( Matriz4f * &traslacion_ceja );
};

#endif

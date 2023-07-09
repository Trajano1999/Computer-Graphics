// *********************************************************************
// ** 
// ** Nombre    : Juan Manuel
// ** Apellidos : Mateos Pérez
// ** DNI       : 77555876Z 
// ** Informática Gráfica - curso 2021-22
// ** Doble Grado Informática y Matemáticas
// **
// *********************************************************************

#ifndef IG_MALLAIND_HPP
#define IG_MALLAIND_HPP

#include <vector>          // usar std::vector

#include "objeto3d.h"   // declaración de 'Objeto3D'
#include "array-verts.h" // clase 'ArrayVert'

// --------------------------------------------------------------------
// clase para objetos gráficos genéricos

class MallaInd : public Objeto3D
{
   // P5 VN
   private:
      // array de vértices con los segmentos de las normales (vis. con GL_LINES) 
      // ( se crea bajo demanda en `visualizarNormales`) 
      ArrayVertices * array_verts_normales = nullptr ;
      std::vector<Tupla3f> segmentos_normales ; // guarda los segmentos de normales

      void visualizarNormales();

   protected:
      // COMPLETAR: incluir aquí las variables y métodos privados que sean
      // necesarios para una malla indexada
      // ......

      std::vector<Tupla3f> vertices ;
      std::vector<Tupla3i> triangulos ;

      std::vector<Tupla3f> col_ver ;  // colores de los vértices
      std::vector<Tupla3f> nor_ver ;  // normales de vértices
      std::vector<Tupla3f> nor_tri ;  // normales de triangulos
      std::vector<Tupla2f> cc_tt_ver ; // coordenadas de textura de los vértices

      // array de vértices con información de tablas para visualizar
      // (se crea bajo demanda: la primera vez que se llama a 'visualizarGL')
      ArrayVertices * array_verts = nullptr ; 

      // normales de triángulos y vértices
      void calcularNormales();

      // calculo de las normales de triángulos (solo si no están creadas ya)
      void calcularNormalesTriangulos() ;

   public:
      // crea una malla vacía (nombre: "malla indexada nueva vacía")
      MallaInd() ;

      // crea una malla vacía con un nombre concreto:
      MallaInd( const std::string & nombreIni );

      // visualizar el objeto con OpenGL
      virtual void visualizarGL( ContextoVis & cv ) ;
} ;
// --------------------------------------------------------------------
// Clase para mallas obtenidas de un archivo 'ply'
// es un tipo de malla indexada que define un nuevo constructor
// que recibe el nombre del archivo ply como parámetro

class MallaPLY : public MallaInd
{
   public:
      MallaPLY( const std::string & nombre_arch ) ;
} ;


// --------------------------------------------------------------------
// P1
// --------------------------------------------------------------------

class Cubo : public MallaInd {
   public:
      Cubo();
};

class Tetraedro : public MallaInd {
   public: 
      Tetraedro();
};

class CuboColores : public MallaInd {
   public:
      CuboColores();
};

// --------------------------------------------------------------------
// EP1 (1) 
// --------------------------------------------------------------------

class EstrellaZ : public MallaInd {
   public:
      EstrellaZ( const unsigned int n );
};

// --------------------------------------------------------------------
// EP2 (2) 
// --------------------------------------------------------------------

class RejillaY : public MallaInd {
   public:
      RejillaY( const unsigned m, const unsigned n );
};

// --------------------------------------------------------------------
// P4
// --------------------------------------------------------------------

class Cubo24 : public MallaInd{
   public:
      Cubo24();
} ;

// --------------------------------------------------------------------
// EP4 (1)
// --------------------------------------------------------------------

class MallaDiscoP4 : public MallaInd{
   public:
      MallaDiscoP4();
};

#endif

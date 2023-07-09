// *********************************************************************
// ** 
// ** Nombre    : Juan Manuel
// ** Apellidos : Mateos Pérez
// ** DNI       : 77555876Z 
// ** Informática Gráfica - curso 2021-22
// ** Doble Grado Informática y Matemáticas
// **
// *********************************************************************

#include "ig-aux.h"
#include "tuplasg.h"
#include "lector-ply.h"
#include "matrices-tr.h"
#include "malla-revol.h"

// para calcular las normales
#include <cmath>

using namespace std ;

// *****************************************************************************

// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar  // P2 // P4
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   // COMPLETAR: Práctica 4: completar: ...

   // calcular normales

   std::vector<Tupla3f> normales_aristas;
   Tupla3f arista, normal_arista;

   // calcular vectores normales a las aristas
   for( unsigned i=0; i<perfil.size()-1; ++i ){
      arista = perfil[i+1] - perfil[i];
      normal_arista[0] =  arista[1];
      normal_arista[1] = -arista[0];
      normal_arista[2] = 0;

      if( normal_arista.lengthSq() > 0 )
         normales_aristas.push_back( normal_arista.normalized() );
      else
         normales_aristas.push_back( normal_arista );                                              // no la normalizamos para no dividir por 0
   }

   nor_ver.insert( nor_ver.begin(), perfil.size(), {0.0, 0.0, 0.0} );
   
   // vector normal al primer vértice
   nor_ver[0] = normales_aristas[0];

   // vectores normales a vértices intermedios
   for( unsigned i=1; i<perfil.size()-1; ++i ){
      nor_ver[i] = normales_aristas[i] + normales_aristas[i-1];
      if( nor_ver[i].lengthSq() != 0 )
         nor_ver[i] = nor_ver[i].normalized();
   }

   // vector normal al último vértice
   if( normales_aristas[ perfil.size()-2 ].lengthSq() != 0 )
      nor_ver[ perfil.size()-1 ] = normales_aristas[ perfil.size()-2 ].normalized();

   // calcular coordenadas de textura

   std::vector<float> d, t;
   float den = 0;

   for( unsigned i=0; i<perfil.size()-1; ++i ){
      d.push_back( sqrt(( perfil[i+1] - perfil[i] ).lengthSq()) );
      den += d[i];
   }
 
   t.push_back(0.0);
   for( unsigned i = 1; i<perfil.size(); ++i ){
      t.push_back( t[i-1] + d[i-1]/den );
   }

   // COMPLETAR: Práctica 2: completar: creación de la malla....

   // creamos la tabla de vértices 
   Matriz4f matriz_rotacion;
   float angulo_giro, t_x, t_y;

   // recorremos todas las instancias
   for ( unsigned int i=0; i<num_copias; ++i ){                                
      angulo_giro = ( 360 * i ) / ( num_copias - 1 );
      matriz_rotacion = MAT_Rotacion( angulo_giro, 0.0, 1.0, 0.0 );                                // aplicamos la matriz de giro con respecto al eje y de ángulo "angulo_giro" 

      // recorremos los vértices de cada instancia         
      for ( unsigned int j=0; j<perfil.size(); ++j ){                              
         vertices.push_back( matriz_rotacion * perfil[j] );                                        // aplicamos la rotación a todos los vertices del perfil j-ésimo

         // Añadimos coordenadas de textura (P4)
         nor_ver.push_back(matriz_rotacion * nor_ver[j]);
         t_x = (float)i/(num_copias-1);
         t_y = 1.0 - t[j];
         cc_tt_ver.push_back({ t_x, t_y });
      }
   }

   // creamos la tabla de triángulos
   int k;
   int m = perfil.size();

   // recorremos todas las instancias menos la última
   for ( unsigned int i=0; i<num_copias-1; ++i )                               
      // recorremos los vértices de cada instancia menos el último
      for ( int j=0; j<m-1; ++j ){                                             
         k = i * m + j;
         triangulos.push_back({ k, k + m    , k + m + 1 });
         triangulos.push_back({ k, k + m + 1, k     + 1 });
      }
}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY  // P2
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)  
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   
   vector<Tupla3f> el_perfil;
   LeerVerticesPLY( nombre_arch, el_perfil );
   inicializar( el_perfil, nperfiles );
}

// --------------------------------------------------------------------
// P2
// --------------------------------------------------------------------

Cilindro::Cilindro( const int num_verts_per, const unsigned nperfiles ){
   const float altura = 1.0;
   const float radio  = 1.0;
   vector<Tupla3f> el_perfil;
   
   assert( num_verts_per >= 4 );                                                                   // al menos se necesitan 4 vértices para generar un cilindro
   ponerNombre( "Cilindro generado por revolución" );                                              // (x, y, z) donde y = altura
   ponerIdentificador(-1);

   // vértice de la base
   el_perfil.push_back({ 0.0, 0.0, 0.0 });                                   
   
   // num_verts_per-2 vertices restantes dibujados en la pared del cilindro a distintas alturas (incluyendo base y tapa)
   for ( int i=0; i<num_verts_per-2; ++i )
      el_perfil.push_back({ radio , (i * altura) / (num_verts_per - 3), 0.0 });

   // vértice de la tapa superior
   el_perfil.push_back({ 0.0, altura, 0.0 });

   inicializar( el_perfil, nperfiles + 1 );                                                        // el +1 es porque el punto inicial y final coinciden
}

Cono::Cono( const int num_verts_per, const unsigned nperfiles ){
   const float altura = 1.0;
   const float radio  = 1.0;
   vector<Tupla3f> el_perfil;

   assert( num_verts_per >= 3 );                                                                   // al menos se necesitan 3 vértices para generar un cono
   ponerNombre( "Cono generado por revolución" );                                                  // (x, y, z) donde y = altura
   ponerIdentificador(-1);

   // vértice de la base
   el_perfil.push_back({ 0.0, 0.0, 0.0});

   // num_verts_per-1 vertices restantes dibujados en la pared inclinada del cono a distintas alturas (incluyendo base y punta)
   for ( int i=0; i<num_verts_per-1; ++i ){
      el_perfil.push_back({ radio - ( (i * radio) / (num_verts_per - 2) ), (i * altura) / (num_verts_per - 2), 0.0 });
   }
   
   inicializar( el_perfil, nperfiles + 1 );                                                        // el +1 es porque el punto inicial y final coinciden
}

Esfera::Esfera( const int num_verts_per, const unsigned nperfiles ){
   const float radio       = 1.0;
   const float angulo_giro = 180.0 / (num_verts_per-1);

   vector<Tupla3f> el_perfil;

   assert( num_verts_per >= 3 );                                                                   // voy a imponer que al menos se necesiten 3 vértices para generar una esfera
   ponerNombre( "Esfera generada por revolución" );                                                // (x, y, z) donde y = altura
   ponerIdentificador(-1);

   Matriz4f matriz_rotacion = MAT_Rotacion( angulo_giro, 0.0, 0.0, 1.0 );                          // aplicamos la matriz de giro con respecto al eje z de ángulo "angulo_giro" 

   // insertamos el "polor sur" de la esfera
   Tupla3f el_vertice = { 0.0, (-1) * radio, 0.0 };
   el_perfil.push_back( el_vertice );

   // num_verts_per-1 vertices restantes dibujados en la pared de la esfera (sin incluir el "polo norte")
   for ( int i=0; i<num_verts_per-1; ++i ){
      el_vertice = matriz_rotacion * el_vertice;
      el_perfil.push_back( el_vertice );
   }

   // insertamos el "polor norte" de la esfera
   el_vertice = { 0.0, radio, 0.0 };
   el_perfil.push_back( el_vertice );

   inicializar( el_perfil, nperfiles + 1 );                                                        // el +1 es porque el punto inicial y final coinciden
}

// --------------------------------------------------------------------
// P3
// --------------------------------------------------------------------

Semiesfera::Semiesfera( const int num_verts_per, const unsigned nperfiles ){
   const float radio       = 1.0;
   const float angulo_giro = 90.0 / (num_verts_per-1);

   vector<Tupla3f> el_perfil;

   assert( num_verts_per >= 3 );                                                                   // voy a imponer que al menos se necesiten 3 vértices para generar una semiesfera
   ponerNombre( "Semiesfera generada por revolución" );                                            // (x, y, z) donde y = altura
   ponerIdentificador(-1);

   Matriz4f matriz_rotacion = MAT_Rotacion( angulo_giro, 0.0, 0.0, 1.0 );                          // aplicamos la matriz de giro con respecto al eje z de ángulo "angulo_giro" 

   // insertamos el "polor sur" de la semiesfera
   Tupla3f el_vertice = { 0.0, (-1) * radio, 0.0 };
   el_perfil.push_back( el_vertice );

   // num_verts_per-1 vertices restantes dibujados en la pared de la semiesfera
   for ( int i=0; i<num_verts_per-1; ++i ){
      el_vertice = matriz_rotacion * el_vertice;
      el_perfil.push_back( el_vertice );
   }

   // insertamos el centro de la semiesfera
   el_vertice = { 0.0, 0.0, 0.0 };
   el_perfil.push_back( el_vertice );

   inicializar( el_perfil, nperfiles + 1 );                                                        // el +1 es porque el punto inicial y final coinciden
}
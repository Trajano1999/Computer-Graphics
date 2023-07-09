// *********************************************************************
// ** 
// ** Nombre    : Juan Manuel
// ** Apellidos : Mateos Pérez
// ** DNI       : 77555876Z 
// ** Informática Gráfica - curso 2021-22
// ** Doble Grado Informática y Matemáticas
// **
// *********************************************************************

// *********************************************************************
// **
// ** Gestión de una grafo de escena (implementación)
// ** Copyright (C) 2016 Carlos Ureña
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"
#include "matrices-tr.h"
#include "grafo-escena.h"

// EP3 (1)
#include "malla-revol.h"

// EP3 (2)
#include "malla-ind.h"

using namespace std ;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != NULL );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const Matriz4f & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new Matriz4f() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != NULL );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL( ContextoVis & cv )   // P3 // P4
{
   // COMPLETAR: práctica 3: recorrer las entradas y visualizar cada nodo.
   
   // guardamos puntero al material activo
   Material * material_pre = cv.iluminacion ? cv.material_act : nullptr;

   // hacemos push de la matriz modelview
   cv.cauce_act->pushMM();

   // guardamos el color actual
   const Tupla4f color_previo = leerFijarColVertsCauce( cv );

   // recorremos las entradas del nodo
   for( auto entrada: entradas ){
      switch( entrada.tipo ){
         case TipoEntNGE::objeto:                                                                  // si es un puntero a un sub-objeto
            entrada.objeto->visualizarGL(cv);                                                      // llamamos recursivamente al método visualizarGL para ese sub-objeto
            break;

         case TipoEntNGE::transformacion:                                                          // si es una matriz de transformación
            cv.cauce_act->compMM(*entrada.matriz);                                                 // componemos la matriz con la modelview actual         
            break;
         
         case TipoEntNGE::material:
            if( cv.iluminacion && !cv.modo_seleccion ){
               cv.material_act = entrada.material;
               cv.material_act->activar(cv);
            }
            break;
            
         default:
            std::cout << "Error NodoGrafoEscena::visualizarGL" << std::endl;
            exit(-1);
            break;
      }
   }

   // restauramos el color previo
   glColor4fv( color_previo );

   // hacemos pop de la matriz modelview
   cv.cauce_act->popMM();

   // COMPLETAR: práctica 4: en la práctica 4, si 'cv.iluminacion' es 'true',
   // se deben de gestionar los materiales:
   //   1. guardar puntero al material activo al inicio (está en cv.material_act)
   //   2. si una entrada es de tipo material, activarlo y actualizar 'cv.material_act'
   //   3. al finalizar, restaurar el material activo del inicio (si es distinto del actual)

   if( material_pre != nullptr ){
      cv.material_act = material_pre;
      cv.material_act->activar(cv);
   }
}




// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...
// ignora el colo o identificador del nodo, ignora las entradas de tipo material
// (se supone que el estado de OpenGL está fijado antes de esta llamada de alguna forma adecuada)




// -----------------------------------------------------------------------------

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )   // P3
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   
   unsigned indice = entradas.size();
   entradas.push_back( entrada );

   return indice;
}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const Matriz4f & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
Matriz4f * NodoGrafoEscena::leerPtrMatriz( unsigned indice ) // P3
{
   // COMPLETAR: práctica 3: devolver puntero la matriz en ese índice
   //   (debe de dar error y abortar si no hay una matriz en esa entrada)
   // ........(sustituir 'return nullptr' por lo que corresponda)

   assert( indice < entradas.size() );
   assert( entradas[indice].tipo == TipoEntNGE::transformacion );
   assert( entradas[indice].matriz != nullptr );

   return entradas[indice].matriz;
}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC(){  // P5
   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   
   if( !centro_calculado ){
      Matriz4f mat = MAT_Ident();
      Tupla3f suma = { 0,0,0 };
      int num_objetos = 0;
      
      for( auto entrada : entradas )
         switch( entrada.tipo ){
            case TipoEntNGE::objeto :
               entrada.objeto->calcularCentroOC();
               suma = suma + mat * (entrada.objeto->leerCentroOC());
               ++num_objetos;
               break;

            case TipoEntNGE::transformacion :
               mat = mat * (*entrada.matriz);
               break;
            
            default:
               break;
         }

      Tupla3f centro = suma/num_objetos;
      ponerCentroOC( centro );
      centro_calculado = true;
   }
}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto  // P5
(
   const int         ident_busc, // identificador a buscar
   const Matriz4f &  mmodelado,  // matriz de modelado
   Objeto3D       ** objeto,     // (salida) puntero al puntero al objeto
   Tupla3f &         centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   
   calcularCentroOC();

   // 2. si el identificador del nodo es el que se busca, ya está (terminar)

   if( leerIdentificador() == ident_busc ){
      centro_wc = mmodelado * leerCentroOC();
      if( objeto == nullptr )
         std::cout << "\tIdentificador encontrado con puntero asociado nulo" << std::endl;
      *objeto = this;
      return true;
   }   

   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   
   Matriz4f mat = mmodelado;
   bool encontrado = false;

   for( auto entrada : entradas ){
      switch( entrada.tipo ){
         case TipoEntNGE::objeto :
            encontrado = entrada.objeto->buscarObjeto( ident_busc, mat, objeto, centro_wc );
            break;

         case TipoEntNGE::transformacion :
            mat = mat * (*entrada.matriz);
            break;
         
         default:
            break;
      }
      if( encontrado ) break;
   }

   // ni este nodo ni ningún hijo es el buscado: terminar
   return encontrado;
}

// -----------------------------------------------------------------------------
// EP3 (1)
// -----------------------------------------------------------------------------

GrafoEstrellaX::GrafoEstrellaX( unsigned int n ){
   ponerNombre("Grafo Extrella X");
   ponerIdentificador(302);

   // movimiento
   unsigned rot = agregar(MAT_Rotacion( 0.0, 1.0, 0.0, 0.0 ));

   agregar(new Estrella( n ));

   for( unsigned int i=0; i<n; ++i ){
      agregar(MAT_Rotacion( 360/n, 1.0, 0.0, 0.0 ));
      agregar( new ConoPunta() );
   }

   // aplicamos el movimiento
   rotacion = leerPtrMatriz( rot );
}

unsigned GrafoEstrellaX::leerNumParametros() const{
   return 1;
}

void GrafoEstrellaX::actualizarEstadoParametro( const unsigned iParam, const float t_sec ){
   assert( iParam < leerNumParametros() );
   if( iParam == 0){
      *rotacion = MAT_Rotacion( (2.5 * 360 * t_sec), 1.0, 0.0, 0.0 );;
   }
}

Estrella::Estrella( unsigned int n ){
   ponerNombre("Extrella");
   ponerIdentificador(-1);
   
   agregar(MAT_Rotacion( 90, 0.0, 1.0, 0.0 ));
   agregar(MAT_Escalado( 2.6, 2.6, 2.6 ));
   agregar(MAT_Traslacion( -0.5, -0.5, 0.0 ));

   agregar(new EstrellaZ( n ));
}

ConoPunta::ConoPunta(){
   ponerNombre("ConoPunta");
   ponerIdentificador(-1);

   agregar(MAT_Traslacion( 1.3, 0.0, -1.3 ));
   agregar(MAT_Rotacion(  90, 0.0, 1.0, 0.0 ));
   agregar(MAT_Rotacion( -90, 0.0, 0.0, 1.0 ));
   agregar(MAT_Traslacion( 0.0, 0.0, -1.3 ));
   agregar(MAT_Escalado( 0.14, 0.15, 0.14 ));
   
   agregar(new Cono( 50, 50 ));
}

// -----------------------------------------------------------------------------
// EP3 (2)
// -----------------------------------------------------------------------------

GrafoCubos::GrafoCubos(){
   ponerNombre("Grafo Cubos");
   ponerIdentificador(303);

   // añadimos el cubo central
   agregar(new CuboRejilla());

   // añadimos cubo pequeños laterales
   agregar( new CuboCaraEjeX() );
   agregar( new CuboCaraEjeY() );
   agregar( new CuboCaraEjeZ() );
}

CuboRejilla::CuboRejilla(){
   ponerNombre("CuboRejilla");
   ponerIdentificador(-1);

   agregar(MAT_Traslacion( 1.0, 0.0, 0.0 ));
   agregar(MAT_Rotacion( 90, 0.0, 0.0, 1.0 ));
   agregar(new CaraRejilla());
   agregar(MAT_Rotacion( 270, 0.0, 0.0, 1.0 ));
   agregar(MAT_Traslacion( -1.0, 0.0, 0.0 ));

   agregar(MAT_Traslacion( -1.0, 0.0, 0.0 ));
   agregar(MAT_Rotacion( 90, 0.0, 0.0, 1.0 ));
   agregar(new CaraRejilla());
   agregar(MAT_Rotacion( 270, 0.0, 0.0, 1.0 ));
   agregar(MAT_Traslacion( 1.0, 0.0, 0.0 ));

   agregar(MAT_Traslacion( 0.0, 1.0, 0.0 ));
   agregar(new CaraRejilla());
   agregar(MAT_Traslacion( 0.0, -1.0, 0.0 ));

   agregar(MAT_Traslacion( 0.0, -1.0, 0.0 ));
   agregar(new CaraRejilla());
   agregar(MAT_Traslacion( 0.0, 1.0, 0.0 ));

   agregar(MAT_Traslacion( 0.0, 0.0, 1.0 ));
   agregar(MAT_Rotacion( 90, 1.0, 0.0, 0.0 ));
   agregar(new CaraRejilla());
   agregar(MAT_Rotacion( 270, 1.0, 0.0, 0.0 ));
   agregar(MAT_Traslacion( 0.0, 0.0, -1.0 ));

   agregar(MAT_Traslacion( 0.0, 0.0, -1.0 ));
   agregar(MAT_Rotacion( 90, 1.0, 0.0, 0.0 ));
   agregar(new CaraRejilla());
   agregar(MAT_Rotacion( 270, 1.0, 0.0, 0.0 ));
   agregar(MAT_Traslacion( 0.0, 0.0, +1.0 ));
}

CaraRejilla::CaraRejilla(){
   ponerNombre("CaraRejilla");
   ponerIdentificador(-1);

   agregar(MAT_Escalado( 2.0, 1.0, 2.0 ));
   agregar(MAT_Traslacion( -0.5, 0.0, -0.5 ));
   agregar(new RejillaY( 5, 5 ));
   agregar(MAT_Traslacion( 0.5, 0.0, 0.5 ));
   agregar(MAT_Escalado( 1.0/2.0, 1.0, 1.0/2.0 ));
}

CuboCara::CuboCara(){
   ponerNombre("CuboCara");
   ponerIdentificador(-1);

   agregar(MAT_Traslacion( 1.5, 0.0, 0.0 ));
   agregar(MAT_Escalado( 0.5, 0.3, 0.3 ));
   agregar(new Cubo());
   agregar(MAT_Escalado( 1.0/0.5, 1.0/0.3, 1.0/0.3 ));
   agregar(MAT_Traslacion( -1.5, 0.0, 0.0 ));
}

CuboCaraEjeX::CuboCaraEjeX(){
   ponerNombre("CuboCaraEjeX");
   ponerIdentificador(-1);

   agregar(new CuboCara());
   agregar(MAT_Rotacion( 180.0, 0.0, 1.0, 0.0 ));
   agregar(new CuboCara());
}

CuboCaraEjeY::CuboCaraEjeY(){
   ponerNombre("CuboCaraEjeY");
   ponerIdentificador(-1);

   agregar(MAT_Rotacion( 90, 0.0, 0.0, 1.0 ));
   agregar(new CuboCara());
   agregar(MAT_Rotacion( 180, 0.0, 0.0, 1.0 ));
   agregar(new CuboCara());
}

CuboCaraEjeZ::CuboCaraEjeZ(){
   ponerNombre("CuboCaraEjeZ");
   ponerIdentificador(-1);

   agregar(MAT_Rotacion( 90, 0.0, 1.0, 0.0 ));
   agregar(new CuboCara());
   agregar(MAT_Rotacion( 180, 0.0, 1.0, 0.0 ));
   agregar(new CuboCara());
}

// -----------------------------------------------------------------------------
// P4
// -----------------------------------------------------------------------------

NodoCubo24::NodoCubo24(){
   ponerNombre("Nodo Cubo 24");
   ponerIdentificador(405);
   
   Textura * tex = new Textura("../recursos/imgs/window-icon.jpg");
   agregar(new Material( tex, 0.5, 0.3, 0.7, 20.0 ));
   agregar(new Cubo24());
}

// -----------------------------------------------------------------------------
// EP4 (1)
// -----------------------------------------------------------------------------

NodoDiscoP4::NodoDiscoP4(){
   ponerIdentificador(406);
   ponerNombre("Nodo Disco P4");
   Textura * tex = new Textura("../trabajo/imgs/EP4(1).jpg");
   agregar( new Material(tex, 0.5, 0.5, 0.5, 20) );
   agregar( new MallaDiscoP4() );
}

// -----------------------------------------------------------------------------
// EP5 (1)
// -----------------------------------------------------------------------------

GrafoEsferasP5::GrafoEsferasP5(){
   ponerNombre("Grafo Esferas P5");

   const unsigned
      n_filas_esferas = 8,
      n_esferas_x_fila = 5 ;
   const float
      e = 0.4/n_esferas_x_fila ;

   agregar(MAT_Escalado( e,e,e ));
   
   for( unsigned i = 0 ; i < n_filas_esferas ; i++ ){
      NodoGrafoEscena * fila_esferas = new NodoGrafoEscena() ;
      for( unsigned j = 0 ; j < n_esferas_x_fila ; j++ ){
         MallaInd * esfera = new Esfera( 20, 20 );
         esfera->ponerIdentificador(510 + i*n_esferas_x_fila + j);                                 // del 510 a 549 (ambos incluidos)
         fila_esferas->agregar( MAT_Traslacion( 2.2, 0.0, 0.0 ));
         fila_esferas->agregar( esfera );
      }
      agregar( fila_esferas );
      agregar( MAT_Traslacion( 0.0, 0.0, 5.0 ));
   }
}

// -----------------------------------------------------------------------------
// EP5 (2)
// -----------------------------------------------------------------------------

GrafoEsferasP5_2::GrafoEsferasP5_2(){
   const unsigned
      n_filas_esferas = 8,
      n_esferas_x_fila = 5 ;
   const float
      e = 2.5/n_esferas_x_fila ;

   agregar( MAT_Escalado( e, e, e ));

   for( unsigned i = 0 ; i < n_filas_esferas ; i++ ){
      NodoGrafoEscena * fila_esferas = new NodoGrafoEscena() ;
      fila_esferas->agregar( MAT_Traslacion( 3.0, 0.0, 0.0 ));
      for( unsigned j = 0 ; j < n_esferas_x_fila ; j++ ){
         MallaInd * esfera = new Esfera( 20, 20 ) ;
         esfera->ponerIdentificador(550 + i*n_esferas_x_fila + j);                                 // del 550 a 589 (ambos incluidos)
         fila_esferas->agregar( MAT_Traslacion( 2.5, 0.0, 0.0 ));
         fila_esferas->agregar( esfera );
      }
      agregar( fila_esferas );
      agregar( MAT_Rotacion( 360.0/n_filas_esferas, { 0.0, 1.0, 0.0 }));
   }
}
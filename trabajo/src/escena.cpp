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
#include "escena.h"

#include "objeto3d.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "practicas.h"
#include "camara.h"
#include "materiales-luces.h"
#include "seleccion.h"

// P3
#include "modelo-jer.h"

// P4
#include "latapeones.h"

// -----------------------------------------------------------------------------------------------

// P5 VN
void Escena::visualizarNormales( ContextoVis & cv )
{
   // recuperar el objeto raiz de esta escena y comprobar que está ok.
   bool ilum_ant = cv.iluminacion ;
   assert( cv.cauce_act != nullptr );
   Objeto3D * objeto = objetos[ind_objeto_actual] ; assert( objeto != nullptr );

   // configurar el cauce:
   cv.cauce_act->fijarEvalMIL( false );
   cv.cauce_act->fijarEvalText( false );
   cv.cauce_act->fijarModoSombrPlano( true ); // sombreado plano
   glLineWidth( 1.5 ); // ancho de líneas (se queda puesto así)
   glColor4f( 1.0, 0.7, 0.4, 1.0 ); // color de las normales

   // configurar el contexto de visualizacion
   cv.visualizando_normales = true ;   // hace que MallaInd::visualizarGL visualize las normales.
   cv.iluminacion           = false ;

   // visualizar objeto actual
   objetos[ind_objeto_actual]->visualizarGL( cv );

   // restaurar atributos cambiados en el contexto de visualización
   cv.visualizando_normales = false ;
   cv.iluminacion = ilum_ant ;
}

Escena::Escena()  // P4 // P5
{
   // COMPLETAR: Práctica 4: inicializar 'col_fuentes' y 'material_ini'
   col_fuentes = new Col2Fuentes();
   material_ini = new Material( 0.4, 0.5, 0.6, 20 );  // jjj

   // COMPLETAR: Práctica 5: hacer 'push_back' de varias cámaras perspectiva u ortogonales,
   // (sustituir la cámara orbital simple ('CamaraOrbitalSimple') por varias cámaras de 3 modos ('Camara3Modos')
   // jjj camaras.push_back( new CamaraOrbitalSimple() );
   camaras.push_back(new Camara3Modos( true, {-3.0, 3.0, 3.5}, 1.0, {0.0, 0.0, 0.0}, 70.0));

   camaras.push_back(new Camara3Modos(  true,  {5.0, 0.0, 0.0}, 1.0, {0.0, 0.0, 0.0}, 70.0));      // alzado perspectiva
   camaras.push_back(new Camara3Modos( false,  {5.0, 0.0, 0.0}, 1.0, {0.0, 0.0, 0.0}, 70.0));      // alzado ortogonal
   camaras.push_back(new Camara3Modos(  true,  {0.0, 0.0, 5.0}, 1.0, {0.0, 0.0, 0.0}, 70.0));      // perfil perspectiva
   camaras.push_back(new Camara3Modos( false,  {0.0, 0.0, 5.0}, 1.0, {0.0, 0.0, 0.0}, 70.0));      // perfil ortogonal
   camaras.push_back(new Camara3Modos(  true, {0.01, 5.0, 0.0}, 1.0, {0.0, 0.0, 0.0}, 70.0));      // planta perspectiva
   camaras.push_back(new Camara3Modos( false, {0.01, 5.0, 0.0}, 1.0, {0.0, 0.0, 0.0}, 70.0));      // planta ortogonal 
}

// -----------------------------------------------------------------------------------------------
// visualiza la escena en la ventana actual, usando la configuración especificada en 'cv'

void Escena::visualizarGL( ContextoVis & cv )   // P1 // P4
{
   using namespace std ;

   // recuperar el cauce actual de 'cv' en 'cauce', activarlo
   Cauce * cauce = cv.cauce_act ; assert( cauce != nullptr );
   cauce->activar() ;

   // recuperar la cámara actual de esta escena y  fijar las matrices 'modelview'
   // y 'projection' en el cauce gráfico (es decir: activar la cámara actual)
   CamaraInteractiva * camara = camaras[ind_camara_actual] ; assert( camara != nullptr );
   const float ratio_vp = float(cv.ventana_tam_y)/float(cv.ventana_tam_x) ;
   camara->fijarRatioViewport( ratio_vp );
   camara->activar( *cauce ) ;


   // dibujar los ejes, si procede
   if ( cv.dibujar_ejes  )
      DibujarEjesSolido( *cauce ) ;

   // fijar el color por defecto en el cauce para dibujar los objetos
   // if ( cv.fondo_blanco && ! cv.iluminacion )
   //    glColor3f( 0.0, 0.0, 0.0 );
   // else
   //    glColor3f( 1.0, 1.0, 1.0 );
   glColor3f( 1.0, 1.0, 1.0 );

   // COMPLETAR: Práctica 1: Configurar el cauce en función de:
   //    cv.sombr_plano (true/false)              --> usar fijarModoSombrPlano (método del 'cauce')
   //    cv.modo_visu   (puntos,lineas o relleno) --> usar glPolygonMode
   
   // fijamos el modo de sombreado
   cauce->fijarModoSombrPlano(cv.sombr_plano);                                 
   
   GLenum tipo_visu;

   // fijamos el modo de visualización
   switch(cv.modo_visu){                                                       
      case ModosVisu::puntos:
         tipo_visu = GL_POINT;
         break;

      case ModosVisu::lineas:
         tipo_visu = GL_LINE;
         break;

      case ModosVisu::relleno:
         tipo_visu = GL_FILL;
         break;

      default:
         assert(false);
         break;
   }
   glPolygonMode(GL_FRONT_AND_BACK, tipo_visu);

   if ( cv.iluminacion )
   {
      // COMPLETAR: Práctica 4: activar evaluación del MIL (y desactivar texturas)
      // * habilitar evaluación del MIL en el cauce (fijarEvalMIL)
      // * activar la colección de fuentes de la escena
      // * activar el material inicial
      
      cauce->fijarEvalMIL(true);                                                                   // habilitamos la iluminación en el cauce
      
      if (col_fuentes != nullptr)
         col_fuentes->activar(*cauce);                                                             // activamos la colección de fuentes de la escena
      
      if( material_ini != nullptr ){                                                               // activamos el material inicial
         cv.material_act = material_ini;
         cv.material_act->activar(cv);
      }
   }
   else // si la iluminación no está activada, deshabilitar MIL y texturas
   {  cauce->fijarEvalMIL( false );
      cauce->fijarEvalText( false );
   }

   // recuperar el objeto actual de esta escena
   Objeto3D * objeto = objetos[ind_objeto_actual] ; assert( objeto != nullptr );

   // COMPLETAR: Práctica 1: visualizar el objeto actual ('objeto')
   objeto->visualizarGL(cv);           

   // P5 VN
   if ( cv.visualizar_normales && !cv.modo_seleccion )
      visualizarNormales( cv );                                        
}

// -----------------------------------------------------------------------------------------------
// pasa la cámara actual a la siguiente

void Escena::siguienteCamara()
{
   assert( ind_camara_actual < camaras.size() );
   ind_camara_actual = (ind_camara_actual+1 ) % camaras.size();
   using namespace std ;
   cout << "Cámara actual cambiada a: " << (ind_camara_actual+1) << " (de " << camaras.size() << ")" << endl ;
}

// -----------------------------------------------------------------------------------------------
// pasa el objeto actual al siguiente

void Escena::siguienteObjeto()
{
   if ( objetos.size() == 0 )
      return ;
   assert( ind_objeto_actual < objetos.size() );
   ind_objeto_actual = (ind_objeto_actual+1 ) % objetos.size();
   using namespace std ;
   cout << "Objeto actual cambiado a: " << objetoActual()->leerNombre()
        << " (" << (ind_objeto_actual+1) << "/" << objetos.size() << ")." << endl  ;
}

// -----------------------------------------------------------------------------------------------
// devuelve puntero al objeto actual

Objeto3D * Escena::objetoActual()
{
   assert( ind_objeto_actual < objetos.size() );
   assert( objetos[ind_objeto_actual] != nullptr );
   return objetos[ind_objeto_actual] ;
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la cámara actual

CamaraInteractiva * Escena::camaraActual()
{
   assert( ind_camara_actual < camaras.size() );
   assert( camaras[ind_camara_actual] != nullptr );
   return camaras[ind_camara_actual] ;
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la colección de fuentes actual

ColFuentesLuz * Escena::colFuentes()
{
   assert( col_fuentes != nullptr );
   return col_fuentes ;
}
// -----------------------------------------------------------------------------------------------

Escena1::Escena1()   // P1 
{
   using namespace std ;
   cout << "Creando objetos de escena 1 .... " << flush ;

   // añadir el objeto 'Cubo' a la lista de objetos de esta escena:
   objetos.push_back( new Cubo() );                                             

   // COMPLETAR: Práctica 1: creación del resto objetos de la práctica 1
   // Añadir objetos al vector 'objetos', con:
   //     objetos.push_back( new .... )

   objetos.push_back( new Tetraedro() );
   objetos.push_back( new CuboColores() );

   // EP1 (1)
   objetos.push_back( new EstrellaZ(8) );

   cout << "hecho." << endl << flush ;
}

// -------------------------------------------------------------------------
// COMPLETAR: Práctica 2
// Añadir la implementación del constructor de la clase Escena2 para construir
// los objetos que se indican en los guiones de las práctica 2

Escena2::Escena2(){  // P2
   using namespace std;
   cout << "Creando objetos de escena 2 .... " << flush ;

   // Objetos de revolución
   objetos.push_back( new Cilindro( 20, 20 ) );
   objetos.push_back( new Cono( 20, 20 ) );
   objetos.push_back( new Esfera( 20, 20 ) );

   // EP2 (2)
   objetos.push_back( new RejillaY(4, 4));

   // Objetos leidos de ficheros .ply
   string pwd = "../recursos/plys/";
   /*objetos.push_back( new MallaPLY( pwd + "ant.ply" ) );
   objetos.push_back( new MallaPLY( pwd + "beethoven.ply" ) );
   objetos.push_back( new MallaPLY( pwd + "big_dodge.ply" ) );
   objetos.push_back( new MallaRevolPLY( pwd + "lata-pcue.ply", 20 ) );
   objetos.push_back( new MallaRevolPLY( pwd + "lata-pinf.ply", 20 ) );
   objetos.push_back( new MallaRevolPLY( pwd + "lata-psup.ply", 20 ) );
   objetos.push_back( new MallaRevolPLY( pwd + "peon.ply", 20 ) );*/

   // Objetos leidos de ficheros de Internet (http://graphics.stanford.edu/data/3Dscanrep/)
   string pwd_internet = "plys/";
   //objetos.push_back( new MallaPLY( pwd_internet + "bun_zipper.ply" ) );

   cout << "hecho." << endl << flush ;
}

// -------------------------------------------------------------------------
// COMPLETAR: Práctica 3
// Añadir la implementación del constructor de la clase Escena3 para construir
// los objetos que se indican en los guiones de las práctica 3

Escena3::Escena3(){  // P3
   using namespace std;
   cout << "Creando objetos de escena 3 .... " << flush;

   objetos.push_back( new MrPotato() );

   // EP3 (1)
   objetos.push_back( new GrafoEstrellaX( 8 ));

   // EP3 (2)
   objetos.push_back( new GrafoCubos() );

   cout << "hecho." << endl << flush;
}

// ----------------------------------------------------------------------
// COMPLETAR: Práctica 4
// Añadir la implementación del constructor de la clase Escena4 para construir
// los objetos que se indican en los guiones de las práctica 4

Escena4::Escena4(){  // P4
   using namespace std;
   cout << "Creando objetos de escena 4 .... " << flush;

   objetos.push_back( new LataPeones() );
   objetos.push_back( new NodoCubo24() );

   // EP4 (1)
   objetos.push_back( new NodoDiscoP4() );

   cout << "hecho." << endl << flush;
}

// ----------------------------------------------------------------------
// COMPLETAR: Práctica 5
// Añadir la implementación del constructor de la clase Escena5 para construir
// los objetos que se indican en los guiones de las práctica 5

Escena5::Escena5(){  // P5
   using namespace std;
   cout << "Creando objetos de escena 5 .... " << flush;

   objetos.push_back( new VariasLatasPeones() );

   // EP5 (1)
   objetos.push_back( new GrafoEsferasP5() );

   // EP5 (2)
   objetos.push_back( new GrafoEsferasP5_2() );

   cout << "hecho." << endl << flush;
}

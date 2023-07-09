// *********************************************************************
// ** 
// ** Nombre    : Juan Manuel
// ** Apellidos : Mateos Pérez
// ** DNI       : 77555876Z 
// ** Informática Gráfica - curso 2021-22
// ** Doble Grado Informática y Matemáticas
// **
// *********************************************************************

//#include <set>   // std::set
#include "ig-aux.h"
#include "tuplasg.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"

// --------------------------------------------------------------------
// Funciones Auxiliares
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// Clase MallaInd
// --------------------------------------------------------------------

// P5 VN
void MallaInd::visualizarNormales()
{
   using namespace std ;

   if ( nor_ver.size() == 0 )
   {
      cout << "Advertencia: intentando dibujar normales de una malla que no tiene tabla (" << leerNombre() << ")." << endl ;
      return ;
   }  
   if ( array_verts_normales == nullptr )
   {  
      for( unsigned i = 0 ; i < vertices.size() ; i++ )
      {  
         segmentos_normales.push_back( vertices[i] );
         segmentos_normales.push_back( vertices[i]+ 0.35f*(nor_ver[i]) );
      }
      array_verts_normales = new ArrayVertices( GL_FLOAT, 3, segmentos_normales.size(), segmentos_normales.data() );
   }

   array_verts_normales->visualizarGL_MI_DAE( GL_LINES );
   CError();
}

MallaInd::MallaInd(){
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}

MallaInd::MallaInd( const std::string & nombreIni ){
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada
void MallaInd::calcularNormalesTriangulos()  // P4
{
   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() ){
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   Tupla3f vector_a, vector_b, vector_normal; 

   nor_tri.clear();
   for( auto triangulo : triangulos){
      vector_a = vertices[ triangulo[1] ] - vertices[ triangulo[0] ];
      vector_b = vertices[ triangulo[2] ] - vertices[ triangulo[1] ];
      vector_normal = vector_a.cross(vector_b);                                                    // producto vectorial

      if( vector_normal.lengthSq() > 0 )
         vector_normal = vector_normal.normalized();
      else
         vector_normal = { 0, 0, 0 };

      nor_tri.push_back(vector_normal);
   }
}

// calcula las dos tablas de normales
void MallaInd::calcularNormales()   // P4
{
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'

   calcularNormalesTriangulos();

   nor_ver.clear();
   nor_ver.insert( nor_ver.begin(), vertices.size(), {0.0, 0.0, 0.0} );

   for( unsigned i=0; i<triangulos.size(); ++i ){
      nor_ver[ triangulos[i][0] ] = nor_ver[ triangulos[i][0] ] + nor_tri[i];
      nor_ver[ triangulos[i][1] ] = nor_ver[ triangulos[i][1] ] + nor_tri[i];
      nor_ver[ triangulos[i][2] ] = nor_ver[ triangulos[i][2] ] + nor_tri[i];
   }

   for( auto n_vertice : nor_ver ){
      if( n_vertice.lengthSq() > 0 )
         n_vertice = n_vertice.normalized();
   }
}

void MallaInd::visualizarGL( ContextoVis & cv )   // P1
{
   using namespace std ;
   assert( cv.cauce_act != nullptr );

   // P5 VN
   if( cv.visualizando_normales ){
      visualizarNormales();
      return;
   }

   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // guardar el color previamente fijado
   const Tupla4f color_previo = leerFijarColVertsCauce( cv );

   // COMPLETAR: práctica 1: si el puntero 'array_verts' es nulo, crear el objeto ArrayVerts
   //   * en el constructor se dan los datos de la tabla de coordenadas de vértices (tabla 'vertices')
   //   * después hay que invocar a 'fijarIndices', usando el formato y datos de la tabla de triángulos ('triangulos')
   //   * si las tablas 'col_ver', 'cc_tt_ver' o 'nor_ver' no están vacías, hay que invocar los métodos 
   //     'fijarColores', 'fijarCoordText' y 'fijarNormales', como corresponda.

   if ( array_verts == nullptr ){
      array_verts = new ArrayVertices( GL_FLOAT, 3, vertices.size(), vertices.data() );

      array_verts->fijarIndices( GL_UNSIGNED_INT, 3*triangulos.size(), triangulos.data() );        // jjj 3*

      if( !col_ver.empty()   ) array_verts->fijarColores( GL_FLOAT, 3, col_ver.data() );
      if( !cc_tt_ver.empty() ) array_verts->fijarCoordText( GL_FLOAT, 2, cc_tt_ver.data() );
      if( !nor_ver.empty()   ) array_verts->fijarNormales( GL_FLOAT, nor_ver.data() );
   }

   // COMPLETAR: práctica 1: visualizar según el modo (en 'cv.modo_envio')
   //   ** inmediato begin/end       : usar método 'visualizarGL_MI_BVE' de 'ArrayVerts'
   //   ** inmediato con una llamada : usar método 'visualizarGL_MI_DAE' de 'ArrayVerts'
   //   ** diferido (con un VAO)     : usar método 'visualizarGL_MD_VAO' de 'ArrayVerts'
   // (en cualquier caso hay que pasar como parámetro el tipo de primitiva adecuada a una malla de triángulos).
   
   switch (cv.modo_envio){
      case ModosEnvio::inmediato_begin_end:
         array_verts->visualizarGL_MI_BVE(GL_TRIANGLES);  
         break;
      
      case ModosEnvio::inmediato_drawelements:
         array_verts->visualizarGL_MI_DAE(GL_TRIANGLES);
         break;

      case ModosEnvio::diferido_vao:
         array_verts->visualizarGL_MD_VAO(GL_TRIANGLES);
         break;

      default:
         assert(false);
         break;
   } 

   // restaurar el color previamente fijado
   glColor4fv( color_previo );
}

// --------------------------------------------------------------------
// Clase MallaPLY
// --------------------------------------------------------------------

MallaPLY::MallaPLY( const std::string & nombre_arch ) // P2 // P4
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   LeerPLY( nombre_arch, vertices, triangulos );

   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   calcularNormales();
}

// --------------------------------------------------------------------
// Clase Cubo P1
// --------------------------------------------------------------------

Cubo::Cubo() : MallaInd( "Cubo 8 vértices" ){
   ponerIdentificador(-1);

   vertices = {  
      { -1.0, -1.0, -1.0 }, // 0
      { -1.0, -1.0, +1.0 }, // 1
      { -1.0, +1.0, -1.0 }, // 2
      { -1.0, +1.0, +1.0 }, // 3
      { +1.0, -1.0, -1.0 }, // 4
      { +1.0, -1.0, +1.0 }, // 5
      { +1.0, +1.0, -1.0 }, // 6
      { +1.0, +1.0, +1.0 }, // 7
   };

   triangulos = {  
      {0,1,3}, {0,3,2}, // X-
      {4,7,5}, {4,6,7}, // X+ (+4)

      {0,5,1}, {0,4,5}, // Y-
      {2,3,7}, {2,7,6}, // Y+ (+2)

      {0,6,4}, {0,2,6}, // Z-
      {1,5,7}, {1,7,3}  // Z+ (+1)
   } ;

   // P4
   calcularNormales();
}

// --------------------------------------------------------------------
// Clase Tetraedro P1
// --------------------------------------------------------------------

Tetraedro::Tetraedro() : MallaInd( "Tetraedro" ){
   ponerIdentificador(-1);

   vertices = {  
      { +1.0,  0.0,  0.0 }, // 0
      { -1.0, -1.0,  0.0 }, // 1
      { -1.0, +1.0,  0.0 }, // 2
      {  0.0,  0.0, +1.0 }, // 3
   };

   triangulos = {  
      {0, 1, 2},
      {0, 3, 1},
      {1, 3, 2},
      {0, 3, 2}
   };

   // Fijamos un color
   Tupla3f color = {0, 1, 0};
   ponerColor(color);

   // P4
   calcularNormales();
}

// --------------------------------------------------------------------
// Clase CuboColores P1
// --------------------------------------------------------------------

CuboColores::CuboColores() : MallaInd( "CuboColores" ){
   ponerIdentificador(-1);

   vertices = {  
      { -1.0, -1.0, -1.0 }, // 0
      { -1.0, -1.0, +1.0 }, // 1
      { -1.0, +1.0, -1.0 }, // 2
      { -1.0, +1.0, +1.0 }, // 3
      { +1.0, -1.0, -1.0 }, // 4
      { +1.0, -1.0, +1.0 }, // 5
      { +1.0, +1.0, -1.0 }, // 6
      { +1.0, +1.0, +1.0 }, // 7
   };

   triangulos = {  
      {0,1,3}, {0,3,2}, // X-
      {4,7,5}, {4,6,7}, // X+ (+4)

      {0,5,1}, {0,4,5}, // Y-
      {2,3,7}, {2,7,6}, // Y+ (+2)

      {0,6,4}, {0,2,6}, // Z-
      {1,5,7}, {1,7,3}  // Z+ (+1)
   } ;
   
   // coloreamos los vértices
   float r, g, b;
   for ( auto v : vertices ){
      r = v[0] == -1 ? 0 : 1; // v[0] = X
      g = v[1] == -1 ? 0 : 1; // v[1] = Y
      b = v[2] == -1 ? 0 : 1; // v[2] = Z
      col_ver.push_back({r, g, b});
   }

   // P4
   calcularNormales();
}

// --------------------------------------------------------------------
// EP1 (1) 
// --------------------------------------------------------------------

EstrellaZ::EstrellaZ( const unsigned int n ) : MallaInd( "EstrellaZ" ){
   ponerIdentificador(-1);
   assert( n > 1 );

   vertices = {{ 0.5, 0.5, 0.0 }};

   Tupla3f q = { 0.5, 0.0, 0.0 };
   Tupla3f p = { 0.2, 0.0, 0.0 };

   // añadimos los vertices
   for( unsigned int i=0, j=1; i<n; i++, j=j+2 ){
      //vertices.push_back({(cos((2*M_PI*i)/n)+1)/2,(sin((2*M_PI*i)/n)+1)/2,0.0});
      vertices.push_back( MAT_Traslacion(0.5,0.5,0.0) * MAT_Rotacion(360*i/n,0.0,0.0,1.0) * q);
      
      //vertices.push_back({(cos((2*M_PI*(j))/(2*n))+2.5)/5,(sin((2*M_PI*(j))/(2*n))+2.5)/5,0.0});
      vertices.push_back( MAT_Traslacion(0.5,0.5,0.0) * MAT_Rotacion(360*j/(2*n),0.0,0.0,1.0) * p);
   }

   // añadimos los triangulos
   for( unsigned int i=0; i<2*n && (i+2)<=2*n; i++ ){
      triangulos.push_back({ 0, (int)(i+1), (int)(i+2) });
   }
   triangulos.push_back({ 0, (int)(2*n), 1 });

   // agregamos color
   float R,G,B;
   col_ver.push_back({ 1.0, 1.0, 1.0 });
	for( unsigned int i = 1; i<vertices.size(); i++ ){
		R = vertices[i](X);
		G = vertices[i](Y);
		B = vertices[i](Z);
		col_ver.push_back({ R,G,B });
	}
   
   calcularNormales();
}

// --------------------------------------------------------------------
// EP2 (2)
// --------------------------------------------------------------------

RejillaY::RejillaY( const unsigned int m, const unsigned n ) : MallaInd( "RejillaY" ){
   ponerIdentificador(-1);
   assert( m > 1 && n > 1);
   
   vertices = {};
   // vertices
   for( unsigned int i=0; i<m; ++i ){
      for( unsigned int j=0; j<n; ++j ){
         vertices.push_back({ (float)(1.0*i)/(m-1), 0.0, (float)(1.0*j)/(n-1) });   
      }
   }

   // triangulos
   int index;
   for( unsigned int i=0; i<m-1; i++ )
      for( unsigned int j=0; j<n-1; j++ ){
         index = i + j*n;
         triangulos.push_back({ index, (int)index+1  , (int)(index+n)+1 });
         triangulos.push_back({ index, (int)(index+n), (int)(index+n)+1 });
      }

   // agregamos color
   float R, G, B;
   for ( auto v : vertices ){
      R = v[0];
      G = v[1];
      B = v[2];
      col_ver.push_back({ R, G, B });
   }

   calcularNormales();
}

// --------------------------------------------------------------------
// Clase Cubo24 P4
// --------------------------------------------------------------------

Cubo24::Cubo24 () : MallaInd( "Cubo 24" ){
   vertices = {
      {-1.0, -1.0, -1.0},                                                                          // 0
      {-1.0, -1.0, +1.0},                                                                          // 1
      {-1.0, +1.0, -1.0},                                                                          // 2
      {-1.0, +1.0, +1.0},                                                                          // 3
      {+1.0, -1.0, -1.0},                                                                          // 4
      {+1.0, -1.0, +1.0},                                                                          // 5
      {+1.0, +1.0, -1.0},                                                                          // 6
      {+1.0, +1.0, +1.0},                                                                          // 7

      {-1.0, -1.0, -1.0},                                                                          // 8
      {-1.0, -1.0, +1.0},                                                                          // 9
      {-1.0, +1.0, -1.0},                                                                          // 10
      {-1.0, +1.0, +1.0},                                                                          // 11
      {+1.0, -1.0, -1.0},                                                                          // 12
      {+1.0, -1.0, +1.0},                                                                          // 13
      {+1.0, +1.0, -1.0},                                                                          // 14
      {+1.0, +1.0, +1.0},                                                                          // 15

      {-1.0, -1.0, -1.0},                                                                          // 16
      {-1.0, -1.0, +1.0},                                                                          // 17
      {-1.0, +1.0, -1.0},                                                                          // 18
      {-1.0, +1.0, +1.0},                                                                          // 19
      {+1.0, -1.0, -1.0},                                                                          // 20
      {+1.0, -1.0, +1.0},                                                                          // 21
      {+1.0, +1.0, -1.0},                                                                          // 22
      {+1.0, +1.0, +1.0}                                                                           // 23
   };

   triangulos = {
      {0, 1, 3}, {0, 3, 2},
      {4, 5 ,7}, {4, 6, 7},

      {8, 13, 9}, {8, 12, 13},      
      {10, 11, 15}, {10, 15, 14},

      {16, 22, 20}, {16, 18, 22}, 
      {17, 21, 23}, {17, 23, 19}
   };

   cc_tt_ver = {
      {0,1},                                                                                       // 0
      {1,1},                                                                                       // 1
      {0,0},                                                                                       // 2
      {1,0},                                                                                       // 3
      {1,1},                                                                                       // 4
      {0,1},                                                                                       // 5
      {1,0},                                                                                       // 6
      {0,0},                                                                                       // 7

      {0,0},                                                                                       // 8
      {1,0},                                                                                       // 9
      {1,0},                                                                                       // 10
      {0,0},                                                                                       // 11
      {0,1},                                                                                       // 12
      {1,1},                                                                                       // 13
      {1,1},                                                                                       // 14
      {0,1},                                                                                       // 15

      {1,1},                                                                                       // 16
      {0,1},                                                                                       // 17
      {1,0},                                                                                       // 18 
      {0,0},                                                                                       // 19
      {0,1},                                                                                       // 20
      {1,1},                                                                                       // 21
      {0,0},                                                                                       // 22
      {1,0}                                                                                        // 23
   };

   calcularNormales();
}

// --------------------------------------------------------------------
// EP4 (1) y EP4 (2)
// --------------------------------------------------------------------

MallaDiscoP4::MallaDiscoP4() : MallaInd( "MallaDiscoP4" ){
   ponerColor({1.0, 1.0, 1.0});
   const int ni = 23, nj = 31;
   
   // vértices
   for( int i= 0 ; i < ni ; i++ )
   for( int j= 0 ; j < nj ; j++ ){
      const float
      fi = float(i)/float(ni-1),
      fj = float(j)/float(nj-1),
      ai = 2.0*M_PI*fi,
      x = fj * cos( ai ),
      y = fj * sin( ai ),
      z = 0.0 ;
      vertices.push_back({ x, y, z });

      // EP4 (2)
      //cc_tt_ver.push_back({ (float)(sqrt(pow(x,2) + pow(y,2))), z });
   }

   // triángulos
   for( int i= 0 ; i < ni-1 ; i++ )
   for( int j= 0 ; j < nj-1 ; j++ ){
      triangulos.push_back({ i*nj+j, i*nj+(j+1), (i+1)*nj+(j+1) });
      triangulos.push_back({ i*nj+j, (i+1)*nj+(j+1), (i+1)*nj+j });
   }

   // EP4 (1) 
   float t_x, t_y;
   Tupla2f textura;
   for( unsigned int i=0; i<ni*nj; i++ ){
      t_x = (vertices[i](0)+1)*1/2;   
      t_y = 1.0 - (vertices[i](1)+1)*1/2;
      textura = {t_x, t_y};
      cc_tt_ver.push_back(textura);
   }

   calcularNormales();
}

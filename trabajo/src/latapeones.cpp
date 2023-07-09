// *********************************************************************
// ** 
// ** Nombre    : Juan Manuel
// ** Apellidos : Mateos Pérez
// ** DNI       : 77555876Z 
// ** Informática Gráfica - curso 2021-22
// ** Doble Grado Informática y Matemáticas
// **
// *********************************************************************

#include "latapeones.h"
#include "malla-revol.h"

// ---------------------------------------------------------------------
// PEONES
// ---------------------------------------------------------------------

PeonMadera::PeonMadera(){
    ponerNombre("Peón de madera");
    ponerIdentificador(402);
    
    TexturaXY * tex = new TexturaXY( "../recursos/imgs/text-madera.jpg" );
    agregar(MAT_Traslacion( 0.0, 0.27, 1.0 ));
    agregar(MAT_Escalado( 0.2, 0.2, 0.2 ));
    agregar(new Material( tex, 0.6, 0.5, 0.8, 20 ));
    agregar(new MallaRevolPLY( "../recursos/plys/peon.ply", 50 ));
}

PeonBlanco::PeonBlanco(){
    ponerNombre("Peón blanco");
    ponerIdentificador(403);
    ponerColor({ 1.0, 1.0, 1.0 });

    agregar(MAT_Traslacion( 0.5, 0.27, 1.0 ));
    agregar(MAT_Escalado( 0.2, 0.2, 0.2 ));
    agregar(new Material( 0.5, 0.5, 0.2, 20 ));
    agregar(new MallaRevolPLY( "../recursos/plys/peon.ply", 50 ));
}

PeonNegro::PeonNegro(){
    ponerNombre("Peón negro");
    ponerIdentificador(404);
    ponerColor({ 0.0, 0.0, 0.0 });

    agregar(MAT_Traslacion( 1.0, 0.27, 1.0 ));
    agregar(MAT_Escalado( 0.2, 0.2, 0.2 ));
    agregar(new Material( 0.5, 0.5, 0.2, 20 ));
    agregar(new MallaRevolPLY( "../recursos/plys/peon.ply", 50 ));
}

// ---------------------------------------------------------------------
// ELEMENTOS LATAS
// ---------------------------------------------------------------------

TapaSuperiorLata::TapaSuperiorLata(){
    ponerNombre("Tapa Superior Lata");
    ponerIdentificador(-1);
    agregar(new Material( 0.6, 0.5, 0.8, 20 ));
    agregar(new MallaRevolPLY( "../recursos/plys/lata-psup.ply", 50 ));
}

TapaInferiorLata::TapaInferiorLata(){
    ponerNombre("Tapa Inferior Lata");
    ponerIdentificador(-1);
    agregar(new Material( 0.6, 0.5, 0.8, 20 ));
    agregar(new MallaRevolPLY( "../recursos/plys/lata-pinf.ply", 50 ));
}

CuerpoLataCola::CuerpoLataCola(){
    ponerNombre("Cuerpo Lata Coca-Cola");
    ponerIdentificador(-1);
    Textura * tex = new Textura( "../recursos/imgs/lata-coke.jpg" );    
    agregar(new Material( tex, 0.6, 0.5, 0.8, 20 ));
    agregar(new MallaRevolPLY( "../recursos/plys/lata-pcue.ply", 50 ));   
}

CuerpoLataPepsi::CuerpoLataPepsi(){
    ponerNombre("Cuerpo Lata Pepsi");
    ponerIdentificador(-1);
    Textura * tex = new Textura( "../recursos/imgs/lata-pepsi.jpg" );
    agregar(new Material( tex, 0.6, 0.5, 0.8, 20 ));
    agregar(new MallaRevolPLY( "../recursos/plys/lata-pcue.ply", 50 ));
}

CuerpoLataUGR::CuerpoLataUGR(){
    ponerNombre("Cuerpo Lata UGR");
    ponerIdentificador(-1);
    Textura * tex = new Textura( "../recursos/imgs/window-icon.jpg" );    
    agregar(new Material( tex, 0.6, 0.5, 0.8, 20 ));
    agregar(new MallaRevolPLY( "../recursos/plys/lata-pcue.ply", 50 ));
}

// ---------------------------------------------------------------------
// LATAS
// ---------------------------------------------------------------------

LataCola::LataCola(){
    ponerNombre("Lata de Coca-Cola");
    ponerIdentificador(401);

    agregar(MAT_Traslacion( 0.0, -0.04, 0.0 ));
    agregar(new CuerpoLataCola());
    agregar(new TapaSuperiorLata());
    agregar(new TapaInferiorLata());
}

LataPepsi::LataPepsi(){
    ponerNombre("Lata de Pepsi");
    ponerIdentificador(501);

    agregar(MAT_Traslacion( +1.0, -0.04, 0.0 ));
    agregar(new CuerpoLataPepsi());
    agregar(new TapaSuperiorLata());
    agregar(new TapaInferiorLata());
}

LataUGR::LataUGR(){
    ponerNombre("Lata de la UGR");
    ponerIdentificador(502);

    agregar(MAT_Traslacion( +2.0, -0.04, 0.0 ));
    agregar(new CuerpoLataUGR());
    agregar(new TapaSuperiorLata());
    agregar(new TapaInferiorLata());
}

// ---------------------------------------------------------------------
// LATAPEONES
// ---------------------------------------------------------------------

LataPeones::LataPeones(){
    agregar(new LataCola());
    agregar(new PeonMadera());
    agregar(new PeonBlanco());
    agregar(new PeonNegro());
}

// ---------------------------------------------------------------------
// VARIASLATASPEONES
// ---------------------------------------------------------------------

VariasLatasPeones::VariasLatasPeones(){
    agregar(new LataPeones());
    agregar(new LataPepsi());
    agregar(new LataUGR());
}
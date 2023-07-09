// *********************************************************************
// ** 
// ** Nombre    : Juan Manuel
// ** Apellidos : Mateos Pérez
// ** DNI       : 77555876Z 
// ** Informática Gráfica - curso 2021-22
// ** Doble Grado Informática y Matemáticas
// **
// *********************************************************************

#include "modelo-jer.h"
#include "malla-revol.h"

#include <cmath>

// --------------------------------------------------------------------
// MR POTATO
// --------------------------------------------------------------------

MrPotato::MrPotato(){
    ponerNombre("Mr Potato");
    ponerIdentificador(301);

    // movimiento
    unsigned r_c = agregar( MAT_Rotacion( 0.0, 0.0, 1.0, 0.0 ));

    agregar( new Pie() );
    agregar( new Cuerpo() ); 
    agregar( new Ojo() );
    agregar( new Nariz() );
    agregar( new Oreja() );
    agregar( new Sombrero() );
    agregar( new Bigote() );
    agregar( new Boca() );
    agregar(new Brazo( pm_rotacion_brazos ));
    agregar(new Ceja( pm_traslacion_cejas ));

    // aplicamos movimiento
    pm_rotacion_cuerpo = leerPtrMatriz( r_c );
}


// --------------------------------------------------------------------
// FUNCIONES MR POTATO
// --------------------------------------------------------------------

void MrPotato::setTraslacionCejas( const float nueva_traslacion_cejas ){
    *pm_traslacion_cejas = MAT_Traslacion( 0.0, nueva_traslacion_cejas, 0.0 );
}

void MrPotato::setRotacionCuerpo( const float nueva_rotacion_cuerpo ){
    *pm_rotacion_cuerpo = MAT_Rotacion( nueva_rotacion_cuerpo, 0.0, 1.0, 0.0 );
}

void MrPotato::setRotacionBrazos( const float nueva_rotacion_brazos ){
    *pm_rotacion_brazos = MAT_Rotacion( nueva_rotacion_brazos, 1.0, 0.0, 0.0 );
}

unsigned MrPotato::leerNumParametros() const{
    return 3;
}                                              

void MrPotato::actualizarEstadoParametro( const unsigned iParam, const float t_sec ){
    assert( iParam < leerNumParametros() );
    switch( iParam ){
        case 0:
            setTraslacionCejas(0.02 * sin( 4.0 * M_PI * t_sec ));
            break;
        
        case 1:
            if ( t_sec < 10 )
                setRotacionCuerpo(360.0 * sin( 0.1 * M_PI * t_sec ));
            break;
        
        case 2:
            //setRotacionBrazos(360 * sin( 0.2 * M_PI * t_sec));
            setRotacionBrazos(360 * t_sec);
            break;

        default:
            std::cerr << "Se ha producido algún fallo en el desarrollo del movimiento" << std::endl;
            exit(1);
            break;
    }
}

// --------------------------------------------------------------------
// PIE
// --------------------------------------------------------------------

Pie::Pie(){
    ponerIdentificador(-1);

    Textura * tex_pie = new Textura( "../trabajo/imgs/zapatos.jpg" );
    agregar( new Material( tex_pie, 0.7, 0.5, 0.5, 20 ) );

    // aplicamos deformacion a la esfera
    agregar(MAT_Escalado( 0.4, 0.3, 0.5 ));

    // pie izquierdo
    agregar(MAT_Traslacion( -1.25, 0.0, 0.0 ));
    agregar(new Esfera( 50, 50 ));

    // pie derecho
    agregar(MAT_Traslacion( +2.5, 0.0, 0.0 ));
    agregar(new Esfera( 50, 50 ));

    // agregamos color
    ponerColor({ 0.0, 0.5, 1 });                                                                   // azul
}

// --------------------------------------------------------------------
// CUERPO
// --------------------------------------------------------------------

Cuerpo::Cuerpo(){
    ponerIdentificador(-1);

    agregar( new Material( 0.7, 0.6, 0.2, 20 ) );

    // aplicamos deformacion a la esfera
    agregar(MAT_Escalado( 0.8, 1.0, 0.7 ));
    agregar(MAT_Traslacion( 0.0, 1.0, 0.0 ));
    agregar(new Esfera( 50, 50 ));

    // agregamos color
    ponerColor({ 0.55, 0.28, 0.14 });                                                              // marrón                       
}

// --------------------------------------------------------------------
// OJO
// --------------------------------------------------------------------

Ojo::Ojo(){
    ponerIdentificador(-1);

    // aplicamos inclinación
    agregar(MAT_Rotacion( -15.0, 1.0, 0.0, 0.0 ));

    // ojo izquierdo
    agregar(MAT_Escalado( 0.15, 0.2, 0.15 ));
    agregar(MAT_Traslacion( -1.25, 6.0, 6.0 ));
    agregar(new Esfera( 50, 50 ));

    // ojo derecho
    agregar(MAT_Traslacion( 2.5, 0.0, 0.0 ));
    agregar(new Esfera( 50, 50 ));

    // pupila izquierda
    agregar(MAT_Traslacion( -2.5, 0.0, 1.0 ));
    agregar(new Pupila());

    // pupila derecha
    agregar(MAT_Traslacion( 2.5, 0.0, 0.0 ));
    agregar(new Pupila());

    // agregamos color
    ponerColor({ 1, 1, 1 });                                                                       // blanco
}

Pupila::Pupila(){
    ponerIdentificador(-1);

    agregar(new Material( 0.7, 0.5, 0.9, 20 ));

    // propiedades generales de una pupila
    agregar(MAT_Escalado( 0.3, 0.3, 0.15 ));
    agregar(new Esfera( 50, 50 ));

    // agreagamos color
    ponerColor({ 0, 0, 0 });                                                                       // negro
}

// --------------------------------------------------------------------
// NARIZ
// --------------------------------------------------------------------

Nariz::Nariz(){
    ponerIdentificador(-1);

    // parte horizontal de la nariz
    agregar(MAT_Escalado( 0.3, 0.16, 0.2 ));
    agregar(MAT_Traslacion( 0.0, 6.4, 3.0 ));
    agregar(new Esfera( 50, 50 ));

    // deshacemos el escalado y la traslación (IMP el orden en que los deshacemos)
    agregar(MAT_Traslacion( 0.0, -6.4, -3.0 ));
    agregar(MAT_Escalado( 1.0/0.3, 1.0/0.16, 1.0/0.2 ));
    
    // parte vertical de la nariz
    agregar(MAT_Escalado( 0.15, 0.19, 0.2 ));
    agregar(MAT_Traslacion( 0.0, 5.7, 3.5 ));
    agregar(new Esfera( 50, 50 ));

    // agreamos color
    ponerColor({ 1, 0.5, 0 });                                                                     // naranja
}

// --------------------------------------------------------------------
// OREJA
// --------------------------------------------------------------------

Oreja::Oreja(){
    ponerIdentificador(-1);

    // oreja izquierda
    agregar(MAT_Rotacion( -20.0, 0.0, 0.0, 1.0 ));
    agregar(MAT_Escalado( 0.2, 0.25, 0.08 ));
    agregar(MAT_Traslacion( -6.3, 4.8, 3.0 ));
    agregar(new Esfera( 50, 50 ));

    // deshacemos los movimientos aplicados (IMP el doble signo negativo en la rotación)
    agregar(MAT_Traslacion( 6.3, -4.8, -3.0 ));
    agregar(MAT_Escalado( 1.0/0.2, 1.0/0.25, 1.0/0.08 ));
    agregar(MAT_Rotacion( -20.0, 0.0, 0.0, -1.0 ));

    // oreja derecha
    agregar(MAT_Rotacion( 20.0, 0.0, 0.0, 1.0 ));
    agregar(MAT_Escalado( 0.2, 0.25, 0.08 ));
    agregar(MAT_Traslacion( 6.3, 4.8, 3.0 ));
    agregar(new Esfera( 50, 50 ));

    // agregamos color
    ponerColor({ 1.0, 0.24, 0.6 });                                                                // rosa
}

// --------------------------------------------------------------------
// SOMBRERO
// --------------------------------------------------------------------

Sombrero::Sombrero(){
    ponerIdentificador(-1);

    Textura * tex_sombrero = new Textura( "../trabajo/imgs/sombrero.jpg" );
    agregar( new Material( tex_sombrero, 0.1, 0.5, 0.1, 20 ) );

    // aplicamos deformaciones a la esfera
    agregar(MAT_Escalado( 0.5, 0.5, 0.5 ));
    agregar(MAT_Traslacion( 0.0, 3.4, 0.0 ));
    agregar(new Esfera( 50, 50 ));

    // deshacemos los cambios
    agregar(MAT_Traslacion( 0.0, -3.4, 0.0 ));

    // agregamos la tapa del sombrero
    agregar(MAT_Traslacion( 0.0, 3.9, 0.0 ));
    agregar(new Semiesfera( 50, 50 ));

    // agregamos color
    ponerColor({ 0, 0, 0 });                                                                       // negro                       
}

// --------------------------------------------------------------------
// BIGOTE
// --------------------------------------------------------------------

Bigote::Bigote(){
    ponerIdentificador(-1);

    Textura * tex_bigote = new Textura( "../trabajo/imgs/pelo.jpg" );
    agregar( new Material( tex_bigote, 0.2, 0.5, 0.2, 20 ) );

    // aplicamos deformación a la semiesfera
    agregar(MAT_Rotacion( 180.0, 0.0, 0.0, 1.0 ));
    agregar(MAT_Escalado( 0.4, 0.2, 0.2 ));
    agregar(MAT_Traslacion( 0.0, -3.5, 4.0 ));
    agregar(new Semiesfera( 50, 50 ));

    // agregamos color
    ponerColor({ 0, 0, 0 });                                                                       // negro       
}

// --------------------------------------------------------------------
// BOCA
// --------------------------------------------------------------------

Boca::Boca(){
    ponerIdentificador(-1);
    
    // añadimos los labios
    agregar(MAT_Escalado( 0.4, 0.1, 0.1 ));
    agregar(MAT_Traslacion( 0.0, 6.0, 6.0 ));
    agregar(new Esfera( 50, 50 ));

    // deshacemos los movimientos aplicados
    agregar(MAT_Traslacion( 0.0, -6.0, -6.0 ));
    agregar(MAT_Escalado( 1.0/0.4, 1.0/0.1, 1.0/0.1 ));

    // añadimos la sonrisa
    agregar(new Sonrisa());

    // agregamos color
    ponerColor({ 1, 0, 0 });                                                                       // rojo       
}

Sonrisa::Sonrisa(){
    ponerIdentificador(-1);

    // aplicamos transformaciones
    agregar(MAT_Escalado( 0.3, 0.05, 0.05 ));
    agregar(MAT_Traslacion( 0.0, 11.8, 13.2 ));
    
    agregar(new Esfera( 50, 50 ));

    // agregamos color
    ponerColor({ 1, 1, 1 });                                                                       // blanco                                          
}

// --------------------------------------------------------------------
// BRAZO
// --------------------------------------------------------------------

Brazo::Brazo( Matriz4f * &rotacion_brazos ){
    ponerIdentificador(-1);

    // movimiento
    agregar(MAT_Traslacion( 0.0, 1.0, 0.2));                                                       // aplicamos esta traslación para fijar los codos
    unsigned r_b = agregar(MAT_Rotacion( 0.0, 0.0, 1.0, 0.0 ));
    agregar(MAT_Traslacion( 0.0, -1.0, -0.2));

    // mano derecha
    agregar(MAT_Traslacion( 1.2, 0.55, 0.2 ));
    agregar(new Mano());

    // mano izquierda
    agregar(MAT_Traslacion( -2.4, 0.0, 0.0 ));
    agregar(new Mano());

    // deshacemos las traslaciones aplicadas
    agregar(MAT_Traslacion( -1.2, -0.55, -0.2 ));
    agregar(MAT_Traslacion( 2.4, 0.0, 0.0 ));

    // brazo derecho
    agregar(MAT_Rotacion( 50.0, 0.0, 0.0, 1.0 ));
    agregar(MAT_Traslacion( 1.2, -0.5, 0.2 ));
    agregar(MAT_Escalado( 0.08, 0.7, 0.08 ));
    agregar(new Cilindro( 50, 50 ));

    // deshacemos los cambios aplicados
    agregar(MAT_Escalado( 1.0/0.08, 1.0/0.7, 1.0/0.08 ));
    agregar(MAT_Traslacion( -1.2, 0.5, -0.2 ));
    agregar(MAT_Rotacion( -50.0, 0.0, 0.0, 1.0 ));

    // brazo izquierdo
    agregar(MAT_Rotacion( -50.0, 0.0, 0.0, 1.0 ));
    agregar(MAT_Traslacion( -1.2, -0.6, 0.2 ));
    agregar(MAT_Escalado( 0.08, 0.7, 0.08 ));
    agregar(new Cilindro( 50, 50 ));

    // agreagamos color
    ponerColor({ 1, 1, 1 });                                                                       // blanco

    // aplicamos movimiento
    rotacion_brazos = leerPtrMatriz( r_b );
}

Mano::Mano(){
    ponerIdentificador(-1);

    // propiedades generales de una mano
    agregar(MAT_Escalado( 0.15, 0.15, 0.15 ));
    agregar(new Esfera( 50, 50 ));

    // agreamos color 
    ponerColor({ 1, 1, 1 });                                                                       // blanco
}

// --------------------------------------------------------------------
// CEJA
// --------------------------------------------------------------------

Ceja::Ceja( Matriz4f * &traslacion_ceja ){
    ponerIdentificador(-1);
    
    Textura * tex_ceja = new Textura( "../trabajo/imgs/pelo.jpg" );
    agregar( new Material( tex_ceja, 0.2, 0.5, 0.2, 20 ) );

    // movimiento
    unsigned tras = agregar(MAT_Traslacion( 0.0, 0.0, 0.0 ));

    // ceja derecha
    agregar(MAT_Traslacion( 0.2, 1.64, 0.54 ));
    agregar(MAT_Escalado( 0.13, 0.025, 0.015 ));
    agregar(new Esfera( 50, 50 ));

    // deshacemos el escalado
    agregar(MAT_Escalado( 1.0/0.13, 1.0/0.025, 1.0/0.015 ));

    // ceja izquierda
    agregar(MAT_Traslacion( -0.4, 0.0, 0.0 ));
    agregar(MAT_Escalado( 0.13, 0.025, 0.015 ));
    agregar(new Esfera( 50, 50 ));

    // agregamos color
    ponerColor({ 0, 0, 0 });                                                                       // negro

    // aplicamos movimiento
    traslacion_ceja = leerPtrMatriz( tras );
}
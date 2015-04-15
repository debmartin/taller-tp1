#include "src/Juego.h"
#include "test/Test.h"
#include "src/modelo/CargadorDeObjetos.h"

#define TITULO_VENTANA "Taller de programacion TP: Mortal Kombat"
#define POS_VENTANA_INICIO Vector2f(100, 100)
#define ALTO_PX_VENTANA_INICIO 480
#define ANCHO_PX_VENTANA_INICIO 640
#define ANCHO_LOGICO_VENTANA_INICIO 640
#define INICIAR_FULLSCREEN false
#define ANCHO_ESCENARIO 1500
#define ALTO_ESCENARIO 600
#define Y_PISO 100
#define ANCHO_LOGICO_CAPA1	800
#define ANCHO_LOGICO_CAPA2	1000

//#define IMAGEN_FONDO1 "goro1-transparente.png"
//#define IMAGEN_FONDO1 "goro1-grilla.png"
#define IMAGEN_FONDO1 "goro1.png"
//#define IMAGEN_FONDO1 "fondo-warrior-shrine-01.png"
//#define IMAGEN_FONDO2 "goro2-transparente.png"
//#define IMAGEN_FONDO2 "goro2-grilla.png"
#define IMAGEN_FONDO2 "goro2.png"
//#define IMAGEN_FONDO2 "fondo-warrior-shrine-03.png"
//#define IMAGEN_FONDO2 "mario.jpg"
//#define IMAGEN_FONDO "Pit2.png"
//#define IMAGEN_FONDO "Pit.jpg"
//#define IMAGEN_FONDO "escenario2.gif"
//#define IMAGEN_FONDO "screen-pit.png"
#define IMAGEN_ZUBZERO_CAMINANDO "sub-zero-caminando.png"
#define IMAGEN_ZUBZERO_QUIETO "sub-zero-reposo.png"
#define IMAGEN_ZUBZERO_SALTANDO_VERTICAL "sub-zero-saltando-vertical.png"
#define IMAGEN_ZUBZERO_SALTANDO_DIAGONAL "sub-zero-saltando-diagonal.png"
#define IMAGEN_ZUBZERO_AGACHADO "sub-zero-agachado.png"

#define CANT_FOTOGRAMAS_FONDO 1
#define CANT_FOTOGRAMAS_FONDO2 1
#define CANT_FOTOGRAMAS_ZUBQUIETO 12
#define CANT_FOTOGRAMAS_ZUBCAMINANDO 9
#define CANT_FOTOGRAMAS_ZUBSALTANDOVERTICAL 3
#define CANT_FOTOGRAMAS_ZUBSALTANDODIAGONAL 7
#define CANT_FOTOGRAMAS_ZUBSAGACHADO 1

#define FPS_FONDO 1
#define FPS_FONDO2 1
#define FPS_ZUBQUIETO 10
#define FPS_ZUBCAMINANDO 10
#define FPS_ZUBSALTANDOVERTICAL 3
#define FPS_ZUBSALTANDODIAGONAL 10
#define FPS_ZUBSAGACHADO 1

//#define IMAGEN_FONDO "../version nueva/imagenes/screen-pit.png"
//#define IMAGEN_ZUBZERO_CAMINANDO "../version nueva/imagenes/zubzero-caminando.png"
//#define IMAGEN_ZUBZERO_QUIETO "../version nueva/imagenes/zubzero-quieto.png"

#define POSICION_INICIAL_CAPA Vector2f(0, 0)
#define POSICION_INICIAL_PERSONAJE Vector2f(750, 100)

#define ANCHO_LOGICO_PERSONAJE 105
#define ALTO_LOGICO_PERSONAJE 280


int main(int argc, char* args[])
{
	static const int FPS = 60;
	static const int DELAY_TIME = 1000.0f / FPS;

	Uint32 frameStart, frameTime;

	///////////////Inicializacion del Cargador de Objetos////
/*	CargadorDeOjbetos cargador_de_objetos;
	cargador_de_objetos.cargarObjetos();
    cout << "Objetos cargados" << endl;

	EscenarioGrafico escenario = *(cargador_de_objetos.getEscenarioGrafico());
	Personaje jugador = *(cargador_de_objetos.getPersonaje());
	PersonajeDibujable personajeDibujable = *(cargador_de_objetos.getPersonajeDibujable());

	Juego g_game(VentanaGrafica::Instance(), &escenario, &jugador, &personajeDibujable);

	    cout << "creacion juego correcta" << endl;

		while (g_game.running())
		{

			frameStart = SDL_GetTicks();

			g_game.handleEvents();

			g_game.update();
		    //cout << "game running" << endl;

			g_game.render();
		    //cout << "game running2" << endl;

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
				SDL_Delay((int)(DELAY_TIME - frameTime));
		}

*/
	/////////////Fin de inicializacion desde Parser////

	//para correr las pruebas comentar o descomentar estas 2 lineas
	//Test tests;
	//tests.ejecutar();
    Vector2f tamanioVentanaPx(ANCHO_PX_VENTANA_INICIO, ALTO_PX_VENTANA_INICIO);
    Vector2f tamanioVentanaLogico(ANCHO_LOGICO_VENTANA_INICIO, ALTO_ESCENARIO);
    bool exito = VentanaGrafica::Instance()->init(TITULO_VENTANA, POS_VENTANA_INICIO, tamanioVentanaPx, tamanioVentanaLogico, INICIAR_FULLSCREEN);

    if (! exito)
		cout << "Error al inicializar juego" << endl;

	Animacion fondoAnim(IMAGEN_FONDO1, CANT_FOTOGRAMAS_FONDO, FPS_FONDO, ID_FONDO, Renderizador::Instance()->getRenderer());
	Animacion fondoAnim2(IMAGEN_FONDO2, CANT_FOTOGRAMAS_FONDO2, FPS_FONDO2, ID_FONDO, Renderizador::Instance()->getRenderer());

	Animacion zubQuieto(IMAGEN_ZUBZERO_QUIETO, CANT_FOTOGRAMAS_ZUBQUIETO, FPS_ZUBQUIETO,  ID_ZUBZERO_QUIETO, Renderizador::Instance()->getRenderer());
	Animacion zubCaminando(IMAGEN_ZUBZERO_CAMINANDO, CANT_FOTOGRAMAS_ZUBCAMINANDO, FPS_ZUBCAMINANDO, ID_ZUBZERO_CAMINANDO, Renderizador::Instance()->getRenderer());
	Animacion zubSaltandoVertical(IMAGEN_ZUBZERO_SALTANDO_VERTICAL, CANT_FOTOGRAMAS_ZUBSALTANDOVERTICAL, FPS_ZUBSALTANDOVERTICAL, ID_ZUBZERO_SALTANDOVERTICAL, Renderizador::Instance()->getRenderer());
	Animacion zubSaltandoDiagonal(IMAGEN_ZUBZERO_SALTANDO_DIAGONAL, CANT_FOTOGRAMAS_ZUBSALTANDODIAGONAL, FPS_ZUBSALTANDODIAGONAL, ID_ZUBZERO_SALTANDODIAGONAL, Renderizador::Instance()->getRenderer());
	Animacion zubAgachado(IMAGEN_ZUBZERO_AGACHADO, CANT_FOTOGRAMAS_ZUBSAGACHADO, FPS_ZUBSAGACHADO, ID_ZUBZERO_AGACHADO, Renderizador::Instance()->getRenderer());

	Vector2f tamIniCapa(ANCHO_LOGICO_CAPA1, ALTO_ESCENARIO);
	Vector2f tamIniCapa2(ANCHO_LOGICO_CAPA2, ALTO_ESCENARIO);
    Vector2f posInCapa = POSICION_INICIAL_CAPA;

    Vector2f relacionAspectos = VentanaGrafica::Instance()->obtener_relacion_aspectos();
	Capa fondoCapa(&fondoAnim, tamIniCapa, posInCapa, relacionAspectos);
	Capa fondoCapa2(&fondoAnim2, tamIniCapa2, posInCapa, relacionAspectos);

	Personaje jugador(ANCHO_LOGICO_PERSONAJE, ALTO_LOGICO_PERSONAJE, POSICION_INICIAL_PERSONAJE, VentanaGrafica::Instance());
    Vector2f tamanioPx(
    		jugador.getAncho()*VentanaGrafica::Instance()->relacion_de_aspectoX(),
			jugador.getAlto()*VentanaGrafica::Instance()->relacion_de_aspectoY());
    cout<<"Gaston:"<<jugador.getAlto()*VentanaGrafica::Instance()->relacion_de_aspectoY()<<endl;
    cout<<"Relaciones de aspectos:"<<VentanaGrafica::Instance()->relacion_de_aspectoX()<<";"<<VentanaGrafica::Instance()->relacion_de_aspectoY()<<endl;
	PersonajeDibujable personaje(&zubQuieto, POSICION_INICIAL_PERSONAJE, tamanioPx, ORIENTACION_IZQUIERDA);
	personaje.agregarAnimacion(&zubQuieto);
	personaje.agregarAnimacion(&zubCaminando);
	personaje.agregarAnimacion(&zubSaltandoVertical);
	personaje.agregarAnimacion(&zubSaltandoDiagonal);
	personaje.agregarAnimacion(&zubAgachado);

	list<Capa*> capas;
	capas.push_back(&fondoCapa);
	capas.push_back(&fondoCapa2);

	list<Dibujable*> capasYPersonajes;
	capasYPersonajes.push_back((Dibujable*) &fondoCapa);
	capasYPersonajes.push_back((Dibujable*) &fondoCapa2);
	capasYPersonajes.push_back((Dibujable*) &personaje);

	EscenarioGrafico escenario(ANCHO_ESCENARIO, ALTO_ESCENARIO, Y_PISO, &capasYPersonajes, &capas);
    VentanaGrafica::Instance()->agregarEscenario(&escenario);
    VentanaGrafica::Instance()->centrar_ventana();////////////////////////////////////////////////////////////////////////////////////
    escenario.centrar_dibujables();////////////////////////////////////////////////////////////////////////////////////////////////////////
    Vector2f vector_centrado(escenario.getAnchoLogico()/2.0, escenario.getYPisoLogico());
    jugador.centrar_en(vector_centrado);////////////////////////////////////////////////////////////////////////////////

    cout << "carga correcta" << endl;
	Juego g_game(VentanaGrafica::Instance(), &escenario, &jugador, &personaje);


	//levantar la información inicial mediante json
	//... usar libreria jsonCpp
    cout << "creacion juego correcta" << endl;



	while (g_game.running())
	{

		frameStart = SDL_GetTicks();

		g_game.handleEvents();

		g_game.update();
	    //cout << "game running" << endl;

		g_game.render();
	    //cout << "game running2" << endl;
		cout << "============INICIO INFORMACION DE OBJETOS============" << endl;
		cout << "ESCENARIO->alto-logico:" << escenario.getAltoLogico() << endl;
		cout << "ESCENARIO->ancho-logico:" << escenario.getAnchoLogico() << endl;
		cout << "ESCENARIO->y-piso-logico:" << escenario.getYPisoLogico() << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "VENTANA-GRAFICA->limite logico Izquierdo:" << VentanaGrafica::Instance()->getLimiteLogicoIzquierdo() << endl;
		cout << "VENTANA-GRAFICA->limite logico Derecho:" << VentanaGrafica::Instance()->getLimiteLogicoDerecho() << endl;
		cout << "VENTANA-GRAFICA->relacion de aspecto X:" << VentanaGrafica::Instance()->relacion_de_aspectoX() << endl;
		cout << "VENTANA-GRAFICA->relacion de aspecto Y:" << VentanaGrafica::Instance()->relacion_de_aspectoY() << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "CAPA1->limite logico Izquierdo:" << fondoCapa.getLimiteLogicoIzquierdo() << endl;
		cout << "CAPA1->limite logico Derecho:" << fondoCapa.getLimiteLogicoDerecho() << endl;
		cout << "CAPA1->sprite->altpPx:" << fondoCapa.getSprite()->getAltoPx() << endl;
		cout << "CAPA1->sprite->anchoPx:" << fondoCapa.getSprite()->getAnchoPx() << endl;
		cout << "CAPA1->sprite->posicionPx-X:" << fondoCapa.getSprite()->getPosicion().X() << endl;
		cout << "CAPA1->sprite->posicionPx-Y:" << fondoCapa.getSprite()->getPosicion().Y() << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "CAPA2->limite logico Izquierdo:" << fondoCapa2.getLimiteLogicoIzquierdo() << endl;
		cout << "CAPA2->limite logico Derecho:" << fondoCapa2.getLimiteLogicoDerecho() << endl;
		cout << "CAPA2->sprite->altpPx:" << fondoCapa2.getSprite()->getAltoPx() << endl;
		cout << "CAPA2->sprite->anchoPx:" << fondoCapa2.getSprite()->getAnchoPx() << endl;
		cout << "CAPA2->sprite->posicionPx-X:" << fondoCapa2.getSprite()->getPosicion().X() << endl;
		cout << "CAPA2->sprite->posicionPx-Y:" << fondoCapa2.getSprite()->getPosicion().Y() << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "PERSONAJE-LOGICO->posicion-logica-X:" << jugador.getPosicion().X() << endl;
		cout << "PERSONAJE-LOGICO->posicion-logica-Y:" << jugador.getPosicion().Y() << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "PERSONAJE-DIBUJABLE->SPRITE->posicionPx-X:" << personaje._getSprite()->getPosicion().X() << endl;
		cout << "PERSONAJE-DIBUJABLE->SPRITE->posicionPx-Y:" << personaje._getSprite()->getPosicion().Y() << endl;
		cout << "PERSONAJE-DIBUJABLE->SPRITE->AnchoPx:" << personaje._getSprite()->getAnchoPx() << endl;
		cout << "PERSONAJE-DIBUJABLE->SPRITE->AltoPx:" << personaje._getSprite()->getAltoPx() << endl;
		cout << "=============FIN INFORMACION DE OBJETOS==============" << endl;
		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < DELAY_TIME)
			SDL_Delay((int)(DELAY_TIME - frameTime));
	}

	return 0;
}

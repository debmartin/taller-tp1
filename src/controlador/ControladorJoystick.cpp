#include "ControladorJoystick.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <iostream>

#include "../modelo/MapaDeCombos.h"

#define CANTIDAD_BOTONES 8

ControladorJoystick* ControladorJoystick::instancia_unica = NULL;

ControladorJoystick* ControladorJoystick::Instance()
{
        if (instancia_unica == NULL)
        {
                instancia_unica = new ControladorJoystick();
        }
        return instancia_unica;
}

ControladorJoystick::ControladorJoystick() {};

bool ControladorJoystick::joysticksInitialised() {
        return m_bJoysticksInitialised;
}

void ControladorJoystick::initialiseJoysticks(
                std::map<string, int>* correspondenciaTeclasJ1,
                std::map<string, int>* correspondenciaEjesJ1,
                std::map<string, int>* correspondenciaTeclasJ2,
                std::map<string, int>* correspondenciaEjesJ2) {

        if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
                SDL_InitSubSystem(SDL_INIT_JOYSTICK);

        if (correspondenciaTeclasJ1)
                this->correspondenciaTeclas = correspondenciaTeclasJ1;
        else
                this->correspondenciaTeclas = correspondenciaTeclasPorDefecto();

        if (correspondenciaEjesJ1)
                this->correspondenciaEjes = correspondenciaEjesJ1;
        else
                this->correspondenciaEjes = correspondenciaEjesPorDefecto();

        this->estadoJoystick1    = new std::map<string, bool>;
        this->estadoJoystick2    = new std::map<string, bool>;
        this->estadoJoystickNulo = new std::map<string, bool>;

        if(SDL_NumJoysticks() > 0) {
                for(int i = 0; i < SDL_NumJoysticks(); i++)     {
                        SDL_Joystick* joy = SDL_JoystickOpen(i);

                        if(joy) {

                                // INICIA JOYSTICKS
                                m_joysticks.push_back(joy);

                                // SETEO DIRECCIONES EN CERO
                                m_joystickValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));

                                // SETEA ESTADO DE TECLAS ACTUALES EN FALSE
                                //cout << "CANTIDAD BOTONES[" << i << "]:" << SDL_JoystickNumButtons(joy) << endl;
                                std::vector<bool> tempButtons_actual;
                                for(int j = 0; j < SDL_JoystickNumButtons(joy); j++)
                                        tempButtons_actual.push_back(false);
                                m_buttonStates_actual.push_back(tempButtons_actual);

                                // SETEA ESTADO DE TECLAS ANTERIORES EN FALSE
                                //cout << "CANTIDAD BOTONES[" << i << "]:" << SDL_JoystickNumButtons(joy) << endl;
                                std::vector<int> tempButtons_anterior;
                                for(int j = 0; j < SDL_JoystickNumButtons(joy); j++)
                                        tempButtons_anterior.push_back(0);
                                m_cantidad_de_pulsaciones.push_back(tempButtons_anterior);
                        }
                        else
                                std::cout << SDL_GetError();
                }

                SDL_JoystickEventState(SDL_ENABLE);
                m_bJoysticksInitialised = true;
        }
        else
                m_bJoysticksInitialised = false;
}

bool ControladorJoystick::getButtonState(JoyNumber joy, string nombreBoton) {
        if(m_joystickValues.size() == 0)
                return false;
        if(m_joystickValues.size() == 1)
                return m_buttonStates_actual[JOYSTICK1][(*this->correspondenciaTeclas)[nombreBoton]];
        return m_buttonStates_actual[joy][(*this->correspondenciaTeclas)[nombreBoton]];
}

void ControladorJoystick::handleEventsJoysticks(SDL_Event event) {

        // BOTONES ACTUALES
        if(event.type == SDL_JOYBUTTONDOWN) {

                int whichOne = event.jaxis.which;

                if (m_cantidad_de_pulsaciones[whichOne][event.jbutton.button] == 0) {
                        //cout << "0 pulsaciones" << endl;
                        m_buttonStates_actual[whichOne][event.jbutton.button] = true;

                        this->resetBotones(whichOne, event.jbutton.button);

                        //Agregar el nombre de la tecla presionada.
                        if (whichOne == 0){
                        	this->mapaDeCombosJugador1->agregar_tecla(getStringDeNumeroDeTecla(whichOne, event.jbutton.button));
                        }else{
                        	this->mapaDeCombosJugador2->agregar_tecla(getStringDeNumeroDeTecla(whichOne, event.jbutton.button));
                        }
                }
                if (m_cantidad_de_pulsaciones[whichOne][event.jbutton.button] == 1) {
                        //cout << "1 pulsacion" << endl;
                        m_buttonStates_actual[whichOne][event.jbutton.button] = false;
                }
                if (m_cantidad_de_pulsaciones[whichOne][event.jbutton.button] > 1) {
                        //cout << "2 pulsaciones" << endl;
                        m_buttonStates_actual[whichOne][event.jbutton.button] = false;
                }

                //TODO: acomodar esta linea para que funcione para todos los casos
                m_cantidad_de_pulsaciones[whichOne][0]++;

        }
        //cout << "CANTIDAD-PULSACIONES:" << m_cantidad_de_pulsaciones[0][0] << endl;


        else if(event.type == SDL_JOYBUTTONUP) {
                //cout << "FALLA" << endl;
                int whichOne = event.jaxis.which;
                m_cantidad_de_pulsaciones[whichOne][event.jbutton.button] = 0;
                m_buttonStates_actual[whichOne][event.jbutton.button] = false;
        }
        else {
                //this->resetBotones(0, CANTIDAD_BOTONES);
        }

        // DIRECCIONES

        if(event.type == SDL_JOYAXISMOTION)
        {
                int whichOne = event.jaxis.which;

                // left stick move left or right - EJE HORIZONTAL
                if(event.jaxis.axis == (*this->correspondenciaEjes)["JOY_EJE_HORIZONTAL"])
                {
                        if (event.jaxis.value > m_joystickDeadZone) {

                        	if (whichOne == 0)
                        		this->mapaDeCombosJugador1->agregar_tecla("JOY_DERECHA");
                        	else
                        		this->mapaDeCombosJugador2->agregar_tecla("JOY_DERECHA");

                            m_joystickValues[whichOne].first->setX(1);
                        }
                        else if(event.jaxis.value < -m_joystickDeadZone) {

                        	if (whichOne == 0)
                        		this->mapaDeCombosJugador1->agregar_tecla("JOY_IZQUIERDA");
                        	else
                        		this->mapaDeCombosJugador2->agregar_tecla("JOY_IZQUIERDA");

                        	m_joystickValues[whichOne].first->setX(-1);
                        }
                        else
                                m_joystickValues[whichOne].first->setX(0);
                }

                // left stick move up or down - EJE VERTICAL
                if(event.jaxis.axis == (*this->correspondenciaEjes)["JOY_EJE_VERTICAL"])
                {
                        if (event.jaxis.value > m_joystickDeadZone) {
                        	if (whichOne == 0)
                                this->mapaDeCombosJugador1->agregar_tecla("JOY_ABAJO");
                        	else
                        		this->mapaDeCombosJugador2->agregar_tecla("JOY_ABAJO");

                        	m_joystickValues[whichOne].first->setY(1);
                        }
                        else if(event.jaxis.value < -m_joystickDeadZone) {
                        	if (whichOne == 0)
                                this->mapaDeCombosJugador1->agregar_tecla("JOY_ARRIBA");
                        	else
                        		this->mapaDeCombosJugador2->agregar_tecla("JOY_ARRIBA");

                        	m_joystickValues[whichOne].first->setY(-1);
                        }
                        else
                                m_joystickValues[whichOne].first->setY(0);
                }
        }
}

int ControladorJoystick::xvalue(JoyNumber joy)
{
        if (m_joystickValues.size() == 0)
                return 0;
        if (m_joystickValues.size() == 1)
                return m_joystickValues[JOYSTICK1].first->getX();

        return m_joystickValues[joy].first->getX();
}

int ControladorJoystick::yvalue(JoyNumber joy) {
        if (m_joystickValues.size() == 0)
                return 0;
        if (m_joystickValues.size() == 1)
                return m_joystickValues[0].first->getY();

        return m_joystickValues[joy].first->getY();
}

bool ControladorJoystick::getAxisState(JoyNumber joy, string nombreDireccion) {
        if(m_joystickValues.size() == 0)
                return false;

        if(m_joystickValues.size() == 1) {
                if (nombreDireccion == "JOY_ARRIBA")
                        return m_joystickValues[JOYSTICK1].first->getY() == -1;
                if (nombreDireccion == "JOY_ABAJO")
                        return m_joystickValues[JOYSTICK1].first->getY() == 1;
                if (nombreDireccion == "JOY_IZQUIERDA")
                        return m_joystickValues[JOYSTICK1].first->getX() == -1;
                if (nombreDireccion == "JOY_DERECHA")
                        return m_joystickValues[JOYSTICK1].first->getX() == 1;
        }

        if (nombreDireccion == "JOY_ARRIBA")
                return m_joystickValues[joy].first->getY() == -1;
        if (nombreDireccion == "JOY_ABAJO")
                return m_joystickValues[joy].first->getY() == 1;
        if (nombreDireccion == "JOY_IZQUIERDA")
                return m_joystickValues[joy].first->getX() == -1;
        if (nombreDireccion == "JOY_DERECHA")
                return m_joystickValues[joy].first->getX() == 1;

        return false; // NUNCA VA A PASAR
}

std::map<string, int>* ControladorJoystick::correspondenciaTeclasPorDefecto() {

        std::map<string, int>* correspondencia = new std::map<string, int>;

        (*correspondencia)["JOY_PINIA_ALTA"]     = 0;
        (*correspondencia)["JOY_PATADA_ALTA"]    = 1;
        (*correspondencia)["JOY_PINIA_BAJA"]     = 2;
        (*correspondencia)["JOY_PATADA_BAJA"]    = 3;
        (*correspondencia)["JOY_DEFENSA"]        = 7;
        (*correspondencia)["JOY_PODER"]          = 6;
        return correspondencia;
}

std::map<string, int>* ControladorJoystick::correspondenciaEjesPorDefecto() {
        std::map<string, int>* correspondencia = new std::map<string, int>;

        (*correspondencia)["JOY_EJE_HORIZONTAL"]  = 0;
        (*correspondencia)["JOY_EJE_VERTICAL"]    = 1;
        return correspondencia;
}

std::map<string, bool>* ControladorJoystick::getJoystickState(JoyNumber joy) {

        if (m_joystickValues.size() == 0) {
                refreshJoystickStateNulo();
                return this->estadoJoystickNulo;
        }

        if (m_joystickValues.size() == 1 && joy == JOYSTICK1) {
                refreshJoystickState1();
                return this->estadoJoystick1;
        }

        if (m_joystickValues.size() == 1 && joy == JOYSTICK2) {
                refreshJoystickStateNulo();
                return this->estadoJoystickNulo;
        }

        if (joy == JOYSTICK1) {
                refreshJoystickState1();
                return this->estadoJoystick1;
        }

        if (joy == JOYSTICK2) {
                refreshJoystickState2();
                return this->estadoJoystick2;
        }

        cout << "ERROR:InputHandler::getJoystickState" << endl;
        return NULL; // ESTO NUNCA VA A PASAR

}

void ControladorJoystick::refreshJoystickState1() {
        (*this->estadoJoystick1)["JOY_PINIA_ALTA"]     = this->getButtonState(JOYSTICK1, "JOY_PINIA_ALTA");
        (*this->estadoJoystick1)["JOY_PATADA_ALTA"]    = this->getButtonState(JOYSTICK1, "JOY_PATADA_ALTA");
        (*this->estadoJoystick1)["JOY_PINIA_BAJA"]     = this->getButtonState(JOYSTICK1, "JOY_PINIA_BAJA");
        (*this->estadoJoystick1)["JOY_PATADA_BAJA"]    = this->getButtonState(JOYSTICK1, "JOY_PATADA_BAJA");
        (*this->estadoJoystick1)["JOY_DEFENSA"]            = this->getButtonState(JOYSTICK1, "JOY_DEFENSA");
        (*this->estadoJoystick1)["JOY_PODER"]              = this->getButtonState(JOYSTICK1, "JOY_PODER");

        (*this->estadoJoystick1)["JOY_ARRIBA"]             = this->getAxisState(JOYSTICK1, "JOY_ARRIBA");
        (*this->estadoJoystick1)["JOY_ABAJO"]              = this->getAxisState(JOYSTICK1, "JOY_ABAJO");
        (*this->estadoJoystick1)["JOY_IZQUIERDA"]          = this->getAxisState(JOYSTICK1, "JOY_IZQUIERDA");
        (*this->estadoJoystick1)["JOY_DERECHA"]            = this->getAxisState(JOYSTICK1, "JOY_DERECHA");
}

void ControladorJoystick::refreshJoystickState2() {
        (*this->estadoJoystick2)["JOY_PINIA_ALTA"]     = this->getButtonState(JOYSTICK2, "JOY_PINIA_ALTA");
        (*this->estadoJoystick2)["JOY_PATADA_ALTA"]    = this->getButtonState(JOYSTICK2, "JOY_PATADA_ALTA");
        (*this->estadoJoystick2)["JOY_PINIA_BAJA"]     = this->getButtonState(JOYSTICK2, "JOY_PINIA_BAJA");
        (*this->estadoJoystick2)["JOY_PATADA_BAJA"]    = this->getButtonState(JOYSTICK2, "JOY_PATADA_BAJA");
        (*this->estadoJoystick2)["JOY_DEFENSA"]        = this->getButtonState(JOYSTICK2, "JOY_DEFENSA");
        (*this->estadoJoystick2)["JOY_PODER"]          = this->getButtonState(JOYSTICK2, "JOY_PODER");

        (*this->estadoJoystick2)["JOY_ARRIBA"]         = this->getAxisState(JOYSTICK2, "JOY_ARRIBA");
        (*this->estadoJoystick2)["JOY_ABAJO"]          = this->getAxisState(JOYSTICK2, "JOY_ABAJO");
        (*this->estadoJoystick2)["JOY_IZQUIERDA"]      = this->getAxisState(JOYSTICK2, "JOY_IZQUIERDA");
        (*this->estadoJoystick2)["JOY_DERECHA"]        = this->getAxisState(JOYSTICK2, "JOY_DERECHA");
}

void ControladorJoystick::refreshJoystickStateNulo() {
        (*this->estadoJoystickNulo)["JOY_PINIA_ALTA"]     = false;
        (*this->estadoJoystickNulo)["JOY_PATADA_ALTA"]    = false;
        (*this->estadoJoystickNulo)["JOY_PINIA_BAJA"]     = false;
        (*this->estadoJoystickNulo)["JOY_PATADA_BAJA"]    = false;
        (*this->estadoJoystickNulo)["JOY_DEFENSA"]        = false;
        (*this->estadoJoystickNulo)["JOY_PODER"]          = false;

        (*this->estadoJoystickNulo)["JOY_ARRIBA"]         = false;
        (*this->estadoJoystickNulo)["JOY_ABAJO"]          = false;
        (*this->estadoJoystickNulo)["JOY_IZQUIERDA"]      = false;
        (*this->estadoJoystickNulo)["JOY_DERECHA"]        = false;
}

void ControladorJoystick::resetControladorJoystick(){
        //Reset Joystick1
        (*this->estadoJoystick1)["JOY_PINIA_ALTA"]     = false;
        (*this->estadoJoystick1)["JOY_PATADA_ALTA"]    = false;
        (*this->estadoJoystick1)["JOY_PINIA_BAJA"]     = false;
        (*this->estadoJoystick1)["JOY_PATADA_BAJA"]    = false;
        (*this->estadoJoystick1)["JOY_DEFENSA"]        = false;
        (*this->estadoJoystick1)["JOY_PODER"]          = false;

        (*this->estadoJoystick1)["JOY_ARRIBA"]         = false;
        (*this->estadoJoystick1)["JOY_ABAJO"]          = false;
        (*this->estadoJoystick1)["JOY_IZQUIERDA"]      = false;
        (*this->estadoJoystick1)["JOY_DERECHA"]        = false;

        //Reset Joystick2
        (*this->estadoJoystick2)["JOY_PINIA_ALTA"]     = false;
        (*this->estadoJoystick2)["JOY_PATADA_ALTA"]    = false;
        (*this->estadoJoystick2)["JOY_PINIA_BAJA"]     = false;
        (*this->estadoJoystick2)["JOY_PATADA_BAJA"]    = false;
        (*this->estadoJoystick2)["JOY_DEFENSA"]        = false;
        (*this->estadoJoystick2)["JOY_PODER"]          = false;

        (*this->estadoJoystick2)["JOY_ARRIBA"]         = false;
        (*this->estadoJoystick2)["JOY_ABAJO"]          = false;
        (*this->estadoJoystick2)["JOY_IZQUIERDA"]      = false;
        (*this->estadoJoystick2)["JOY_DERECHA"]        = false;
}


ControladorJoystick::~ControladorJoystick()
{
    // clear our arrays
    m_joystickValues.clear();
    m_joysticks.clear();
    m_buttonStates_actual.clear();

    correspondenciaTeclas->clear();
    delete correspondenciaTeclas;
    correspondenciaEjes->clear();
    delete correspondenciaEjes;

    estadoJoystick1->clear();
    delete estadoJoystick1;
    estadoJoystick2->clear();
    delete estadoJoystick2;
    estadoJoystickNulo->clear();
    delete estadoJoystickNulo;
}


void ControladorJoystick::clean() {
    // clear our arrays

    m_joystickValues.clear();
    m_joysticks.clear();
    m_buttonStates_actual.clear();

        /*
    correspondenciaTeclas->clear();
    delete correspondenciaTeclas;
    correspondenciaEjes->clear();
    delete correspondenciaEjes;
    */

    estadoJoystick1->clear();
    delete estadoJoystick1;
    estadoJoystick2->clear();
    delete estadoJoystick2;
    estadoJoystickNulo->clear();
    delete estadoJoystickNulo;
}

// RESET VERDADERO. Reseteo los botones menos el indicado por nro_boton.
void ControladorJoystick::resetBotones(int whichOne, Uint8 nro_boton) {
	for (Uint8 b = 0; b < 8; b++)
		if (b != nro_boton)
			m_buttonStates_actual[whichOne][b] = false;
}

string ControladorJoystick::getStringDeNumeroDeTecla(int joy, Uint8 nro_boton) {
	// TODO: Corroborar numero de JOY
    for (map<string, int>::iterator it = this->correspondenciaTeclas->begin() ; it != this->correspondenciaTeclas->end(); ++it)
    	if (it->second == nro_boton)
    		return it->first;

    cout << "ControladorJoystick::getStringofNumber: TERRIBLE ERROR" << endl;
    return "ERROR";
}

bool ControladorJoystick::cargarMapasDeCombos(MapaDeCombos* mapaJugador1, MapaDeCombos* mapaJugador2){
	this->mapaDeCombosJugador1 = mapaJugador1;
	this->mapaDeCombosJugador2 = mapaJugador2;
}


//Para manejar mapa de combos.
bool ControladorJoystick::combo_completado(int numeroJoystick){
	if(numeroJoystick == 0){
		return this->mapaDeCombosJugador1->combo_completado();
	}else{
		return this->mapaDeCombosJugador2->combo_completado();
	}
}

string ControladorJoystick::informar_combo(int numeroJoystick){
	if(numeroJoystick == 0){
		return this->mapaDeCombosJugador1->informar_combo();
	}else{
		return this->mapaDeCombosJugador2->informar_combo();
	}
}

void ControladorJoystick::buscar_combo(int numeroJoystick){
	if(numeroJoystick == 0){
		this->mapaDeCombosJugador1->buscarCombo();
	}else{
		this->mapaDeCombosJugador2->buscarCombo();
	}
}

deque<string>* ControladorJoystick::getColaDeTeclas(int numeroJoystick) {
	if (numeroJoystick == 0)
		return this->mapaDeCombosJugador1->getColaDeTeclas();
	return this->mapaDeCombosJugador2->getColaDeTeclas();
}

void ControladorJoystick::imprimirColaBotones(JoyNumber joy) {

	cout << "========== COLA EVENTOS JOYSTICK" << joy << "===========" << endl;

	if (joy == JOYSTICK1)
		mapaDeCombosJugador1->imprimir();

	if (joy == JOYSTICK2)
		mapaDeCombosJugador2->imprimir();

	cout << "============================================" << endl;

}

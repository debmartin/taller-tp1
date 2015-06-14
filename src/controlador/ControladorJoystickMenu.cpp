/*
 * ControladorJoystickMenu.cpp
 *
 *  Created on: 10/6/2015
 *      Author: val
 */

#include "ControladorJoystickMenu.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <iostream>

#define CANTIDAD_BOTONES 8

ControladorJoystickMenu* ControladorJoystickMenu::instancia_unica = NULL;

ControladorJoystickMenu* ControladorJoystickMenu::Instance()
{
        if (instancia_unica == NULL)
        {
                instancia_unica = new ControladorJoystickMenu();
        }
        return instancia_unica;
}

ControladorJoystickMenu::ControladorJoystickMenu() {};

bool ControladorJoystickMenu::joysticksInitialised() {
        return m_bJoysticksInitialised;
}

void ControladorJoystickMenu::initialiseJoysticks(
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

    	//agrego el mapeo para los botones select y start
    	(*this->correspondenciaTeclas)["JOY_SELECT"] = 8;
    	(*this->correspondenciaTeclas)["JOY_START"] = 9;

        for ( std::map<string,int>::iterator it = correspondenciaTeclasJ1->begin(); it!=correspondenciaTeclasJ1->end(); it++ )
        {
        	cout<<it->first<<","<<it->second<<endl;
        }

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

bool ControladorJoystickMenu::getButtonState(JoyNumberMenu joy, string nombreBoton) {
        if(m_joystickValues.size() == 0)
                return false;
        if(m_joystickValues.size() == 1)
                return m_buttonStates_actual[JOYSTICK1MENU][(*this->correspondenciaTeclas)[nombreBoton]];
        return m_buttonStates_actual[joy][(*this->correspondenciaTeclas)[nombreBoton]];
}

void ControladorJoystickMenu::handleEventsJoysticks(SDL_Event event) {

        // BOTONES ACTUALES
        if(event.type == SDL_JOYBUTTONDOWN) {

                int whichOne = event.jaxis.which;

                if (m_cantidad_de_pulsaciones[whichOne][event.jbutton.button] == 0) {
                        //cout << "0 pulsaciones" << endl;
                        m_buttonStates_actual[whichOne][event.jbutton.button] = true;

                        this->resetBotones(whichOne, event.jbutton.button);

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
                            m_joystickValues[whichOne].first->setX(1);
                        }
                        else if(event.jaxis.value < -m_joystickDeadZone) {
                        	m_joystickValues[whichOne].first->setX(-1);
                        }
                        else
                                m_joystickValues[whichOne].first->setX(0);
                }

                // left stick move up or down - EJE VERTICAL
                if(event.jaxis.axis == (*this->correspondenciaEjes)["JOY_EJE_VERTICAL"])
                {
                        if (event.jaxis.value > m_joystickDeadZone) {
                                m_joystickValues[whichOne].first->setY(1);
                        }
                        else if(event.jaxis.value < -m_joystickDeadZone) {
                                m_joystickValues[whichOne].first->setY(-1);
                        }
                        else
                                m_joystickValues[whichOne].first->setY(0);
                }
        }
}

int ControladorJoystickMenu::xvalue(JoyNumberMenu joy)
{
        if (m_joystickValues.size() == 0)
                return 0;
        if (m_joystickValues.size() == 1)
                return m_joystickValues[JOYSTICK1MENU].first->getX();

        return m_joystickValues[joy].first->getX();
}

int ControladorJoystickMenu::yvalue(JoyNumberMenu joy) {
        if (m_joystickValues.size() == 0)
                return 0;
        if (m_joystickValues.size() == 1)
                return m_joystickValues[0].first->getY();

        return m_joystickValues[joy].first->getY();
}

bool ControladorJoystickMenu::getAxisState(JoyNumberMenu joy, string nombreDireccion) {
        if(m_joystickValues.size() == 0)
                return false;

        if(m_joystickValues.size() == 1) {
                if (nombreDireccion == "JOY_ARRIBA")
                        return m_joystickValues[JOYSTICK1MENU].first->getY() == -1;
                if (nombreDireccion == "JOY_ABAJO")
                        return m_joystickValues[JOYSTICK1MENU].first->getY() == 1;
                if (nombreDireccion == "JOY_IZQUIERDA")
                        return m_joystickValues[JOYSTICK1MENU].first->getX() == -1;
                if (nombreDireccion == "JOY_DERECHA")
                        return m_joystickValues[JOYSTICK1MENU].first->getX() == 1;
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

std::map<string, int>* ControladorJoystickMenu::correspondenciaTeclasPorDefecto() {

        std::map<string, int>* correspondencia = new std::map<string, int>;

        (*correspondencia)["JOY_PINIA_ALTA"]     = 0;
        (*correspondencia)["JOY_PATADA_ALTA"]    = 1;
        (*correspondencia)["JOY_PINIA_BAJA"]     = 2;
        (*correspondencia)["JOY_PATADA_BAJA"]    = 3;
        (*correspondencia)["JOY_DEFENSA"]        = 7;
        (*correspondencia)["JOY_PODER"]          = 6;
        return correspondencia;
}

std::map<string, int>* ControladorJoystickMenu::correspondenciaEjesPorDefecto() {
        std::map<string, int>* correspondencia = new std::map<string, int>;

        (*correspondencia)["JOY_EJE_HORIZONTAL"]  = 0;
        (*correspondencia)["JOY_EJE_VERTICAL"]    = 1;
        return correspondencia;
}

std::map<string, bool>* ControladorJoystickMenu::getJoystickState(JoyNumberMenu joy) {

        if (m_joystickValues.size() == 0) {
                refreshJoystickStateNulo();
                return this->estadoJoystickNulo;
        }

        if (m_joystickValues.size() == 1 && joy == JOYSTICK1MENU) {
                refreshJoystickState1();
                return this->estadoJoystick1;
        }

        if (m_joystickValues.size() == 1 && joy == JOYSTICK2MENU) {
                refreshJoystickStateNulo();
                return this->estadoJoystickNulo;
        }

        if (joy == JOYSTICK1MENU) {
                refreshJoystickState1();
                return this->estadoJoystick1;
        }

        if (joy == JOYSTICK2MENU) {
                refreshJoystickState2();
                return this->estadoJoystick2;
        }

        cout << "ERROR:InputHandler::getJoystickState" << endl;
        return NULL; // ESTO NUNCA VA A PASAR

}

void ControladorJoystickMenu::refreshJoystickState1() {
        (*this->estadoJoystick1)["JOY_PINIA_ALTA"]     = this->getButtonState(JOYSTICK1MENU, "JOY_PINIA_ALTA");
        (*this->estadoJoystick1)["JOY_PATADA_ALTA"]    = this->getButtonState(JOYSTICK1MENU, "JOY_PATADA_ALTA");
        (*this->estadoJoystick1)["JOY_PINIA_BAJA"]     = this->getButtonState(JOYSTICK1MENU, "JOY_PINIA_BAJA");
        (*this->estadoJoystick1)["JOY_PATADA_BAJA"]    = this->getButtonState(JOYSTICK1MENU, "JOY_PATADA_BAJA");
        (*this->estadoJoystick1)["JOY_DEFENSA"]        = this->getButtonState(JOYSTICK1MENU, "JOY_DEFENSA");
        (*this->estadoJoystick1)["JOY_PODER"]          = this->getButtonState(JOYSTICK1MENU, "JOY_PODER");
        (*this->estadoJoystick1)["JOY_SELECT"]         = this->getButtonState(JOYSTICK1MENU, "JOY_SELECT");
        (*this->estadoJoystick1)["JOY_START"]          = this->getButtonState(JOYSTICK1MENU, "JOY_START");

        (*this->estadoJoystick1)["JOY_ARRIBA"]             = this->getAxisState(JOYSTICK1MENU, "JOY_ARRIBA");
        (*this->estadoJoystick1)["JOY_ABAJO"]              = this->getAxisState(JOYSTICK1MENU, "JOY_ABAJO");
        (*this->estadoJoystick1)["JOY_IZQUIERDA"]          = this->getAxisState(JOYSTICK1MENU, "JOY_IZQUIERDA");
        (*this->estadoJoystick1)["JOY_DERECHA"]            = this->getAxisState(JOYSTICK1MENU, "JOY_DERECHA");
}

void ControladorJoystickMenu::refreshJoystickState2() {
        (*this->estadoJoystick2)["JOY_PINIA_ALTA"]     = this->getButtonState(JOYSTICK2MENU, "JOY_PINIA_ALTA");
        (*this->estadoJoystick2)["JOY_PATADA_ALTA"]    = this->getButtonState(JOYSTICK2MENU, "JOY_PATADA_ALTA");
        (*this->estadoJoystick2)["JOY_PINIA_BAJA"]     = this->getButtonState(JOYSTICK2MENU, "JOY_PINIA_BAJA");
        (*this->estadoJoystick2)["JOY_PATADA_BAJA"]    = this->getButtonState(JOYSTICK2MENU, "JOY_PATADA_BAJA");
        (*this->estadoJoystick2)["JOY_DEFENSA"]        = this->getButtonState(JOYSTICK2MENU, "JOY_DEFENSA");
        (*this->estadoJoystick2)["JOY_PODER"]          = this->getButtonState(JOYSTICK2MENU, "JOY_PODER");
        (*this->estadoJoystick2)["JOY_SELECT"]         = this->getButtonState(JOYSTICK2MENU, "JOY_SELECT");
        (*this->estadoJoystick2)["JOY_START"]          = this->getButtonState(JOYSTICK2MENU, "JOY_START");

        (*this->estadoJoystick2)["JOY_ARRIBA"]         = this->getAxisState(JOYSTICK2MENU, "JOY_ARRIBA");
        (*this->estadoJoystick2)["JOY_ABAJO"]          = this->getAxisState(JOYSTICK2MENU, "JOY_ABAJO");
        (*this->estadoJoystick2)["JOY_IZQUIERDA"]      = this->getAxisState(JOYSTICK2MENU, "JOY_IZQUIERDA");
        (*this->estadoJoystick2)["JOY_DERECHA"]        = this->getAxisState(JOYSTICK2MENU, "JOY_DERECHA");
}

void ControladorJoystickMenu::refreshJoystickStateNulo() {
        (*this->estadoJoystickNulo)["JOY_PINIA_ALTA"]     = false;
        (*this->estadoJoystickNulo)["JOY_PATADA_ALTA"]    = false;
        (*this->estadoJoystickNulo)["JOY_PINIA_BAJA"]     = false;
        (*this->estadoJoystickNulo)["JOY_PATADA_BAJA"]    = false;
        (*this->estadoJoystickNulo)["JOY_DEFENSA"]        = false;
        (*this->estadoJoystickNulo)["JOY_PODER"]          = false;
        (*this->estadoJoystickNulo)["JOY_SELECT"]         = false;
        (*this->estadoJoystickNulo)["JOY_START"]          = false;

        (*this->estadoJoystickNulo)["JOY_ARRIBA"]         = false;
        (*this->estadoJoystickNulo)["JOY_ABAJO"]          = false;
        (*this->estadoJoystickNulo)["JOY_IZQUIERDA"]      = false;
        (*this->estadoJoystickNulo)["JOY_DERECHA"]        = false;
}

void ControladorJoystickMenu::resetControladorJoystick(){
        //Reset Joystick1
        (*this->estadoJoystick1)["JOY_PINIA_ALTA"]     = false;
        (*this->estadoJoystick1)["JOY_PATADA_ALTA"]    = false;
        (*this->estadoJoystick1)["JOY_PINIA_BAJA"]     = false;
        (*this->estadoJoystick1)["JOY_PATADA_BAJA"]    = false;
        (*this->estadoJoystick1)["JOY_DEFENSA"]        = false;
        (*this->estadoJoystick1)["JOY_PODER"]          = false;
        (*this->estadoJoystick1)["JOY_SELECT"]         = false;
        (*this->estadoJoystick1)["JOY_START"]          = false;

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
        (*this->estadoJoystick2)["JOY_SELECT"]         = false;
        (*this->estadoJoystick2)["JOY_START"]          = false;

        (*this->estadoJoystick2)["JOY_ARRIBA"]         = false;
        (*this->estadoJoystick2)["JOY_ABAJO"]          = false;
        (*this->estadoJoystick2)["JOY_IZQUIERDA"]      = false;
        (*this->estadoJoystick2)["JOY_DERECHA"]        = false;
}


ControladorJoystickMenu::~ControladorJoystickMenu()
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


void ControladorJoystickMenu::clean() {
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
void ControladorJoystickMenu::resetBotones(int whichOne, Uint8 nro_boton) {
        for (Uint8 b = 0; b < 8; b++)
                if (b != nro_boton)
                        m_buttonStates_actual[whichOne][b] = false;
}

string ControladorJoystickMenu::getStringDeNumeroDeTecla(int joy, Uint8 nro_boton) {
	// TODO: Corroborar numero de JOY
    for (map<string, int>::iterator it = this->correspondenciaTeclas->begin() ; it != this->correspondenciaTeclas->end(); ++it)
    	if (it->second == nro_boton)
    		return it->first;
    return "ERROR";
}

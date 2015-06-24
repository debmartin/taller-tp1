/*
 * ControladorJoystickMenu.h
 *
 *  Created on: 10/6/2015
 *      Author: val
 */

#ifndef SRC_CONTROLADOR_CONTROLADORJOYSTICKMENU_H_
#define SRC_CONTROLADOR_CONTROLADORJOYSTICKMENU_H_

#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_stdinc.h>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Vector2D.h"

union SDL_Event;

using namespace std;

enum JoyNumberMenu {
        JOYSTICK1MENU,
        JOYSTICK2MENU
} typedef JoyNumberMenu;

class ControladorJoystickMenu {

private:

        static const int m_joystickDeadZone = 10000;

        // GUARDA JOYSTICKS
        std::vector< SDL_Joystick* > m_joysticks;
        // GUARDA ESTADO DE BOTONES
        std::vector< std::vector<bool> > m_buttonStates_actual;
        std::vector< std::vector<int> > m_cantidad_de_pulsaciones;
        // GUARDA BOTONES ARRIBA, ABAJO, IZQUIERDA, DERECHA
        std::vector< std::pair<Vector2D*, Vector2D*> > m_joystickValues;

        bool m_bJoysticksInitialised;

        static ControladorJoystickMenu* instancia_unica;
        ControladorJoystickMenu();

        std::map<string, int>* correspondenciaTeclas;
        std::map<string, int>* correspondenciaEjes;

        std::map<string, bool>* estadoJoystick;

        std::map<string, int>* correspondenciaTeclasPorDefecto();
        std::map<string, int>* correspondenciaEjesPorDefecto();

        std::map<string, bool>* estadoJoystick1;
        std::map<string, bool>* estadoJoystick2;
        std::map<string, bool>* estadoJoystickNulo;

        void refreshJoystickState1();
        void refreshJoystickState2();
        void refreshJoystickStateNulo();

public:
        void handleEventsJoysticks(SDL_Event e);
        //TODO falta utilizar las correspondencias respectivas al jugador 2. Estan en los ultimos 2 parametros
        void initialiseJoysticks(std::map<string, int>* correspondenciaTeclasJ1 = NULL, std::map<string, int>* correspondenciaEjesJ1 = NULL,
                                                         std::map<string, int>* correspondenciaTeclasJ2 = NULL, std::map<string, int>* correspondenciaEjesJ2 = NULL);
        bool joysticksInitialised();
        static ControladorJoystickMenu* Instance();
        bool getButtonState(JoyNumberMenu joy, string nombreBoton);
        bool getAxisState(JoyNumberMenu joy, string nombreDireccion);
        int xvalue(JoyNumberMenu joy);
        int yvalue(JoyNumberMenu joy);
        void update();
        void resetControladorJoystick();
        void clean();
        std::map<string, bool>* getJoystickState(JoyNumberMenu joy);
        void resetBotones(int whichOne, Uint8 nro_boton);
        virtual ~ControladorJoystickMenu();

        void imprimirColaBotones(JoyNumberMenu joy);

    	string getStringDeNumeroDeTecla(int joy, Uint8 nro_boton);
    	//string getStringdeNumerodeEje(JoyNumber joy, Uint8 nro_boton);

};
typedef ControladorJoystickMenu TheInputHandlerMenu;


#endif /* SRC_CONTROLADOR_CONTROLADORJOYSTICKMENU_H_ */
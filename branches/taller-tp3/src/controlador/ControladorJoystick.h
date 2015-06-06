#include "SDL2/SDL.h"
#include <vector>
#include <iostream>
#include <map>
#include "Vector2D.h"

#include "../modelo/MapaDeCombos.h"

using namespace std;

enum JoyNumber {
        JOYSTICK1,
        JOYSTICK2
} typedef JoyNumber;

class ControladorJoystick {

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

        static ControladorJoystick* instancia_unica;
        ControladorJoystick();

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

    	MapaDeCombos* mapaCombos;
public:
        void handleEventsJoysticks(SDL_Event e);
        //TODO falta utilizar las correspondencias respectivas al jugador 2. Estan en los ultimos 2 parametros
        void initialiseJoysticks(std::map<string, int>* correspondenciaTeclasJ1 = NULL, std::map<string, int>* correspondenciaEjesJ1 = NULL,
                                                         std::map<string, int>* correspondenciaTeclasJ2 = NULL, std::map<string, int>* correspondenciaEjesJ2 = NULL);
        bool joysticksInitialised();
        static ControladorJoystick* Instance();
        bool getButtonState(JoyNumber joy, string nombreBoton);
        bool getAxisState(JoyNumber joy, string nombreDireccion);
        int xvalue(JoyNumber joy);
        int yvalue(JoyNumber joy);
        void update();
        void resetControladorJoystick();
        void clean();
        std::map<string, bool>* getJoystickState(JoyNumber joy);
        void resetBotones(int whichOne, Uint8 nro_boton);
        virtual ~ControladorJoystick();

        //Para manejar mapa de combos:
        bool combo_completado();
        int informar_combo();
};
typedef ControladorJoystick TheInputHandler;

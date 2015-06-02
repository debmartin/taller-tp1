#include "ControladorJoystick.h"

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
		for(int i = 0; i < SDL_NumJoysticks(); i++)	{
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			if(joy) {

				// INICIA JOYSTICKS
				m_joysticks.push_back(joy);

				// SETEO DIRECCIONES EN CERO
				m_joystickValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));

				// SETEA ESTADO DE TECLAS EN FALSE
				//cout << "CANTIDAD BOTONES[" << i << "]:" << SDL_JoystickNumButtons(joy) << endl;
				std::vector<bool> tempButtons;
				for(int j = 0; j < SDL_JoystickNumButtons(joy); j++)
					tempButtons.push_back(false);

				m_buttonStates.push_back(tempButtons);
			}
			else
				std::cout << SDL_GetError();
		}

		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;
		//std::cout << "Initialised "<< m_joysticks.size() << " joystick(s)";
	}
	else
		m_bJoysticksInitialised = false;
}

bool ControladorJoystick::getButtonState(JoyNumber joy, string nombreBoton) {
	if(m_joystickValues.size() == 0)
		return false;
	if(m_joystickValues.size() == 1)
		return m_buttonStates[JOYSTICK1][(*this->correspondenciaTeclas)[nombreBoton]];
	return m_buttonStates[joy][(*this->correspondenciaTeclas)[nombreBoton]];
}

void ControladorJoystick::handleEventsJoysticks(SDL_Event event) {


	// BOTONES
	if(event.type == SDL_JOYBUTTONDOWN) {
		int whichOne = event.jaxis.which;
		m_buttonStates[whichOne][event.jbutton.button] = true;
	}
	if(event.type == SDL_JOYBUTTONUP) {
		int whichOne = event.jaxis.which;
		m_buttonStates[whichOne][event.jbutton.button] = false;
	}

	// DIRECCIONES

	if(event.type == SDL_JOYAXISMOTION)
	{
		int whichOne = event.jaxis.which;

		// left stick move left or right - EJE HORIZONTAL
		if(event.jaxis.axis == (*this->correspondenciaEjes)["JOY_EJE_HORIZONTAL"])
		{
			if (event.jaxis.value > m_joystickDeadZone)
				m_joystickValues[whichOne].first->setX(1);
			else if(event.jaxis.value < -m_joystickDeadZone)
				m_joystickValues[whichOne].first->setX(-1);
			else
				m_joystickValues[whichOne].first->setX(0);
		}

		// left stick move up or down - EJE VERTICAL
		if(event.jaxis.axis == (*this->correspondenciaEjes)["JOY_EJE_VERTICAL"])
		{
			if (event.jaxis.value > m_joystickDeadZone)
				m_joystickValues[whichOne].first->setY(1);
			else if(event.jaxis.value < -m_joystickDeadZone)
				m_joystickValues[whichOne].first->setY(-1);
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
	(*correspondencia)["JOY_DEFENSA"] 	     = 7;
	(*correspondencia)["JOY_PODER"] 	     = 6;
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

	if (m_joystickValues.size() == 1) {
		refreshJoystickState1();
		return this->estadoJoystick1;
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
	(*this->estadoJoystick1)["JOY_DEFENSA"] 	   = this->getButtonState(JOYSTICK1, "JOY_DEFENSA");
	(*this->estadoJoystick1)["JOY_PODER"]		   = this->getButtonState(JOYSTICK1, "JOY_PODER");

	(*this->estadoJoystick1)["JOY_ARRIBA"]		   = this->getAxisState(JOYSTICK1, "JOY_ARRIBA");
	(*this->estadoJoystick1)["JOY_ABAJO"]		   = this->getAxisState(JOYSTICK1, "JOY_ABAJO");
	(*this->estadoJoystick1)["JOY_IZQUIERDA"]	   = this->getAxisState(JOYSTICK1, "JOY_IZQUIERDA");
	(*this->estadoJoystick1)["JOY_DERECHA"]		   = this->getAxisState(JOYSTICK1, "JOY_DERECHA");
}

void ControladorJoystick::refreshJoystickState2() {
	(*this->estadoJoystick2)["JOY_PINIA_ALTA"]     = this->getButtonState(JOYSTICK2, "JOY_PINIA_ALTA");
	(*this->estadoJoystick2)["JOY_PATADA_ALTA"]    = this->getButtonState(JOYSTICK2, "JOY_PATADA_ALTA");
	(*this->estadoJoystick2)["JOY_PINIA_BAJA"]     = this->getButtonState(JOYSTICK2, "JOY_PINIA_BAJA");
	(*this->estadoJoystick2)["JOY_PATADA_BAJA"]    = this->getButtonState(JOYSTICK2, "JOY_PATADA_BAJA");
	(*this->estadoJoystick2)["JOY_DEFENSA"] 	   = this->getButtonState(JOYSTICK2, "JOY_DEFENSA");
	(*this->estadoJoystick2)["JOY_PODER"]		   = this->getButtonState(JOYSTICK2, "JOY_PODER");

	(*this->estadoJoystick2)["JOY_ARRIBA"]		   = this->getAxisState(JOYSTICK2, "JOY_ARRIBA");
	(*this->estadoJoystick2)["JOY_ABAJO"]		   = this->getAxisState(JOYSTICK2, "JOY_ABAJO");
	(*this->estadoJoystick2)["JOY_IZQUIERDA"]	   = this->getAxisState(JOYSTICK2, "JOY_IZQUIERDA");
	(*this->estadoJoystick2)["JOY_DERECHA"]		   = this->getAxisState(JOYSTICK2, "JOY_DERECHA");
}

void ControladorJoystick::refreshJoystickStateNulo() {
	(*this->estadoJoystickNulo)["JOY_PINIA_ALTA"]     = false;
	(*this->estadoJoystickNulo)["JOY_PATADA_ALTA"]    = false;
	(*this->estadoJoystickNulo)["JOY_PINIA_BAJA"]     = false;
	(*this->estadoJoystickNulo)["JOY_PATADA_BAJA"]    = false;
	(*this->estadoJoystickNulo)["JOY_DEFENSA"] 	  	  = false;
	(*this->estadoJoystickNulo)["JOY_PODER"]		  = false;

	(*this->estadoJoystickNulo)["JOY_ARRIBA"]		  = false;
	(*this->estadoJoystickNulo)["JOY_ABAJO"]		  = false;
	(*this->estadoJoystickNulo)["JOY_IZQUIERDA"]	  = false;
	(*this->estadoJoystickNulo)["JOY_DERECHA"]		  = false;
}

void ControladorJoystick::resetControladorJoystick(){
	//Reset Joystick1
	(*this->estadoJoystick1)["JOY_PINIA_ALTA"]     = false;
	(*this->estadoJoystick1)["JOY_PATADA_ALTA"]    = false;
	(*this->estadoJoystick1)["JOY_PINIA_BAJA"]     = false;
	(*this->estadoJoystick1)["JOY_PATADA_BAJA"]    = false;
	(*this->estadoJoystick1)["JOY_DEFENSA"] 	   = false;
	(*this->estadoJoystick1)["JOY_PODER"]		  = false;

	(*this->estadoJoystick1)["JOY_ARRIBA"]		  = false;
	(*this->estadoJoystick1)["JOY_ABAJO"]		  = false;
	(*this->estadoJoystick1)["JOY_IZQUIERDA"]	  = false;
	(*this->estadoJoystick1)["JOY_DERECHA"]		  = false;

	//Reset Joystick2
	(*this->estadoJoystick2)["JOY_PINIA_ALTA"]     = false;
	(*this->estadoJoystick2)["JOY_PATADA_ALTA"]    = false;
	(*this->estadoJoystick2)["JOY_PINIA_BAJA"]     = false;
	(*this->estadoJoystick2)["JOY_PATADA_BAJA"]    = false;
	(*this->estadoJoystick2)["JOY_DEFENSA"] 	   = false;
	(*this->estadoJoystick2)["JOY_PODER"]		  = false;

	(*this->estadoJoystick2)["JOY_ARRIBA"]		  = false;
	(*this->estadoJoystick2)["JOY_ABAJO"]		  = false;
	(*this->estadoJoystick2)["JOY_IZQUIERDA"]	  = false;
	(*this->estadoJoystick2)["JOY_DERECHA"]		  = false;
}


ControladorJoystick::~ControladorJoystick()
{
    // clear our arrays
    m_joystickValues.clear();
    m_joysticks.clear();
    m_buttonStates.clear();

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
    m_buttonStates.clear();

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

#ifndef SRC_VISTA_VENTANAGRAFICA_H_
#define SRC_VISTA_VENTANAGRAFICA_H_

using namespace std;

class VentanaGrafica {
private:

public:
	VentanaGrafica();
	virtual ~VentanaGrafica();

	void agregarSprite(Sprite* s, string s);
	void quitarSprite(string id);
	void cambiarSprite(string id, Sprite* nuevoSprite);
	void getSprite(string id);
	void dibujar();
};

#endif /* SRC_VISTA_VENTANAGRAFICA_H_ */

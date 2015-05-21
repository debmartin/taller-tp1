/*
 * BVH.h
 *
 *  Created on: 27/4/2015
 *      Author: val
 */

#ifndef SRC_MODELO_FISICA_BVH_H_
#define SRC_MODELO_FISICA_BVH_H_

#include "AABB.h"
#include <vector>
using namespace std;

class BVH {
private:
	AABB* cajaLimitadora;
	vector<AABB*>* cajasAABB;
	Vector2f desplazamiento;
	Vector2f pivote;

	void efectuarDesplazamiento();

public:
	BVH(vector<AABB*>* aabb, Vector2f pivote);
	virtual ~BVH();
	bool interseccion(BVH* bvh);
	void desplazarBVH(Vector2f v);
	/*Espeja respecto al centro de la caja limitadora*/
	void espejarBVH();
	double calcularAnchoEnvolvente();
	double calcularAltoEnvolvente();
	void calcularEnvolvente();
	Vector2f calcularPosicion();
	friend ostream& operator<<(ostream &o, const BVH &bvh);
	Vector2f getPivote();
};

#endif /* SRC_MODELO_FISICA_BVH_H_ */

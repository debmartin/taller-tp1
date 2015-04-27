/*
 * AABB.h
 *
 *  Created on: 27/4/2015
 *      Author: val
 */

#ifndef SRC_MODELO_FISICA_AABB_H_
#define SRC_MODELO_FISICA_AABB_H_

#include "../Vector2f.h"

class AABB {
public:
	AABB();
	AABB(Vector2f Vmin, Vector2f Vmax);
	virtual ~AABB();
	bool interseccion(AABB a);
	void desplazarAABB(Vector2f v);
	void espejarAABB(float posicionX);

private:

};

#endif /* SRC_MODELO_FISICA_AABB_H_ */

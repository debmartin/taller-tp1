/*
 * Posicionable.h
 *
 *  Created on: 3/4/2015
 *      Author: val
 */

#ifndef SRC_VISTA_POSICIONABLE_H_
#define SRC_VISTA_POSICIONABLE_H_

#include "LimitesLogicos.h"
#include "../modelo/Vector2f.h"

class Posicionable
{
    public:
        Posicionable();
        virtual ~Posicionable();
        virtual LimitesLogicos getLimitesLogicos() = 0;
};



#endif /* SRC_VISTA_POSICIONABLE_H_ */

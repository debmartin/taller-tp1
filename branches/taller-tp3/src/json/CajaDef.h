/*
 * CajaDef.h
 *
 *  Created on: 8/5/2015
 *      Author: val
 */

#ifndef SRC_JSON_CAJADEF_H_
#define SRC_JSON_CAJADEF_H_

class CajaDef {
private:
	float x1;
	float x2;
	float y1;
	float y2;

public:
	CajaDef();
	virtual ~CajaDef();
	float getX1();
	float getX2();
	float getY1();
	float getY2();
};

#endif /* SRC_JSON_CAJADEF_H_ */

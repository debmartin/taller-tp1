/*
 * ControlDef.h
 *
 *  Created on: 11/5/2015
 *      Author: ariel
 */

#ifndef SRC_JSON_CONTROLDEF_H_
#define SRC_JSON_CONTROLDEF_H_

#include <iostream>
#include <map>
#include <string>

#include "../utils/Loggeable.h"

using namespace std;

class ControlDef: public Loggeable {
private:
        std::map<string, int>* correspondenciaTeclas;
        std::map<string, int>* correspondenciaEjes;

public:
	ControlDef();
	ControlDef(map<string, int>* correspondenciaTeclas, map<string, int>* correspondenciaEjes);
	virtual ~ControlDef();
    friend ostream& operator<<(ostream &o, const ControlDef &c);
    string toString();
	std::map<string, int>* getCorrespondenciaEjes();
	std::map<string, int>* getCorrespondenciaTeclas();
};

#endif /* SRC_JSON_CONTROLDEF_H_ */

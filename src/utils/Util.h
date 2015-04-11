/*
 * Util.h
 *
 *  Created on: 7/4/2015
 *      Author: ariel
 */

#ifndef SRC_UTILS_UTIL_H_
#define SRC_UTILS_UTIL_H_

#include <string>

using namespace std;

class Util {
private:
	static Util* instancia;
	Util();
public:
	static Util* getInstancia();
	bool existeArchivo(string ruta_archivo);
	virtual ~Util();
};

#endif /* SRC_UTILS_UTIL_H_ */

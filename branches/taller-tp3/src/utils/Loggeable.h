/*
 * Loggeable.h
 *
 *  Created on: 25/4/2015
 *      Author: ariel
 */

#ifndef SRC_UTILS_LOGGEABLE_H_
#define SRC_UTILS_LOGGEABLE_H_

#include <iostream>
#include <string>
using namespace std;

class Loggeable {
public:
	Loggeable();
	virtual string toString() = 0;
	virtual ~Loggeable();
};

#endif /* SRC_UTILS_LOGGEABLE_H_ */

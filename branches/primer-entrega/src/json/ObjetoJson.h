/*
 * ObjetoJson.h
 *
 *  Created on: 17/4/2015
 *      Author: ariel
 */

#ifndef SRC_JSON_OBJETOJSON_H_
#define SRC_JSON_OBJETOJSON_H_

#include <iostream>
#include <string>
using namespace std;

class ObjetoJson {
public:
	virtual string toString() = 0;
	ObjetoJson();
	virtual ~ObjetoJson();
};

#endif /* SRC_JSON_OBJETOJSON_H_ */

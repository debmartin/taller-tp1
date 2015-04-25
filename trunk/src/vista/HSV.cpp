/*
 * HSV.cpp
 *
 *  Created on: 25/4/2015
 *      Author: gaston
 */

#include "HSV.h"

HSV::HSV(SDL_Texture* s) {
	// TODO Auto-generated constructor stub

}

float HSV::maximo(float R, float G, float V){
	if(R > G || R > V){
		return R;
	}else if(G > R || G > V){
		return G;
	}return V;
}

float HSV::minimo(float R, float G, float V){
	if(R < G || R < V){
		return R;
	}else if(G < R || G < V){
		return G;
	}return V;
}

/*
float HSV::componenteS(){
	if(maximo() == 0){
		return maximo();
	}
	return (1-maximo()/minimo());
}*/

HSV::~HSV() {
	// TODO Auto-generated destructor stub
}

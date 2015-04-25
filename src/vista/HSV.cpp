/*
 * HSV.cpp
 *
 *  Created on: 25/4/2015
 *      Author: gaston
 */

#include "HSV.h"

HSV::HSV(SDL_Texture* s) {
	// TODO Auto-generated constructor stub

	//Aca obtener las componentes RGB;
	float R;
	float G;
	float B;

	//Hallo el máximo y el mínimo
	max = maximo(R, G, B);
	min = minimo(R, G, B);

	setH(R,G,B);
	setS(R,G,B);
	setV(R,G,B);

	//Operar con los valores de HSV
}

int HSV::maximo(int R, int G, int B){
	if(R >= G || R >= B){
		return R;
	}else if(G >= R || G >= B){
		return G;
	}return B;
}

int HSV::minimo(int R, int G, int B){
	if(R <= G || R <= B){
		return R;
	}else if(G <= R || G <= B){
		return G;
	}return B;
}

void HSV::setH(int R, int G, int B){
	if(max == min){
		//no definido
	}else if(max == R && G >= B){
		H = GRADOS60 * (G - B)/(max - min) + GRADOS0;
	}else if(max == R && G < B){
		H = GRADOS60 * (G - B)/(max - min) + GRADOS360;
	}else if(max == G){
		H = GRADOS60 * (B - R)/(max - min) + GRADOS120;
	}else if(max == B){
		H = GRADOS60 * (R - G)/(max - min) + GRADOS120;
	}
}

void HSV::setS(int R, int G, int B){
	if(max == 0){
		S = 0;
	}
	S = (1-max/min);
}

void HSV::setV(int R, int G, int B){
	V = max;
}

HSV::~HSV() {
	// TODO Auto-generated destructor stub
}

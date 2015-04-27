#include "PixelColor.h"

Uint8 PixelColor::maximo(Uint8 R, Uint8 G, Uint8 B) {
	if(R >= G && R >= B){
		return R;
	}else if(G >= R && G >= B){
		return G;
	}return B;
}

Uint8 PixelColor::minimo(Uint8 R, Uint8 G, Uint8 B) {
	if(R <= G && R <= B){
		return R;
	}else if(G <= R && G <= B){
		return G;
	}return B;
}

Uint16 PixelColor::RGBtoH(Uint8 R, Uint8 G, Uint8 B) {

	float minRGB = minimo(R,G,B)/255.0f;
	float maxRGB = maximo(R,G,B)/255.0f;

	float r = R/255.0f;
	float g = G/255.0f;
	float b = B/255.0f;

	float H;

	if(maxRGB == minRGB){
		H = 0.0f;
	}else if(maxRGB == r && g >= b){
		H = GRADOS60 * (g - b)/(maxRGB - minRGB) + GRADOS0;
	}else if(maxRGB == r && g < b){
		H = GRADOS60 * (g - b)/(maxRGB - minRGB) + GRADOS360;
	}else if(maxRGB == g){
		H = GRADOS60 * (b - r)/(maxRGB - minRGB) + GRADOS120;
	}else if(maxRGB == b){
		H = GRADOS60 * (r - g)/(maxRGB - minRGB) + GRADOS240;
	}

	H = round(H); //EL REDONDEO ELIMINA LA PARTE DECIMAL, CAUSANDO EL ERROR DE 1, ESTA ES LA SOLUCION

	return (H == 360.0) ? 0 : (Uint16)H;
}

Uint16 PixelColor::RGBtoS(Uint8 R, Uint8  G, Uint8  B) {
	float minRGB = minimo(R,G,B)/255.0f;
	float maxRGB = maximo(R,G,B)/255.0f;

	return (maxRGB == 0) ? 0 : round(100*(1-minRGB/maxRGB));
}

Uint16 PixelColor::RGBtoV(Uint8 R, Uint8 G, Uint8 B){
	return round(100*(maximo(R, G, B)/255.0f));
}

void PixelColor::RGBtoHSV(Uint8 R, Uint8 G, Uint8 B, Uint16& H, Uint16& S, Uint16& V) {
	H = RGBtoH(R, G, B);
	S = RGBtoS(R, G, B);
	V = RGBtoV(R, G, B);
}

void PixelColor::HSVtoRGB(Uint16 H, Uint16 S, Uint16 V, Uint8&  R, Uint8&  G, Uint8&  B){

	float r,g,b;
	float h = H/359.0f;
	float s = S/100.0f;
	float v = V/100.0f;

	int i = floor(h * 6);
	float f = h * 6.0f - i;
	float p = v * (1.0f - s);
	float q = v * (1.0f - f * s);
	float t = v * (1.0f - (1.0f - f) * s);

	switch(i % 6){
		case 0: r = v, g = t, b = p; break;
		case 1: r = q, g = v, b = p; break;
		case 2: r = p, g = v, b = t; break;
		case 3: r = p, g = q, b = v; break;
		case 4: r = t, g = p, b = v; break;
		case 5: r = v, g = p, b = q; break;
	}

	R = (Uint8)round(r * 255);
	G = (Uint8)round(g * 255);
	B = (Uint8)round(b * 255);

}

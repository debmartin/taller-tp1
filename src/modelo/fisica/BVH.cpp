/*
 * BVH.cpp
 *
 *  Created on: 27/4/2015
 *      Author: val
 */

#include "BVH.h"

BVH::BVH(vector<AABB*>* aabb, Vector2f unPivote) :
    cajasAABB(aabb){
	pivote = unPivote;
	this->cajaLimitadora = NULL;
	calcularEnvolvente();
}

void BVH::calcularEnvolvente() {

 float limiteInferior = (*cajasAABB)[0]->getLimiteInferior();
	float limiteSuperior = (*cajasAABB)[0]->getLimiteSuperior();
	float limiteDerecho = (*cajasAABB)[0]->getLimiteDerecho();
	float limiteIzquierdo = (*cajasAABB)[0]->getLimiteIzquierdo();
	float aux;
	//cout << "tam" << cajasAABB->size()<< endl;
	for (size_t i = 1; i < cajasAABB->size(); i++){
		aux = (*cajasAABB)[i]->getLimiteInferior();
		limiteInferior = (aux < limiteInferior) ? aux : limiteInferior;
		aux = (*cajasAABB)[i]->getLimiteSuperior();
		limiteSuperior = (aux > limiteSuperior) ? aux : limiteSuperior;
		aux = (*cajasAABB)[i]->getLimiteDerecho();
		limiteDerecho = (aux > limiteDerecho) ? aux : limiteDerecho;
		aux = (*cajasAABB)[i]->getLimiteIzquierdo();
		limiteIzquierdo = (aux < limiteIzquierdo) ? aux : limiteIzquierdo;
		//cout << "itera: "<< i <<endl;
	}
	delete(this->cajaLimitadora);
	this->cajaLimitadora = new AABB(Vector2f(limiteIzquierdo, limiteInferior), Vector2f(limiteDerecho, limiteSuperior));
}

BVH::~BVH() {
	delete cajaLimitadora;
	for (int i = 0; i < cajasAABB->size(); i++)
        delete (*cajasAABB)[i];
	delete cajasAABB;
}

bool BVH::interseccion(BVH* bvh){

	// IMPRIMO TODAS LAS CAJAS DEL BVH
    for (size_t i = 0; i < cajasAABB->size(); i++)
    	cout << "CAJA[" << i << "]:" << *(*cajasAABB)[i] << endl;

    if (! cajaLimitadora->interseccion(bvh->cajaLimitadora)) {
        cout << "no llega" <<endl;
        return false;
    }
    cout << "llega";
    for (int i = 0; i < cajasAABB->size(); i++){
        for (int j = 0; j < bvh->cajasAABB->size(); j++){
            if ((*cajasAABB)[i]->interseccion((*(bvh->cajasAABB))[j]))
                return true;
        }
    }
    return false;
}

void BVH::desplazarBVH(Vector2f v){
	// DESPLAZAMIENTO DE PIVOTE
	this->pivote += v;

	// DESPLAZAMIENTO DE CAJAS AABB
    cajaLimitadora->desplazarAABB(v);
    for (int i = 0; i < cajasAABB->size(); i++){
        (*cajasAABB)[i]->desplazarAABB(v);
    }
}
/*Espeja respecto al centro de la caja limitadora*/
void BVH::espejarBVH(){
    //float ancho = cajaLimitadora->getLimiteDerecho() - cajaLimitadora->getLimiteIzquierdo();
    //float posMedia = cajaLimitadora->getLimiteIzquierdo() + ancho/2;
    for (int i = 0; i < cajasAABB->size(); i++){
        (*cajasAABB)[i]->espejarAABB(this->pivote.X());
    }
    calcularEnvolvente();
}

double BVH::calcularAnchoEnvolvente(){
	return cajaLimitadora->getLimiteDerecho() - cajaLimitadora->getLimiteIzquierdo();
}

double BVH::calcularAltoEnvolvente(){
	return cajaLimitadora->getLimiteSuperior() - cajaLimitadora->getLimiteInferior();
}

Vector2f BVH::calcularPosicion() {
    return Vector2f(cajaLimitadora->getLimiteIzquierdo(), cajaLimitadora->getLimiteInferior());
}

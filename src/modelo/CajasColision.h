/*
 * CajasColision.h
 *
 *  Created on: 9/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_CAJASCOLISION_H_
#define SRC_MODELO_CAJASCOLISION_H_

///////////////////////////////////////////////////////////////////////////
//////////////////////////Valores finales/////////////////////////////////

///*reposo:*///
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.34,0.594,0.363,0.838)
#define REPOSO_CAJA1_X1_PORCENTUAL 0.34
#define REPOSO_CAJA1_X2_PORCENTUAL 0.594
#define REPOSO_CAJA1_Y1_PORCENTUAL 0.363
#define REPOSO_CAJA1_Y2_PORCENTUAL 0.838

//caja1: piernas
//(x1,x2,y1,y2)=(0.34,0.594,0,0.363)
#define REPOSO_CAJA2_X1_PORCENTUAL 0.34
#define REPOSO_CAJA2_X2_PORCENTUAL 0.594
#define REPOSO_CAJA2_Y1_PORCENTUAL 0
#define REPOSO_CAJA2_Y2_PORCENTUAL 0.363

///*patada alta*///
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.406,0.708,0.025,0.625)
#define PATADA_ALTA_CAJA1_X1_PORCENTUAL 0.406
#define PATADA_ALTA_CAJA1_X2_PORCENTUAL 0.708
#define PATADA_ALTA_CAJA1_Y1_PORCENTUAL 0.025
#define PATADA_ALTA_CAJA1_Y2_PORCENTUAL 0.625

//caja2: pierna
//(x1,x2,y1,y2)=(0.708,0.943,0.5,0.8)
#define PATADA_ALTA_CAJA2_X1_PORCENTUAL 0.708
#define PATADA_ALTA_CAJA2_X2_PORCENTUAL 0.943
#define PATADA_ALTA_CAJA2_Y1_PORCENTUAL 0.5
#define PATADA_ALTA_CAJA2_Y2_PORCENTUAL 0.8

///*pinia alta:*///
//cuerpo:
//(x1,x2,y1,y2)=(0.359,0.651,0,0.838)

#define PINIA_ALTA_CAJA1_X1_PORCENTUAL 0.359
#define PINIA_ALTA_CAJA1_X2_PORCENTUAL 0.651
#define PINIA_ALTA_CAJA1_Y1_PORCENTUAL 0
#define PINIA_ALTA_CAJA1_Y2_PORCENTUAL 0.838

//brazo:
//(x1,x2,y1,y2)=(0.651,0.877,0.675,0.813)

#define PINIA_ALTA_CAJA2_X1_PORCENTUAL 0.651
#define PINIA_ALTA_CAJA2_X2_PORCENTUAL 0.877
#define PINIA_ALTA_CAJA2_Y1_PORCENTUAL 0.675
#define PINIA_ALTA_CAJA2_Y2_PORCENTUAL 0.813

///*agachado:*///
//(x1,x2,y1,y2)=(0.34,0.623,0,0.425)
#define AGACHADO_CAJA1_X1_PORCENTUAL 0.34
#define AGACHADO_CAJA1_X2_PORCENTUAL 0.623
#define AGACHADO_CAJA1_Y1_PORCENTUAL 0
#define AGACHADO_CAJA1_Y2_PORCENTUAL 0.425

//saltando diagonal:
//(x1,x2,y1,y2)=(0.377,0.66,0.413,0.925)
#define SALTANDO_DIAGONAL_CAJA1_X1_PORCENTUAL 0.377
#define SALTANDO_DIAGONAL_CAJA1_X2_PORCENTUAL 0.66
#define SALTANDO_DIAGONAL_CAJA1_Y1_PORCENTUAL 0.413
#define SALTANDO_DIAGONAL_CAJA1_Y2_PORCENTUAL 0.925

//saltando vertical:
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.34,0.642,0.45,0.8)
#define SALTANDO_VERTICAL_CAJA1_X1_PORCENTUAL 0.34
#define SALTANDO_VERTICAL_CAJA1_X2_PORCENTUAL 0.642
#define SALTANDO_VERTICAL_CAJA1_Y1_PORCENTUAL 0.45
#define SALTANDO_VERTICAL_CAJA1_Y2_PORCENTUAL 0.8

//caja2: piernas
//(x1,x2,y1,y2)=(0.377,0.622,0.125,0.45)
#define SALTANDO_VERTICAL_CAJA2_X1_PORCENTUAL 0.377
#define SALTANDO_VERTICAL_CAJA2_X2_PORCENTUAL 0.622
#define SALTANDO_VERTICAL_CAJA2_Y1_PORCENTUAL 0.125
#define SALTANDO_VERTICAL_CAJA2_Y2_PORCENTUAL 0.45

//patada baja:
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.406,0.708,0.025,0.625)
#define PATADA_BAJA_CAJA1_X1_PORCENTUAL 0.406
#define PATADA_BAJA_CAJA1_X2_PORCENTUAL 0.708
#define PATADA_BAJA_CAJA1_Y1_PORCENTUAL 0.025
#define PATADA_BAJA_CAJA1_Y2_PORCENTUAL 0.625

//caja2: piernas
//(x1,x2,y1,y2)=(0.717,1,0.488,0.675)
#define PATADA_BAJA_CAJA2_X1_PORCENTUAL 0.717
#define PATADA_BAJA_CAJA2_X2_PORCENTUAL 1
#define PATADA_BAJA_CAJA2_Y1_PORCENTUAL 0.488
#define PATADA_BAJA_CAJA2_Y2_PORCENTUAL 0.675

//PATADA ALTA AGACHADO:
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.35,0.717,0,0.375)
#define PATADA_ALTA_AGACHADO_CAJA1_X1_PORCENTUAL 0.35
#define PATADA_ALTA_AGACHADO_CAJA1_X2_PORCENTUAL 0.717
#define PATADA_ALTA_AGACHADO_CAJA1_Y1_PORCENTUAL 0
#define PATADA_ALTA_AGACHADO_CAJA1_Y2_PORCENTUAL 0.375
//caja2: piernas
//(x1,x2,y1,y2)=(0.717,0.85,0.375,0.563)
#define PATADA_ALTA_AGACHADO_CAJA2_X1_PORCENTUAL 0.717
#define PATADA_ALTA_AGACHADO_CAJA2_X2_PORCENTUAL 0.85
#define PATADA_ALTA_AGACHADO_CAJA2_Y1_PORCENTUAL 0.375
#define PATADA_ALTA_AGACHADO_CAJA2_Y2_PORCENTUAL 0.563

//PATADA SALTANDO VERTICAL:
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.217,0.547,0.325,0.938)
#define PATADA_SALTANDO_VERTICAL_CAJA1_X1_PORCENTUAL 0.217
#define PATADA_SALTANDO_VERTICAL_CAJA1_X2_PORCENTUAL 0.547
#define PATADA_SALTANDO_VERTICAL_CAJA1_Y1_PORCENTUAL 0.325
#define PATADA_SALTANDO_VERTICAL_CAJA1_Y2_PORCENTUAL 0.938

//caja2: piernas
//(x1,x2,y1,y2)=(0.547,0.764,0.55,0.75)
#define PATADA_SALTANDO_VERTICAL_CAJA2_X1_PORCENTUAL 0.547
#define PATADA_SALTANDO_VERTICAL_CAJA2_X2_PORCENTUAL 0.764
#define PATADA_SALTANDO_VERTICAL_CAJA2_Y1_PORCENTUAL 0.55
#define PATADA_SALTANDO_VERTICAL_CAJA2_Y2_PORCENTUAL 0.75

//PATADA SALTANDO DIAGONAL DERECHA:
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.189,0.585,0.3,0.925)
#define PATADA_SALTANDO_DIAGONAL_DERECHA_CAJA1_X1_PORCENTUAL 0.189
#define PATADA_SALTANDO_DIAGONAL_DERECHA_CAJA1_X2_PORCENTUAL 0.585
#define PATADA_SALTANDO_DIAGONAL_DERECHA_CAJA1_Y1_PORCENTUAL 0.3
#define PATADA_SALTANDO_DIAGONAL_DERECHA_CAJA1_Y2_PORCENTUAL 0.925
//caja2: piernas
//(x1,x2,y1,y2)=(0.585,0.811,0.4,0.55)
#define PATADA_SALTANDO_DIAGONAL_DERECHA_CAJA2_X1_PORCENTUAL 0.585
#define PATADA_SALTANDO_DIAGONAL_DERECHA_CAJA2_X2_PORCENTUAL 0.811
#define PATADA_SALTANDO_DIAGONAL_DERECHA_CAJA2_Y1_PORCENTUAL 0.4
#define PATADA_SALTANDO_DIAGONAL_DERECHA_CAJA2_Y2_PORCENTUAL 0.55

//PATADA SALTANDO DIAGONAL IZQUIERDA:
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.415,0.811,0.3,0.925)
#define PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_X1_PORCENTUAL 0.415
#define PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_X2_PORCENTUAL 0.811
#define PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_Y1_PORCENTUAL 0.3
#define PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_Y2_PORCENTUAL 0.925
//caja2: piernas
//(x1,x2,y1,y2)=(0.189,0.415,0.4,0.55)
#define PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_X1_PORCENTUAL 0.189
#define PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_X2_PORCENTUAL 0.415
#define PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_Y1_PORCENTUAL 0.4
#define PATADA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_Y2_PORCENTUAL 0.55

//PINIA BAJA:
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.359,0.651,0,0.838)
#define PINIA_BAJA_CAJA1_X1_PORCENTUAL 0.359
#define PINIA_BAJA_CAJA1_X2_PORCENTUAL 0.651
#define PINIA_BAJA_CAJA1_Y1_PORCENTUAL 0
#define PINIA_BAJA_CAJA1_Y2_PORCENTUAL 0.838
//caja2: piernas
//(x1,x2,y1,y2)=(0.651,0.868,0.625,0.688)
#define PINIA_BAJA_CAJA2_X1_PORCENTUAL 0.651
#define PINIA_BAJA_CAJA2_X2_PORCENTUAL 0.868
#define PINIA_BAJA_CAJA2_Y1_PORCENTUAL 0.625
#define PINIA_BAJA_CAJA2_Y2_PORCENTUAL 0.688

//PINIA SALTANDO VERTICAL Y DIAGONAL (es la misma):
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.151,0.642,0.45,0.9)
#define PINIA_SALTANDO_VERTICAL_CAJA1_X1_PORCENTUAL 0.151
#define PINIA_SALTANDO_VERTICAL_CAJA1_X2_PORCENTUAL 0.642
#define PINIA_SALTANDO_VERTICAL_CAJA1_Y1_PORCENTUAL 0.45
#define PINIA_SALTANDO_VERTICAL_CAJA1_Y2_PORCENTUAL 0.9
//caja2: piernas
//(x1,x2,y1,y2)=(0.642,0.83,0.525,0.675)
#define PINIA_SALTANDO_VERTICAL_CAJA2_X1_PORCENTUAL 0.642
#define PINIA_SALTANDO_VERTICAL_CAJA2_X2_PORCENTUAL 0.83
#define PINIA_SALTANDO_VERTICAL_CAJA2_Y1_PORCENTUAL 0.525
#define PINIA_SALTANDO_VERTICAL_CAJA2_Y2_PORCENTUAL 0.675

//PINIA SALTANDO DIAGONAL DERECHA:
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.151,0.642,0.45,0.9)
#define PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA1_X1_PORCENTUAL 0.151
#define PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA1_X2_PORCENTUAL 0.642
#define PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA1_Y1_PORCENTUAL 0.45
#define PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA1_Y2_PORCENTUAL 0.9
//caja2: piernas
//(x1,x2,y1,y2)=(0.642,0.83,0.525,0.675)
#define PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA2_X1_PORCENTUAL 0.642
#define PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA2_X2_PORCENTUAL 0.83
#define PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA2_Y1_PORCENTUAL 0.525
#define PINIA_SALTANDO_DIAGONAL_DERECHA_CAJA2_Y2_PORCENTUAL 0.675


//PINIA SALTANDO DIAGONAL IZQUIERDA:
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.358,0.849,0.45,0.9)

#define PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_X1_PORCENTUAL 0.358
#define PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_X2_PORCENTUAL 0.849
#define PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_Y1_PORCENTUAL 0.45
#define PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA1_Y2_PORCENTUAL 0.9

//caja2: piernas
//(x1,x2,y1,y2)=(0.17,0.358,0.525,0.675)
#define PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_X1_PORCENTUAL 0.17
#define PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_X2_PORCENTUAL 0.358
#define PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_Y1_PORCENTUAL 0.525
#define PINIA_SALTANDO_DIAGONAL_IZQUIERDA_CAJA2_Y2_PORCENTUAL 0.675

//DEFENDIENDO:
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.377,0.623,0.375,0.85)
#define DEFENDIENDO_CAJA1_X1_PORCENTUAL 0.377
#define DEFENDIENDO_CAJA1_X2_PORCENTUAL 0.623
#define DEFENDIENDO_CAJA1_Y1_PORCENTUAL 0.375
#define DEFENDIENDO_CAJA1_Y2_PORCENTUAL 0.85
//caja2: piernas
//(x1,x2,y1,y2)=(0.368,0.66,0,0.375)
#define DEFENDIENDO_CAJA2_X1_PORCENTUAL 0.368
#define DEFENDIENDO_CAJA2_X2_PORCENTUAL 0.66
#define DEFENDIENDO_CAJA2_Y1_PORCENTUAL 0
#define DEFENDIENDO_CAJA2_Y2_PORCENTUAL 0.375

//DEFENDIENDO AGACHADO:
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.377,0.613,0.313,0.6)
#define DEFENDIENDO_AGACHADO_CAJA1_X1_PORCENTUAL 0.377
#define DEFENDIENDO_AGACHADO_CAJA1_X2_PORCENTUAL 0.613
#define DEFENDIENDO_AGACHADO_CAJA1_Y1_PORCENTUAL 0.313
#define DEFENDIENDO_AGACHADO_CAJA1_Y2_PORCENTUAL 0.6
//caja2: piernas
//(x1,x2,y1,y2)=(0.368,0.66,0,0.313)
#define DEFENDIENDO_AGACHADO_CAJA2_X1_PORCENTUAL 0.368
#define DEFENDIENDO_AGACHADO_CAJA2_X2_PORCENTUAL 0.66
#define DEFENDIENDO_AGACHADO_CAJA2_Y1_PORCENTUAL 0
#define DEFENDIENDO_AGACHADO_CAJA2_Y2_PORCENTUAL 0.313

//GANCHO:
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.33,0.613,0,0.875)
#define GANCHO_CAJA1_X1_PORCENTUAL 0.33
#define GANCHO_CAJA1_X2_PORCENTUAL 0.613
#define GANCHO_CAJA1_Y1_PORCENTUAL 0
#define GANCHO_CAJA1_Y2_PORCENTUAL 0.875
//caja2: brazo
//(x1,x2,y1,y2)=(0.613,0.821,0.5,0.8)
#define GANCHO_CAJA2_X1_PORCENTUAL 0.613
#define GANCHO_CAJA2_X2_PORCENTUAL 0.821
#define GANCHO_CAJA2_Y1_PORCENTUAL 0.5
#define GANCHO_CAJA2_Y2_PORCENTUAL 0.8

//CAIDA DERECHA:
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.171,0.8,0,0.905)
#define CAIDA_DERECHA_CAJA1_X1_PORCENTUAL 0.171
#define CAIDA_DERECHA_CAJA1_X2_PORCENTUAL 0.8
#define CAIDA_DERECHA_CAJA1_Y1_PORCENTUAL 0
#define CAIDA_DERECHA_CAJA1_Y2_PORCENTUAL 0.905

//CAIDA IZQUIERDA:
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.2,0.828,0,0.905)
#define CAIDA_IZQUIERDA_CAJA1_X1_PORCENTUAL 0.2
#define CAIDA_IZQUIERDA_CAJA1_X2_PORCENTUAL 0.828
#define CAIDA_IZQUIERDA_CAJA1_Y1_PORCENTUAL 0
#define CAIDA_IZQUIERDA_CAJA1_Y2_PORCENTUAL 0.905

///TIRANDO PODER///
//caja1: cuerpo
//(x1,x2,y1,y2)=(0.30,0.755,0,0,0.75)
#define TIRANDO_PODER_CAJA1_X1_PORCENTUAL 0.30
#define TIRANDO_PODER_CAJA1_X2_PORCENTUAL 0.755
#define TIRANDO_PODER_CAJA1_Y1_PORCENTUAL 0
#define TIRANDO_PODER_CAJA1_Y2_PORCENTUAL 0.75

//Arma:
#define ARMA_CAJA1_X1_PORCENTUAL 0
#define ARMA_CAJA1_X2_PORCENTUAL 1
#define ARMA_CAJA1_Y1_PORCENTUAL 0
#define ARMA_CAJA1_Y2_PORCENTUAL 1
#endif /* SRC_MODELO_CAJASCOLISION_H_ */

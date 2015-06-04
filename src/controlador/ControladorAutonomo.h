/*
 * ControladorAutonomo.h
 *
 *  Created on: 30/5/2015
 *      Author: Juan
 */

#ifndef CONTROLADORAUTONOMO_H_
#define CONTROLADORAUTONOMO_H_
#ifndef NULL;
#define NULL 0;
#include "Personaje.h"
class ControladorAutonomo
{
	private:
		Personaje *personajeAControlar;
		Personaje *Oponente;

	public:
	ControladorAutonomo()
	{
		this->personajeAControlar=NULL;
		this->Oponente=NULL;
	};

	ControladorAutonomo(Personaje* acontrolar,Personaje* oponente)
	{
		this->personajeAControlar=acontrolar;
		this->Oponente=oponente;
		if (this->Oponente->direccion==DIRECCION_DERECHA)
			this->personajeAControlar->caminarIzquierda();
		else
			this->personajeAControlar->caminarDerecha();
	};

	void cambiarDireccion()
	{
		if (this->personajeAControlar->direccion==DIRECCION_DERECHA)
			this->personajeAControlar->direccion=DIRECCION_IZQUIERDA;
		else
			this->personajeAControlar->direccion=DIRECCION_DERECHA;
	};

	void hacerAvanzar()
	{
		if (this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion()==DIRECCION_IZQUIERDA)
			this->personajeAControlar->caminarDerecha();
		else
		{
			if (this->personajeAControlar->direccion()==DIRECCION_IZQUIERDA && this->Oponente->direccion()==DIRECCION_DERECHA)
				this->personajeAControlar->caminarIzquierda();
			else
				this->cambiarDireccion();
		};
	};

	void hacerRetroceder()
	{
		if (this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion()==DIRECCION_IZQUIERDA)
			this->personajeAControlar->caminarIzquierda();
		else
		{
			if (this->personajeAControlar->direccion()==DIRECCION_IZQUIERDA && this->Oponente->direccion()==DIRECCION_DERECHA)
				this->personajeAControlar->caminarDerecha();
			else
				this->cambiarDireccion();
		};
	};

	void setPersonajeaControlar(Personaje* otropersonaje)
	{
		this->personajeAControlar=otropersonaje;
	};

	void setOponente(Personaje* unoponente)
	{
		this->Oponente=unoponente;
	};

	void controlar()
	{
		switch (this->Oponente->getEstado())
		{
			case EN_ESPERA:{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
						this->personajeAControlar->patadaBaja();
				};
			}break;
			case AGACHADO:{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
						this->personajeAControlar->gancho();
				};
			}break;
			case CAMINANDO_DERECHA:{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
						this->personajeAControlar->patadaAlta();
				};
			}break;
			case CAMINANDO_IZQUIERDA:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
						this->personajeAControlar->patadaAlta();
				};
			}break;
			case SALTANDO_VERTICAL:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
						this->personajeAControlar->patadaSaltandoVertical();
				};
			}break;
			case SALTANDO_OBLICUO_DERECHA:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
						this->personajeAControlar->saltarOblicuoIzquierda();
				};
			}break;
			case SALTANDO_OBLICUO_IZQUIERDA:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
						this->personajeAControlar->saltarOblicuoDerecha();
				};
			}break;
			case PINIA_ALTA:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
					{
						this->personajeAControlar->defender();
						this->personajeAControlar->arrojarArma();
					};
				};
			}break;
			case PINIA_BAJA:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
					{
						this->personajeAControlar->agacharse();
						this->personajeAControlar->gancho();
					}
					else
					{
						this->cambiarDireccion();
						this->personajeAControlar->agacharse();
						this->personajeAControlar->gancho;
					};
				};
			}break;
			case PINIA_SALTANDO_VERTICAL:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if (this->Oponente->direccion==DIRECCION_DERECHA)
						this->personajeAControlar->saltarOblicuoIzquierda();
					else
						this->personajeAControlar->saltarOblicuoDerecha();
				};
			}break;
			case PINIA_SALTANDO_DIAGONAL_DERECHA:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
					this->personajeAControlar->saltarOblicuoIzquierda();
			}break;
			case PINIA_SALTANDO_DIAGONAL_IZQUIERDA:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
					this->personajeAControlar->saltarOblicuoDerecha();
			}break;
			case PATEANDO_SALTANDO_VERTICAL:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
					{
						this->personajeAControlar->defender();
						this->personajeAControlar->patadaAlta();
					};
				};
			}break;
			case PATEANDO_SALTANDO_DIAGONAL_DERECHA:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if (this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)
					{
						this->personajeAControlar->defender();
						this->personajeAControlar->patadaBaja();
					}
					else
					{
						this->cambiarDireccion();
						this->personajeAControlar->defender();
						this->personajeAControlar->patadaBaja();
					}
				};
			}break;
			case PATEANDO_SALTANDO_DIAGONAL_IZQUIERDA:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if (this->personajeAControlar->direccion==DIRECCION_DERECHA)
					{
						this->personajeAControlar->piniaSaltandoDiagonalIzquierda();
					}
					else
					{
						this->cambiarDireccion();
						this->personajeAControlar->piniaSaltandoDiagonalIzquierda();
					};
				};
			}break;
			case PATEANDO_ALTO:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
					{
						this->personajeAControlar->agacharse();
						this->personajeAControlar->gancho();
					};
				};
			}break;
			case PATEANDO_BAJO:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					this->hacerRetroceder();
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
						this->personajeAControlar->patadaBaja();
				};
			};
			}break;
			case PATEANDO_ALTO_AGACHADO:
			{
				this->hacerRetroceder();
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
						this->personajeAControlar->patadaBaja();
				}
			}break;
			case GANCHO:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
						this->personajeAControlar->defender();
					else
						this->cambiarDireccion();
				}
			}break;
			case DEFENDIENDO:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
						this->personajeAControlar->patadaAlta();
					else
						this->cambiarDireccion();
				};
			}break;
			case DEFENDIENDO_AGACHADO:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
						this->personajeAControlar->gancho();
				}
				else
				{
					this->cambiarDireccion();
					this->personajeAControlar->gancho();
				};
			}break;
			case RECIBIENDO_GOLPE:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
						this->personajeAControlar->piniaAlta();
				};
			}break;
			case CAIDA_DERECHA:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if (this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)
						this->personajeAControlar->arrojarArma();
				}
				else
				{
					this->cambiarDireccion();
					this->personajeAControlar->arrojarArma();
				}
			}break;
			case CAIDA_IZQUIERDA:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if (this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA)
						this->personajeAControlar->arrojarArma();
				}
				else
				{
					this->cambiarDireccion();
					this->personajeAControlar->arrojarArma();
				}
			}break;
			case TIRANDO_PODER:
			{
				if (this->personajeAControlar->vaAColisionar(this->Oponente))
				{
					if ((this->Oponente->direccion==DIRECCION_DERECHA && this->personajeAControlar->direccion==DIRECCION_IZQUIERDA)||(this->personajeAControlar->direccion==DIRECCION_DERECHA && this->Oponente->direccion==DIRECCION_IZQUIERDA))
						this->personajeAControlar->saltarVertical();
					else
					{
						this->cambiarDireccion();
						this->personajeAControlar->defenderAgachado();
					};
				};
			}break;
			default: this->hacerAvanzar();
		};
	};

	~ControladorAutonomo()
	{
/*		this->personajeAControlar=NULL;
		this->Oponente=NULL;*/
	};
};

#endif /* CONTROLADORAUTONOMO_H_ */

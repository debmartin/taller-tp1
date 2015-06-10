/*
 * Textura.h
 *
 *  Created on: 16/5/2015
 *      Author: ariel
 */

#ifndef SRC_TEXTURA_H_
#define SRC_TEXTURA_H_

#include <SDL2/SDL_ttf.h>
#include <string>

struct SDL_Color;

struct SDL_Rect;
struct SDL_Texture;

//Texture wrapper class
class Textura
{
	public:
		//Initializes variables
		Textura();

		//Deallocates memory
		~Textura();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL );

		void setFont(TTF_Font* gFont);

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;

		TTF_Font* gFont;
};

#endif /* SRC_TEXTURA_H_ */

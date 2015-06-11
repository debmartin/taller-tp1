/*
 * Textura.cpp
 *
 *  Created on: 16/5/2015
 *      Author: ariel
 */

#include "Textura.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>

#include "../utils/Logger.h"
#include "../vista/Renderizador.h"

Textura::Textura()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Textura::~Textura()
{
	//Deallocate
	free();
}

bool Textura::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		Logger::getInstance()->error("SDL_image Error. Unable to load image");
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( Renderizador::Instance()->getRenderer(), loadedSurface );
		if( newTexture == NULL )
		{
			Logger::getInstance()->error("SDL Error. Unable to create texture from.");
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool Textura::loadFromRenderedText(std::string textureText, SDL_Color textColor) {

	//Get rid of preexisting texture
	//this->free();

	SDL_Surface* textSurface = TTF_RenderText_Solid( this->gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( Renderizador::Instance()->getRenderer(), textSurface );
		if( mTexture == NULL )
		{
			Logger::getInstance()->error("SDL Error. Unable to create texture from rendered text!");
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		Logger::getInstance()->error("SDL_ttf Error. Unable to render text surface");
	}


	//Return success
	return mTexture != NULL;

}

void Textura::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Textura::render( int x, int y, SDL_Rect* clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( Renderizador::Instance()->getRenderer(), mTexture, clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE );
}

void Textura::setFont(TTF_Font* gFont) {
	this->gFont = gFont;
}

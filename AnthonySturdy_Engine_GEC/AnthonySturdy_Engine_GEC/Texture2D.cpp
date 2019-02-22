#include"Texture2D.h"

#include<SDL_image.h>
#include<iostream>

Texture2D::Texture2D(SDL_Renderer* renderer) {
	mRenderer = renderer;
}

Texture2D::~Texture2D() {
	Free();

	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(std::string path) {
	//Remove the memory used for a previous texture
	Free();

	//Load image
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL) {
		//Colour Key the image - the colour to be transparent.
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));

		//Create texture from pixels on the surface
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);

		mWidth = pSurface->w;
		mHeight = pSurface->h;

		if (mTexture == NULL) {
			std::cout << "Unable to create texture from surface. Error: " << SDL_GetError() << std::endl;
		}
		//Remove loaded surface now that we've used it
		SDL_FreeSurface(pSurface);
	} else {
		std::cout << "Unable to create surface. Error: " << IMG_GetError() << std::endl;
	}

	return mTexture != NULL;
}

void Texture2D::Free() {
	//Check texture exists before destroying
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}

	mWidth = 0.0f;
	mHeight = 0.0f;
}

void Texture2D::Render(Vector2D position, SDL_RendererFlip flip, double angle) {
	//Set where to render the texture and texture size.
	SDL_Rect renderLocation = { position.x, position.y, mWidth, mHeight };

	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip);
}
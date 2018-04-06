#pragma once
#include "Texture.h"

Texture::Texture(SDL_Renderer* renderer) :  renderer(renderer), width(0), height(0) {
}

Texture::Texture(SDL_Renderer* renderer, string fileName, uint numRows, uint numCols) : renderer(renderer) {
	loadFromImg(fileName, numRows, numCols);
}

Texture::Texture(SDL_Renderer* renderer, string text, const Font& font, const SDL_Color color) : renderer(renderer), texture(nullptr), width(0), height(0) {
	loadFromText(text, font, color);
}

Texture::~Texture() {
	close();
}

int Texture::getWidth() {
	return width;
}

int Texture::getHeight() {
	return height;
}

int Texture::getFrameWidth()
{
	return frameWidth;
}

int Texture::getFrameHeight()
{
	return frameHeight;
}

int Texture::getNumCols()
{
	return width/frameWidth;
}

int Texture::getNumRows()
{
	return height / frameHeight;
}


void Texture::close() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture); // delete current texture
		texture = nullptr;
		width = 0;
		height = 0;
	}
}

bool Texture::loadFromImg(string fileName, uint numRows, uint numCols) {
	SDL_Surface* surface = IMG_Load(fileName.c_str());
	if (surface != nullptr) {
		close(); // destroy current texture
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture != nullptr) {
			width = surface->w;
			height = surface->h;
			frameWidth = width / numCols;
			frameHeight = height / numRows;

		}
		SDL_FreeSurface(surface);
	}
	return texture != nullptr;
}

bool Texture::loadFromText(std::string text, const Font& font, const SDL_Color color) {
	SDL_Surface* textSurface = font.renderText(text, color);
	if (textSurface != nullptr) {
		close();
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture != nullptr) {
			width = textSurface->w;
			height = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return texture != nullptr;
}

void Texture::render(int x, int y) const {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = width;
	dest.h = height;
	render(dest);
}

void Texture::render(const SDL_Rect& dest, SDL_Rect* clip, SDL_RendererFlip flip) const {
	if (texture) {
		SDL_Rect default_clip = { 0, 0, width, height };
		if (clip == nullptr) {
			clip = &default_clip;
		}
		SDL_RenderCopyEx(renderer, texture, clip, &dest, NULL, NULL, flip);
	}
}

void Texture::render(const SDL_Rect& dest, double angle, SDL_Rect* clip) const {
	if (texture) {
		SDL_Rect default_clip = { 0, 0, width, height };
		if (clip == nullptr) {
			clip = &default_clip;
		}
		SDL_RenderCopyEx(renderer, texture, clip, &dest, angle, nullptr, SDL_FLIP_NONE);
	}
}

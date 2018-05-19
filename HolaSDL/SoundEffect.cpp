#include "SoundEffect.h"
#include "Game.h"
SoundEffect::SoundEffect() :
		chunck_(nullptr) {

}

SoundEffect::SoundEffect(std::string fileName) :
		chunck_(nullptr) {
	load(fileName);
}

SoundEffect::~SoundEffect() {
	close();
}

bool SoundEffect::load(std::string fileName) {
	close();
	chunck_ = Mix_LoadWAV(fileName.c_str());
	return chunck_ != nullptr;
}

void SoundEffect::play(int repetirions) {
	if (!Game::getGame()->getMute()) {
		if (chunck_ != nullptr) {
			Mix_PlayChannel(-1, chunck_, repetirions);
		}

	}
}

void SoundEffect::mute()
{
	if(chunck_ != nullptr)
		changeVolume(0);
}

void SoundEffect::unMute()
{
	if (chunck_ != nullptr)
		changeVolume(MIX_MAX_VOLUME);
}

//Metodo para seleccionar en que canal se quiere el sonido, para que no se acoplen varios del mismo tipo
void SoundEffect::playChannel(int channel, int rep)
{
	if (chunck_ != nullptr) {
		Mix_PlayChannel(channel, chunck_, rep);
	}
}

void SoundEffect::pause() {
}

void SoundEffect::close() {
	if (chunck_ != nullptr) {
		Mix_FreeChunk(chunck_);
		chunck_ = nullptr;
	}
}

void SoundEffect::changeVolume(int volume) {
	Mix_VolumeChunk(chunck_, volume);
}
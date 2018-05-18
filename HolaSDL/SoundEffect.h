#ifndef SOUNDEFFECT_H_
#define SOUNDEFFECT_H_
//#include "checkML.h"
#include "sdl_includes.h"
#include "SDL_mixer.h"
#include <string>

class SoundEffect {
public:
	SoundEffect();
	SoundEffect(std::string fileName);
	virtual ~SoundEffect();
	bool load(std::string fileName);
	void play(int repetirions = 0);
	void playChannel(int channel = -1, int rep = 0);
	void pause();
	void changeVolume(int volume);
	void close();
private:
	Mix_Chunk *chunck_ = nullptr;
};

#endif /* SOUNDEFFECT_H_ */

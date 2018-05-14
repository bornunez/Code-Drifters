#ifndef MUSIC_H_
#define MUSIC_H_

#include "SDL_mixer.h"
#include <string>

class Music {
public:
	Music();
	Music(std::string fileName);
	virtual ~Music();

	bool load(std::string fileName);
	void play(int repetitions = -1);
	void pause();
	void close();
	void stop();
private:
	Mix_Music* music_;
};

#endif /* MUSIC_H_ */

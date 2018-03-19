#ifndef SKELETONTENDERER_H_
#define SKELETONTENDERER_H_

#include "RenderComponent.h"

class SkeletonRendered : public RenderComponent {
public:
	SkeletonRendered(GameObject* o, SDL_Color color = { COLOR(0xffffffff) });
	virtual ~SkeletonRendered();
	void render();
	virtual void recieveMessage(std::string msg) {};
private:
	SDL_Color color_;
};

#endif /* SKELETONTENDERER_H_ */

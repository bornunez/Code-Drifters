#ifndef SKELETONTENDERER_H_
#define SKELETONTENDERER_H_

#include "checkML.h"
#include "RenderComponent.h"

class SkeletonRendered : public RenderComponent {
public:
	SkeletonRendered(GameObject * o, GameObject * camera);
	SkeletonRendered(SDL_Color color,GameObject* o);
	virtual ~SkeletonRendered();
	void render();
	virtual void receiveMessage(std::string msg) {};
private:
	SDL_Color color_;
	GameObject* camera;
};

#endif /* SKELETONTENDERER_H_ */

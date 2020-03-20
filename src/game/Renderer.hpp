#ifndef __RENDERER__
#define __RENDERER__

class Game;

class Renderer {
	public:
	virtual ~Renderer() {}
	virtual bool init(void) = 0;
	virtual void frame(Game* game) const = 0;
	virtual void shutdown(void) = 0;
};

#endif

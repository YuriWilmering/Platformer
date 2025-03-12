#ifndef _JIMI_H_
#define _JIMI_H_

#include "baseEntity.h"

class Jimi final : public Entity {
	public:
		Jimi();
		void draw() final;
		void update() final;
		void keyPressed(int key);
		void keyReleased(int key);

	private:
		bool pressingLeft, pressingUp, pressingRight;
};

#endif // _JIMI_H_

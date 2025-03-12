#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "baseEntity.h"

class Enemy final : public Entity {
	public:
		Enemy(int x);
		void draw() final;
		void update() final;
        void die(int timeOfHit);

    private:
        bool alive, hit;
		int direction, x;
        int green, brightness;
};

#endif // _ENEMY_H_
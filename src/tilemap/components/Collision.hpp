#ifndef __COLLISION_COMPONENT__
#define __COLLISION_COMPONENT__

#include <vector>
#include "game/Component.hpp"
#include "tilemap/Tilemap.hpp"

class CollisionComponent : public Component {
	private:
	std::vector<std::pair<float, float>> m_hitboxPoints = {};
	Tilemap &m_tilemap;

	public:
	CollisionComponent(std::shared_ptr<GameObject> owner, Tilemap &tilemap);
	void addHitboxPoint(float x, float y);
	bool collides() const;
};

#endif

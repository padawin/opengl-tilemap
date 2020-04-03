#include "Collision.hpp"

CollisionComponent::CollisionComponent(std::shared_ptr<GameObject> owner, Tilemap &tilemap) :
	Component(owner),
	m_tilemap(tilemap)
{
}

void CollisionComponent::addHitboxPoint(float x, float y) {
	m_hitboxPoints.push_back(std::make_pair(x, y));
}

bool CollisionComponent::collides() const {
	float baseX = m_owner->getPosition().x;
	float baseY = m_owner->getPosition().y;
	bool collides = false;
	for (auto point : m_hitboxPoints) {
		collides = collides || m_tilemap.collides(
			baseX + point.first,
			baseY + point.second
		);
	}
	return collides;
}

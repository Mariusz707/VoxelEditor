#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Editor/Graphic/Voxel.h"
#include "Editor/Editor/Voxel handler.h"
#include "Editor/Graphic/Camera.h"

struct CollisionID
{
	CollisionID();
	bool collision = false;
	int closestVoxel = 0;
	int closestWall = 0;
};

class Collider
{
	public:

		struct Ray
		{
			Ray() = default;
			Ray(glm::vec3 origin, glm::vec3 direction);

			glm::vec3 m_origin;
			glm::vec3 m_direction;
		};

		Collider() = default;
		Collider(Camera* camera, VoxelHandler* voxelHandler);

		void update();
		CollisionID checkForCollisions(Collider::Ray ray);

		Collider::Ray calculateScreenRay(MouseStatus* mouseStatus, Camera camera);

		bool AABBvsRAY(glm::vec3 boxMax, glm::vec3 boxMin, Collider::Ray ray);

		float max(float a, float b);
		float min(float a, float b);

	private:

		VoxelHandler* m_voxelHandler;
		Camera* m_camera;

};


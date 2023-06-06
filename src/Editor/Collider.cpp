#include <Editor/Editor/Collider.h>

Collider::Collider(Camera* camera, VoxelHandler* voxelHandler)
{
	m_voxelHandler = voxelHandler;
	m_camera = camera;
}

void Collider::update()
{
	
}

CollisionID Collider::checkForCollisions(Collider::Ray ray)
{
	CollisionID colID;
	colID.collision = false;
	colID.closestVoxel = 0;
	colID.closestWall = 0;
	float closestWallDist = 1000000;

	if (m_voxelHandler->getAllVoxels().size() != 0)
	{
		for (int i = 0; i < m_voxelHandler->getAllVoxels().size(); i++)
		{
			for (int j = 0; j < 6; j++)
			{	
				if (AABBvsRAY(m_voxelHandler->getAllVoxels()[i].getWalls()[j].m_max, m_voxelHandler->getAllVoxels()[i].getWalls()[j].m_min, ray))
				{
					if (glm::distance(m_voxelHandler->getAllVoxels()[i].getWalls()[j].m_center, m_camera->getPosition()) < closestWallDist)
					{
						closestWallDist = glm::distance(m_voxelHandler->getAllVoxels()[i].getWalls()[j].m_center, m_camera->getPosition());
						colID.closestVoxel = i;
						colID.closestWall = j;
						colID.collision = true;
					}
				}
			}
		}
	}
	if (colID.collision)
	{
		m_voxelHandler->getAllDots()[0].setPosition(m_voxelHandler->getAllVoxels()[colID.closestVoxel].getWalls()[colID.closestWall].corner[0]);
		m_voxelHandler->getAllDots()[1].setPosition(m_voxelHandler->getAllVoxels()[colID.closestVoxel].getWalls()[colID.closestWall].corner[1]);
		m_voxelHandler->getAllDots()[2].setPosition(m_voxelHandler->getAllVoxels()[colID.closestVoxel].getWalls()[colID.closestWall].corner[2]);
		m_voxelHandler->getAllDots()[3].setPosition(m_voxelHandler->getAllVoxels()[colID.closestVoxel].getWalls()[colID.closestWall].corner[3]);

	}
	else
	{
		m_voxelHandler->getAllDots()[0].setPosition(glm::vec3(0));
		m_voxelHandler->getAllDots()[1].setPosition(glm::vec3(0));
		m_voxelHandler->getAllDots()[2].setPosition(glm::vec3(0));
		m_voxelHandler->getAllDots()[3].setPosition(glm::vec3(0));
	}

	return colID;
}

Collider::Ray Collider::calculateScreenRay(MouseStatus* mouseStatus, Camera camera)
{
	float x = (2.0f * mouseStatus->m_mousePosition.x) / 800 - 1.0f;
	float y = 1.0f - (2.0f * mouseStatus->m_mousePosition.y) / 600;
	float z = 1.0f;
	glm::vec3 ray_nds = glm::vec3(x, y, z);

	glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);

	glm::vec4 ray_eye = glm::inverse(camera.getProjection()) * ray_clip;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

	glm::vec3 ray_wor = (glm::inverse(camera.getView()) * ray_eye);
	// don't forget to normalise the vector at some point
	ray_wor = glm::normalize(ray_wor);

	//std::cout << ray_wor.x << " --- " << ray_wor.y << " --- " << ray_wor.z << std::endl;

	return Collider::Ray(camera.getPosition(), ray_wor);
}

bool Collider::AABBvsRAY(glm::vec3 boxMax, glm::vec3 boxMin, Collider::Ray ray)
{
	glm::vec3 dirfrac;
	// r.dir is unit direction vector of ray
	dirfrac.x = 1.0f / ray.m_direction.x;
	dirfrac.y = 1.0f / ray.m_direction.y;
	dirfrac.z = 1.0f / ray.m_direction.z;
	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	float t1 = (boxMin.x - ray.m_origin.x) * dirfrac.x;
	float t2 = (boxMax.x - ray.m_origin.x) * dirfrac.x;
	float t3 = (boxMin.y - ray.m_origin.y) * dirfrac.y;
	float t4 = (boxMax.y - ray.m_origin.y) * dirfrac.y;
	float t5 = (boxMin.z - ray.m_origin.z) * dirfrac.z;
	float t6 = (boxMax.z - ray.m_origin.z) * dirfrac.z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		//t = tmax;
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		//t = tmax;
		return false;
	}

	//t = tmin;
	return true;

}

float Collider::max(float a, float b)
{
	if (a > b)
		return a;
	else
		return b;
}

float Collider::min(float a, float b)
{
	if (a < b)
		return a;
	else
		return b;
}

Collider::Ray::Ray(glm::vec3 origin, glm::vec3 direction)
{
	m_origin = origin;
	m_direction = direction;
}

CollisionID::CollisionID()
{
	collision = false;
	closestVoxel = 0;
	closestWall = 0;
}

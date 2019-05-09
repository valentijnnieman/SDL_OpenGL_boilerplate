#include "Rigidbody.hpp"
#include "../Engine.hpp"
//#include <string>

Rigidbody::Rigidbody(float mass, glm::vec3 position, btCollisionShape *col)
{
	if (col != nullptr)
	{
		collider = col;
	}
	// Get shape from model's meshes
	//else
	//{
	//	btTriangleMesh* trimesh = new btTriangleMesh();

	//	for(std::map<std::string, Mesh>::iterator it = parent->getMeshes()->begin(); it != parent->getMeshes()->end(); ++it ) {
	//		std::vector<Vertex> verts = *it->second.getVertices();
	//		for (int i = 0; i < verts.size(); i++)
	//		{
	//			//vertices.push_back(verts[i]);
	//			int index0 = parent->getIndices()[i * 3];
	//			int index1 = data.getIndices()[i * 3 + 1];
	//			int index2 = data.getIndices()[i * 3 + 2];
	//			trimesh->addTriangle(btVector3(verts[i].Position.x, verts[i].Position.y, verts[i].Position.z), );
	//		}
	//	}
	//	collider = btConvexHullShape(vertices, );
	//}

	btTransform trans;
	trans.setIdentity();

	btScalar btMass = mass;
	btVector3 localInertia(0, 0, 0);
	collider->calculateLocalInertia(mass, localInertia);

	trans.setOrigin(btVector3(position.x, position.y, position.z));

	btDefaultMotionState *motionstate = new btDefaultMotionState(trans);

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
		btMass,
		motionstate,
		collider,	// collision shape of body
		localInertia // local inertia
	);
	rigidBodyCI.m_restitution = 1.0f;
	rigidBodyCI.m_friction = 1.0f;
	rigidBodyCI.m_rollingFriction = 1.0f;
	rigidbody = new btRigidBody(rigidBodyCI);
	rigidbody->setWorldTransform(trans);

	Engine::getWorld()->addRigidBody(rigidbody);
}

Rigidbody::~Rigidbody()
{
	//delete collider;
	//delete rigidbody->getMotionState();
	//delete rigidbody;
}

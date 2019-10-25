#pragma once
#include <iostream>
#include "Bullet/LinearMath/btIDebugDraw.h"
#include "Material.hpp"

namespace Bodhisattva {
	class Debug
	{
	public:
		template<class message>
		static void Log(message msg) { std::cout << msg << std::endl; }
		static void Log(glm::vec3 vector) {
			std::cout << "[";
			for (int i = 0; i < vector.length(); i++) {
				std::cout << vector[i] << " | ";
			}
			std::cout << "]";
			std::cout << std::endl;
		}
	};

#ifndef GL_DEBUG_DRAWER_H
#define GL_DEBUG_DRAWER_H
	class GLDebugDrawer : public btIDebugDraw
	{
	private:
		int m_debugMode;
		Material* material;
		unsigned int VBO, EBO, VAO;

	public:

		GLDebugDrawer();
		virtual ~GLDebugDrawer(); 

		virtual void	drawLine(const btVector3& from,const btVector3& to,const btVector3& fromColor, const btVector3& toColor);

		virtual void	drawLine(const btVector3& from,const btVector3& to,const btVector3& color);

		virtual void	drawSphere (const btVector3& p, btScalar radius, const btVector3& color);

		virtual void	drawTriangle(const btVector3& a,const btVector3& b,const btVector3& c,const btVector3& color,btScalar alpha);
		
		virtual void	drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);

		virtual void	reportErrorWarning(const char* warningString);

		virtual void	draw3dText(const btVector3& location,const char* textString);

		virtual void	setDebugMode(int debugMode);

		virtual int		getDebugMode() const { return m_debugMode;}

	};
#endif
}
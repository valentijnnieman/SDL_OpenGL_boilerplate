#include "Debug.hpp"
#include <stdio.h> //printf debugging
#include "Engine.hpp"
#include "Bullet/btBulletDynamicsCommon.h"
#include <glm/glm.hpp>
#include "glad/glad.h"

namespace Bodhisattva {
	GLDebugDrawer::GLDebugDrawer()
		:m_debugMode(0)
	{
	}

	GLDebugDrawer::~GLDebugDrawer()
	{
		material = nullptr;
		delete material;

		glDeleteBuffers(VBO, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}

	void GLDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
	{
			if (material != nullptr)
			{
				material->setAttrib();

				// Calculate model
				glm::mat4 model = glm::mat4(1.0f);
				glm::mat4 transformMatrix = glm::mat4(1.0f);
				glm::mat4 rotationMatrix = glm::mat4(1.0f);
				glm::mat4 scaleMatrix = glm::mat4(1.0f);

				std::vector<Vertex> vertices;

				// FROM AND TO -> VERTICES
				Vertex fromVertex;
				glm::vec3 fromVector;
				fromVector.x = from.getX();
				fromVector.y = from.getY();
				fromVector.z = from.getZ();
				fromVertex.Position = fromVector;
				vertices.push_back(fromVertex);

				Vertex toVertex;
				glm::vec3 toVector;
				toVector.x = to.getX();
				toVector.y = to.getY();
				toVector.z = to.getZ();
				toVertex.Position = toVector;
				vertices.push_back(toVertex);

				//transformMatrix = glm::translate(transformMatrix, glm::vec3(from.getX(), from.getY(), from.getZ()));

				//model = transformMatrix * model;

				glUniformMatrix4fv(glGetUniformLocation(material->shaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));

				Camera* cam = Engine::getCurrentCamera();

				// Set the view of the vertex data
				glm::mat4 view = glm::lookAt(
					cam->position,
					cam->position + cam->front,
					cam->up
				);

				glUniformMatrix4fv(glGetUniformLocation(material->shaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));

				// Set projection of the vertex data
				glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1F, 1000.0f);
				glUniformMatrix4fv(glGetUniformLocation(material->shaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

				// Create space for the vertices
				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

				// Bind Element Buffer Object
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

				// vertex positions
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

				glBindVertexArray(0);

				// draw mesh
				glBindVertexArray(VAO);

				//glDrawElements(GL_LINES, vertices.size() * 2, GL_UNSIGNED_INT, 0);
				glDrawArrays(GL_LINES, 0, vertices.size());
				glBindVertexArray(0);

				// Clear vector of vertices 
				std::vector<Vertex>().swap(vertices);
			}
			else {
				material = new Material(glm::vec3(0.0, 0.5, 0.4), glm::vec3(0.1, 1.0, 0.0), "shaders/vert.glsl", "shaders/color-frag.glsl");

				// Generate 1 Vertex Buffer Object, 1 Element Buffer Object, and 1 Vertex Array Object
				glGenBuffers(1, &VBO);
				glGenBuffers(1, &EBO);
				glGenVertexArrays(1, &VAO);

				// Bind newly created objects
				glBindVertexArray(VAO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
			}
	}

	void GLDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		drawLine(from, to, color, color);
	}

	void GLDebugDrawer::drawSphere(const btVector3& p, btScalar radius, const btVector3& color)
	{
		glColor4f(color.getX(), color.getY(), color.getZ(), btScalar(1.0f));
		glPushMatrix();
		glTranslatef(p.getX(), p.getY(), p.getZ());

		int lats = 5;
		int longs = 5;

		int i, j;
		for (i = 0; i <= lats; i++) {
			btScalar lat0 = SIMD_PI * (-btScalar(0.5) + (btScalar)(i - 1) / lats);
			btScalar z0 = radius * sin(lat0);
			btScalar zr0 = radius * cos(lat0);

			btScalar lat1 = SIMD_PI * (-btScalar(0.5) + (btScalar)i / lats);
			btScalar z1 = radius * sin(lat1);
			btScalar zr1 = radius * cos(lat1);

			glBegin(GL_QUAD_STRIP);
			for (j = 0; j <= longs; j++) {
				btScalar lng = 2 * SIMD_PI * (btScalar)(j - 1) / longs;
				btScalar x = cos(lng);
				btScalar y = sin(lng);

				glNormal3f(x * zr0, y * zr0, z0);
				glVertex3f(x * zr0, y * zr0, z0);
				glNormal3f(x * zr1, y * zr1, z1);
				glVertex3f(x * zr1, y * zr1, z1);
			}
			glEnd();
		}

		glPopMatrix();
	}



	void GLDebugDrawer::drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha)
	{
		//	if (m_debugMode > 0)
		//{
			const btVector3	n = btCross(b - a, c - a).normalized();
			glBegin(GL_TRIANGLES);
			glColor4f(color.getX(), color.getY(), color.getZ(), alpha);
			glNormal3d(n.getX(), n.getY(), n.getZ());
			glVertex3d(a.getX(), a.getY(), a.getZ());
			glVertex3d(b.getX(), b.getY(), b.getZ());
			glVertex3d(c.getX(), c.getY(), c.getZ());
			glEnd();
		//}
	}

	void GLDebugDrawer::setDebugMode(int debugMode)
	{
		m_debugMode = debugMode;
	}

	void	GLDebugDrawer::draw3dText(const btVector3& location, const char* textString)
	{
		glRasterPos3f(location.x(), location.y(), location.z());
		//BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),textString);
	}

	void GLDebugDrawer::reportErrorWarning(const char* warningString)
	{
		printf("%s\n", warningString);
	}

	void GLDebugDrawer::drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
	{

		{
			btVector3 to = pointOnB + normalOnB * 1;//distance;
			const btVector3&from = pointOnB;
			glColor4f(color.getX(), color.getY(), color.getZ(), 1.f);
			//glColor4f(0,0,0,1.f);
			glBegin(GL_LINES);
			glVertex3d(from.getX(), from.getY(), from.getZ());
			glVertex3d(to.getX(), to.getY(), to.getZ());
			glEnd();


			//		glRasterPos3f(from.x(),  from.y(),  from.z());
			//		char buf[12];
			//		sprintf(buf," %d",lifeTime);
					//BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);


		}
	}
}
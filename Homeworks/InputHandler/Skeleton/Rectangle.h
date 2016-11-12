#pragma once

#include <GL/glew.h>		// must be downloaded 
#include "vectormath.h"
#include "Shader.h"

namespace GameObject {
	class Rectangle{
	public:
		Rectangle ()
			: pos (0, 0, 0)
		{
		}
		void setShader (Shader * shader) { this->shader = shader; }
		void loadToGpu ()
		{
			GLfloat vertices[] = {
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				-0.5f,  0.5f, 0.0f,
				0.5f,  0.5f, 0.0f,
			};


			glGenBuffers(1, &vertexBufferObject);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		}

		void Draw ()
		{
			RenderState state;
			state.M = Translate (pos.x, pos.y, pos.z);
			shader->Bind (state);
			// 1rst attribute buffer : vertices
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);
			// Draw the triangle !
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Starting from vertex 0; 3 vertices total -> 1 triangle
			glDisableVertexAttribArray(0);
		}

		void posAdd (float x, float y)
		{
			pos.x += x;
			pos.y += y;
		}
	private:
		Shader * shader;
		GLuint vertexBufferObject;
		vec3 pos;
		vec3 MaxAcceleration;
		vec3 MaxVelocity;

		vec3 acceleration;
		vec3 velocity;
	};
} //NS GameObject
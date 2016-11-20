#pragma once

#include <GL/glew.h>		// must be downloaded 
#include "vectormath.h"
#include "Shader.h"
#include "Input/InputMapper.h"

namespace GameObject {
	class Gameobject {
	public:
		virtual void update (float dx) = 0;
	};

	class Rectangle : Gameobject{
	public:
		Rectangle ()
			: pos (0, 0, 0), sprint (false)
		{
		}
		void setShader (Shader * shader) { this->shader = shader; }
		void update (float dx)
		{
			if (sprint)
				pos = pos + velocity * dx * 3;
			else
				pos = pos + velocity * dx;
		}
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
			state.M = Scale (0.06f, 0.06f, 0.06f) * Translate (pos.x, pos.y, pos.z);
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
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Starting from vertex 0; 4 vertices total -> 2 triangle
			glDisableVertexAttribArray(0);
		}

		void HandleInput (InputMapping::MappedInput& input)
		{
			float MoveX = static_cast<float> (input.Ranges[InputMapping::Range::MoveX]);
			float MoveY = static_cast<float> (input.Ranges[InputMapping::Range::MoveY]);
			velocity = vec3 (MoveX, MoveY, 0) * 0.1f;

			if (input.Action.find (InputMapping::Action::Teleport) != input.Action.end ())
				pos = pos + velocity * 4; //TODO teleport

			sprint = input.State.find (InputMapping::State::Sprint) != input.State.end ();

			///TODO Refresh acceleration
		}
	private:
		Shader * shader;
		GLuint vertexBufferObject;
		bool sprint;
		vec3 pos;
		vec3 MaxAcceleration;
		vec3 MaxVelocity;

		vec3 acceleration;
		vec3 velocity;
	};
} //NS GameObject
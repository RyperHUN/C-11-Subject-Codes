#pragma once

#include <GL/glew.h>		// must be downloaded 
#include "ErrorHandler.h"
#include "RenderState.h"

#include <cstdio>
#include <string>
#include <fstream>

class Shader
{
public:
	unsigned int shaderProgram;
	///TODO megirni altalanosabban
	int getUniform(const char* uniformName)
	{
		int location = glGetUniformLocation(shaderProgram, uniformName);
		if (location < 0)
		{
			printf("uniform %s cannot be set\n", uniformName);
			throw "hibas lekeres"; // Ezt esetleg kivenni
		}
		return location;
	}
	///TODO Arguments Shader name
	void createShader()
	{
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		if (!vertexShader) {
			printf("Error in vertex shader creation\n");
		}
		std::string vertexShaderCode = Shader::loadShader ("SimpleVertexShader.glsl");
		char const * vertexShaderCodePtr = vertexShaderCode.c_str();
		glShaderSource(vertexShader, 1, &vertexShaderCodePtr, NULL);
		glCompileShader(vertexShader);
		checkShader(vertexShader, "Vertex shader error");

		// Create fragment shader from string
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		if (!fragmentShader) {
			printf("Error in fragment shader creation\n");
			exit(1);
		}
		std::string fragmentShaderCode = Shader::loadShader("SimpleFragmentShader.glsl");
		char const * fragmentShaderCodePtr = fragmentShaderCode.c_str();
		glShaderSource(fragmentShader, 1, &fragmentShaderCodePtr, NULL);
		glCompileShader(fragmentShader);
		checkShader(fragmentShader, "Fragment shader error");

		// Attach shaders to a single program
		shaderProgram = glCreateProgram();
		if (!shaderProgram) {
			printf("Error in shader program creation\n");
			exit(1);
		}
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);

		///TODO ez valszeg nemkell
		//bindAttributes();

		// program packaging
		glLinkProgram(shaderProgram);
		checkLinking(shaderProgram);
		// make this program run
		glUseProgram(shaderProgram);

		//Toroljuk a shadereket - Mar hozzaadtuk a programhoz szoval mar nem kell
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	///TODO
	virtual void Bind(RenderState& state) {
		///TODO
		glUseProgram(shaderProgram);
		mat4 MVP = state.M;
		MVP.SetUniform(shaderProgram, "MVP");
	}
	//void Bind(RenderState& state) {
	//	//====================== VERTEX SHADER TOLTES ================================//
	//	glUseProgram(shaderProgram);
	//	mat4 MVP = state.M * state.V * state.P;
	//	MVP.SetUniform(shaderProgram, "MVP");
	//	state.Minv.SetUniform(shaderProgram, "Minv");
	//	state.M.SetUniform(shaderProgram, "M");

	//	//Feny
	//	Light* light = state.light1;
	//	location = getUniform("wLiPos");
	//	glUniform4f(location, light->wLightPos.v[0], light->wLightPos.v[1], light->wLightPos.v[2], light->wLightPos.v[3]);
	//	location = getUniform("La");
	//	glUniform3f(location, light->La.x, light->La.y, light->La.z);
	//	location = getUniform("Le");

	//	location = getUniform("shine");
	//	glUniform1f(location, state.material->shininess);
	//	//====================== FRAGMENT SHADER KESZ ================================//
	//	//Csak texturazo
	//	int samplerUnit = GL_TEXTURE0;
	//	location = getUniform("samplerUnit");
	//	glUniform1i(location, samplerUnit);

	//	glActiveTexture(samplerUnit);
	//	if (state.texture != nullptr)
	//		glBindTexture(GL_TEXTURE_2D, state.texture->textureId);
	//}
private:
	static std::string loadShader(std::string fileName)
	{
		std::string shaderCode;
		std::ifstream VertexShaderStream(fileName, std::ios::in);
		if (VertexShaderStream.is_open()) {
			std::string Line = "";
			while (getline(VertexShaderStream, Line))
				shaderCode += "\n" + Line;
			VertexShaderStream.close();
		}
		else {
			printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", fileName);
			getchar();
			return 0;
		}
		return shaderCode;
	}
};

//class ShaderTextureLoaded : public Shader
//{
//	
//	vec3 color;
//public:
//
//	//unsigned int programID;
//
//	//unsigned int vertexShaderID;  // Esetleg ezeket is eltárolni
//	//unsigned int fragmentShaderID;
//	// vertex shader in GLSL
//	ShaderTextureLoaded()
//	{
//	}
//
//	
//	//void bindAttributes()
//	//{
//	//	// Connect Attrib Arrays to input variables of the vertex shader
//	//	glBindAttribLocation(shaderProgram, 0, "vtxPos"); // vertexPosition gets values from Attrib Array 0
//	//	glBindAttribLocation(shaderProgram, 1, "vtxNormal"); // vertexPosition gets values from Attrib Array 0
//	//	glBindAttribLocation(shaderProgram, 2, "uv"); // vertexPosition gets values from Attrib Array 0
//	//	glBindFragDataLocation(shaderProgram, 0, "fragmentColor");	// fragmentColor goes to the frame buffer memory
//	//}
//	
//};
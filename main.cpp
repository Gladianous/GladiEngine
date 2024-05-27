#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//Vertex Shader Source
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader Source
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.8f, 0.8f, 1.0f);\n"
" }\n";

//Fragment Shader Source
const char* fragmentShaderSourceTip = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.6f, 0.8f, 1.0f);\n"
" }\n";


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//----------
	//Shaders
	//----------
	//Vertex Shader
	unsigned int vertexShader; //vertexShader handle.
	vertexShader = glCreateShader(GL_VERTEX_SHADER); //Create the shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Define the source code for the shader (the string const we have at the top of the file)
	glCompileShader(vertexShader); //Runtime compile the shader
		//(Error Catching the Runtime Compilation)
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	//Fragment Shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
		//(Error Catching the Runtime Compilation)
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	//Fragment Shader
	unsigned int fragmentShaderTip;
	fragmentShaderTip = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderTip, 1, &fragmentShaderSourceTip, NULL);
	glCompileShader(fragmentShaderTip);
	//(Error Catching the Runtime Compilation)
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Shader Program and Linking
		//Create Shader Program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram(); //Create Shader Program and pass the Ref ID to the unsigned int.
		//Link Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
		//(Error Catching the Runtime Compilation)
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Create Shader Program
	unsigned int shaderProgramTip;
	shaderProgramTip = glCreateProgram(); //Create Shader Program and pass the Ref ID to the unsigned int.
	//Link Shader Program
	glAttachShader(shaderProgramTip, vertexShader);
	glAttachShader(shaderProgramTip, fragmentShaderTip);
	glLinkProgram(shaderProgramTip);
	//(Error Catching the Runtime Compilation)
	glGetProgramiv(shaderProgramTip, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramTip, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	//----------
	//Vertex and Buffers
	//----------
	float vertices[] = {
	-0.1f,  0.0f, 0.0f,  // left ball top right
	-0.1f, -0.2f, 0.0f,  // left ball bottom right
	-0.3f, -0.2f, 0.0f,  // left ball bottom left
	-0.3f,  0.0f, 0.0f,  // left ball top left 
	 0.3f,  0.0f, 0.0f,  // right ball top right
	 0.3f, -0.2f, 0.0f,  // right ball bottom right
	 0.1f, -0.2f, 0.0f,  // right ball bottom left
	 0.1f,  0.0f, 0.0f,  // right ball top left
	 0.1f,  0.4f, 0.0f,  // shaft top right
	 0.1f,  0.0f, 0.0f,  // shaft bottom right
	-0.1f,  0.0f, 0.0f,  // shaft bottom left
	-0.1f,  0.4f, 0.0f   // shaft top left
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3,    // second triangle
		4, 5, 7,   // first triangle
		5, 6, 7,    // second triangle
		8, 9, 11,   // first triangle
		9, 10, 11    // second triangle
	};
	float verticesTip[] = {
	 0.1f,  0.6f, 0.0f,  // tip top right
	 0.1f,  0.4f, 0.0f,  // tip bottom right
	-0.1f,  0.4f, 0.0f,  // tip bottom left
	-0.1f,  0.6f, 0.0f,  // tip top left 
	};
	unsigned int indicesTip[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3,    // second triangle
	};
	


	unsigned int lbVBO, lbVAO, lbEBO, tVBO, tVAO, tEBO;
	
	glGenBuffers(1, &lbVBO);
	glGenVertexArrays(1, &lbVAO);
	glGenBuffers(1, &lbEBO);
	glBindBuffer(GL_ARRAY_BUFFER, lbVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	
	
	glBindVertexArray(lbVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lbVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lbEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &tVBO);
	glGenVertexArrays(1, &tVAO);
	glGenBuffers(1, &tEBO);
	glBindVertexArray(tVAO);
	glBindBuffer(GL_ARRAY_BUFFER, tVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTip), verticesTip, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesTip), indicesTip, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glViewport(0,0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  //Sets the "clear color"
		glClear(GL_COLOR_BUFFER_BIT);  //Clears the Window by setting it all to the "clear color"
		
		glUseProgram(shaderProgram);
		glBindVertexArray(lbVAO);
		glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glUseProgram(shaderProgramTip);
		glBindVertexArray(tVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


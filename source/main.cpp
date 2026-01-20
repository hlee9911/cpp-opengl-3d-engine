#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

struct Vec2
{
	float x = 0.0f;
	float y = 0.0f;
};

Vec2 offset;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_UP:
				offset.y += 0.01f;
				break;
			case GLFW_KEY_DOWN:
				offset.y -= 0.01f;
				break;
			case GLFW_KEY_LEFT:
				offset.x -= 0.01f;
				break;
			case GLFW_KEY_RIGHT:
				offset.x += 0.01f;
				break;
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, true);
				break;
			default:
				break;
		}
	}
}

int main(int argc, char* argv[])
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
    }
    
	// Set GLFW window hints for OpenGL version and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "GameDevelopmentEngine", nullptr, nullptr);

    if (window == nullptr)
    {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
    }

	glfwSetKeyCallback(window, keyCallback);

    glfwSetWindowPos(window, 640, 360);
	glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
        return -1;
    }

	////////////// Vertex Shader //////////////

    std::string vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 position;
		layout(location = 1) in vec3 color;

		uniform vec2 uOffset;

		out vec3 vColor;

        void main()
        {
			vColor = color;
            gl_Position = vec4(position.x + uOffset.x, position.y + uOffset.y, position.z, 1.0);
        }
    )";

	// create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// convert std::string to const char*
	const char* vertexShaderCStr = vertexShaderSource.c_str();
	// tell OpenGL about the shader source code
    glShaderSource(vertexShader, 1, &vertexShaderCStr, nullptr);
	// compile the shader
	glCompileShader(vertexShader);


	// check for compilation errors
	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::VERTEX_SHADER_COMPILATION_FAILED: \n" << infoLog << std::endl;
    }

    //////////////////////////////////////////////


	////////////// Fragment Shader //////////////

    std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

		in vec3 vColor;
		uniform vec4 uColor;
        
        void main()
        {
            FragColor = vec4(vColor, 1.0) * uColor;
        }
    )";

	// create fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// convert std::string to const char*
	const char* fragmentShaderCStr = fragmentShaderSource.c_str();
	// tell OpenGL about the shader source code
	glShaderSource(fragmentShader, 1, &fragmentShaderCStr, nullptr);
	// compile the shader
	glCompileShader(fragmentShader);

	// check for compilation errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::FRAGMENT_SHADER_COMPILATION_FAILED: \n" << infoLog << std::endl;
    }

	//////////////////////////////////////////////

	///////////// Shader Program //////////////

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER_PROGRAM_LINKING_FAILED: \n" << infoLog << std::endl;
    }

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

    std::vector<float> vertices =
    {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f
    };

	std::vector<unsigned int> indicies =
	{
		0, 1, 2,
		0, 2, 3
	};

	/////////////////////////////////////////////

	// Create Vertex Buffer Object (VBO)
	GLuint vbo;
	glGenBuffers(1, &vbo);
	// Bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// now convert the buffer data from cpu to gpu
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	// unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create Element Buffer Object (EBO)
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), indicies.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Create Vertex Array Object (VAO)
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// bind the EBO to the VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	// specify the layout of the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// set uniform locations
	GLint uColorLoc = glGetUniformLocation(shaderProgram, "uColor");
	GLint uOffsetLoc = glGetUniformLocation(shaderProgram, "uOffset");
	
    while (!glfwWindowShouldClose(window))
    {
        // Cleara frame buffer
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // green background
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glUniform4f(uColorLoc, 0.0f, 1.0f, 0.0f, 1.0f); // set uniform color to green
		glUniform2f(uOffsetLoc, offset.x, offset.y);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
    }

	glfwTerminate();

    return 0;
}

// double buffering
// double buffering is a technique used in computer graphics to minimize 
// flickering and provide smooth rendering of images on the screen. 
// It involves the use of two buffers: a front buffer and a back buffer. 
// The front buffer is the one currently being displayed on the screen, 
// while the back buffer is used for drawing the next frame. 
// Once the drawing in the back buffer is complete, the two buffers are swapped, 
// making the back buffer the new front buffer and vice versa. 
// This way, the user sees a complete frame without any partial updates, 
// resulting in a smoother visual experience.

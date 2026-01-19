#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

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

	GLFWwindow* window = glfwCreateWindow(1280, 720, "GameDevelopmentProject", nullptr, nullptr);

    if (window == nullptr)
    {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
    }

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
        void main()
        {
            gl_Position = vec4(position.x, position.y, position.z, 1.0);
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
        
        void main()
        {
            FragColor = vec4(1.0, 0.0, 0.0, 1.0);
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
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    while (!glfwWindowShouldClose(window))
    {
        // Cleara frame buffer
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // green background
		glClear(GL_COLOR_BUFFER_BIT);

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

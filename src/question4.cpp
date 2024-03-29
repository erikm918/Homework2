#include "headers/question1-2-3-4.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int Question4() {
    if ( !glfwInit() ) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1000, 1000, "Question 4 Graph", NULL, NULL);
    if ( !window ) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent( window );
    if ( glewInit() != GLEW_OK ) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    while ( !glfwWindowShouldClose( window ) ) {
        glClear( GL_COLOR_BUFFER_BIT );
        glBegin( GL_LINES );
        // Draw X and Y axis
        glColor3f( 1.0, 1.0, 1.0 );
        glVertex2f( -1.0, 0.0 );
        glVertex2f( 1.0, 0.0 );
        glVertex2f( 0.0, 1.0 );
        glVertex2f( 0.0, -1.0 );
        glEnd();


        
        glColor3f(0.0f, 1.0f, 0.75f);
        
        // Pseudo launch path. Imitates the trajectory of a rocket leaving Earth
        glBegin(GL_LINES);
        for (float i = 0; i < 100; i += 0.00001) {
            float theta = 2.0f * 3.1415926f * i / float(100);

            float x = (theta/7.5) * cosf(theta);
            float y = (theta/7.5) * sinf(theta);

            glVertex2f(x, y);
        }
        glEnd();

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
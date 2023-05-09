#include <iostream>
#include <GLFW/glfw3.h>
#include <math.h>

/*void display(GLFWwindow* window, double currentTime) {
    glClearColor(1.8, 1.2, 0.5, 0.2);//fakó-sárga
    //glClearColor(1.0, 1.0, 0.0, 0.0);//sárga
    //glClearColor(1.0, 0.0, 0.0, 1.0);//piros
    glClear(GL_COLOR_BUFFER_BIT);
}*/

//to-do -


const int WS = 600; //Ablak mérete


//KÖR
const float RADIUS = (2.0f / float(WS)) * 50.0f;
const float MOV_SPEED = 0.045f;
const int STEPS = 350;
const float ANGLE = 2.f * 3.14 / STEPS;

//VONAL(KÉK)
const float vonal_x = 1.f / 3.f;
float vonal_y = 0.f;



//mozgások
float kor_x = 0.0f;
float kor_y = 0.0f;
float mozog = MOV_SPEED;

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    window = glfwCreateWindow(WS, WS, "Ablak sarga haterrel", 0, 0);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glMatrixMode(GL_PROJECTION);

    while (!glfwWindowShouldClose(window)) {
        GLfloat line[] = { -vonal_x, vonal_y, 0.f, vonal_x, vonal_y, 0.f };

        glClearColor(1.8, 1.2, 0.5, 0.2);//fakó-sárga, also known as banán sárga;
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSetWindowSizeLimits(window, WS, WS, WS, WS);

        kor_x += mozog;
        if ((kor_x > 1-RADIUS) || (kor_x < -(1-RADIUS))) 
            mozog = -mozog;

        float prev_x = kor_x;
        float prev_y = kor_y - RADIUS;

        for (int i = 0; i <= STEPS; ++i) {
            float next_x = RADIUS * sin(ANGLE * i) + kor_x;
            float next_y = -RADIUS * cos(ANGLE * i);

            glBegin(GL_TRIANGLES);
            glColor4f(1.0, 0.25, 0.35, 1.0);
            glVertex3f(kor_x, 0.0, 0.0);
            glColor4f(0.2, 1.3, 0.45, 1.0);
            glVertex3f(prev_x, prev_y, 0.0);
            glColor4f(0.0, 1.2, 0.30, 1.2);
            glVertex3f(next_x, next_y, 0.0);
            glEnd();

            prev_x = next_x;
            prev_y = next_y;
        }

        glEnable(GL_LINE_SMOOTH);
        glLineWidth(3.0); //Vastagásg fix 3
        glColor4f(0.31, 0.10, 1.0, 0.31); //Esküszöm, hogy nem lila
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, line);
        glDrawArrays(GL_LINES, 0, 2); //vonal kirajzolása
        glDisableClientState(GL_VERTEX_ARRAY);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}


/*int main(void) {

	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Ablak sarga haterrel);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	init(window);

	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);*/
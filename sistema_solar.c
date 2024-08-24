#include <GL/glut.h>
#include <SOIL/SOIL.h> // Biblioteca para carregar texturas

GLuint textureSun;
GLuint texturePlanet;

void loadTexture(const char* filename, GLuint* textureID) {
    int width, height;
    unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
    glGenTextures(1, textureID);
    glBindTexture(GL_TEXTURE_2D, *textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SOIL_free_image_data(image);
}

void drawSphere(float radius, GLuint textureID) {
    glBindTexture(GL_TEXTURE_2D, textureID);
    glutWireSphere(radius, 20, 20); // Use glutSolidSphere se preferir uma esfera sólida
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Configuração da câmera
    gluLookAt(0.0, 0.0, 5.0,   0.0, 0.0, 0.0,   0.0, 1.0, 0.0);

    // Desenha o Sol
    glPushMatrix();
    glTranslatef(0.0, 0.0, -2.0);
    drawSphere(1.0, textureSun);
    glPopMatrix();

    // Desenha o Planeta
    glPushMatrix();
    glTranslatef(2.0, 0.0, -3.0);
    drawSphere(0.5, texturePlanet);
    glPopMatrix();

    glutSwapBuffers();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    loadTexture("sol.jpg", &textureSun);
    loadTexture("terra.jpg", &texturePlanet);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sun and Planet");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

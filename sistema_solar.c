#include <GL/glut.h>
#include <SOIL/SOIL.h>

// Tamanhos dos planetas e Sol
float planetSizes[] = {0.383, 0.949, 1.0, 0.532, 11.21, 9.45, 4.01, 3.88, 0.186};
float planetDistances[] = {5.8, 10.8, 15.0, 22.8, 77.8, 143.0, 287.0, 450.0, 590.0};
GLuint textures[10];

void loadTextures() {
    const char* filenames[] = {
        "sun.jpg", "mercury.jpg", "venus.jpg", "earth.jpg", 
        "mars.jpg", "jupiter.jpg", "saturn.jpg", "uranus.jpg", 
        "neptune.jpg", "pluto.jpg"
    };
    
    glGenTextures(10, textures);

    for (int i = 0; i < 10; i++) {
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        int width, height;
        unsigned char* image = SOIL_load_image(filenames[i], &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}

void drawSphere(float size, GLuint texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluSphere(quad, size, 50, 50);
    gluDeleteQuadric(quad);
    glDisable(GL_TEXTURE_2D);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 1000.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Desenha o Sol no centro
    drawSphere(5.0, textures[0]);

    // Desenha os planetas
    for (int i = 0; i < 9; i++) {
        glPushMatrix();
        glTranslatef(planetDistances[i], 0.0, 0.0);
        drawSphere(planetSizes[i], textures[i + 1]);
        glPopMatrix();
    }

    glutSwapBuffers();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    loadTextures();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Solar System");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

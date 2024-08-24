#include <GL/glut.h>
#include <GL/glu.h>
#include <SOIL/SOIL.h>

GLuint texture;

void loadTexture() {
    texture = SOIL_load_OGL_texture(
        "sol.jpg",  // caminho para a imagem da textura
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (!texture) {
        printf("Erro ao carregar a textura: '%s'\n", SOIL_last_result());
        exit(1);
    }

    glBindTexture(GL_TEXTURE_2D, texture);

    // Configurações de textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void init() {
    glEnable(GL_TEXTURE_2D);    // Ativar texturas
    loadTexture();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Posicionar a esfera
    glTranslatef(0.0f, 0.0f, -5.0f);

    glBindTexture(GL_TEXTURE_2D, texture);

    // Criar a esfera e aplicar a textura
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluSphere(quad, 1.0, 50, 50);  // raio 1.0, subdivisões 50x50

    gluDeleteQuadric(quad);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Textura do Sol em OpenGL");

    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

#include <GL/glut.h>
#include <SOIL/SOIL.h> // Biblioteca para carregar texturas
#include <math.h>

// Variáveis para controle de rotação
GLfloat angle = 0.0f;

// ID da textura
GLuint texture;

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
    // Carregar a textura do Sol usando SOIL
    texture = SOIL_load_OGL_texture(
        "sol.jpg", 
        SOIL_LOAD_AUTO, 
        SOIL_CREATE_NEW_ID, 
        SOIL_FLAG_INVERT_Y
    );

    if (!texture) {
        printf("Falha ao carregar a textura: %s\n", SOIL_last_result());
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Configuração de iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_pos[] = {0.0f, 0.0f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Definir a câmera
    gluLookAt(0.0f, 0.0f, 5.0f,  // Posição da câmera
              0.0f, 0.0f, 0.0f,  // Para onde a câmera aponta
              0.0f, 1.0f, 0.0f); // Para cima

    glBindTexture(GL_TEXTURE_2D, texture);

    // Rotacionar o Sol
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    // Criar a esfera e aplicar a textura
    GLUquadric* quad;
    quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluSphere(quad, 1.0f, 50, 50);
    gluDeleteQuadric(quad);

    glutSwapBuffers();
}

void timer(int value) {
    angle += 0.2f;  // Controla a velocidade de rotação
    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);  // Aproximadamente 60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sol Girando em OpenGL");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}

//#include <SDL/SDL.h>
//#include "SDL/SDL_opengl.h"
#include <SOIL/SOIL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

// Estruturas
typedef struct {
    int Faces;
    GLuint Texture;
} Astro;

// Variáveis dos Astro(s)
Astro sol;

//---------------------------------------------------- Carregamento de Texturas ------------------------------------------------------------
GLuint carregarTextura(const char* arquivo) {
    GLuint idTextura = SOIL_load_OGL_texture(
                        arquivo,
                        SOIL_LOAD_AUTO,
                        SOIL_CREATE_NEW_ID,
                        SOIL_FLAG_INVERT_Y
                    );

    if (idTextura == 0) {
        printf("Erro do SOIL: '%s' - '%s'\n", arquivo, SOIL_last_result());
    }

    return idTextura;
}

//---------------------------------------------------- Renderização ------------------------------------------------------------
void criaSphere(float radius, int stacks, int columns) {
    GLUquadric* quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    gluQuadricTexture(quadObj, GL_TRUE);
    gluSphere(quadObj, radius, stacks, columns);
    gluDeleteQuadric(quadObj);
}

void renderiza() {
    //Sol
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sol.Texture);
    glPushMatrix();
    criaSphere(100, sol.Faces, sol.Faces);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //...
}

void estadoExecucao() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 500, 0, 0, 0, 0, 1, 0);  // Camera fixa
    renderiza();
    glutSwapBuffers();
}

void configJanela(int w, int h) {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 0.2, 5000.0);
    glMatrixMode(GL_MODELVIEW);
}

void defBase() {
    glClearColor(0, 0, 0, 0.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Sol
    sol.Texture = carregarTextura("sol.jpg");
    sol.Faces = 200;

    //...
}

int main(int argc, char* args[]) {
    //SDL_Init(SDL_INIT_EVERYTHING);
    glutInit(&argc, args);
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // Configs da Janela
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("test texture");

    // funções principais
    glutDisplayFunc(estadoExecucao);
    glutReshapeFunc(configJanela);
    defBase();
    glutMainLoop(); // Loop
    //SDL_Quit(); 

    return 0;
}

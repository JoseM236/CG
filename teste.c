#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include <SOIL/SOIL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

// Estruturas
typedef struct {
    int Faces;
    int TamanhoTranslacao;
    GLuint Texture;
} Astro;

// Variáveis dos Astros
Astro sol;
Astro mercurio;

//---------------------------------------------------- Carregamento de Texturas ------------------------------------------------------------
GLuint carregaTextura(const char* arquivo) {
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

void renderizaSol() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sol.Texture);
    glPushMatrix();
    criaSphere(100, sol.Faces, sol.Faces);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void renderizaCorpos() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mercurio.Texture);
    glPushMatrix();
    glTranslatef(mercurio.TamanhoTranslacao, 0.0, 0);
    criaSphere(0.5, mercurio.Faces, mercurio.Faces);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

//---------------------------------------------------- Estado de Execução ------------------------------------------------------------
void estadoExecucao() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 500, 0, 0, 0, 0, 1, 0);  // Camera fixa
    renderizaSol();
    renderizaCorpos();
    glutSwapBuffers();
}

//---------------------------------------------------- Configurações da Aplicação ------------------------------------------------------------
void confJanela(int w, int h) {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 0.2, 2147483647.0);
    glMatrixMode(GL_MODELVIEW);
}

/* Define estado inicial dos componentes */
void defineBase() {
    glClearColor(0, 0, 0, 0.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // SOL
    sun.Texture = carregaTextura("sol.jpg");
    sun.Faces = 200;

    // MERCÚRIO
    mercurio.Texture = carregaTextura("mercurio.jpg");
    mercurio.TamanhoTranslacao = 150;
    mercurio.Faces = 200;
}

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    glutInit(&argc, args);
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // Configurações da Janela
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1400, 840);
    glutCreateWindow("Solar System");

    // Chama nossas funções principais
    glutDisplayFunc(estadoExecucao);
    glutReshapeFunc(confJanela);
    defineBase(); // Processos Iniciais
    glutMainLoop(); // Loop
    SDL_Quit(); // Encerra o SDL

    return 0;
}

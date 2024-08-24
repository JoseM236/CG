#include <GL/glut.h>
#include <SOIL/SOIL.h>

// IDs das texturas
GLuint texturaSol;
GLuint texturaMercurio;
GLuint texturaVenus;
GLuint texturaTerra;
GLuint texturaMarte;
GLuint texturaJupiter;
GLuint texturaSaturno;
GLuint texturaUrano;
GLuint texturaNetuno;

// Função para carregar a textura a partir de um arquivo
GLuint carregarTextura(const char* arquivo) {
    GLuint id = SOIL_load_OGL_texture(
        arquivo,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
    );
    
    if (id == 0) {
        printf("Erro ao carregar a textura: '%s'\n", arquivo);
    }
    
    return id;
}

// Função para desenhar uma esfera com textura
void desenharEsfera(GLfloat raio, GLuint textura) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textura);
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluSphere(quad, raio, 50, 50);
    gluDeleteQuadric(quad);
    glDisable(GL_TEXTURE_2D);
}

// Função de exibição
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Sol
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f); // Posição do Sol
    desenharEsfera(2.0f, texturaSol); // Tamanho do Sol
    glPopMatrix();
    
    // Mercúrio
    glPushMatrix();
    glTranslatef(4.0f, 0.0f, 0.0f); // Posição de Mercúrio
    desenharEsfera(0.4f, texturaMercurio); // Tamanho de Mercúrio
    glPopMatrix();
    
    // Vênus
    glPushMatrix();
    glTranslatef(7.0f, 0.0f, 0.0f); // Posição de Vênus
    desenharEsfera(0.95f, texturaVenus); // Tamanho de Vênus
    glPopMatrix();
    
    // Terra
    glPushMatrix();
    glTranslatef(10.0f, 0.0f, 0.0f); // Posição da Terra
    desenharEsfera(1.0f, texturaTerra); // Tamanho da Terra
    glPopMatrix();
    
    // Marte
    glPushMatrix();
    glTranslatef(15.0f, 0.0f, 0.0f); // Posição de Marte
    desenharEsfera(0.53f, texturaMarte); // Tamanho de Marte
    glPopMatrix();
    
    // Júpiter
    glPushMatrix();
    glTranslatef(20.0f, 0.0f, 0.0f); // Posição de Júpiter
    desenharEsfera(1.5f, texturaJupiter); // Tamanho de Júpiter
    glPopMatrix();
    
    // Saturno
    glPushMatrix();
    glTranslatef(30.0f, 0.0f, 0.0f); // Posição de Saturno
    desenharEsfera(1.2f, texturaSaturno); // Tamanho de Saturno
    glPopMatrix();
    
    // Urano
    glPushMatrix();
    glTranslatef(40.0f, 0.0f, 0.0f); // Posição de Urano
    desenharEsfera(1.0f, texturaUrano); // Tamanho de Urano
    glPopMatrix();
    
    // Netuno
    glPushMatrix();
    glTranslatef(50.0f, 0.0f, 0.0f); // Posição de Netuno
    desenharEsfera(1.0f, texturaNetuno); // Tamanho de Netuno
    glPopMatrix();

    glutSwapBuffers();
}

// Inicialização das texturas e OpenGL
void init(void) {
    glEnable(GL_DEPTH_TEST);
    
    texturaSol = carregarTextura("sol.jpg");
    texturaMercurio = carregarTextura("mercurio.jpg");
    texturaVenus = carregarTextura("venus.jpg");
    texturaTerra = carregarTextura("terra.jpg");
    texturaMarte = carregarTextura("marte.jpg");
    texturaJupiter = carregarTextura("jupiter.jpg");
    texturaSaturno = carregarTextura("saturno.jpg");
    texturaUrano = carregarTextura("urano.jpg");
    texturaNetuno = carregarTextura("netuno.jpg");
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sistema Solar");
    
    init();
    
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <SOIL/SOIL.h> // Inclua a biblioteca SOIL para carregamento de texturas

GLuint textureSun, texturePlanet;

void loadTexture(const char *filename, GLuint *texture) {
    int width, height, channels;
    unsigned char *data = SOIL_load_image(filename, &width, &height, &channels, SOIL_LOAD_AUTO);
    if (data) {
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SOIL_free_image_data(data);
    } else {
        printf("Failed to load texture: %s\n", filename);
    }
}

void init(void) 
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    
    // Carregue as texturas
    loadTexture("sun.jpg", &textureSun);
    loadTexture("planet.jpg", &texturePlanet);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    // Desenhe o Sol
    glBindTexture(GL_TEXTURE_2D, textureSun);
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glutWireSphere(1.0, 20, 16);   /* Desenhe o Sol */
    glPopMatrix();

    // Desenhe os planetas
    glBindTexture(GL_TEXTURE_2D, texturePlanet);
    glPushMatrix();
    glTranslatef(2.0, 0.0, 0.0);  // Posicione o planeta
    glutWireSphere(0.2, 10, 8);    /* Desenhe um planeta */
    glPopMatrix();
    
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500); 
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

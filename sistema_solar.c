#include <GL/glut.h>
#include <SOIL/SOIL.h>

GLuint sunTexture, mercuryTexture, venusTexture, earthTexture, marsTexture;
GLuint jupiterTexture, saturnTexture, uranusTexture, neptuneTexture;

void loadTextures() {
    sunTexture = SOIL_load_OGL_texture("sol.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    mercuryTexture = SOIL_load_OGL_texture("mercurio.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    venusTexture = SOIL_load_OGL_texture("venus.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    earthTexture = SOIL_load_OGL_texture("terra.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    marsTexture = SOIL_load_OGL_texture("marte.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    jupiterTexture = SOIL_load_OGL_texture("jupiter.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    saturnTexture = SOIL_load_OGL_texture("saturno.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    uranusTexture = SOIL_load_OGL_texture("urano.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    neptuneTexture = SOIL_load_OGL_texture("netuno.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

void drawSphere(GLfloat radius, GLuint texture) {
    glBindTexture(GL_TEXTURE_2D, texture);
    GLUquadric *quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluSphere(quad, radius, 50, 50);
    gluDeleteQuadric(quad);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    // Render Sun
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, sunTexture);
    drawSphere(2.0f, sunTexture);
    glPopMatrix();

    // Render Mercury
    glPushMatrix();
    glTranslatef(3.0f, 0.0f, 0.0f);
    drawSphere(0.5f, mercuryTexture);
    glPopMatrix();

    // Render Venus
    glPushMatrix();
    glTranslatef(5.0f, 0.0f, 0.0f);
    drawSphere(0.6f, venusTexture);
    glPopMatrix();

    // Render Earth
    glPushMatrix();
    glTranslatef(7.0f, 0.0f, 0.0f);
    drawSphere(0.7f, earthTexture);
    glPopMatrix();

    // Render Mars
    glPushMatrix();
    glTranslatef(9.0f, 0.0f, 0.0f);
    drawSphere(0.6f, marsTexture);
    glPopMatrix();

    // Render Jupiter
    glPushMatrix();
    glTranslatef(12.0f, 0.0f, 0.0f);
    drawSphere(1.2f, jupiterTexture);
    glPopMatrix();

    // Render Saturn
    glPushMatrix();
    glTranslatef(15.0f, 0.0f, 0.0f);
    drawSphere(1.0f, saturnTexture);
    glPopMatrix();

    // Render Uranus
    glPushMatrix();
    glTranslatef(18.0f, 0.0f, 0.0f);
    drawSphere(0.8f, uranusTexture);
    glPopMatrix();

    // Render Neptune
    glPushMatrix();
    glTranslatef(21.0f, 0.0f, 0.0f);
    drawSphere(0.8f, neptuneTexture);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    loadTextures();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Solar System Visualization");

    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

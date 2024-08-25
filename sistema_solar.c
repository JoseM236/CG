#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <SOIL/SOIL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <math.h>

//Estruturas
typedef struct{
	float Translacao;
	float Rotacao;
	int Faces;
	int TamanhoTranslacao;
	GLuint Texture;
	bool Estado;
}Corpo;

typedef struct{
	int X;
	int Y;
	int Z;
}EixoINT;

typedef struct{
	float X;
	float Y;
	float Z;
}EixoFLOAT;

typedef struct{
	float Largura;
	float Altura;
}Janela;

//Variaveis dos Corpos
Corpo sun;
Corpo mercury;
Corpo venus;
Corpo earth;
Corpo mars;
Corpo jupiter;
Corpo uranus;
Corpo neptune;
Corpo saturn;
Corpo space;

//Variaveis de Luz
float difusa;
float especular;
float posicional;
float global;
float matrizAD[] = {1.0, 1.0, 1.0, 1.0};
float matrizEspecular[] = {1.0, 1.0, 1,0, 1.0};
float matrizBrilho[] = {50};
EixoFLOAT luzBranca;

 
//Variaveis de Controle
int horizonteEventos = 1;//Espaço Visivel
EixoINT cursor;
EixoINT mouse;
Janela janela;
bool podeBrilhar = true;
bool podeOrbitar = false;

//Variaveis da Camera
int modoCamera = 1;
float anguloCameraA = 90;
float anguloCameraB = 0;
EixoFLOAT camera;

//Variaveis de Musica
Mix_Chunk *startingOdyssey;

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
void criaSphere(float radius, int stacks, int columns){
    GLUquadric* quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    gluQuadricTexture(quadObj, GL_TRUE);
    gluSphere(quadObj, radius, stacks, columns);
    gluDeleteQuadric(quadObj);
}
void renderizaAstroRei(){
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, sun.Texture);
    	glPushMatrix();
	        glRotatef(sun.Translacao, 0, 1, 0);
	        glRotatef(90, 1, 0, 0);
	        criaSphere(100 , sun.Faces, sun.Faces);
   		 glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void renderizaCorpos(){
	glEnable(GL_TEXTURE_2D);
		//Mercurio
		glBindTexture(GL_TEXTURE_2D, mercury.Texture);
		glPushMatrix();
	        glRotatef(mercury.Translacao, 0, 1, 0);
	        glTranslatef(mercury.TamanhoTranslacao, 0.0, 0);
	        glRotatef(mercury.Rotacao, 0, 1, 0);
	        glRotatef(97, 1, 0, 0); 
	        criaSphere(0.5 * horizonteEventos, mercury.Faces, mercury.Faces);
	    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void queHajaLuz(){
	if(podeBrilhar){
		float luzAmbiente[] = {0.0, 0.0, 0.0, 1.0};
	    float luzDifusa0[] = {difusa, difusa, difusa, 1.0};
	    float luzEpecular0[] = {especular, especular, especular, 1.0};
	    float luzPosicional0[] = {0.0, 0.0, 3.0, posicional};
	    float luzDE[] = {0.0, 1.0, 0.0, 1.0};
	    float luzPosicional1[] = {1.0, 2.0, 0.0, 1.0};
	    float luzGlobal[] = {global, global, global, 1.0};

	    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa0);
	    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEpecular0);

	    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobal);
	    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, false);
	    glEnable(GL_LIGHT0);
	    glDisable(GL_LIGHTING);
	    glPushMatrix();
	        glRotatef(luzBranca.X, 1.0, 0.0, 0.0);
	        glRotatef(luzBranca.Y, 0.0, 1.0, 0.0);
	        glLightfv(GL_LIGHT0, GL_POSITION, luzPosicional0);
	        glTranslatef(luzPosicional0[0], luzPosicional0[1], luzPosicional0[2]);
	        glColor3f(difusa, difusa, difusa);
	        renderizaAstroRei();
	    glPopMatrix();
	}else{
		glDisable(GL_LIGHT0);
	}

	glEnable(GL_LIGHTING);

}

void exibeCamera(){
	camera.X = 800 * sin(anguloCameraA) * cos(anguloCameraB);
    camera.Y = 800 * sin(anguloCameraA);
    camera.Z = 800 * cos(anguloCameraA) * sin(anguloCameraB);
    switch(modoCamera){
    	case 1:
    		 gluLookAt(cursor.X+camera.X, camera.Y, cursor.Z+camera.Z, cursor.X+0, 0, cursor.Z+0, 0, 1, 0);
    	break;
    	case 2:
    		gluLookAt(0, 0, 1080, 0, 0, 0, 0, 1, 0);
    	break;
    }
}

//---------------------------------------------------- Estado de Execução ------------------------------------------------------------

void estadoExecucao(){
	Mix_PlayChannel(-1, startingOdyssey, -1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    exibeCamera();
   	glMaterialfv(GL_FRONT, GL_SHININESS, matrizBrilho);
    glColor3f(1, 1, 1);
    queHajaLuz();
    renderizaCorpos();
    exibeOrbitas();
    glutSwapBuffers();
}

void estadoAtualizacao(int time){
	glutPostRedisplay();
    glutTimerFunc(time, estadoAtualizacao, time);
}

//---------------------------------------------------- Processos de Execução ------------------------------------------------------------

void estadoTranslacao(){
	mercury.Translacao = mercury.Translacao + 0.16f;
	venus.Translacao = venus.Translacao + 0.12f;
	earth.Translacao = earth.Translacao + 0.1f;
	mars.Translacao = mars.Translacao + 0.08f;
	jupiter.Translacao = jupiter.Translacao + 0.043f;
	uranus.Translacao = uranus.Translacao + 0.22f;
	neptune.Translacao = neptune.Translacao + 0.18f;
	saturn.Translacao = saturn.Translacao + 0.031f;
	estadoRotacao();
	glutPostRedisplay();
}

//---------------------------------------------------- Configurações da Aplicação ------------------------------------------------------------
/*Define as configurações da janela*/
void confJanela(int w, int h){
	janela.Largura = w;
	janela.Altura = h;

	glEnable(GL_DEPTH_TEST);
    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w/(float)h, 0.2, 2147483647.0);
    glMatrixMode(GL_MODELVIEW);
}
/*Define as configurações da camera*/
void confCamera(int x, int y){
	float altX = x - mouse.X;
	float altY = y - mouse.Y;

	anguloCameraA = anguloCameraA + altX/150;
	anguloCameraB = anguloCameraB + altY/150;

	if(anguloCameraB > 180){
		anguloCameraB = 180;
	}

	mouse.X = x;
	mouse.Y = y;
}

/*Define estado inicial dos componentes*/
void defineBase(){
	glClearColor(0,0,0, 0.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /*Configurações da Luz*/
    difusa = 1;
	especular = 1;
	posicional = 1;
	global = 0.2;
	luzBranca.X = 0;
	luzBranca.Y = 0;

	/*Configurações do Cursor*/
	cursor.X = 0;
	cursor.Y = 0;
	cursor.Z = 0;

	/*Configurações do Mouse*/
	mouse.X = 0;
	mouse.Y = 0;
	mouse.Z = 0;

    /*Configurações dos Corpos*/
    //SOL
	sun.Texture = carregaTextura("resources/textures/sun.jpg");
	sun.Translacao = 0;
	sun.Faces = 200;
	sun.Estado = true;
	sun.Rotacao = 0;

	//MERCURIO
	mercury.Texture = carregaTextura("resources/textures/mercury.jpg");
	mercury.Translacao = 90;
	mercury.Rotacao = 10;
	mercury.TamanhoTranslacao = 126;
	mercury.Faces = 200;
	mercury.Estado = true;

	/*Configurações do Material*/
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matrizAD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matrizEspecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matrizBrilho);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

int main(int argc, char* args[]){ //Nossa querida e tão aguardada (Pela Linguagem C), Main
	printf("Commands:\n  Move the mouse to change the perspective in Free Mode\n  Press 'V' to view Orbits\n  Press 'F' to turn ON/OFF the light\n  Press 'E' to change the size of the planets\n  Press '1' or '2' to change the camera mode (1 - Free Mode | 2 - Fixed Mode)\n  Press 'W', 'S', 'A' or 'D' to move the camera in Free Mode\n  Press 'ESC' to exit\n");
	SDL_Init(SDL_INIT_EVERYTHING); //Inicia o SDL
	glutInit(&argc, args);
	glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    //Configurações da Janela
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //Modo
    glutInitWindowSize(1400, 840);//Dimensão
    glutInitWindowPosition (0, 0);//Posição
    glutCreateWindow("Solar System"); //Nome     

	//Chama nossas funções principais
	glutDisplayFunc(estadoExecucao);//Execução
	glutReshapeFunc(confJanela);
	glutTimerFunc(10, estadoAtualizacao, 10); //Taxa de Atualização
	glutKeyboardFunc(estadoTeclado);
	glutPassiveMotionFunc(confCamera);
	glutIdleFunc(estadoTranslacao);
	defineBase(); //Processos Iniciais
	glutMainLoop();//Loop
	SDL_Quit();	//Encerra o SDL

	return 0;
}

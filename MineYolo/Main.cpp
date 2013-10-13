#include "Main.h"

using namespace std;

Player *player;
ChunkMgr *chunkMgr;

void HandleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // ESC
		exit(0);

	default:
		player->HandleInput(key, x, y);
		break;
	}
}

void initRendering()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	player = new Player();
	chunkMgr = new ChunkMgr();

	for (int x = 0; x < 6; x++)
	{
		for (int z = 0; z < 6; z++)
		{
			chunkMgr->GenerateChunk(x, z);
		}
	}
}

void HandleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity(); // Reset camera
	gluPerspective(45.0, (double) w / (double) h, 1.0, 200.0);
}


void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Reset drawing perspective

	// Camera
	glTranslatef(player->GetX(), player->GetY(), player->GetZ());
	glRotatef(75.0f, 0.0f, 1.0f, 0.0f);

	// Add ambient light
	GLfloat ambientColor [] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	// Add directed light
	GLfloat lightColor1 [] = { 1.5f, 1.2f, 1.2f, 1.0f };
	// Coming from direction
	GLfloat lightPos1 [] = { -1.0f, 0.5f, 0.5f, 0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);

	chunkMgr->Render();

	glutSwapBuffers();
}

void Update(int value)
{
	player->Update();

	glutPostRedisplay(); // Redraw

	glutTimerFunc(16, Update, 0);
}

int main(int argc, char** argv)
{
	// Init GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	// Window
	glutCreateWindow("MineYolo v0.01 DEV");
	initRendering();

	// Set handler functions
	glutDisplayFunc(DrawScene);
	glutKeyboardFunc(HandleKeypress);
	glutReshapeFunc(HandleResize);

	glutTimerFunc(16, Update, 0);

	glutMainLoop(); // Start loop. Never returns
	return 0;
}
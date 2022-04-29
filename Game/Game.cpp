#define G0
#ifdef G0
#include "Header/Angel.h"
//#include "Common/Quad.h"
#include "InputUtilities.h"
#include <iostream>
#include "Common/Text.h"
#include "Common/Player.h"
#include <string>

#include "View.h"
namespace View {
	mat4 view = mat4(1.0f);
	mat4 projection = mat4(Ortho(-SCREEN_WIDTH / 2.f, SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f, SCREEN_HEIGHT / 2.f, -2.0f, 2.0f));
}

void SetVSync(bool);
// 必須在 glewInit(); 執行完後,在執行物件實體的取得
//Quad* g_pQuad;	// 宣告 Quad 指標物件，結束時記得釋放
Player* g_player;
Text* g_text1;

// For Model View and Projection Matrix
void init() {
	//std::cout << sizeof(vec4) << std::endl;
	glClearColor(0.0, 0.0, 0.0, 1.0); // black background
	InputUtilities::Init();
	Text::Init("fonts/arial.ttf", View::projection);
	// 必須在 glewInit(); 執行完後,在執行物件實體的取得
	//g_pQuad = new Quad;
	//g_pQuad->SetShader(mat4(0), mat4(Ortho(-SCREEN_WIDTH / 2.f, SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f, SCREEN_HEIGHT / 2.f, -2.0f, 2.0f)));

	//  產生 projection 矩陣，此處為產生正投影矩陣
	//g_mxProjection = Ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
	//g_pQuad->SetShader(g_mxModelView, g_mxProjection);
	g_player = new Player(nullptr, vec3(), vec3(), vec3(48.f));
	g_text1 = new Text("Exp:0", vec3(255, 0, 0), -SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 48, 1.f);

}
#pragma region DISPLAY
Circle* a = nullptr;

void GL_Display(void)
{
	///*
	if (a != nullptr)
		delete a;
	a = new Circle();
	//*/
	glClear(GL_COLOR_BUFFER_BIT); // clear the window
	//g_pQuad->Draw();
	g_player->Draw();
	g_text1->Draw();
	//Draw(g_textShader, "This is sample text", -100.f, 200.f, 1.f, vec3(0.5, 0.8f, 0.2f));
	//Draw(g_textShader, "(C) LearnOpenGL.com", -100.f, 0.f, 1.f, vec3(0.3, 0.7f, 0.9f));
	glutSwapBuffers();	// 交換 Frame Buffer
}
void GL_Reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
}
extern void IdleProcess();
void onFrameMove(float delta)
{
	if (InputUtilities::GetKeyState(27)) {
		glutLeaveMainLoop();
	}
	g_player->Update(delta);
	int mouseX = 0, mouseY = 0;
	InputUtilities::GetMousePosition(mouseX, mouseY);
	//std::cout << "Mouse: " + std::to_string( mouseX) +" " + std::to_string(mouseY) << std::endl;
	g_text1->ChangeText("Mouse: " + std::to_string(mouseX) + " " + std::to_string(mouseY));
}
#pragma endregion
int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// If you use freeglut the two lines of code can be added to your application 
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Game");
	//For easier memory freeing process(this keeps main function running after window has been closed,
	//so I can free all those allocated below;
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE;
	glewInit();
	init();
	glutDisplayFunc(GL_Display);
	glutReshapeFunc(GL_Reshape);
	glutIdleFunc(IdleProcess);
	//SetVSync(false);
	glutMainLoop();
	//delete g_pQuad;
	delete g_text1;
	delete g_player;
	delete a;
	std::cout << "Game Process terminated.";
	return 0;
}

void SetVSync(bool sync)
{
	typedef BOOL(APIENTRY* PFNWGLSWAPINTERVALPROC)(int);
	PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

	const char* extensions = (char*)glGetString(GL_EXTENSIONS);

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");

	if (wglSwapIntervalEXT)
		wglSwapIntervalEXT(sync);
}
#endif

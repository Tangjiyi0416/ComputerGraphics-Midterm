#define G0
#ifdef G0
#include "Header/Angel.h"
//#include "Common/Quad.h"
#include "InputUtilities.h"
#include <iostream>
#include "Common/Text.h"
#include "Common/Player.h"
#include "Common/Big.h"
#include "Common/Small.h"
#include "Common/Sentinel.h"
#include "Common/Collider.h"
#include "Common/Boss0.h"
#include "LinkList.h"
#include <string>
#include "Common/Star.h"
#include "View.h"
#include "Common/TimedTextManager.h"
#include <ctime>
namespace View {
	mat4 view = mat4(1.0f);
	mat4 projection = mat4(Ortho(-SCREEN_WIDTH / 2.f, SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f, SCREEN_HEIGHT / 2.f, -2.0f, 2.0f));
}

void SetVSync(bool);
// 必須在 glewInit(); 執行完後,在執行物件實體的取得
//Quad* g_pQuad;	// 宣告 Quad 指標物件，結束時記得釋放
Player* g_player;
Linklist<GameObject*> g_worldObjects;
//Enemy** g_enemy;
#define STAR_NUMBER 50
Star* stars[STAR_NUMBER];
Text* g_text1;
//#define ENEMY_NUM 5
// For Model View and Projection Matrix
void init() {
	//std::cout << sizeof(vec4) << std::endl;
	glClearColor(0.0, 0.0, 0.0, 1.0); // black background
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	InputUtilities::Init();
	Collider::Init();
	Text::Init("fonts/arial.ttf", View::projection);
	// 必須在 glewInit(); 執行完後,在執行物件實體的取得
	//g_pQuad = new Quad;
	//g_pQuad->SetShader(mat4(0), mat4(Ortho(-SCREEN_WIDTH / 2.f, SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f, SCREEN_HEIGHT / 2.f, -2.0f, 2.0f)));

	//  產生 projection 矩陣，此處為產生正投影矩陣
	//g_mxProjection = Ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
	//g_pQuad->SetShader(g_mxModelView, g_mxProjection);
	g_text1 = new Text("", vec3(0.6f, 0.8f, 0.8f), -SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 48, 1.f);
	g_worldObjects.pushBack(Player::GetInstance());
	g_worldObjects.pushBack(new Boss0(nullptr, vec3(0, SCREEN_HEIGHT / 2 - 20, 0), vec3(), vec3(12.f)));
	srand(time(NULL));
	for (size_t i = 0; i < STAR_NUMBER; i++)
	{
		stars[i] = new Star(nullptr, vec3(rand() % SCREEN_WIDTH - SCREEN_WIDTH / 2, rand() % (SCREEN_HEIGHT * 2) - 1.5f * SCREEN_WIDTH, 0));
		stars[i]->localScale = vec3(rand() % 10 + 4);
	}
	//g_enemy = new Enemy * [ENEMY_NUM];
	//for (size_t i = 0; i < ENEMY_NUM; i++)
	//{
	//	g_enemy[i] = new Enemy(nullptr, vec3(0, 150, 0), vec3(0,0,90), vec3(12.f));
	//}
}
void BackgroundEffect(float delta) {

	for (size_t i = 0; i < STAR_NUMBER; i++)
	{
		if (stars[i]->localPosition.y < -SCREEN_HEIGHT / 2) {
			stars[i]->localPosition.y += SCREEN_HEIGHT * 1.5f;
		}
		stars[i]->Update(delta);
	}
}
float g_spawnCD = 0;
void WaveSpawn(float delta) {
	if (g_spawnCD >= 1) {
		int s = rand() % 100;
		//if (s < 40) {
		//	g_worldObjects.pushBack(new Big(nullptr, vec3(rand() % (SCREEN_WIDTH-20) - (SCREEN_WIDTH-20) / 2, SCREEN_HEIGHT, 0), vec3(), vec3(12.f)));
		//}
		//else if (s < 80) {
		//	g_worldObjects.pushBack(new Small(nullptr, vec3(rand() % (SCREEN_WIDTH - 20) - (SCREEN_WIDTH - 20) / 2, SCREEN_HEIGHT, 0), vec3(), vec3(12.f)));

		//}
		//else {
		g_worldObjects.pushBack(new Sentinel(nullptr, vec3(rand() % (SCREEN_WIDTH - 20) - (SCREEN_WIDTH - 20) / 2, SCREEN_HEIGHT, 0), vec3(), vec3(12.f)));

		//}
		g_spawnCD -= 1;
	}
	g_spawnCD += delta;
}

#pragma region DISPLAY
void GL_Display(void)
{

	glClear(GL_COLOR_BUFFER_BIT); // clear the window
	//g_pQuad->Draw();
	for (size_t i = 0; i < STAR_NUMBER; i++)
	{
		stars[i]->Draw();
	}
	//if (g_player != nullptr) g_player->Draw();
	ListNode<GameObject*>* cur = g_worldObjects.front();
	while (cur != nullptr)
	{
		cur->data->Draw();
		cur = cur->next();
	}
	BulletManager::Draw();
	TimedTextManager::Draw();
	g_text1->Draw();
	//Draw(g_textShader, "This is sample text", -100.f, 200.f, 1.f, vec3(0.5, 0.8f, 0.2f));
	//Draw(g_textShader, "(C) LearnOpenGL.com", -100.f, 0.f, 1.f, vec3(0.3, 0.7f, 0.9f));
	glutSwapBuffers();	// 交換 Frame Buffer
}
void GL_Reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	//glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	//std::cout << "reshape" << std::endl;
}
extern void IdleProcess();
//slowmotion
bool g_slow = false;
bool g_lastQState = false;
void onFrameMove(float delta)
{
	//slowmotion
	if (InputUtilities::GetKeyState('q') && InputUtilities::GetKeyState('q') != g_lastQState) {
		g_slow = !g_slow;
	}
	g_lastQState = InputUtilities::GetKeyState('q');
	if (g_slow)delta /= 2;

	//exit
	if (InputUtilities::GetKeyState(27)) {
		glutLeaveMainLoop();
	}
	BackgroundEffect(delta);

	//if (g_player != nullptr) {
	//	if (g_player->isDisabled()) {
	//		delete g_player;
	//		g_player = nullptr;
	//	}
	//}
	WaveSpawn(delta);
	ListNode<GameObject*>* cur = g_worldObjects.front();
	while (cur != nullptr)
	{
		if (cur->data->isDisabled()) {
			delete cur->data;
			ListNode<GameObject*>* next = cur->next();
			g_worldObjects.remove(cur);
			cur = next;
			continue;
		}
		cur->data->Update(delta);
		cur = cur->next();
	}
	//if (g_player != nullptr) {
	//	g_player->Update(delta);
	//}
	BulletManager::Update(delta);
	TimedTextManager::Update(delta);
	Collider::FrameUpdate();

	//int mouseX = 0, mouseY = 0;
	//InputUtilities::GetMousePosition(mouseX, mouseY);
	//std::cout << "Mouse: " + std::to_string( mouseX) +" " + std::to_string(mouseY) << std::endl;
	g_text1->ChangeText("Exp: " + std::to_string(Player::GetInstance()->GetExp()));
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
	SetVSync(false);
	glutMainLoop();
	//delete g_pQuad;
	delete g_text1;
	delete g_player;
	for (size_t i = 0; i < STAR_NUMBER; i++)
	{
		delete stars[i];
	}
	//for (size_t i = 0; i < ENEMY_NUM; i++)
	//{
	//	delete g_enemy[i];
	//}
	//delete[] g_enemy;
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

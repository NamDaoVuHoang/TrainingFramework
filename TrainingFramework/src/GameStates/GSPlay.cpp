#include "GSPlay.h"

#include "MainCharacter.h"
#include "Minotaur.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "AnimationSprite.h"
#include "Text.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}
void GSPlay::InitBackground(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, string tex, int i) {
	auto texture = ResourceManagers::GetInstance()->GetTexture(tex);
	m_BackGround[i] = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround[i]->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround[i]->SetSize(screenWidth, screenHeight);
	//m_BackGround->push_back(n_BackGround);
}

void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	
	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader1");
	//m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	for (int i = 0; i < num_background; i++) {
		//auto texture = ResourceManagers::GetInstance()->GetTexture(background_string[i]);
		InitBackground(model,shader,background_string[i],i);
	}

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	m_main_character = std::make_shared<MainCharacter>();
	m_main_character->Init();

	m_minotaur = std::make_shared<Minotaur>();
	m_minotaur->Init();
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{
	//printf("%f\n", "s");
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{	
	m_main_character->HandleKeyEvents(key, bIsPressed);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{
	m_main_character->Update(deltaTime);
	m_minotaur->Update(deltaTime,m_main_character->GetCurrentX(), m_main_character->GetCurrentY());
}

void GSPlay::Draw()
{	
	//printf("%s\n", is_FacingRight);
	for (int i = 0; i < num_background; i++) {
		m_BackGround[i]->Draw();
	}
	m_main_character->Draw();
	m_minotaur->Draw();
}

void GSPlay::SetNewPostionForBullet()
{

}
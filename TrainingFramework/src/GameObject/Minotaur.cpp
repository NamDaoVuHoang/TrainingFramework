#include "Minotaur.h"
#include "AnimationSprite.h"
using namespace std;

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine


Minotaur::Minotaur() {};
Minotaur::~Minotaur() {};

void Minotaur::InitAttack() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader1");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Minotaur");

	m_list_attacking[0] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 9, 3, (0.17f));

	m_list_attacking[1] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 5, 4, (0.25f));

	m_list_attacking[2] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 9, 6, (0.17f));

	for (int i = 0; i < num_attacks; i++) {
		m_list_attacking[i]->Set2DPosition(c_current_width, c_current_height);
		m_list_attacking[i]->SetSize(270, 270);
	}

	shader = ResourceManagers::GetInstance()->GetShader("AnimationShaderFlip1");

	m_list_flip_attacking[0] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 9, 3, (0.17f));

	m_list_flip_attacking[1] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 5, 4, (0.25f));

	m_list_flip_attacking[2] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 9, 6, (0.17f));

	for (int i = 0; i < num_attacks; i++) {
		m_list_flip_attacking[i]->Set2DPosition(c_current_width, c_current_height);
		m_list_flip_attacking[i]->SetSize(270, 270);
	}
}

void Minotaur::InitTaunt() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader1");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Minotaur");

	m_list_taunting[0] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 5, 2, (0.1f));

	m_list_taunting[1] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 6, 5, (0.1f));

	for (int i = 0; i < num_taunts; i++) {
		m_list_taunting[i]->Set2DPosition(c_current_width, c_current_height);
		m_list_taunting[i]->SetSize(270, 270);
	}

	shader = ResourceManagers::GetInstance()->GetShader("AnimationShaderFlip1");

	m_list_flip_taunting[0] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 5, 2, (0.1f));

	m_list_flip_taunting[1] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 6, 5, (0.1f));

	for (int i = 0; i < num_taunts; i++) {
		m_list_flip_taunting[i]->Set2DPosition(c_current_width, c_current_height);
		m_list_flip_taunting[i]->SetSize(270, 270);
	}
}

void Minotaur::Init() {
	num_attacks = 3;
	num_taunts = 2;
	run_speed = 100;
	InitAttack();
	InitTaunt();
	is_FacingRight = false;
	c_current_width = 700;
	c_current_height = 508;
	//Animation
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader1");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Minotaur");
	m_running = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 8, 1, (0.1f));
	m_running->Set2DPosition(c_current_width, c_current_height);
	m_running->SetSize(270, 270);

	//texture = ResourceManagers::GetInstance()->GetTexture("knight");

	//shader = ResourceManagers::GetInstance()->GetShader("AnimationShader1");
	//texture = ResourceManagers::GetInstance()->GetTexture("knight");

	m_standing = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 5, 0, (0.1f));
	m_standing->Set2DPosition(c_current_width, c_current_height);
	m_standing->SetSize(270, 270);

	m_takingdamage = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 7, 7, (0.3f));
	m_takingdamage->Set2DPosition(c_current_width, c_current_height);
	m_takingdamage->SetSize(270, 270);

	m_dying = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 6, 9, (0.1f));
	m_dying->Set2DPosition(c_current_width, c_current_height);
	m_dying->SetSize(270, 270);

	//Animation flip
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShaderFlip1");
	//texture = ResourceManagers::GetInstance()->GetTexture("knight");
	m_flip_running = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 8, 1, (0.1f));
	m_flip_running->Set2DPosition(c_current_width, c_current_height);
	m_flip_running->SetSize(270, 270);

	//texture = ResourceManagers::GetInstance()->GetTexture("knight");
	m_flip_standing = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 5, 0, (0.1f));
	m_flip_standing->Set2DPosition(c_current_width, c_current_height);
	m_flip_standing->SetSize(270, 270);


	m_flip_takingdamage = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 7, 7, (0.3f));
	m_flip_takingdamage->Set2DPosition(c_current_width, c_current_height);
	m_flip_takingdamage->SetSize(270, 270);

	m_flip_dying = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 6, 9, (0.1f));
	m_flip_dying->Set2DPosition(c_current_width, c_current_height);
	m_flip_dying->SetSize(270, 270);

};
void Minotaur::Update(GLfloat deltaTime, GLfloat c_x, GLfloat c_y) {
	standing_time = max(0, standing_time - deltaTime);
	if (standing_time > 0) {
		is_Standing = false;
		return;
	}
	if (abs(c_x - c_current_width) >= 110 && !is_Attacking && !is_Taunting) {
		if (c_x < c_current_width) {
			is_FacingRight = false;
		}
		else is_FacingRight = true;
		is_Running = true;
		if (is_FacingRight) {
			GLfloat s = deltaTime * run_speed;
			c_current_width += s;
			c_current_width = min(c_current_width, screenWidth - 30);
			m_running->Set2DPosition(c_current_width, c_current_height);
			m_running->UpdateRunning(deltaTime, is_Running);
		}
		else {
			GLfloat s = deltaTime * run_speed;
			c_current_width -= s;
			c_current_width = max(c_current_width, 30);
			m_flip_running->Set2DPosition(c_current_width, c_current_height);
			m_flip_running->UpdateRunning(deltaTime, is_Running);
		}
	}
	else {
		is_Running = false;
		m_running->SetCurrentFrames(0);
		if (!is_Attacking && !is_Taunting) {
			chosen_attack = rand() % 3;
			if (chosen_attack <= 1) chosen_taunt = 0;
			else chosen_taunt = 1;
			is_Taunting = true;
		}
		if (is_Taunting) {
			if (is_FacingRight) m_list_taunting[chosen_taunt]->UpdateTaunting(deltaTime,&is_Taunting);
			else m_list_flip_taunting[chosen_taunt]->UpdateTaunting(deltaTime, &is_Taunting);
		}
		if (!is_Taunting) {
			if (!is_Attacking) is_Attacking = true;
			if (is_FacingRight) m_list_attacking[chosen_attack]->UpdateAttacking(deltaTime, &is_Attacking);
			else m_list_flip_attacking[chosen_attack]->UpdateAttacking(deltaTime, &is_Attacking);
			if (!is_Attacking) {
				is_Standing = true;
				standing_time = 0.8f;
				if (c_x < c_current_width) {
					is_FacingRight = false;
				}
				else is_FacingRight = true;
			}
		}
	}
};

void Minotaur::Draw() {
	if (is_FacingRight) {
		if (is_Running) {
			m_running->Set2DPosition(c_current_width, c_current_height);
			m_running->Draw();
		}
		else if (is_Taunting) {
			m_list_taunting[chosen_taunt]->Set2DPosition(c_current_width, c_current_height);
			m_list_taunting[chosen_taunt]->Draw();
		}
		else if (is_Attacking) {
			m_list_attacking[chosen_attack]->Set2DPosition(c_current_width, c_current_height);
			m_list_attacking[chosen_attack]->Draw();
		}
		else {
			m_standing->Set2DPosition(c_current_width, c_current_height);
			m_standing->Draw();
		}
	}
	else {
		if (is_Running) {
			m_flip_running->Set2DPosition(c_current_width, c_current_height);
			m_flip_running->Draw();
		}
		else if (is_Taunting) {
			m_list_flip_taunting[chosen_taunt]->Set2DPosition(c_current_width, c_current_height);
			m_list_flip_taunting[chosen_taunt]->Draw();
		}
		else if (is_Attacking) {
			m_list_flip_attacking[chosen_attack]->Set2DPosition(c_current_width, c_current_height);
			m_list_flip_attacking[chosen_attack]->Draw();
		}
		else {
			m_flip_standing->Set2DPosition(c_current_width, c_current_height);
			m_flip_standing->Draw();
		}
	}
};
void Minotaur::HandleKeyEvents(int key, bool bIsPressed) {
};

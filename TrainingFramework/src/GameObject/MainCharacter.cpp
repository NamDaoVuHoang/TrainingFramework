#include "MainCharacter.h"
#include "AnimationSprite.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

MainCharacter::MainCharacter() {};
MainCharacter::~MainCharacter() {};

void MainCharacter::Init() {
	//hitbox = std::make_shared<Hitbox>(c_current_width, c_current_height, 24.0f, 24.0f);

	//Animation
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader1");
	auto texture = ResourceManagers::GetInstance()->GetTexture("knight");
	m_running = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 8, 1, (0.1f));
	m_running->Set2DPosition(c_current_width, c_current_height);
	m_running->SetSize(120, 120);

	//texture = ResourceManagers::GetInstance()->GetTexture("knight");
	m_attacking = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 6, 4, (0.05f));
	m_attacking->Set2DPosition(c_current_width, c_current_height);
	m_attacking->SetSize(120, 120);
	//m_attacking->SetHitboxX(30.0f, 2);
	//m_attacking->SetHitboxY(50.0f, 2);
	//m_attacking->SetHitboxX(30.0f, 3);
	//m_attacking->SetHitboxY(20.0f, 3);

	//shader = ResourceManagers::GetInstance()->GetShader("AnimationShader1");
	//texture = ResourceManagers::GetInstance()->GetTexture("knight");
	m_standing = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 5, 0, (0.1f));
	m_standing->Set2DPosition(c_current_width, c_current_height);
	m_standing->SetSize(120, 120);

	m_jumping = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 3, 2, (0.1f));
	m_jumping->Set2DPosition(c_current_width, c_current_height);
	m_jumping->SetSize(120, 120);

	m_falling = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 2, 3, (0.15f));
	m_falling->Set2DPosition(c_current_width, c_current_height);
	m_falling->SetSize(120, 120);

	m_takingdamage = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 1, 5, (0.3f));
	m_takingdamage->Set2DPosition(c_current_width, c_current_height);
	m_takingdamage->SetSize(120, 120);

	m_dying = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 7, 6, (0.15f));
	m_dying->Set2DPosition(c_current_width, c_current_height);
	m_dying->SetSize(120, 120);

	m_blocking = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 2, 7, (0.15f));
	m_blocking->Set2DPosition(c_current_width, c_current_height);
	m_blocking->SetSize(120, 120);
	//Animation flip
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShaderFlip1");
	//texture = ResourceManagers::GetInstance()->GetTexture("knight");
	m_flip_running = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 8, 1, (0.1f));
	m_flip_running->Set2DPosition(c_current_width, c_current_height);
	m_flip_running->SetSize(120, 120);

	//texture = ResourceManagers::GetInstance()->GetTexture("knight");
	m_flip_attacking = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 6, 4, (0.05f));
	m_flip_attacking->Set2DPosition(c_current_width, c_current_height);
	m_flip_attacking->SetSize(120, 120);
	//m_flip_attacking->SetHitboxX(30.0f, 2);
	//m_flip_attacking->SetHitboxY(50.0f, 2);
	//m_flip_attacking->SetHitboxX(30.0f, 3);
	//m_flip_attacking->SetHitboxY(20.0f, 3);

	//texture = ResourceManagers::GetInstance()->GetTexture("knight");
	m_flip_standing = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 5, 0, (0.1f));
	m_flip_standing->Set2DPosition(c_current_width, c_current_height);
	m_flip_standing->SetSize(120, 120);

	m_flip_jumping = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 3, 2, (0.1f));
	m_flip_jumping->Set2DPosition(c_current_width, c_current_height);
	m_flip_jumping->SetSize(120, 120);

	m_flip_falling = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 2, 3, (0.15f));
	m_flip_falling->Set2DPosition(c_current_width, c_current_height);
	m_flip_falling->SetSize(120, 120);

	m_flip_takingdamage = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 1, 5, (0.3f));
	m_flip_takingdamage->Set2DPosition(c_current_width, c_current_height);
	m_flip_takingdamage->SetSize(120, 120);

	m_flip_dying = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 7, 6, (0.15f));
	m_flip_dying->Set2DPosition(c_current_width, c_current_height);
	m_flip_dying->SetSize(120, 120);

	m_flip_blocking = std::make_shared<AnimationSprite>(model, shader, texture, 8, 8, 2, 7, (0.15f));
	m_flip_blocking->Set2DPosition(c_current_width, c_current_height);
	m_flip_blocking->SetSize(120, 120);
};
void MainCharacter::Update(GLfloat deltaTime) {
	//printf("%f\n", slide_wait_time);
	if (!is_Dodging)
		slide_wait_time = max(0, slide_wait_time - deltaTime);
	if (is_Jumping) {
		float in_air_time = min(rise_time, deltaTime);
		c_current_height -= in_air_time * jump_speed;
		rise_time = max(0, rise_time - deltaTime);
		m_jumping->Update(deltaTime);
		if (rise_time <= 0) {
			is_Jumping = false;
			is_Falling = true;
			m_jumping->SetCurrentFrames(0);
		}
	}
	else
		if (is_Falling) {
			//.printf("%f %f\n", fall_time, fall_time);
			float in_air_time = min(fall_time, deltaTime);
			c_current_height += in_air_time * jump_speed;
			fall_time = max(0, fall_time - deltaTime);
			m_falling->Update(deltaTime);
			if (fall_time == 0) {
				is_Falling = false;
				m_falling->SetCurrentFrames(0);
			}
		}
	if (is_FacingRight) {
		if (is_Dodging) {
			GLfloat in_slide_time = min(slide_time, deltaTime);
			GLfloat s = in_slide_time * slide_speed;
			slide_time = max(0, slide_time - deltaTime);
			c_current_width += s;
			c_current_width = min(c_current_width, screenWidth - 30);
			if (slide_time == 0) {
				is_Dodging = false;
				slide_wait_time = 0.5f;
			}
		}
		if (is_Attacking) {
			m_attacking->UpdateAttacking(deltaTime, &is_Attacking);
			is_Running = false;
		}
		else if (is_Running) {
				GLfloat s = deltaTime * run_speed;
				c_current_width += s;
				c_current_width = min(c_current_width, screenWidth - 30);
				m_running->Set2DPosition(c_current_width, c_current_height);
				m_running->UpdateRunning(deltaTime, is_Running);
			}
		else if (is_Blocking) {
			m_blocking->UpdateBlocking(deltaTime, is_Blocking);
		}
	}
	else {
		if (is_Dodging) {
			GLfloat in_slide_time = min(slide_time, deltaTime);
			GLfloat s = in_slide_time * slide_speed;
			slide_time = max(0, slide_time - deltaTime);
			c_current_width -= s;
			c_current_width = max(c_current_width, 30);
			if (slide_time == 0) {
				is_Dodging = false;
				slide_wait_time = 0.5f;
			}
		}
		if (is_Attacking) {
			m_flip_attacking->UpdateAttacking(deltaTime, &is_Attacking);
			is_Running = false;
		}
		else if (is_Running) {
				GLfloat s = deltaTime * run_speed;
				c_current_width -= s;
				c_current_width = max(c_current_width, 30);
				m_flip_running->Set2DPosition(c_current_width, c_current_height);
				m_flip_running->UpdateRunning(deltaTime, is_Running);
			}
		else if (is_Blocking) {
			m_flip_blocking->UpdateBlocking(deltaTime, is_Blocking);
		}
	}
};
void MainCharacter::Draw() {
	if (is_FacingRight) {
		if (is_Jumping) {
			m_jumping->Set2DPosition(c_current_width, c_current_height);
			m_jumping->Draw();
		}
		 else if (is_Falling) {
			m_falling->Set2DPosition(c_current_width, c_current_height);
			m_falling->Draw();
		}
		 else if (is_Running) {
			m_running->Set2DPosition(c_current_width, c_current_height);
			m_running->Draw();
		}
		 else if (is_Attacking) {
			m_attacking->Set2DPosition(c_current_width, c_current_height);
			m_attacking->Draw();
		}
		else if (is_Blocking) {
			m_blocking->Set2DPosition(c_current_width, c_current_height);
			m_blocking->Draw();
		}
		else {
			m_standing->Set2DPosition(c_current_width, c_current_height);
			m_standing->Draw();
		}
	}
	else {
		//printf("Draw\n");
		if (is_Jumping) {
			m_flip_jumping->Set2DPosition(c_current_width, c_current_height);
			m_flip_jumping->Draw();
		}
		else if (is_Falling) {
			m_flip_falling->Set2DPosition(c_current_width, c_current_height);
			m_flip_falling->Draw();
		}
		else if (is_Running) {
			m_flip_running->Set2DPosition(c_current_width, c_current_height);
			m_flip_running->Draw();
		}
		else if (is_Attacking) {
			m_flip_attacking->Set2DPosition(c_current_width, c_current_height);
			m_flip_attacking->Draw();
		}
		else if (is_Blocking) {
			m_flip_blocking->Set2DPosition(c_current_width, c_current_height);
			m_flip_blocking->Draw();
		}
		else {
			m_flip_standing->Set2DPosition(c_current_width, c_current_height);
			m_flip_standing->Draw();
		}
	}
};
void MainCharacter::HandleKeyEvents(int key, bool bIsPressed) {
	if (!is_Alive) return;
	if (is_Dodging && slide_wait_time > 0.05f) return;
	//printf("%d\n", key);
	switch (key) {
	case KEY_MOVE_FORWORD:
		if (!is_Jumping && !is_Falling && !is_TakingDamage) {
			is_Jumping = true;
			rise_time = (0.3f);
			fall_time = (0.3f);
		}
		break;
	case KEY_MOVE_BACKWORD:
		if (bIsPressed && !is_Jumping && !is_Falling && !is_TakingDamage && !is_Attacking && !is_Dodging) {
			is_Blocking = true;
		}
		else {
			is_Blocking = false;
		}
		break;
	case KEY_DODGE:
		if (bIsPressed && !is_Dodging && slide_wait_time <= 0.05f && !is_Falling && !is_TakingDamage && !is_Attacking) {
			is_Dodging = true;
			//is_Running = false;
			is_Attacking = false;
			is_Blocking = false;
			slide_time = 0.3f;
		}
		break;
	case KEY_ATTACK:
		if (bIsPressed) {
			if (!is_Falling && !is_Jumping && !is_Dodging && !is_TakingDamage) {
				is_Running = false;
				is_Attacking = true;
				is_Blocking = false;
			}
		}
		break;
	case KEY_MOVE_RIGHT:
		if (bIsPressed && !is_Attacking && !is_TakingDamage) {
			is_Running = true;
			if (!is_FacingRight) {
				m_running->SetCurrentFrames(0);
				is_FacingRight = true;
			}
		}
		else is_Running = false;
		break;
	case KEY_MOVE_LEFT:
		if (bIsPressed && !is_Attacking && !is_TakingDamage) {
			is_Running = true;
			if (is_FacingRight) {
				m_flip_running->SetCurrentFrames(0);
				is_FacingRight = false;
			}
		}
		else is_Running = false;
		break;
	}
};

GLfloat MainCharacter::GetCurrentX() {
	return c_current_width;
}

GLfloat MainCharacter::GetCurrentY() {
	return c_current_height;
}
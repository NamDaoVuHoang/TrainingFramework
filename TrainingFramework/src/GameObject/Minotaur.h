#pragma once
#include "Character.h"
class Minotaur :
    public Character
{
public:
    Minotaur();
    ~Minotaur();

    void InitAttack();
    void InitTaunt();
    void Init();
    void Update(GLfloat deltaTime, GLfloat c_x, GLfloat c_y);
    void Draw();
    void HandleKeyEvents(int key, bool bIsPressed);
protected:

    int chosen_attack = 0;
    int chosen_taunt = 0;
    int num_attacks = 0;
    int num_taunts = 0;
    float standing_time = 1.0f;
    bool is_Standing = true;
    bool is_Taunting = false;

    std::shared_ptr<AnimationSprite> m_list_attacking[10];
    std::shared_ptr<AnimationSprite> m_list_flip_attacking[10];
    std::shared_ptr<AnimationSprite> m_list_taunting[10];
    std::shared_ptr<AnimationSprite> m_list_flip_taunting[10];
};


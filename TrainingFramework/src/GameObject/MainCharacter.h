#pragma once
#include "Character.h"
class MainCharacter :
    public Character
{
public:
    MainCharacter();
    ~MainCharacter();

    void Init();
    void Update(GLfloat deltaTime);
    void Draw();
    void HandleKeyEvents(int key, bool bIsPressed);
    GLfloat GetCurrentX();
    GLfloat GetCurrentY(); 
};


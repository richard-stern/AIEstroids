#pragma once
#include "DynamicArray.h"
#include "Texture.h"
#include "Renderer2D.h"
#include "GameObject.h"


class AnimatedSprite : GameObject
{
public:
	AnimatedSprite(DynamicArray<aie::Texture*>& pTextures, float fAnimationFPS = 30, int nDrawOrder = 0);
	~AnimatedSprite();
	
	void Update(float deltaTime) override;

	void SetAnimationTextures(const DynamicArray<aie::Texture*>& pTextures);
	

	float GetAnimationFPS() const { return m_fAnimationFPS; }
	void SetAnimationFPS(float fFPS) { m_fAnimationFPS = fFPS; }

	int GetDrawOrder() const { return m_nDrawOrder; }

private:
	int m_nDrawOrder;
	DynamicArray<aie::Texture*> m_vAnimTextures;
	float m_fCurrentFrame;
	float m_fAnimationFPS;
};


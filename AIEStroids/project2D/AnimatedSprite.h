#pragma once
#include "DynamicArray.h"
#include "Texture.h"
#include "Renderer2D.h"
#include "GameObject.h"

struct AnimationDefinition
{
	int m_nFrameStart;
	int m_nFrameEnd;
};

class AnimatedSprite : GameObject
{
public:
	AnimatedSprite(DynamicArray<aie::Texture*>& pTextures, bool bLoop = true, float fAnimationFPS = 30, int nDrawOrder = 0);
	~AnimatedSprite();
	
	void Update(float deltaTime);
	void Draw(aie::Renderer2D* _renderer2D);

	void SetAnimationTextures(const DynamicArray<aie::Texture*>& pTextures);
	
	void SetAnimationDefinitions(const DynamicArray<AnimationDefinition> vDefs);

	float GetAnimationFPS() const { return m_fAnimationFPS; }
	void SetAnimationFPS(float fFPS) { m_fAnimationFPS = fFPS; }

	int GetCurrentAnimation() const { return m_nCurrentAnimation; }
	void SetCurrentAnimation(int nCurrent);

	int GetDrawOrder() const { return m_nDrawOrder; }

private:
	int m_nDrawOrder;
	DynamicArray<AnimationDefinition>* m_vAnimDefs;
	DynamicArray<aie::Texture*>* m_vAnimTextures;

	int m_nCurrentAnimation;
	float m_fCurrentFrame;
	float m_fAnimationFPS;

	bool m_bLoop;
};


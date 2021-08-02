#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(DynamicArray<aie::Texture*>& pTextures, bool bLoop, float fAnimationFPS, int nDrawOrder)
{
	m_bLoop = bLoop;
	m_fAnimationFPS = fAnimationFPS;
	m_fCurrentFrame = 0;
	m_nCurrentAnimation = 0;
	m_nDrawOrder = nDrawOrder;

	//Set Up Textures
	m_vAnimTextures = new DynamicArray<aie::Texture*>();
	SetAnimationTextures(pTextures);
	/*for (int i = 0; i < pTextures.Count(); i++)
	{
		m_vAnimTextures->InsertEnd(pTextures[i]);
	}*/

	m_vAnimDefs = new DynamicArray<AnimationDefinition>();
	SetTexture(m_vAnimTextures->GetAt(0));
}

AnimatedSprite::~AnimatedSprite()
{
	if (m_vAnimDefs)
		delete m_vAnimDefs;
	if (m_vAnimTextures)
		delete m_vAnimTextures;
}

void AnimatedSprite::Update(float deltaTime)
{
	if (m_vAnimTextures->Count() > 0)
	{
		//Update the current frame based on frame rate and delta time

		m_fCurrentFrame += m_fAnimationFPS * deltaTime;

		if (m_vAnimDefs->Count() > 0)
		{
			/*AnimationDefinition* currDef = m_vAnimDefs->GetAt(m_nCurrentAnimation);
			if (m_fCurrentFrame >= m_vAnimTextures->Count() || m_fCurrentFrame >= m_vAnimDefs->GetAt(m_nCurrentAnimation).m_nFrameEnd)
			{
				if (m_bLoop)
					m_fCurrentFrame = (float)m_vAnimDefs->GetAt(m_nCurrentAnimation).m_nFrameEnd;
				else

			}*/
		}
	}
}

void AnimatedSprite::Draw(aie::Renderer2D* _renderer2D)
{
}

void AnimatedSprite::SetAnimationTextures(const DynamicArray<aie::Texture*>& pTextures)
{
}

void AnimatedSprite::SetAnimationDefinitions(const DynamicArray<AnimationDefinition> vDefs)
{
}

void AnimatedSprite::SetCurrentAnimation(int nCurrent)
{
}

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(DynamicArray<aie::Texture*>& pTextures, float fAnimationFPS, int nDrawOrder)
{
	m_fAnimationFPS = fAnimationFPS;
	m_fCurrentFrame = 0;
	m_nDrawOrder = nDrawOrder;

	//Set Up Textures
	SetAnimationTextures(pTextures);
	SetTexture(m_vAnimTextures.GetAt(0));
}

AnimatedSprite::~AnimatedSprite()
{

}

void AnimatedSprite::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	if (m_vAnimTextures.Count() > 0)
	{
		//Update the current frame based on frame rate and delta time
		m_fCurrentFrame += m_fAnimationFPS * deltaTime;

		if (m_fCurrentFrame >= m_vAnimTextures.Count())
		{
			m_fCurrentFrame -= m_vAnimTextures.Count();
		}

		//Set the current Texture
		SetTexture(m_vAnimTextures[static_cast<int> (m_fCurrentFrame)]);

	}
}

void AnimatedSprite::SetAnimationTextures(const DynamicArray<aie::Texture*>& pTextures)
{
	m_vAnimTextures = pTextures;
	if (m_vAnimTextures.Count() > 0)
	{
		//Set the active texture to the first frame
		m_fCurrentFrame = 0.0f;
		SetTexture(m_vAnimTextures[0]);
	}
}


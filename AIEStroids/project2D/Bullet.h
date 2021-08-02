#pragma once
#include <Texture.h>
class Bullet /*: Actor*/
{
public:
	Bullet();
	~Bullet();

	void Shoot();

	void OnCollision(/*GameObject overload*/);

private:
	aie::Texture* m_pTexture;
};


#include "stdafx.h"
#include "Following.h"

Following::Following(IFollowing * focus)
	:focus(focus)
{
}

Following::~Following()
{
}

void Following::Change(IFollowing * focus)
{
	this->focus = focus;
}

void Following::Update()
{
	if (focus == NULL) return;

	D3DXVECTOR2 location, size;
	focus->Focus(&location, &size);

	D3DXVECTOR2 temp = location;
	temp.x -= (float)Width * 0.15f;
	temp.y -= (float)Height * 0.15f;

	temp.x += size.x * 0.1f;
	temp.y += size.x * 0.1f;

	position = temp;

	__super::Update();

}

#include "stdafx.h"
#include "Clip.h"

//-----------------------------------------------------------------------------
// Frame
//-----------------------------------------------------------------------------

Frame::Frame(Sprite * sprite, float time)
{
	Image = sprite;
	Time = time;
}

Frame::~Frame()
{
	SafeDelete(Image);
}

//-----------------------------------------------------------------------------
// Clip
//-----------------------------------------------------------------------------
Clip::Clip(PlayMode mode, float speed)
	: mode(mode), speed(speed)
	, length(0), playTime(0), bPlay(false), currentFrame(0)
	, position(0,0), scale(1,1), rotation(0,0,0)
{

}

Clip::~Clip()
{
	for (Frame* frame : frames)
		SafeDelete(frame);
}

void Clip::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Clip::Position(D3DXVECTOR2 & vec)
{
	position = vec;
}

D3DXVECTOR2 Clip::Position()
{
	return position;
}

void Clip::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Clip::Scale(D3DXVECTOR2 & vec)
{
	scale = vec;
}

D3DXVECTOR2 Clip::Scale()
{
	return scale;
}

void Clip::Rotation(float x, float y, float z)
{
	Rotation(D3DXVECTOR3(x, y, z));
}

void Clip::Rotation(D3DXVECTOR3 & vec)
{
	rotation = vec;
}

D3DXVECTOR2 Clip::Rotation()
{
	return rotation;
}

void Clip::RotationDegree(float x, float y, float z)
{
	RotationDegree(D3DXVECTOR3(x, y, z));

}

void Clip::RotationDegree(D3DXVECTOR3 & vec)
{
	D3DXVECTOR3 temp;
	temp.x = Math::ToRadian(vec.x);
	temp.y = Math::ToRadian(vec.y);
	temp.z = Math::ToRadian(vec.z);

	Rotation(temp);
}

D3DXVECTOR3 Clip::RotationDegree()
{
	D3DXVECTOR3 temp = Rotation();
	temp.x = Math::ToDegree(temp.x);
	temp.y = Math::ToDegree(temp.y);
	temp.z = Math::ToDegree(temp.z);

	return temp;
}

D3DXVECTOR2 Clip::TextureSize()
{
	return frames[currentFrame]->Image->TextureSize();
}

void Clip::AddFrame(Sprite * sprite, float time)
{
	frames.push_back(new Frame(sprite, time));
}

void Clip::Play()
{
	playTime = 0.0f;
	currentFrame = 0;

	bPlay = true;
}

void Clip::Play(UINT startFrame)
{
	playTime = 0.0f;
	currentFrame = startFrame;

	bPlay = true;
}

void Clip::Stop()
{
	bPlay = false;
	currentFrame = 0;
}

void Clip::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	Frame* frame = frames[currentFrame];
	frame->Image->Update(V, P);

	if (bPlay == true)
	{
		float time = frame->Time * speed;
		playTime += Timer->Elapsed();

		if (playTime >= time)
		{
			switch (mode)
			{
				case PlayMode::End:
				{
					currentFrame++;

					if (currentFrame >= frames.size())
						Stop();
				}
				break;
				
				case PlayMode::Loop:
				{
					currentFrame++;
					currentFrame %= frames.size();
				}
				break;
			}
			playTime = 0.0f;
		}
	}

	frames[currentFrame]->Image->Position(position);
	frames[currentFrame]->Image->Scale(scale);
	frames[currentFrame]->Image->Rotation(rotation);
	frames[currentFrame]->Image->Update(V, P);
}

void Clip::Render()
{
	Frame* frame = frames[currentFrame];
	frame->Image->Render();
}

void Clip::DrawBound(bool val)
{
	for (Frame* frame : frames)
		frame->Image->DrawBound(val);
}

Sprite * Clip::GetSprite()
{
	return frames[currentFrame]->Image;
}

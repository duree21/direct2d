#pragma once

class Animation
{
public:
	Animation();
	~Animation();

	void AddClip(Clip* clip);
	void Play(UINT clipNumber);
	void Stop();

	void Position(float x, float y);
	void Position(D3DXVECTOR2& vec);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& vec);
	D3DXVECTOR2 Scale() { return scale; }

	void Rotation(float x, float y, float z);
	void Rotation(D3DXVECTOR3& vec);
	D3DXVECTOR3 Rotation() { return rotation; }

	void RotationDegree(float x, float y, float z);
	void RotationDegree(D3DXVECTOR3& vec);
	D3DXVECTOR3 RotationDegree();

	D3DXVECTOR2 TextureSize();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void DrawBound(bool val);

	Clip* GetClip();
	Sprite* GetSprite();

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;

	UINT currentClip;
	vector<Clip *> clips;
};
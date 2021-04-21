#pragma once
class Table
{
public:
	Table(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Table();

	void Position(float x, float y) { Position(D3DXVECTOR2(x, y)); }
	void Position(D3DXVECTOR2& vec) { position = vec; animation->Position(position); }
	D3DXVECTOR2 Position() { return position; } 
	
	void Scale(float x, float y) { Scale(D3DXVECTOR2(x, y)); }
	void Scale(D3DXVECTOR2& vec) { scale = vec; animation->Scale(scale); }
	D3DXVECTOR2 Scale() { return scale; }

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	Animation* GetAnim() { return animation; }

private:
	Animation* animation;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
};

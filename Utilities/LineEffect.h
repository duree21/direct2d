#pragma once

class LineEffect {
public:
	struct DoubleVector2 {
		DoubleVector2(D3DXVECTOR2 st, D3DXVECTOR2 ed) :start(st), end(ed) {}
		D3DXVECTOR2 start;
		D3DXVECTOR2 end;
	};
public:
	// private 함수 이용 충돌 판정 후, 위치 값 반환 
	static bool LineCollision(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXVECTOR2 p3, D3DXVECTOR2 p4, D3DXVECTOR2& result) { return LineCollision(DoubleVector2(p1, p2), DoubleVector2(p3, p4), result); }
	static bool LineCollision(DoubleVector2 one, DoubleVector2 two, D3DXVECTOR2& result);

private:
	static float cross(D3DXVECTOR2 a, D3DXVECTOR2 b) { return a.x*b.y - a.y*b.x; }
	static float ccw(D3DXVECTOR2 p, D3DXVECTOR2 a, D3DXVECTOR2 b) { return D3DXVec2CCW(&(a - p), &(b - p)); }
	static bool lineIntersection(D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, D3DXVECTOR2 d, D3DXVECTOR2& p);
	static bool paralleSegments(D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, D3DXVECTOR2 d, D3DXVECTOR2& p);
	static bool segmentIntersects(D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, D3DXVECTOR2 d);
};
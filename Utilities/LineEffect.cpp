#include "stdafx.h"
#include "LineEffect.h"

bool LineEffect::LineCollision(DoubleVector2 one, DoubleVector2 two, D3DXVECTOR2& result)
{
	//D3DXVec2CCW(a,b)
	//D3DXVec2CCW(a-p, b-p)
	if (segmentIntersects(one.start, one.end, two.start, two.end)) 
	{
		lineIntersection(one.start, one.end, two.start, two.end, result);
		return true;
	}
	return false;
}

//Code Segment from https://bowbowbow.tistory.com/17
bool LineEffect::lineIntersection(D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, D3DXVECTOR2 d, D3DXVECTOR2 & p)
{
	float det = cross(b - a, d - c);
	//두선이 평행인 경우
	if (fabs(det) < FLT_EPSILON) return false;
	p = a + (b - a)*(cross(c - a, d - c) / det);
	return true;
}

//Code Segment from https://bowbowbow.tistory.com/17
bool LineEffect::paralleSegments(D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, D3DXVECTOR2 d, D3DXVECTOR2 & p)
{
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);

	//한 직선위에 없거나 두 선분이 겹치지 않는 경우를 우선 걸러낸다. 본문의 1번 관계인 경우이다.
	if (ccw(a, b, c) != 0 || b < c || d < a) return false;

	//두 선분이 확실히 겹친다면 교차점 하나를 찾는다.
	if (a < c) p = c;
	else p = a;
	return true;
}

//Code Segment from https://bowbowbow.tistory.com/17
bool LineEffect::segmentIntersects(D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, D3DXVECTOR2 d)
{
	double ab = ccw(a, b, c)*ccw(a, b, d);
	double cd = ccw(c, d, a)*ccw(c, d, b);
	//두 선분이 한 직선에 위에 있거나 끝점이 겹치는 경우
	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}
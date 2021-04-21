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
	//�μ��� ������ ���
	if (fabs(det) < FLT_EPSILON) return false;
	p = a + (b - a)*(cross(c - a, d - c) / det);
	return true;
}

//Code Segment from https://bowbowbow.tistory.com/17
bool LineEffect::paralleSegments(D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, D3DXVECTOR2 d, D3DXVECTOR2 & p)
{
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);

	//�� �������� ���ų� �� ������ ��ġ�� �ʴ� ��츦 �켱 �ɷ�����. ������ 1�� ������ ����̴�.
	if (ccw(a, b, c) != 0 || b < c || d < a) return false;

	//�� ������ Ȯ���� ��ģ�ٸ� ������ �ϳ��� ã�´�.
	if (a < c) p = c;
	else p = a;
	return true;
}

//Code Segment from https://bowbowbow.tistory.com/17
bool LineEffect::segmentIntersects(D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, D3DXVECTOR2 d)
{
	double ab = ccw(a, b, c)*ccw(a, b, d);
	double cd = ccw(c, d, a)*ccw(c, d, b);
	//�� ������ �� ������ ���� �ְų� ������ ��ġ�� ���
	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}
#include "Pivot.h"

namespace std
{
	Pivot::Pivot(const float3& center, const float3& xaxis, const float3& yaxis, const float3& zaxis)
	{
		this->center = center;
		this->xaxis = xaxis;
		this->yaxis = yaxis;
		this->zaxis = zaxis;
		updLocalMatrix();
		updGlobalMatrix();
	}

	Pivot::Pivot(const float3& center) : Pivot(center, float3(1, 0, 0), float3(0, 1, 0), float3(0, 0, 1))
	{

	}

	Pivot::Pivot()
	{
	}

	Pivot::~Pivot()
	{
	}

	void Pivot::updLocalMatrix()
	{
		localMatrix = Matrix3x3(
			xaxis.x, xaxis.y, xaxis.z,
			yaxis.x, yaxis.y, yaxis.z,
			zaxis.x, zaxis.y, zaxis.z);
	}

	void Pivot::updGlobalMatrix()
	{
		globalMatrix = Matrix3x3(
			xaxis.x, yaxis.x, zaxis.x,
			xaxis.y, yaxis.y, zaxis.y,
			xaxis.z, yaxis.z, zaxis.z
		);
	}

	float3 Pivot::toLocalCoords(const float3& f)
	{
		return transform(localMatrix, f - center);
	}

	float3 Pivot::toGlobalCoords(const float3& f)
	{
		return transform(globalMatrix, f) + center;
	}

	void Pivot::movePivot(const float3& f)
	{
		center += f;
	}

	void Pivot::rotatePivot(float angle, char axis)
	{
		xaxis = rotate(xaxis, angle, axis);
		yaxis = rotate(yaxis, angle, axis);
		zaxis = rotate(zaxis, angle, axis);
		updGlobalMatrix();
		updLocalMatrix();
	}
}
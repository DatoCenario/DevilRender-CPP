#include "Camera.h"
#include <iostream>

namespace std
{
	Camera::Camera()
	{}

	Camera::Camera(const float3& pos, int width, int height, float screenDist, float observeRange)
	{
		pivot = Pivot(pos);
		this->width = width;
		this->height = height;
		this->half_width = width / 2;
		this->half_height = height / 2;
		this->observeRange = observeRange;
		this->screenDist = screenDist;
		updScale();
	}

	Camera::~Camera()
	{
	}

	void Camera::updScale()
	{
		scale = width / (screenDist * tan(observeRange / 2));
	}

	void Camera::rotate(float angle, char axis)
	{
		pivot.rotatePivot(angle , axis);
	}

	void Camera::move(const float3& f)
	{
		pivot.movePivot(f);
	}

	bool Camera::inObserve(const float3& local)
	{
		if (local.z < screenDist)
		{
			return false;
		}
		float ang = angle(local , float3(0,0,1));
		if (abs(ang) > observeRange / 2)
		{
			return false;
		}
		return true;
	}

	float2 Camera::proection(const float3& local)
	{
		float delta = screenDist / max(local.z , 0.01) * scale;
		float2 p(local.x * delta , local.y * delta);
		float2 sCoords(p.x + half_width , half_height - p.y);
		return sCoords;
	}
}
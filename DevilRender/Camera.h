#pragma once
#include "Object3D.h";

namespace std
{
	class Camera : public Object3D
	{
	private:
		void updScale();

	public:
		int width, height , half_width , half_height;
		float screenDist, observeRange, scale;

		Camera();
		Camera(const float3& pos , int width , int height , float screenDist , float observeRange);
		~Camera();

		void move(const float3& f) override;

		void rotate(float angle , char axis) override;

		float2 proection(const float3& local);

		bool inObserve(const float3& local);
	};
}



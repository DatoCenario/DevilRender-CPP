#pragma once
#include "Camera.h"
#include "Geometry.h"


namespace std
{
	class Rasterizer
	{
	private:
		Camera camera;
		Vertex* vbuffer;
		int* visibleIndexes;
		int visibleCount;
		int vbufferSize;
		int visibleIndSize;

		bool observed(const Poly3D& poly);

		void makeLocal(Poly3D& poly);

		void computePoly(Poly3D& poly);

		void computePolyPart(int steps, const float2& ps, float pU, float pD, const float3& s, const float3& u,
			const float3& d, const float2& ts, const float2& tU, const float2& tD, const float3& ns,
			const float3& nU, const float3& nD, int dir , Primitive* prim);

	public:
		Rasterizer(const Camera& cam);

		~Rasterizer();

		void initializeVBuffer(const vector<Primitive*>& primitives);

		TGAImage* computeShaders();
	};
}




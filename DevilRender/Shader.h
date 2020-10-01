#pragma once
#include "Geometry.h"
#include "Camera.h"

namespace std
{
	class Vertex;

	struct Light
	{
		float3 pos;
		float intensivity;

		Light(const float3& pos, float intensivity)
		{
			this->pos = pos;
			this->intensivity = intensivity;
		}
	};

	class Shader
	{
	public:
		virtual void compute(Vertex& v, Camera& c) = 0;
	};

	class PhongModelShader : public Shader
	{
	private:
		vector<Light> lights;
		float diffuseCoef = 0.5f;
		float reflectCoef = 0.5f;
	public:
		PhongModelShader(const vector<Light>& lights);
		~PhongModelShader();

		void compute(Vertex& v, Camera& c) override;
	};
}



#include "Shader.h"

namespace std
{
	PhongModelShader::PhongModelShader(const vector<Light>& lights)
	{
		this->lights = lights;
	}

	PhongModelShader::~PhongModelShader()
	{
	}

	void PhongModelShader::compute(Vertex& v, Camera& c) 
	{
		float3 gPos = c.pivot.toGlobalCoords(v.pos);
		for (Light l : lights)
		{
			float3 lDir = normalize(l.pos - gPos);
			float3 pct = proection(lDir, -v.normal);
			float3 d = lDir - pct;
			float3 refl = pct - d;
			float diffuse = max(0.0, cross(lDir , -v.normal)) * l.intensivity;
			float3 eye = -normalize(v.pos);
			float reflect = max(0.0, cross(refl, eye)) * l.intensivity;
			float total = diffuse * diffuseCoef + reflect * reflectCoef;
			v.color.r = min(255 , (v.color.r + 30) * total);
			v.color.g = min(255 , (v.color.g + 30) * total);
			v.color.b = min(255 , (v.color.b + 30) * total);
		}
	}

}
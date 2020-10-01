#pragma once
#include "Geometry.h"
#include "Shader.h"

namespace std
{
	class Scene
	{
	private:
		vector<pair<Primitive, Shader>> primitives;
	};
}


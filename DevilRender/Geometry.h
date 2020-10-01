#pragma once
#include "Pivot.h";
#include "Object3D.h";
#include <vector>
#include "tgaImage.h"
#include "Shader.h"




namespace std
{
	class Primitive;
	class PolyIterator;
	class Vertex;
	class Poly3D;
	class Shader;

	class Primitive : public Object3D
	{
	protected:
		vector<float3>* localVertices;
		vector<float3>* globalVertices;
		vector<float3>* normals;
		vector<float2>* textureCoods;
		vector<int>* indexes;
		vector<int>* texCoordsIndexes;
		vector<int>* normalsIndexes;
		vector<Shader*>* shaders;
	public:
		friend class PolyIterator;

		Primitive();

		Primitive(const float3& center, vector<float3>* localVertices, vector<float3>* normals, vector<float2>* texCoords,
			vector<int>* indexes, vector<int>* nIndexes, vector<int>* tIndexes);

		~Primitive();

		void rotate(float angle, char axis);

		void move(const float3& f);

		void scale(float k);

		void updGlobalVertices();

		void addShader(Shader* shader);

		Shader* getShader(int index);

		int shadersLen();

		PolyIterator begin();
		PolyIterator end();
	};

	struct Vertex
	{
		float3 pos, normal;
		float2 texCoord;
		TGAColor color;

		Primitive* prim;

		Vertex();

		Vertex(const float3& pos, const float3& normal, const float2& texCoord, const TGAColor& color, Primitive* prim);
	};

	class Poly3D
	{
	public:
		Vertex v1, v2, v3;

		Poly3D()
		{}

		Poly3D(const Vertex& v1, const Vertex& v2, const Vertex& v3)
		{
			this->v1 = v1;
			this->v2 = v2;
			this->v3 = v3;
		}
	};

	class PolyIterator
	{
	private:
		int currentIndex;
		Poly3D currentPoly;
		Primitive* prim;

	public:

		PolyIterator(Primitive* prim, int index);

		~PolyIterator();

		Poly3D& getCurrent();

		Poly3D& operator * ();
		Poly3D& operator ++ ();
		Poly3D& operator -- ();
		Poly3D& operator ++ (int);
		Poly3D& operator -- (int);

		bool operator == (const PolyIterator& pI);
		bool operator != (const PolyIterator& pI);

	};
}
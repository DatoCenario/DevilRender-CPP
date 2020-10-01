#include "Geometry.h"

namespace std
{
	Primitive::Primitive()
	{
		shaders = new vector<Shader*>();
	}

	Primitive::Primitive(const float3& center, vector<float3>* localVertices, vector<float3>* normals, vector<float2>* texCoords,
		vector<int>* indexes, vector<int>* nIndexes, vector<int>* tIndexes) : Primitive()
	{
		this->pivot = Pivot(center);
		this->localVertices = localVertices;
		this->normals = normals;
		this->textureCoods = texCoords;
		this->indexes = indexes;
		this->normalsIndexes = nIndexes;
		this->texCoordsIndexes = tIndexes;
		this->globalVertices = new vector<float3>(localVertices->size());
		updGlobalVertices();
	}

	Primitive::~Primitive()
	{
	}

	void Primitive::rotate(float angle, char axis)
	{
		pivot.rotatePivot(angle, axis);
		updGlobalVertices();
	}

	void Primitive::move(const float3& f)
	{
		pivot.movePivot(f);
		for (auto v : *globalVertices)
			v += f;
	}

	void Primitive::scale(float k)
	{
		for (size_t i = 0; i < localVertices->size(); i++)
		{
			localVertices->at(i) *= k;
		}

		updGlobalVertices();
	}

	void Primitive::updGlobalVertices()
	{
		for (size_t i = 0; i < localVertices->size(); i++)
		{
			globalVertices->at(i) = pivot.toLocalCoords(localVertices->at(i));
		}
	}

	void Primitive::addShader(Shader* shader)
	{
		shaders->push_back(shader);
	}

	Shader* Primitive::getShader(int index)
	{
		return shaders->at(index);
	}

	int Primitive::shadersLen()
	{
		return shaders->size();
	}

	Vertex::Vertex()
	{
	}

	Vertex::Vertex(const float3& pos, const float3& normal, const float2& texCoord, const TGAColor& color, Primitive* prim)
	{
		this->color = color;
		this->normal = normal;
		this->pos = pos;
		this->texCoord = texCoord;
		this->prim = prim;
	}

	PolyIterator Primitive::begin()
	{
		return PolyIterator(this, 0);
	}

	PolyIterator Primitive::end()
	{
		return PolyIterator(this, indexes->size() - 3);
	}

	PolyIterator::PolyIterator(Primitive* prim, int index)
	{
		this->prim = prim;
		this->currentIndex = index;
		getCurrent();
	}

	PolyIterator::~PolyIterator()
	{
	}

	Poly3D& PolyIterator::getCurrent()
	{
		if (currentIndex >= prim->indexes->size())
		{
			Poly3D p = Poly3D();
			return p;
		}
		float3 v1, v2, v3, n1, n2, n3; float2 t1, t2, t3;
		int i1, i2, i3, in1, in2, in3, it1, it2, it3;
		i1 = prim->indexes->at(currentIndex);
		i2 = prim->indexes->at(currentIndex + 1);
		i3 = prim->indexes->at(currentIndex + 2);

		v1 = prim->globalVertices->at(i1);
		v2 = prim->globalVertices->at(i2);
		v3 = prim->globalVertices->at(i3);

		if (prim->normalsIndexes->size() != 0)
		{
			in1 = prim->normalsIndexes->at(currentIndex);
			in2 = prim->normalsIndexes->at(currentIndex + 1);
			in3 = prim->normalsIndexes->at(currentIndex + 2);

			n1 = prim->normals->at(in1);
			n2 = prim->normals->at(in2);
			n3 = prim->normals->at(in3);
		}

		if (prim->texCoordsIndexes->size() != 0)
		{
			it1 = prim->texCoordsIndexes->at(currentIndex);
			it2 = prim->texCoordsIndexes->at(currentIndex + 1);
			it3 = prim->texCoordsIndexes->at(currentIndex + 2);

			t1 = prim->textureCoods->at(it1);
			t2 = prim->textureCoods->at(it2);
			t3 = prim->textureCoods->at(it3);
		}
		return currentPoly = Poly3D(Vertex(v1, n1, t1, TGAColor(), prim),
			Vertex(v2, n2, t2, TGAColor(), prim),
			Vertex(v3, n3, t3, TGAColor(), prim));
	}

	Poly3D& PolyIterator::operator*()
	{
		return currentPoly;
	}

	Poly3D& PolyIterator::operator++()
	{
		currentIndex += 3;
		if (currentIndex < prim->indexes->size())
		{
			return getCurrent();
		}
		else
		{
			return currentPoly;
		}
	}

	Poly3D& PolyIterator::operator--()
	{
		currentIndex -= 3;
		if (currentIndex >= 0)
		{
			return getCurrent();
		}
		else
		{
			return currentPoly;
		}
	}
	Poly3D& PolyIterator::operator++(int)
	{
		currentIndex += 3;
		if (currentIndex < prim->indexes->size())
		{
			return getCurrent();
		}
		else
		{
			return currentPoly;
		}
	}
	Poly3D& PolyIterator::operator--(int)
	{
		if (currentIndex >= 0)
		{
			return getCurrent();
		}
		else
		{
			return currentPoly;
		}
	}
	bool PolyIterator::operator==(const PolyIterator& pI)
	{
		return this->currentIndex == pI.currentIndex;
	}
	bool PolyIterator::operator!=(const PolyIterator& pI)
	{
		return this->currentIndex != pI.currentIndex;
	}
}
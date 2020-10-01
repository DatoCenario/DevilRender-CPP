#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Geometry.h"

namespace std
{
	class ObjParser
	{
	public:
		Primitive* readObjFile(string filePath);
		void writeObjFile(char* filePath, Primitive* primitive);

	private:
		void readVert(string& line, vector<float3>* vertices);

		void readTex(string& line, vector<float2>* texCoords);

		void readPoly(string& line, vector<int>* ind, vector<int>* tInd, vector<int>* nInd, const vector<float3>* vert);

		vector<string> split(const string& str, const vector<char>& delimiters);
	};
}
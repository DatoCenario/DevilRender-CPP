
#include "ObjParser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace std
{
	Primitive* ObjParser::readObjFile(string filePath)
	{
		auto vert = new vector<float3>();
		auto norm = new vector<float3>();
		auto tex = new vector<float2>();
		auto ind = new vector<int>();
		auto tInd = new vector<int>();
		auto nInd = new vector<int>();

		ifstream in = ifstream();
		string line;
		in.open(filePath);
		if (!in.is_open())
		{
			cerr << "an error occured in openning file";
		}
		while (getline(in, line))
		{
			string l;
			if (line[0] == 'v')
			{
				switch (line[1])
				{
				case ' ':
					l = line.substr(2);
					readVert(l, vert);
					break;
				case 't':
					l = line.substr(3);
					readTex(l, tex);
					break;
				case 'n':
					l = line.substr(3);
					readVert(l, norm);
					break;
				}
			}
			else if (line[0] == 'f')
			{
				l = line.substr(2);
				readPoly(l, ind, tInd, nInd, vert);
			}
		}
		return new Primitive(float3(0,0,0), vert, norm, tex, ind, nInd, tInd);
	}

	void ObjParser::readVert(string& line, vector<float3>* vertices)
	{
		istringstream v(line);
		float x, y, z;
		v >> x; v >> y; v >> z;
		vertices->push_back(float3(x, y, z));
	}

	void ObjParser::readTex(string& line, vector<float2>* texCoords)
	{
		istringstream v(line);
		float x, y;
		v >> x; v >> y;
		texCoords->push_back(float2(x, y));
	}

	void ObjParser::readPoly(string& line, vector<int>* ind, vector<int>* tInd, vector<int>* nInd, const vector<float3>* vert)
	{
		//vector<string> indSet;
		//for (size_t i = 0; i < sp.size(); i++)
		//{
		//	sps.push_back(split(sp[i], { '/' }));
		//}
		//for (size_t i = 0; i < sps.size() - 2; i++)
		//{
		//	ind->push_back(stoi(sps[0][0]) - 1);
		//	ind->push_back(stoi(sps[i + 1][0]) - 1);
		//	ind->push_back(stoi(sps[i + 2][0]) - 1);

		//	if (sps[0].size() > 1)
		//	{
		//		tInd->push_back(stoi(sps[0][1]) - 1);
		//		tInd->push_back(stoi(sps[i + 1][1]) - 1);
		//		tInd->push_back(stoi(sps[i + 2][1]) - 1);
		//	}
		//	if (sps[0].size() > 2)
		//	{
		//		nInd->push_back(stoi(sps[0][2]) - 1);
		//		nInd->push_back(stoi(sps[i + 1][2]) - 1);
		//		nInd->push_back(stoi(sps[i + 2][2]) - 1);
		//	}
		//}
	}

	vector<string> ObjParser::split(const string& str, const vector<char>& delimiters)
	{
		vector<string> strings = vector<string>();
		string current = string();
		for (size_t i = 0; i < str.size(); i++)
		{
			bool delim = false;
			for (auto d : delimiters)
				if (str[i] == d)
				{
					delim = true;
					strings.push_back(current);
					current = string();
					break;
				}
			if (!delim)
			{
				current.insert(current.size(), { str[i] });
			}
		}
		if (current.size() != 0)
		{
			strings.push_back(current);
		}
		return strings;
	}
}
#include "Rasterizer.h"

namespace std
{
	bool Rasterizer::observed(const Poly3D& poly)
	{
		return camera.inObserve(poly.v1.pos) ||
			   camera.inObserve(poly.v2.pos) ||
			   camera.inObserve(poly.v3.pos);
	}

	void Rasterizer::makeLocal(Poly3D& poly)
	{
		poly.v1.pos = camera.pivot.toLocalCoords(poly.v1.pos);
		poly.v2.pos = camera.pivot.toLocalCoords(poly.v2.pos);
		poly.v3.pos = camera.pivot.toLocalCoords(poly.v3.pos);
	}

	void Rasterizer::computePoly(Poly3D& poly)
	{
        float2 v1p = camera.proection(poly.v1.pos),
        v2p = camera.proection(poly.v2.pos),
        v3p = camera.proection(poly.v3.pos);

        if (v1p.x > v2p.x) { f3swap(poly.v1.pos, poly.v2.pos); f2swap(v1p, v2p); }
        if (v2p.x > v3p.x) { f3swap(poly.v2.pos, poly.v3.pos); f2swap(v2p, v3p); }
        if (v1p.x > v2p.x) { f3swap(poly.v1.pos, poly.v2.pos); f2swap(v1p, v2p); }

        int x1 = (int)v1p.x;
        int x2 = (int)v2p.x;
        int x3 = (int)v3p.x;

        int x12 = x2 - x1;
        int x13 = x3 - x1;
        int x32 = x3 - x2;

        float3 u, d, du, dd, nu, nd, dnu, dnd;
        float2 tu, td, dtu, dtd;
        float pu, pd, dpu, dpd;
        int rDiff;

        if (x2 > 0 && x1 < camera.width)
        {
            u = poly.v1.pos;
            d = poly.v1.pos;
            tu = poly.v1.texCoord;
            td = poly.v1.texCoord;
            nu = poly.v1.normal;
            nd = poly.v1.normal;
            pu = v1p.y;
            pd = v1p.y;

            if (x12 != 0)
            {
                dpu = (v2p.y - v1p.y) / x12;
                dpd = (v3p.y - v1p.y) / x13;

                if (dpu > dpd)
                {
                    du = (poly.v2.pos - poly.v1.pos) / x12;
                    dtu = (poly.v2.texCoord - poly.v1.texCoord) / x12;
                    dnu = (poly.v2.normal - poly.v1.normal) / x12;

                    dd = (poly.v3.pos - poly.v1.pos) / x13;
                    dtd = (poly.v3.texCoord - poly.v1.texCoord) / x13;
                    dnd = (poly.v3.normal - poly.v1.normal) / x13;
                }
                else
                {
                    float t = dpu; dpu = dpd; dpd = t;

                    du = (poly.v3.pos - poly.v1.pos) / x13;
                    dtu = (poly.v3.texCoord - poly.v1.texCoord) / x13;
                    dnu = (poly.v3.normal - poly.v1.normal) / x13;

                    dd = (poly.v2.pos - poly.v1.pos) / x12;
                    dtd = (poly.v2.texCoord - poly.v1.texCoord) / x12;
                    dnd = (poly.v2.normal - poly.v1.normal) / x12;
                }
            }
            else
            {
                dpu = 0;
                dpd = 0;
                dtu = float2(0,0);
                dtd = float2(0,0);
                dnu = float3(0,0,0);
                dnd = float3(0,0,0);
                du = float3(0,0,0);
                dd = float3(0,0,0);
            }

            rDiff = camera.width - 1 - x2;

            if (rDiff < 0)
            {
                x12 += rDiff;
            }

            if (x1 < 0)
            {
                x12 += x1;
                u -= du * x1;
                d -= dd * x1;
                tu -= dtu * x1;
                td -= dtd * x1;
                nu -= dnu * x1;
                nd -= dnd * x1;
                pu -= dpu * x1;
                pd -= dpd * x1;
                x1 = 0;
            }

            //method for computing part of poly
            for (int i = 0; i <= x12; i++)
            {
                float3 pos = d;
                float3 norm = nd;
                float2 tex = td;
                float3 delta, deltaNormal;
                float2 deltaTexture;

                if (pu > 0)
                {
                    int steps;
                    int up = (int)pu, down = (int)pd;
                    int diffU = camera.height - 1 - up;

                    if (diffU < 0)
                    {
                        up = camera.height - 1;
                    }

                    steps = up - down;
                    if (steps != 0)
                    {
                        delta = (u - d) / steps;
                        deltaTexture = (tu - td) / steps;
                        deltaNormal = (nu - nd) / steps;
                    }
                    else
                    {
                        delta = float3(0,0,0);
                        deltaNormal = float3(0,0,0);
                        deltaTexture = float2(0,0);
                    }

                    if (down < 0)
                    {
                        pos -= delta * down;
                        tex -= deltaTexture * down;
                        norm -= deltaNormal * down;
                        steps += down;
                        down = 0;
                    }
                    int x = x1 + i;
                    for (int g = 0; g <= steps; g++)
                    {
                        int y = down + g;
                        int index = y * camera.width + x;
                        if (vbuffer[index].pos.z == 0)
                        {
                            vbuffer[index] = Vertex(pos, norm, tex, TGAColor(), poly.v1.prim);
                            visibleIndexes[visibleCount] = index;
                            visibleCount++;
                        }
                        else if (vbuffer[index].pos.z > pos.z)
                        {
                            vbuffer[index] = Vertex(pos, norm, tex, TGAColor(), poly.v1.prim);
                        }

                        pos += delta;
                        norm += deltaNormal;
                        tex += deltaTexture;
                    }
                }

                d += dd;
                u += du;
                pu += dpu;
                pd += dpd;
                nu += dnu;
                nd += dnd;
                tu += dtu;
                td += dtd;
            }
            //*method for computing part of poly

        }

        if (x2 < camera.width && x3 > 0)
        {
            u = poly.v3.pos;
            d = poly.v3.pos;
            tu = poly.v3.texCoord;
            td = poly.v3.texCoord;
            nu = poly.v3.normal;
            nd = poly.v3.normal;
            pu = v3p.y;
            pd = v3p.y;

            if (x32 != 0)
            {
                dpu = (v2p.y - v3p.y) / x32;
                dpd = (v1p.y - v3p.y) / x13;

                if (dpu > dpd)
                {
                    du = (poly.v2.pos - poly.v3.pos) / x32;
                    dtu = (poly.v2.texCoord - poly.v3.texCoord) / x32;
                    dnu = (poly.v2.normal - poly.v3.normal) / x32;

                    dd = (poly.v1.pos - poly.v3.pos) / x13;
                    dtd = (poly.v1.texCoord - poly.v3.texCoord) / x13;
                    dnd = (poly.v1.normal - poly.v3.normal) / x13;
                }
                else
                {
                    float t = dpu; dpu = dpd; dpd = t;

                    du = (poly.v1.pos - poly.v3.pos) / x13;
                    dtu = (poly.v1.texCoord - poly.v3.texCoord) / x13;
                    dnu = (poly.v1.normal - poly.v3.normal) / x13;

                    dd = (poly.v2.pos - poly.v3.pos) / x32;
                    dtd = (poly.v2.texCoord - poly.v3.texCoord) / x32;
                    dnd = (poly.v2.normal - poly.v3.normal) / x32;
                }
            }
            else
            {
                dpu = 0;
                dpd = 0;
                dtu = float2(0, 0);
                dtd = float2(0, 0);
                dnu = float3(0, 0, 0);
                dnd = float3(0, 0, 0);
                du = float3(0, 0, 0);
                dd = float3(0, 0, 0);
            }

            if (x2 < 0)
            {
                x32 += x2;
                x2 = 0;
            }

            rDiff = camera.width - 1 - x3;

            if (rDiff < 0)
            {
                x32 += rDiff;
                u -= du * rDiff;
                d -= dd * rDiff;
                tu -= dtu * rDiff;
                td -= dtd * rDiff;
                nu -= dnu * rDiff;
                nd -= dnd * rDiff;
                pu -= dpu * rDiff;
                pd -= dpd * rDiff;
                x3 = camera.width - 1;
            }

            //method for computing part of poly
            for (int i = 0; i <= x32; i++)
            {
                float3 pos = d;
                float3 norm = nd;
                float2 tex = td;
                float3 delta, deltaNormal;
                float2 deltaTexture;

                if (pu > 0)
                {
                    int steps;
                    int up = (int)pu, down = (int)pd;
                    int diffU = camera.height - 1 - up;

                    if (diffU < 0)
                    {
                        up = camera.height - 1;
                    }

                    steps = up - down;
                    if (steps != 0)
                    {
                        delta = (u - d) / steps;
                        deltaTexture = (tu - td) / steps;
                        deltaNormal = (nu - nd) / steps;
                    }
                    else
                    {
                        delta = float3(0, 0, 0);
                        deltaNormal = float3(0, 0, 0);
                        deltaTexture = float2(0, 0);
                    }

                    if (down < 0)
                    {
                        pos -= delta * down;
                        tex -= deltaTexture * down;
                        norm -= deltaNormal * down;
                        steps += down;
                        down = 0;
                    }

                    int x = x3 - i;
                    for (int g = 0; g <= steps; g++)
                    {
                        int y = down + g;
                        int index = y * camera.width + x;
                        if (vbuffer[index].pos.z == 0)
                        {
                            vbuffer[index] = Vertex(pos, norm, tex, TGAColor(), poly.v1.prim);
                            visibleIndexes[visibleCount] = index;
                            visibleCount++;
                        }
                        else if (vbuffer[index].pos.z > pos.z)
                        {
                            vbuffer[index] = Vertex(pos, norm, tex, TGAColor(), poly.v1.prim);
                        }

                        pos += delta;
                        norm += deltaNormal;
                        tex += deltaTexture;
                    }
                }

                d += dd;
                u += du;
                pu += dpu;
                pd += dpd;
                nu += dnu;
                nd += dnd;
                tu += dtu;
                td += dtd;
            }
            //*method for computing part of poly
        }
	}

	Rasterizer::Rasterizer(const Camera& cam)
	{
		camera = cam;
		int size = (camera.width) * (camera.height);
		vbufferSize = sizeof(Vertex) * size;
		visibleIndSize = sizeof(int) * size;
		vbuffer = (Vertex*)malloc(vbufferSize);
		visibleIndexes = (int*)malloc(visibleIndSize);
	}

	Rasterizer::~Rasterizer()
	{
		delete[] vbuffer;
		delete[] visibleIndexes;
	}

	void Rasterizer::initializeVBuffer(const vector<Primitive*>& primitives)
	{
		visibleCount = 0;
		memset(vbuffer , 0, vbufferSize);
		for (auto prim : primitives)
		{
			for (auto poly : *prim)
			{
				makeLocal(poly);
				if (observed(poly))
				{
					computePoly(poly);
				}
			}
		}
	}

	TGAImage* Rasterizer::computeShaders()
	{
		TGAImage* buffer = new TGAImage(camera.width, camera.height, 1);
		for (size_t i = 0; i < visibleCount; i++)
		{
			int index = visibleIndexes[i];
			Vertex v = vbuffer[index];
			for (size_t i = 0; i < v.prim->shadersLen(); i++)
			{
				Shader* sh = v.prim->getShader(i);
				sh->compute(v, camera);
			}
			buffer->set(index % camera.width, index / camera.width, v.color);
		}
		return buffer;
	}
}
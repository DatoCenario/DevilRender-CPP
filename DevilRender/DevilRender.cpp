// DevilRender.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Math.h"
#include "Geometry.h"
#include "Cube.h"
#include "Camera.h"
#include "Rasterizer.h"
#include "Windows.h"
#include "tgaImage.h"
#include "Poly.h"
#include "ObjParser.h"

using namespace std;








int main()
{

    vector<Primitive*> primitives = vector<Primitive*>();
    primitives.push_back(new Cube(float3(rand() % 200, rand() % 200, rand() % 200), 100));
    primitives.push_back(new Cube(float3(rand() % 500, rand() % 500, rand() % 500), 100));
    primitives.push_back(new Cube(float3(rand() % 500, rand() % 500, rand() % 500), 100));
    primitives.push_back(new Cube(float3(rand() % 500, rand() % 500, rand() % 500), 100));
    primitives.push_back(new Cube(float3(rand() % 500, rand() % 500, rand() % 500), 100));
    primitives.push_back(new Cube(float3(rand() % 500, rand() % 500, rand() % 500), 100));
    primitives.push_back(new Cube(float3(rand() % 500, rand() % 500, rand() % 500), 100));
    primitives[0]->addShader(new PhongModelShader(vector<Light>{Light(float3(0,0,0), 100.0)}));
    primitives[1]->addShader(new PhongModelShader(vector<Light>{Light(float3(0,0,0), 100.0)}));
    primitives[2]->addShader(new PhongModelShader(vector<Light>{Light(float3(0,0,0), 100.0)}));
    primitives[3]->addShader(new PhongModelShader(vector<Light>{Light(float3(0,0,0), 100.0)}));
    primitives[4]->addShader(new PhongModelShader(vector<Light>{Light(float3(0,0,0), 100.0)}));
    primitives[5]->addShader(new PhongModelShader(vector<Light>{Light(float3(0,0,0), 100.0)}));
    primitives[6]->addShader(new PhongModelShader(vector<Light>{Light(float3(0,0,0), 100.0)}));

    //primitives[0]->rotate(frand() * 3.14f , 'y');
    //primitives[1]->rotate(frand() * 3.14f , 'y');
    //primitives[2]->rotate(frand() * 3.14f , 'y');
    //primitives[3]->rotate(frand() * 3.14f , 'y');
    //primitives[4]->rotate(frand() * 3.14f , 'y');
    //primitives[5]->rotate(frand() * 3.14f , 'y');
    //primitives[6]->rotate(frand() * 3.14f , 'y');

    //primitives[0]->rotate(frand() * 3.14f, 'x');
    //primitives[1]->rotate(frand() * 3.14f, 'x');
    //primitives[2]->rotate(frand() * 3.14f, 'x');
    //primitives[3]->rotate(frand() * 3.14f, 'x');
    //primitives[4]->rotate(frand() * 3.14f, 'x');
    //primitives[5]->rotate(frand() * 3.14f, 'x');
    //primitives[6]->rotate(frand() * 3.14f, 'x');

    //primitives[0]->rotate(frand() * 3.14f, 'z');
    //primitives[1]->rotate(frand() * 3.14f, 'z');
    //primitives[2]->rotate(frand() * 3.14f, 'z');
    //primitives[3]->rotate(frand() * 3.14f, 'z');
    //primitives[4]->rotate(frand() * 3.14f, 'z');
    //primitives[5]->rotate(frand() * 3.14f, 'z');
    //primitives[6]->rotate(frand() * 3.14f, 'z');

    //Primitive* model = ObjParser().readObjFile("F:/c#/DevilRender/DevilRender/Models/sylvanas_obj.obj");
    //model->scale(10);
    //primitives.push_back(model);
    //primitives[0]->addShader(new PhongModelShader(vector<Light>{Light(float3(0, 500, -2000), 100.0)}));
    Camera cam = Camera(float3(0,0,-500), 1920,  1080, 1, 1.57f);
    Rasterizer rast = Rasterizer(cam);
    while (true)
    {
        rast.initializeVBuffer(primitives);
        TGAImage* std = rast.computeShaders();
        std->write_tga_file("F:/CODE/c++/tga from tiny/tinyrenderer-909fe20934ba5334144d2c748805690a1fa4c89f/image.tga");
        delete std;
    }
    int a = 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

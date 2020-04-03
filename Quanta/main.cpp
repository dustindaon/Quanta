#include "RenderingManager.h"
#include "Engine.h"
#include "SandCastlesManager.h"
#include <iostream>
#include "Matrix4.h"

using namespace std;
int main()
{
	Engine::Instance()->Start();
	SandCastlesManager::Instance();

	RenderingManager renderMan = RenderingManager();
	renderMan.Initiatiate();

	/*Matrix4 test1 = Matrix4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	Matrix4 test2 = Matrix4(1, 0, 0, 0,
							0, 1, 0, 0, 
							0, 0, 1, 0, 
							0, 0, 0, 1);
	Matrix4 test3 = Matrix4();

	float* data1 = test1.GetData();
	float* data2 = test2.GetData();
	float* data3 = test3.GetData();

	Vector4 testVec = Vector4(1, 2, 3, 4);
	Vector4 testVecMult = test2 * testVec;

	for (int i = 0; i < 16; ++i)
	{
		cout << " " << *(data1 + i);

		if ((i + 1) % 4 == 0)
		{
			cout << endl;
		}
	}
	cout << endl;

	for (int i = 0; i < 16; ++i)
	{
		cout << " " << *(data2 + i);

		if ((i + 1) % 4 == 0)
		{
			cout << endl;
		}
	}
	cout << endl;


	for (int i = 0; i < 16; ++i)
	{
		cout << " " << *(data3 + i);

		if ((i + 1) % 4 == 0)
		{
			cout << endl;
		}
	}

	cout << testVecMult.GetX() << endl;
	cout << testVecMult.GetY() << endl;
	cout << testVecMult.GetZ() << endl;
	cout << testVecMult.GetW() << endl;*/

	return 0;
}
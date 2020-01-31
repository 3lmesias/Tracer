// Tracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Lib/stb_image.h"
#include <iostream>
#include <fstream>  

int main()
{
	std::ofstream imgfile("image.ppm");
	int nx = 200;
	int ny = 100;

	//std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	imgfile<< "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++) 
		{
			float r = float(i) / float(nx); // 0 - 1
			float g = float(j) / float(ny); // 1 - 0
			float b = 0.2;
			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);
			//std::cout << ir <<" "<< ig << " " << ib << "\n";
			imgfile << ir << " " << ig << " " << ib << "\n";
		}
	}
	imgfile.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

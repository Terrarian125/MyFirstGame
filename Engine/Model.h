#pragma once
#include <string>
#include <vector>
#include "fbx.h"

namespace Model
{
	struct ModelData
	{
		Fbx* pfbx_;
		Transform transform_;
		std::string filename_;
	};
	int Load(std::string fileName);
	void SetTransform(int hmodele, Transform transform);
	void Draw(int hmodel);
	void Release();
}
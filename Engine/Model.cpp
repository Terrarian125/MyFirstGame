#include "Model.h"

namespace Model
{
	std::vector<ModelData*> modelList;
}

int Model::Load(std::string fileName)
{
	ModelData* pModelData = new ModelData();
	pModelData->filename_ = fileName;
	pModelData->pfbx_ = nullptr;

	for (auto& itr : modelList)
	{
		if (itr->filename_ == fileName)
		{
			pModelData->pfbx_ = itr->pfbx_;
			break;
		}
	}

	if (pModelData->pfbx_ == nullptr)
	{
		pModelData->pfbx_ = new Fbx();
		pModelData->pfbx_->Load(fileName.c_str());
	}
	modelList.push_back(pModelData);
	return((int)(modelList.size() - 1));

}

void Model::SetTransform(int hmodele, Transform transform)
{
	modelList[hmodele]->transform_ = transform;
}

void Model::Draw(int hmodel)
{
	modelList[hmodel]->pfbx_->Draw(modelList[hmodel]->transform_);
}

void Model::Release()
{
}

#pragma once

#include <nsmb_nitro.hpp>


//vtable 0203c4bc
class ModelBase
{
public:

	NNSG3dRenderObj renderObj;

	//02019c08
	ModelBase();

	//D0:02019bd8
	//D1:02019bf8
	//D2:02019bc8
	virtual ~ModelBase();

	//02019b7c
	static NNSG3dResMdl* loadModel(void* bmd, u32 modelID, NNSG3dResTex** texture);	//Loads the model with ID modelID from the NSBMD-file pointed to by bmd and outputs texture (if a valid one has been found). returns a pointer to the model if successful, a nullptr otherwise.

};
NTR_SIZE_GUARD(ModelBase, 0x58);

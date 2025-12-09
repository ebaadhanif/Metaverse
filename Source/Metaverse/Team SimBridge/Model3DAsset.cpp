// Class Added by Ebaad, This class is parent class for FBX Asset Class and Obj Asset Class and deals with pure virtual functions 
#include "Model3DAsset.h"
#include <IImageWrapperModule.h>


UTexture2D* UModel3DAsset::LoadIRTexture()
{
	FString FolderName;


	FString FullPath =FPaths::GetPath( FolderPath )+"/"+ _modelConfig.ModelInfo.IRTextureName;

	TArray<uint8> FileData;
	if (!FFileHelper::LoadFileToArray(FileData, *FullPath))
	{
		return nullptr;
	}
	IImageWrapperModule& ImgWrapperMod = FModuleManager::LoadModuleChecked <IImageWrapperModule>(TEXT("ImageWrapper"));
	TSharedPtr<IImageWrapper> Wrapper = ImgWrapperMod.CreateImageWrapper(EImageFormat::PNG);

	if (Wrapper.IsValid() && Wrapper->SetCompressed(FileData.GetData(), FileData.Num())) {

		TArray<uint8> RawData;
		if (Wrapper->GetRaw(ERGBFormat::BGRA, 8, RawData)) {

			UTexture2D* Tex = UTexture2D::CreateTransient(Wrapper->GetWidth(), Wrapper->GetHeight(), PF_B8G8R8A8);
			if (!Tex) return nullptr;

			void* TextureData = Tex->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, RawData.GetData(), RawData.Num());

			Tex->GetPlatformData()->Mips[0].BulkData.Unlock();
			//Tex->UpdateResource();
			return Tex;
		}
	}
	return nullptr;
}


FString UModel3DAsset::ExtractModelNameFromPath(const FString& Path)
{
    return FPaths::GetBaseFilename(Path);
}




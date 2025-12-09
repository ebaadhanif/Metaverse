// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class METAVERSE_API MetaverseLogger
{
private:
	static MetaverseLogger* m_pMetaverseLoggerInstance;
	FString LogFilePath;
	MetaverseLogger();

public:
	static MetaverseLogger* GetMetaverseLoggerInstance();
	static void setMetaverseLoggerInstance(MetaverseLogger* instance);
	void AddLog(const FString& log);
	~MetaverseLogger();
};

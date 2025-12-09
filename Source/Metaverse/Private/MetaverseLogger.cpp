// Fill out your copyright notice in the Description page of Project Settings.


#include "MetaverseLogger.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include"HAL/PlatformFileManager.h"
#include"HAL/FileManager.h"

MetaverseLogger::MetaverseLogger()
{
	FString TimeStamp = *FDateTime::Now().ToString();
	LogFilePath = FPaths::ProjectContentDir() + "Archive/Log Files/"+TimeStamp+" LogFile.txt";
}

MetaverseLogger::~MetaverseLogger()
{
}


MetaverseLogger* MetaverseLogger::m_pMetaverseLoggerInstance = NULL;
MetaverseLogger* MetaverseLogger::GetMetaverseLoggerInstance()
{
	if (m_pMetaverseLoggerInstance == nullptr)
	{
		m_pMetaverseLoggerInstance = new MetaverseLogger();
	}
	return m_pMetaverseLoggerInstance;
}

void MetaverseLogger::setMetaverseLoggerInstance(MetaverseLogger* instance)
{
	m_pMetaverseLoggerInstance = instance;
}



void MetaverseLogger::AddLog(const FString& log)
{
	IFileHandle* FileHandle = FPlatformFileManager::Get().GetPlatformFile().OpenWrite(*LogFilePath, true);
	if (!FileHandle)
	{
		return;
	}

	//format msg with TimeStamp
	FString FormattedMsg = FString::Printf(TEXT("[%s]	%s\n"), *FDateTime::Now().ToString(), *log);

	//convert string to UTF-8 for writing
	FTCHARToUTF8 Converter(*FormattedMsg);
	const uint8* Buffer = reinterpret_cast<const uint8*>(Converter.Get());
	int32 Length = Converter.Length();

	//Write to the file
	if (!FileHandle->Write(Buffer, Length))
	{
		delete FileHandle;
		return;
	}
	
	//flush to ensure data is written immediately
	FileHandle->Flush();

	delete FileHandle;

}


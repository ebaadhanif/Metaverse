#pragma once

#include <DISUtils/DISDefinitions.h>

#include<vector>
#include<stdlib.h>
#include<string>
#include <DIS7\msLibMacro.h>

namespace DIS
{
#define MAX_PATH 260

	struct ENUM_PARAMETERS
	{
		int						code;
		std::string				name;
		EntityType			entityType;
		EntityTypeDescription	entityTypeDesc;
		EntityType			alternateEntityType;
		EntityTypeDescription	alternateEntityTypeDesc;
		std::string				description;
		float					rcs;
	};

	class EXPORT_MACRO CDISEnumerationsManager
	{
	private:
		std::vector<ENUM_PARAMETERS>	 _vecEnums;
		CDISEnumerationsManager();
		static  CDISEnumerationsManager* _instance;
	public:

		static CDISEnumerationsManager* GetInstance();
		~CDISEnumerationsManager();

	private:
		void ReadEnumerationsFromFile();
		bool CompareEntityTypesForDefaultType(EntityType entityType, EntityType typeToCompare, bool compareCountry, bool compareCategory, bool compareSubCategory);

	public:
		std::string						GetEntityNameByAFISEEntityID(int afiseEntityID);
		EntityTypeWithDescription		GetEntityTypeByAFISEEntityID(int afiseEntityID);
		EntityTypeWithDescription		GetAlternateEntityTypeByAFISEEntityID(int afiseEntityID);
		int								GetAFISEEntityIDByEntityType(EntityType entityType, bool findDefault = false/*If not found any*/);

		float GetRCSByDISEntityType(EntityType entityType);
		float GetRCSByAFISEEntityID(int afiseEntityID);
	};
}


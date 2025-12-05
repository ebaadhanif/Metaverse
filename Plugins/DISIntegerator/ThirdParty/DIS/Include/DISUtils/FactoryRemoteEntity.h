#pragma once

#include <DISUtils/RemoteEntity.h>
#include <DISUtils/DISDefinitions.h>
#include <DIS7/EntityType.h>
#include <DIS7\msLibMacro.h>

namespace DIS
{
	class EXPORT_MACRO CFactoryRemoteEntity
	{
	private:
		CFactoryRemoteEntity(void);
		~CFactoryRemoteEntity(void);

	public:
		static CRemoteEntity* GetRemoteEntityObj(EntityType eType);
		static MunitionDescriptorRecord GetMunitionDescriptor(int afiseEntityType);
	};
}

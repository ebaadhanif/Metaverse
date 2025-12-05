#pragma once

#include <DISUtils/DRAlgorithm.h>

namespace DIS
{
	class EXPORT_MACRO CFactoryDrAlgorithm
	{
	public:
		CFactoryDrAlgorithm(void);
		~CFactoryDrAlgorithm(void);
		CDRAlgorithm* GetDrAlgorithmObj(int drAlgo);
	};
}

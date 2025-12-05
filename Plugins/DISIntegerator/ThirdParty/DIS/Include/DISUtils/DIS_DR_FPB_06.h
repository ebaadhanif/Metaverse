#pragma once
#include <DISUtils/DRAlgorithm.h>
#include <DIS7\msLibMacro.h>

namespace DIS
{
	class EXPORT_MACRO CDIS_DR_FPB_06 : public CDRAlgorithm
	{
	public:
		CDIS_DR_FPB_06(void);
		~CDIS_DR_FPB_06(void);

		void Render(float changeDelta, unsigned short applicationType);
		void Interpolate(float changeDelta, double lerpFactor, Vector3Double startPoint, Vector3Double controlPoint, Vector3Double predictedPoint);
	};
}

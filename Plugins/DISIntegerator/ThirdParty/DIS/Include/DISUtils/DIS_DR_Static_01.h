#pragma once
#include <DISUtils/DRAlgorithm.h>

namespace DIS
{
	class EXPORT_MACRO CDIS_DR_Static_01 : public CDRAlgorithm
	{
	public:
		CDIS_DR_Static_01(void);
		~CDIS_DR_Static_01(void);

		void Render(float changeDelta, unsigned short applicationType);
		void Interpolate(float changeDelta, double lerpFactor, Vector3Double startPoint, Vector3Double controlPoint, Vector3Double predictedPoint);
	};
}

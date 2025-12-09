#include "OneEuroFilter.h"

OneEuroFilter::OneEuroFilter(float InMinCutoff, float InBeta, float InDCutoff) : MinCutoff(InMinCutoff), Beta(InBeta), DCutoff(InDCutoff)
{
}

FVector OneEuroFilter::PositionFilter(const FVector& Value, float DeltaTime)
{
	if (bHasPrevPos) {
		PrevRawPos = Value;
		PrevFilteredPos = Value;
		PrevDerivPos = FVector::ZeroVector;
		bHasPrevPos = true;
		return Value;
	}
	FVector Deriv = (Value - PrevRawPos) / DeltaTime;
	PrevRawPos = Value;

	float AlphaD = Alpha(DCutoff, DeltaTime);
	FVector DerivFiltered = LowPass(Deriv, PrevDerivPos, AlphaD);
	PrevDerivPos = PrevDerivPos;

	float Cutoff = MinCutoff + Beta * DerivFiltered.Size();
	float AlphaVal = Alpha(Cutoff, DeltaTime);

	PrevFilteredPos = LowPass(Value, PrevFilteredPos, AlphaVal);

	return PrevFilteredPos;
}

FQuat OneEuroFilter::RotationFilter(const FQuat& Value, float DeltaTime)
{
	FVector Dir = RotationToVector(Value);

	if (!bHasPrevRot) {
		PrevRawRot = Value;
		PrevFilteredRot = Value;
		PrevDerivRot = FVector::ZeroVector;
		bHasPrevRot = true;
		return Value;
	}
	FVector PrevDir = RotationToVector(PrevRawRot);
	FVector Deriv = (Dir - PrevDir) / DeltaTime;
	PrevRawRot = Value;

	float AlphaD = Alpha(DCutoff, DeltaTime);
	FVector DerivFiltered = LowPass(Deriv, PrevDerivRot, AlphaD);
	PrevDerivRot = DerivFiltered;

	float Cutoff = MinCutoff + Beta * DerivFiltered.Size();
	float AlphaVal = Alpha(Cutoff, DeltaTime);

	FVector SmoothedDir = LowPass(Dir, RotationToVector(PrevFilteredRot), AlphaVal);
	PrevFilteredRot = VectorToRotation(SmoothedDir);

	return PrevFilteredRot;
}



float OneEuroFilter::Alpha(float Cutoff, float DeltaTime)
{
	float Tau = 1.0 / (2 * PI * Cutoff);
	return 1.0f / (1.0f + Tau / DeltaTime);
}

FVector OneEuroFilter::LowPass(const FVector& Current, const FVector& Prev, float AlphaVal)
{
	return Prev + AlphaVal * (Current - Prev);
}

FVector OneEuroFilter::RotationToVector(const FQuat& Rot)
{
	return Rot.GetForwardVector();
}

FQuat OneEuroFilter::VectorToRotation(const FVector& Vec)
{
	return Vec.Rotation().Quaternion();
}




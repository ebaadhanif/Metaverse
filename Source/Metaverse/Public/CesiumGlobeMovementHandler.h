#pragma once
#include "CoreMinimal.h"
#include "CesiumGeoreference.h"
#include "Engine/World.h"

struct FTween
{
    bool    bActive = false;
    double  T = 0.0;
    double  Duration = 0.5;

    // endpoints
    FVector StartPos, EndPos;
    FQuat   StartRot, EndRot;

    // spherical-safe extras
    bool    bUseSafeSpherical = false;
    FVector Center;            // globe center (use your RefPosUU)
    double  ClearanceUU = 300000.0; // push path this far outside the smaller endpoint radius
    FVector Dir0, Dir1;        // normalized directions from Center to endpoints
    double  R0 = 0.0, R1 = 0.0;

    static double EaseInOut(double t)
    {
        return (t < 0.5) ? (2.0 * t * t) : (1.0 - FMath::Pow(-2.0 * t + 2.0, 2.0) / 2.0);
    }

    // legacy linear begin (kept for compatibility)
    void Begin(const FVector& SP, const FQuat& SR, const FVector& EP, const FQuat& ER, double Dur)
    {
        StartPos = SP; StartRot = SR; EndPos = EP; EndRot = ER;
        Duration = FMath::Max(1e-3, Dur);
        T = 0.0;
        bActive = true;
        bUseSafeSpherical = false;
    }

    // NEW: spherical/clearance-safe begin
    void BeginSafe(const FVector& SP, const FQuat& SR,
        const FVector& EP, const FQuat& ER,
        double Dur,
        const FVector& InCenter,
        double InClearanceUU /*~300 800 km in UU, tune to taste*/)
    {
        Begin(SP, SR, EP, ER, Dur);
        bUseSafeSpherical = true;
        Center = InCenter;
        ClearanceUU = FMath::Max(0.0, InClearanceUU);

        Dir0 = (SP - Center).GetSafeNormal();
        Dir1 = (EP - Center).GetSafeNormal();
        R0 = FVector::Dist(SP, Center);
        R1 = FVector::Dist(EP, Center);

        if (Dir0.IsNearlyZero() || Dir1.IsNearlyZero())
            bUseSafeSpherical = false; // fall back to linear if degenerate
    }

    bool Tick(double dt, USceneComponent* Root)
    {
        if (!bActive || !Root) return true;

        T = FMath::Min(1.0, T + dt / Duration);
        const double k = EaseInOut(T);

        // interpolate rotation first (unchanged)
        const FQuat R = FQuat::Slerp(StartRot, EndRot, k);

        FVector P;
        if (bUseSafeSpherical)
        {
            // direction lerp around globe (normalize to keep on sphere-like arc)
            FVector Dir = (Dir0 * (1.0 - k) + Dir1 * k).GetSafeNormal();
            if (Dir.IsNearlyZero())
            {
                // emergency fallback: project linear point outward
                const FVector Plinear = FMath::Lerp(StartPos, EndPos, k);
                Dir = (Plinear - Center).GetSafeNormal();
            }

            // radius lerp but never go inside min endpoint radius + clearance
            double Rlin = FMath::Lerp(R0, R1, k);
            const double RminAllowed = FMath::Min(R0, R1) + ClearanceUU;
            if (Rlin < RminAllowed) Rlin = RminAllowed;

            P = Center + Dir * Rlin;
        }
        else
        {
            // original straight-line tween
            P = FMath::Lerp(StartPos, EndPos, k);
        }

        Root->SetWorldLocation(P);
        Root->SetWorldRotation(R);

        if (T >= 1.0) { bActive = false; return true; }
        return false;
    }
};
static FTween Tween;
enum class EState : uint8 { Normal, AtOrigin, Tweener };

class METAVERSE_API CesiumGlobeMovementHandler
{
public:
	~CesiumGlobeMovementHandler();
	void CustomGlobeMovementBeginPlay(UWorld* myWorld);
	static CesiumGlobeMovementHandler* GetInstance();
	void CesiumGlobeMovementHandlerCustomTick(float DeltaSeconds);
	UPROPERTY(EditAnywhere, Category = "Pinch Orbit")
	bool    bPinchActiveLatched = false;
	UPROPERTY(EditAnywhere, Category = "Pinch Orbit")
	FVector PrevSmMid = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Pinch Orbit")
	FVector BaseMid = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Pinch Orbit")
	bool    bArmed = false;
	const double HMin = 400.0;     // height where you want MinDeg
	const double HMax = 100000.0;
	UPROPERTY(EditAnywhere, Category = "Pinch Orbit")
	float MinDegPerSec = 0.008f;
	UPROPERTY(EditAnywhere, Category = "Pinch Orbit")
	float MaxDegPerSec = 8.0f;
	UPROPERTY(EditAnywhere, Category = "XR|Ray")
	float RotSmoothHz = 12.f;
	float   HandDeltaMaxUU = 60.0f;
	float   PinchSmoothHz = 8.0f;
	double LastEarthCenterRefreshTime = -1.0;
	float EarthCenterRefreshInterval = 0.25f;

	//MOVE ACTOR WITH SPEED::


	bool bInit = false;
	FVector PreEntryDirUnit = FVector::ForwardVector;
	double PrevHeightM = 0.0;
	bool bEntryArmedByAlt = false;
	UPROPERTY(EditAnywhere, Category = "Orbit|Entry")
	double EntryHeightM = 10000000.0;
	UPROPERTY(EditAnywhere, Category = "Orbit|Entry")
	double ExitHeightM = 1000000.0;
	double ExitDownHysteresisM = 100.0;
	EState State = EState::Normal;
	double EntryUpHysteresisM = 100.0;
	FVector EnterPosition = FVector::ZeroVector;
	FRotator enterRotaion;
	const double OriginLonDeg = 72.4;
	const double OriginLatDeg = 33.8692;
	UPROPERTY(EditAnywhere, Category = "EXIT|LAT")
	double ExitLat = 37;
	const double MaxOutHeightM = 3.0e7;
	const double OriginHeightM = 700000.0;
	const double EntryLerpSec = 0.80;
	bool  bTweeningExit = false;

	float Distance = 0.0f;
	APlayerController* PlayerControllerRef = nullptr;
	APlayerCameraManager* CamManager;
private:

	ACesiumGeoreference* m_DefaultGeoreferenceActor = nullptr;
	FVector CachedEarthCenterUU = FVector::ZeroVector;
	CesiumGlobeMovementHandler();
	static CesiumGlobeMovementHandler* CesiumGlobeMovementHandlerInstance;
	void GlobeMovementHandler(float DeltaSeconds);
	void PanOrbitAroundCesiumCenter_Stable(
		const TArray<FVector>& RightHandPositions, // note: const ref
		bool bPinchActive,
		float DeltaSeconds);
	void RefreshEarthCenterIfNeeded();
	FVector UnrealFromLLH(double LonDeg, double LatDeg, double HeightMeters) const;
	double GetHeightM() const;
	double GetHeightMAtPos(const FVector& Pos) const;
	FRotator MakeUprightRotAtPos(const FVector& Pos, const FVector& PrefFwd) const;
	FRotator MakeLookAtEarthRotAtPos(const FVector& Pos) const;
	void MoveActorWithSpeed(float Speed, float DeltaTime);
};

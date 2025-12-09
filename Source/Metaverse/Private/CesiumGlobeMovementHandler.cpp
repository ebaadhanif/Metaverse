
#include "CesiumGlobeMovementHandler.h"
#include "../../../Plugins/MetaverseXRSystem/Source/MetaverseXRSystem/Public/HanTracking.h"
#include <Kismet/KismetMathLibrary.h>
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include <Metaverse/Team Visioneers/DisplayManager.h>
CesiumGlobeMovementHandler* CesiumGlobeMovementHandler::CesiumGlobeMovementHandlerInstance = nullptr;
CesiumGlobeMovementHandler::CesiumGlobeMovementHandler()
{
}

CesiumGlobeMovementHandler::~CesiumGlobeMovementHandler()
{
}


CesiumGlobeMovementHandler* CesiumGlobeMovementHandler::GetInstance()
{
    if (CesiumGlobeMovementHandlerInstance == nullptr)
    {
        CesiumGlobeMovementHandlerInstance = new CesiumGlobeMovementHandler();
    }
    return CesiumGlobeMovementHandlerInstance;
}

void CesiumGlobeMovementHandler::CustomGlobeMovementBeginPlay(UWorld* myWorld)
{

    for (TActorIterator<ACesiumGeoreference> It(myWorld); It; ++It) {
        m_DefaultGeoreferenceActor = *It;
        break;
    }
    PlayerControllerRef = UGameplayStatics::GetPlayerController(myWorld, 0);
    CamManager = UGameplayStatics::GetPlayerCameraManager(myWorld, 0);

}
void CesiumGlobeMovementHandler::CesiumGlobeMovementHandlerCustomTick(float DeltaSeconds)
{
    if (ADisplayManager::GetInstance()->HandTrackingActor != nullptr && ADisplayManager::GetInstance()->isVRMode)
    {
        GlobeMovementHandler(DeltaSeconds);
    }

}

void CesiumGlobeMovementHandler::MoveActorWithSpeed(float Speed, float DeltaTime)
{
    if (!m_DefaultGeoreferenceActor) return;

    RefreshEarthCenterIfNeeded();

    // ---------------- Init ----------------
    if (!bInit)
    {
        bInit = true;
        PreEntryDirUnit = PlayerControllerRef->GetPawn()->GetActorForwardVector().GetSafeNormal();
        if (PreEntryDirUnit.IsNearlyZero()) PreEntryDirUnit = FVector::ForwardVector;

        PrevHeightM = GetHeightM();
        bEntryArmedByAlt = (PrevHeightM <= EntryHeightM - ExitDownHysteresisM);
        State = EState::Normal;
    }

    const bool bZoomIn = (Speed >= 0.f);
    const bool bZoomOut = !bZoomIn;

    // ---------------- Tween tick ----------------
    if (Tween.bActive)
    {
        if (USceneComponent* Root = PlayerControllerRef->GetPawn()->GetRootComponent())
        {
            const bool bDone = Tween.Tick(DeltaTime, Root);
            if (!bDone) { PrevHeightM = GetHeightM(); return; }
        }
    }

    const double HeightM = GetHeightM();

    // ---------------- ENTRY ----------------
    if (State == EState::Normal)
    {
        if (!bEntryArmedByAlt && HeightM <= EntryHeightM - ExitDownHysteresisM)
            bEntryArmedByAlt = true;

        const bool bCrossedUp =
            bEntryArmedByAlt &&
            PrevHeightM < (EntryHeightM + EntryUpHysteresisM) &&
            HeightM <= (EntryHeightM + EntryUpHysteresisM);

        if (bCrossedUp)
        {
            // remember where & how we entered (for returning later)
            EnterPosition = PlayerControllerRef->GetPawn()->GetActorLocation();
            enterRotaion = PlayerControllerRef->GetPawn()->GetActorRotation();
            // CachedGeo->SetOriginLongitudeLatitudeHeight(FVector(OriginLonDeg, OriginLatDeg, 300.0));

            const FVector TargetPos = UnrealFromLLH(OriginLonDeg, OriginLatDeg, OriginHeightM);

            // End rotation: tangent/upright at the target
            const FVector prefFwd = (AHanTracking::GetInstance()->CamManager ? AHanTracking::GetInstance()->CamManager->GetActorForwardVector() : PlayerControllerRef->GetPawn()->GetActorForwardVector());
            const FRotator UprightEndRot = MakeUprightRotAtPos(TargetPos, prefFwd);
            const FQuat StartRot = PlayerControllerRef->GetPawn()->GetActorQuat();
            const FQuat EndRot = UprightEndRot.Quaternion();

            if (USceneComponent* Root = PlayerControllerRef->GetPawn()->GetRootComponent())
            {
                Tween.Begin(PlayerControllerRef->GetPawn()->GetActorLocation(), StartRot, TargetPos, EndRot, EntryLerpSec);
                bTweeningExit = false;   // this is the entry tween
                State = EState::Tweener;
            }
            else
            {
                PlayerControllerRef->GetPawn()->SetActorLocation(TargetPos);
                PlayerControllerRef->GetPawn()->SetActorRotation(UprightEndRot); // snap upright if not tweening
                State = EState::AtOrigin;
            }

            bEntryArmedByAlt = false;
            PrevHeightM = HeightM;
            return;
        }
    }

    // ---------------- tween end ----------------
    if (State == EState::Tweener && !Tween.bActive)
    {
        if (bTweeningExit)
        {
            // exit tween finished -> back to Normal flight
            bTweeningExit = false;

            // ensure movement resumes the same way we entered
            FVector StraightDir = enterRotaion.Vector().GetSafeNormal();
            if (StraightDir.IsNearlyZero()) StraightDir = PlayerControllerRef->GetPawn()->GetActorForwardVector().GetSafeNormal();
            PreEntryDirUnit = StraightDir;

            State = EState::Normal;
            bEntryArmedByAlt = true; // allow future re-entry
            PrevHeightM = GetHeightM();
        }
        else
        {
            // entry tween finished -> now at origin
            State = EState::AtOrigin;
        }
    }

    // ---------------- EXIT (tween back to entry pose) ----------------
    if (State == EState::AtOrigin && bZoomOut)
    {
        const bool bCrossedDown =
            PrevHeightM > (ExitHeightM - ExitDownHysteresisM) &&
            HeightM >= (ExitHeightM - ExitDownHysteresisM);

        if (bCrossedDown)
        {
            const FQuat StartRot = PlayerControllerRef->GetPawn()->GetActorQuat();
            const FQuat EndRot = FRotator(0.0f, 0.0f, 0.0f).Quaternion();
            // CachedGeo->SetOriginLongitudeLatitudeHeight(FVector(90.0, 139.142919, 300.0));
            // RefreshEarthCenterIfNeeded();
            // FVector Exit = UnrealFromLLH(OriginLonDeg, ExitLat, 100000000.0);
            if (USceneComponent* Root = PlayerControllerRef->GetPawn()->GetRootComponent())
            {

                Tween.Begin(PlayerControllerRef->GetPawn()->GetActorLocation(), StartRot, FVector(-1780617510.000000, 0.000000, -182580580.000000), EndRot, EntryLerpSec);
                PlayerControllerRef->GetPawn()->AddActorLocalRotation(enterRotaion);
                bTweeningExit = true;
                State = EState::Tweener;
            }
            else
            {
                // Fallback: snap if no tween
                PlayerControllerRef->GetPawn()->SetActorLocation(FVector(-1780617510.000000, 0.000000, -182580580.000000));
                PlayerControllerRef->GetPawn()->SetActorRotation(enterRotaion);



                State = EState::Normal;
                bEntryArmedByAlt = true;
                PrevHeightM = GetHeightM();
            }
        }
    }

    // ---------------- Movement (+ zoom-out height cap) ----------------
    FVector OutwardDir;

    // Radial outward from Earth center (always well-defined unless at center)
    {
        const FVector EarthToActor = PlayerControllerRef->GetPawn()->GetActorLocation() - CachedEarthCenterUU;
        OutwardDir = EarthToActor.IsNearlyZero()
            ? (CamManager ? CamManager->GetActorForwardVector() : PlayerControllerRef->GetPawn()->GetActorForwardVector()).GetSafeNormal()
            : EarthToActor.GetSafeNormal();
    }

    FVector MoveDir;
    if (State == EState::AtOrigin)
    {
        // Near/origin: free-look uses camera/actor forward


        MoveDir = (CamManager ? CamManager->GetActorForwardVector() : PlayerControllerRef->GetPawn()->GetActorForwardVector()).GetSafeNormal();
    }
    else
    {
        // In space: always radial. Speed sign decides inward vs outward.
        // Speed > 0 => inward; Speed < 0 => outward (use abs speed after picking direction)
        MoveDir = -OutwardDir;
    }


    FVector MoveDelta = MoveDir * Speed * DeltaTime;


    if (bZoomOut && !MoveDelta.IsNearlyZero())
    {
        const FVector CurrPos = PlayerControllerRef->GetPawn()->GetActorLocation();

        const double  nextH = GetHeightMAtPos(CurrPos + MoveDelta);

        if (nextH > MaxOutHeightM && HeightM < MaxOutHeightM && Speed < 0)
        {

            MoveDelta = FVector::ZeroVector;

        }
    }

    if (USceneComponent* Root = PlayerControllerRef->GetPawn()->GetRootComponent())
    {
        Root->MoveComponent(MoveDelta, Root->GetComponentQuat(), /*bSweep*/ true);
    }
    else
    {
        PlayerControllerRef->GetPawn()->AddActorLocalOffset(MoveDelta, /*bSweep*/ true);
    }

    PrevHeightM = GetHeightM();
}

void CesiumGlobeMovementHandler::GlobeMovementHandler(float DeltaSeconds)
{
    if (!(GEngine && GEngine->XRSystem.IsValid()))
        return;
    TArray<FVector> LP, RP;  TArray<FQuat> LR, RR;  TArray<float> LRd, RRd;
    const bool bL = AHanTracking::GetInstance()->GetHandKeypoints(EControllerHand::Left, LP, LR, LRd);
    const bool bR = AHanTracking::GetInstance()->GetHandKeypoints(EControllerHand::Right, RP, RR, RRd);

    bool bLPinch = false, bRPinch = false;



    bRPinch = AHanTracking::GetInstance()->IsPinching(RP);
    bLPinch = AHanTracking::GetInstance()->IsPinching(LP);

    if (bR && bRPinch && !bLPinch)
    {
        PanOrbitAroundCesiumCenter_Stable(RP, true, DeltaSeconds);
    }
    else
    {
        PanOrbitAroundCesiumCenter_Stable(RP, /*bPinchActive*/ false, DeltaSeconds); // resets state
    }

    float speed = AHanTracking::GetInstance()->CalculateTwoHandSpeed(LP, RP, bLPinch, bRPinch, DeltaSeconds);

    if (speed != 0.f)
    {
        // Use the speed to move the actor
        MoveActorWithSpeed(speed, DeltaSeconds);
    }
   // if (!bRPinch && bLPinch)
   // {
   //    AHanTracking::GetInstance()->ApplyYawRotationToPawn(LP, bLPinch, DeltaSeconds);
   // }
    AHanTracking::GetInstance()->height = GetHeightM();
}

static FORCEINLINE FVector LerpExpVec(const FVector& from, const FVector& to, float hz, float dt)
{
    const float a = 1.f - FMath::Exp(-FMath::Max(0.f, hz) * dt);
    return FMath::Lerp(from, to, a);
}

void CesiumGlobeMovementHandler::RefreshEarthCenterIfNeeded()
{
    const double Now = FApp::GetCurrentTime();
    if ((LastEarthCenterRefreshTime < 0.0 || (Now - LastEarthCenterRefreshTime) >= EarthCenterRefreshInterval) && m_DefaultGeoreferenceActor)
    {

        CachedEarthCenterUU = m_DefaultGeoreferenceActor->TransformEarthCenteredEarthFixedPositionToUnreal(FVector::ZeroVector);
        LastEarthCenterRefreshTime = Now;
    }
}

FVector CesiumGlobeMovementHandler::UnrealFromLLH(double LonDeg, double LatDeg, double HeightMeters) const
{
    if (!m_DefaultGeoreferenceActor) return PlayerControllerRef->GetPawn()->GetActorLocation();

    const CesiumGeospatial::Cartographic carto(
        FMath::DegreesToRadians(LonDeg),
        FMath::DegreesToRadians(LatDeg),
        HeightMeters);

    const glm::dvec3 ecef = CesiumGeospatial::Ellipsoid::WGS84.cartographicToCartesian(carto);
    return m_DefaultGeoreferenceActor->TransformEarthCenteredEarthFixedPositionToUnreal({ (double)ecef.x, (double)ecef.y, (double)ecef.z });
}

double CesiumGlobeMovementHandler::GetHeightM() const
{
    if (!m_DefaultGeoreferenceActor) return 0.0;
    const FVector ecefF = m_DefaultGeoreferenceActor->TransformUnrealPositionToEarthCenteredEarthFixed(PlayerControllerRef->GetPawn()->GetActorLocation());
    const glm::dvec3 ecef(ecefF.X, ecefF.Y, ecefF.Z);
    const auto carto = CesiumGeospatial::Ellipsoid::WGS84.cartesianToCartographic(ecef);
    return carto ? carto->height : 0.0;
}

double CesiumGlobeMovementHandler::GetHeightMAtPos(const FVector& Pos) const
{
    if (!m_DefaultGeoreferenceActor) return 0.0;
    const FVector ecefF = m_DefaultGeoreferenceActor->TransformUnrealPositionToEarthCenteredEarthFixed(Pos);
    const glm::dvec3 ecef(ecefF.X, ecefF.Y, ecefF.Z);
    const auto carto = CesiumGeospatial::Ellipsoid::WGS84.cartesianToCartographic(ecef);
    return carto ? carto->height : 0.0;
}

FRotator CesiumGlobeMovementHandler::MakeUprightRotAtPos(const FVector& Pos, const FVector& PrefFwd) const
{
    // Use cached Earth center to avoid an extra transform each call
    const FVector Earth = CachedEarthCenterUU;
    const FVector up = (Pos - Earth).GetSafeNormal(); // geodetic up (radial)

    FVector fwd = FVector::VectorPlaneProject(PrefFwd, up).GetSafeNormal(); // tangent forward
    if (fwd.IsNearlyZero())
    {
        FVector north = FVector::VectorPlaneProject(FVector::UpVector, up).GetSafeNormal();
        if (north.IsNearlyZero()) north = FVector::ForwardVector;
        fwd = FVector::CrossProduct(up, north).GetSafeNormal();
    }
    return FRotationMatrix::MakeFromXZ(fwd, up).Rotator();
}

FRotator CesiumGlobeMovementHandler::MakeLookAtEarthRotAtPos(const FVector& Pos) const
{
    const FVector Earth = CachedEarthCenterUU;
    const FVector up = (Pos - Earth).GetSafeNormal();          // geodetic up
    FVector fwd = (Earth - Pos).GetSafeNormal();                // look at globe
    fwd = FVector::VectorPlaneProject(fwd, up).GetSafeNormal(); // stabilize roll
    return FRotationMatrix::MakeFromXZ(fwd, up).Rotator();
}

void CesiumGlobeMovementHandler::PanOrbitAroundCesiumCenter_Stable(
    const TArray<FVector>& RightHandPositions, // note: const ref
    bool bPinchActive,
    float DeltaSeconds)
{
    // --------- Validate input / georef ---------
    const int32 ThumbTip = (int32)EHandKeypoint::ThumbTip;
    const int32 IndexTip = (int32)EHandKeypoint::IndexTip;
    const FVector EarthCenterUU =
        m_DefaultGeoreferenceActor->TransformEarthCenteredEarthFixedPositionToUnreal(FVector::ZeroVector);

    if (!RightHandPositions.IsValidIndex(ThumbTip) ||
        !RightHandPositions.IsValidIndex(IndexTip))
    {
        return;
    }

    // --------- Start / end of pinch (now uses member state) ---------
    if (!bPinchActive)
    {
        bPinchActiveLatched = false;
        PrevSmMid = FVector::ZeroVector;
        BaseMid = FVector::ZeroVector;
        bArmed = false;
        return;
    }

    // Pinch midpoint (raw & smoothed)
    const FVector pinchMidRaw = 0.5f * (RightHandPositions[ThumbTip] + RightHandPositions[IndexTip]);

    if (!bPinchActiveLatched)
    {
        bPinchActiveLatched = true;
        PrevSmMid = pinchMidRaw;
        BaseMid = pinchMidRaw; // baseline (significant displacement measured from here)
        bArmed = false;
        return;
    }

    const FVector smMid = LerpExpVec(PrevSmMid, pinchMidRaw, PinchSmoothHz, DeltaSeconds);

    // --- Baseline check (significant enough) ---
    const FVector dispFromBase = smMid - BaseMid;
    const float   baseMag = dispFromBase.Size();
    if (!bArmed)
    {
        if (baseMag < AHanTracking::GetInstance()->BaselineArmUU)
        {
            PrevSmMid = smMid;
            return;
        }
        bArmed = true;
    }

    // --- Per-frame delta with deadzone & clamp ---
    FVector d = smMid - PrevSmMid;
    float   mag = d.Size();
    if (mag <= AHanTracking::GetInstance()->PinchDeadzoneUU) { PrevSmMid = smMid; return; }
    if (mag > HandDeltaMaxUU) { d *= (HandDeltaMaxUU / mag); mag = HandDeltaMaxUU; }

    // --------- Robust tangent basis at pawn ---------
    const FVector P = PlayerControllerRef->GetPawn()->GetActorLocation();
    const FVector r = P - EarthCenterUU;
    const double  R = r.Size();
    if (R < 1e-3) { PrevSmMid = smMid; return; }

    const FVector up = r / R;

    // Build EAST first (avoid parallel helper), then NORTH = EAST × UP
    FVector helper = FVector::UpVector;
    if (FMath::Abs(FVector::DotProduct(helper, up)) > 0.99f)
        helper = FVector::ForwardVector;

    FVector east = FVector::CrossProduct(up, helper).GetSafeNormal();
    if (east.IsNearlyZero()) east = FVector::RightVector;

    FVector north = FVector::CrossProduct(east, up).GetSafeNormal();

    // Project hand motion to tangent plane
    FVector dTan = d - up * FVector::DotProduct(d, up);
    if (dTan.IsNearlyZero(1e-6f)) { PrevSmMid = smMid; return; }

    // Signed components
    float dEast = FVector::DotProduct(dTan, east);   // +right/-left
    float dNorth = FVector::DotProduct(dTan, north);  // +up/-down

    FVector axis = FVector::ZeroVector;

    if (State == EState::Normal)
    {
        // Optional: per-axis deadzone for east so tiny left/right doesn’t rotate
        const float AxisDeadzoneUU = AHanTracking::GetInstance()->PinchDeadzoneUU; // or a smaller value just for east

        // If there is no meaningful eastward motion, do NOTHING (ignore north entirely)
        if (FMath::Abs(dEast) <= AxisDeadzoneUU) {
            PrevSmMid = smMid;        // keep filters happy
            return;                   // <- no action for north-only movement
        }

        dNorth = 0.0f;                // hard-zero north contribution
        axis = (-dEast) * north;    // left/right rotates about local north
    }
    else
    {
        // Full 2D input on the tangent plane
        axis = (-dEast) * north + (dNorth)*east;
    }

    const double axisLn = axis.Size();
    if (axisLn < 1e-8) { PrevSmMid = smMid; return; }
    axis /= axisLn;

    // --------- Height-only theta lerp (smooth from MinDeg to MaxDeg) ---------
    const double h = FMath::Max(0.0, GetHeightM()); // meters


    // Normalize height to [0..1] between HMin and HMax
    double u = 0.0;
    if (HMax > HMin)
    {
        u = FMath::Clamp((h - HMin) / (HMax - HMin), 0.0, 1.0);
    }

    // Lerp degrees/sec, then convert to radians *per frame*

    const double degPerSec = FMath::Lerp(MinDegPerSec, MaxDegPerSec, u) * 0.4;

    const double theta = FMath::DegreesToRadians(degPerSec) * FMath::Max(DeltaSeconds, KINDA_SMALL_NUMBER);

    // Rotate and apply
    const FQuat  qRot(axis, (float)theta);
    const FVector rNew = qRot.RotateVector(r);
    const FVector newPos = EarthCenterUU + rNew;

    if (USceneComponent* root = PlayerControllerRef->GetPawn()->GetRootComponent())
        root->SetWorldLocation(newPos);
    else
        PlayerControllerRef->GetPawn()->SetActorLocation(newPos, /*bSweep*/ false);

    // --------- Auto-orient (keep Earth in front, no roll) ---------
    {
        const FVector upDesired = (newPos - EarthCenterUU).GetSafeNormal();
        FVector       fwdDesired = (EarthCenterUU - newPos).GetSafeNormal();
        fwdDesired = FVector::VectorPlaneProject(fwdDesired, upDesired).GetSafeNormal();

        if (!upDesired.IsNearlyZero() && !fwdDesired.IsNearlyZero())
        {
            const FQuat target = FRotationMatrix::MakeFromXZ(fwdDesired, upDesired).ToQuat();
            const FQuat curr = PlayerControllerRef->GetPawn()->GetActorQuat();
            const float aRot = 1.f - FMath::Exp(-RotSmoothHz * DeltaSeconds);
            const FQuat sm = FQuat::Slerp(curr, target, aRot).GetNormalized();

            if (USceneComponent* root = PlayerControllerRef->GetPawn()->GetRootComponent())
                root->SetWorldRotation(sm);
            else
                PlayerControllerRef->GetPawn()->SetActorRotation(sm);
        }
    }

    // --------- Persist for next frame ---------
    PrevSmMid = smMid;
}


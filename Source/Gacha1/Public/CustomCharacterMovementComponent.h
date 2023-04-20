// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ObjectMacros.h"
#include "CustomCharacterMovementComponent.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum ECustomMovementMode
{
	CMOVE_Climbing UMETA(DisplayName = "Climbing"),
	CMOVE_MAX      UMETA(Hdden),
};
UCLASS()
class GACHA1_API UCustomCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()


private:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;

	void SweepAndStoreWallHits();

	UPROPERTY(Category = "Character Movement Climbing", EditAnywhere)
		int CollisionCapsuleRadius = 50;

	UPROPERTY(Category = "Character Movement Climbing", EditAnywhere)
		int CollisionCapsuleHeight = 72;

	TArray<FHitResult> CurrentWallHits;

	FCollisionQueryParams ClimbQueryParams;

	UPROPERTY(Category = "Character Movement Climbing", EditAnywhere, meta = (ClampMin = "1.0", ClampMax = "75.0"))
		float MinHorizontalDegreeToStartClimbing = 25;

	bool CanStartClimbing();

	bool EyeHeightTrace(const float TraceDistance) const;

	bool IsFacingSurface(float Steepness) const;

	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;

	UPROPERTY(Category = "Character Movement Climbing", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "80.0"))
		float ClimbingCollisionShrinkAmount = 30;

public:
	void TryClimbing();
	void CancelClimbing();
	UFUNCTION(BlueprintPure)
		bool IsClimbing() const;
	UFUNCTION(BlueprintPure)
		FVector GetClimbSurfaceNormal() const;



private:

	bool bWantsToClimb = false;
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;

	void PhysClimbing(float deltaTime,int32 Iterations);

	void ComputeSurfaceInfo();
	void ComputeClimbingVelocity(float deltaTime);
	bool ShouldStopClimbing();
	void StopClimbing(float deltaTime, int32 Iterations);
	void MoveAlongClimbingSurface(float deltaTime);
	void SnapToClimbingSurface(float deltaTime) const;

	FVector CurrentClimbingNormal;
	FVector CurrentClimbingPosition;

	UPROPERTY(Category = "Character Movement: Climbing", EditAnywhere, meta = (ClampMin = "10.0", ClampMax = "500.0"))
		float MaxClimbingSpeed = 120.f;

	UPROPERTY(Category = "Character Movement: Climbing", EditAnywhere, meta = (ClampMin = "10.0", ClampMax = "2000.0"))
		float MaxClimbingAcceleration = 380.f;

	UPROPERTY(Category = "Character Movement: Climbing", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "3000.0"))
		float BrakingDecelerationClimbing = 550.f;

	virtual float GetMaxSpeed() const override;
	virtual float GetMaxAcceleration() const override;

	UPROPERTY(Category = "Character Movement: Climbing", EditAnywhere, meta = (ClampMin = "1.0", ClampMax = "12.0"))
		int ClimbingRotationSpeed = 6;

	FQuat GetClimbingRotation(float deltaTime) const;

	//FVector CurrentClimbingNormal;

	UPROPERTY(Category = "Character Movement: Climbing", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "60.0"))
		float ClimbingSnapSpeed = 4.f;

	UPROPERTY(Category = "Character Movement: Climbing", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "80.0"))
		float DistanceFromSurface = 45.f;

};



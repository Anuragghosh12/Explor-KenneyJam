// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomCharacterMovementComponent.generated.h"

/**
 * 
 */
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
};

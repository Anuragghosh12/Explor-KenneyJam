// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacterMovementComponent.h"

#include "GameFramework/Character.h"


void UCustomCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	SweepAndStoreWallHits();
}

void UCustomCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	ClimbQueryParams.AddIgnoredActor(GetOwner());
}

void UCustomCharacterMovementComponent::SweepAndStoreWallHits()
{
	const FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(CollisionCapsuleRadius,CollisionCapsuleHeight);
	const FVector StartOffSet = UpdatedComponent->GetForwardVector() * 20;

	const FVector Start = UpdatedComponent->GetComponentLocation() + StartOffSet;
	const FVector End = UpdatedComponent->GetForwardVector() + Start;

	TArray<FHitResult>Hits;
	const bool HitWall = GetWorld()->SweepMultiByChannel(Hits, Start, End, FQuat::Identity, ECC_WorldStatic, CollisionShape, ClimbQueryParams);
	HitWall ? CurrentWallHits = Hits : CurrentWallHits.Reset();

}

bool UCustomCharacterMovementComponent::CanStartClimbing()
{
	for(FHitResult& Hit: CurrentWallHits)
	{
		const FVector HorizontalNormal = Hit.Normal.GetSafeNormal();

		const float HorizontalDot = FVector::DotProduct(UpdatedComponent->GetForwardVector(), -HorizontalNormal);
		const float VerticalDot = FVector::DotProduct(Hit.Normal, HorizontalNormal);

		const float HorizontalDegree = FMath::RadiansToDegrees(FMath::Acos(HorizontalDot));
		const bool bIsCeiling = FMath::IsNearlyZero(VerticalDot);

		if(HorizontalDegree<=MinHorizontalDegreeToStartClimbing && !bIsCeiling &&IsFacingSurface(VerticalDot))
		{
			return true;
		}
	}
	return false;
}

bool UCustomCharacterMovementComponent::EyeHeightTrace(const float TraceDistance) const
{
	FHitResult UpperEdgeHit;
	const FVector Start = UpdatedComponent->GetComponentLocation() +
		(UpdatedComponent->GetUpVector() * GetCharacterOwner()->BaseEyeHeight);
	const FVector End = Start + (UpdatedComponent->GetForwardVector() * TraceDistance);

	return GetWorld()->LineTraceSingleByChannel(UpperEdgeHit, Start, End, ECC_WorldStatic, ClimbQueryParams);
}

bool UCustomCharacterMovementComponent::IsFacingSurface(const float Steepness) const
{
	constexpr float BaseLength = 80;
	const float SteepnessMultiplier = 1 + (1 - Steepness) * 5;

	return EyeHeightTrace(BaseLength*SteepnessMultiplier);
}

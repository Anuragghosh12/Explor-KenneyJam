// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable_Base.h"
#include "Main2.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Gacha1_GameMode.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACollectable_Base::ACollectable_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollectibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collectible Mesh"));
	RootComponent = CollectibleMesh;
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	Sphere->SetupAttachment(CollectibleMesh);
	isActive = false;
	isCollected = false;
}

// Called when the game starts or when spawned
void ACollectable_Base::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACollectable_Base::OnHit);

}

// Called every frame
void ACollectable_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isActive)
	{
		Duration -= DeltaTime; // Deduct from duration

		if (Duration <= 0.0f)
		{
			if (Char)
			{
				UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement();
				MoveComp->MaxWalkSpeed /= 100;
				Duration = 2.f;
				isActive = false;
				// Reset duration
			}
		}
	}
}

void ACollectable_Base::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	Char = Cast<AMain2>(OtherActor);
	
	
	if(Char && !isCollected)
	{
		CollectibleMesh->SetVisibility(false);
		CollectibleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		isActive = true;
		isCollected = true;
		UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement();
		MoveComp->MaxWalkSpeed *= 100;
		
	}
}

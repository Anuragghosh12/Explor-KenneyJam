// Fill out your copyright notice in the Description page of Project Settings.


#include "End_LVL_Door.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Main2.h"
#include "Gacha1_GameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnd_LVL_Door::AEnd_LVL_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	RootComponent = DoorMesh;
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	CollisionComponent->SetupAttachment(DoorMesh);
}

// Called when the game starts or when spawned
void AEnd_LVL_Door::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnd_LVL_Door::OnHit);

}

// Called every frame
void AEnd_LVL_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnd_LVL_Door::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AMain2* Char = Cast<AMain2>(OtherActor);

	if(Char)
	{

		AGacha1_GameMode* MyGameMode =
			Cast<AGacha1_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if(MyGameMode)
		{
			MyGameMode->RestartGameplay(true);
		} 

	}
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Main2.h"
#include "Collectable_Base.generated.h"

UCLASS()
class GACHA1_API ACollectable_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectable_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	AMain2* Char;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectable")
		float Duration=2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* CollectibleMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USphereComponent* Sphere;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectable")
		int Speed_Multiplier = 10;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectable")
		int Double_Jump_Infinite = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectable")
		bool Wall_Run_Allow=false;
	int8 isActive,isCollected;
	void ResetSpeed();
	
	

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
};

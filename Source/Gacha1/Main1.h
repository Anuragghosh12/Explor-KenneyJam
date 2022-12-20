// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperZD.h"
#include "Paper2D/Classes/PaperCharacter.h"
#include "Paper2D/Classes/PaperSprite.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main1.generated.h"

UCLASS()
class GACHA1_API AMain1 : public ACharacter
{
	GENERATED_UCLASS_BODY()

		

public:
	// Sets default values for this character's properties
	//AMain1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Landed(const FHitResult& Hit) override;
	UFUNCTION()
		void DoubleJump();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Paper)
		class UPaperFlipbookComponent* PlaneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Paper)
		class UPaperFlipbook* PlaneAnimation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Paper)
		class UPaperSprite* BallComponent;

	UPROPERTY()
		int DoubleJumpCounter;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		float JumpHeight;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* SideViewCamera;
protected:

	void MoveRight(float Value);

public:
	void RestartLevel();
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	float zPosition;
	FVector TempPos = FVector();
	

	bool CanMove;
};

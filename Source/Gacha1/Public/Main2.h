// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
//#include "PaperZD/Public/AnimSequences/PaperZDAnimSequence_Flipbook.h"
#include "PaperFlipbookComponent.h"
#include "Main2.generated.h"

/**
 *
 */

UENUM(BlueprintType, Category = "Animation")
enum class EAnimationDirection :uint8
{
	Up,
	Down,
	Left,
	Right,
	UpperLeft,
	UpperRight,
	DownLeft,
	DownRight,
	Jump_Right,
	Jump_Left,
	Fall_Right,
	Fall_Left,
	Last

};

USTRUCT(BlueprintType, Category = "Animation")
struct FAnimationFlipbooks
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* IdleUp {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* IdleDown {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* IdleLeft {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* IdleRight {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* IdleUpperLeft {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* IdleUpperRight {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* IdleDownLeft {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* IdleDownRight {
		nullptr
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* WalkUp {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* WalkDown {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* WalkLeft {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* WalkRight {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* WalkUpperLeft {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* WalkUpperRight {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* WalkDownLeft {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* WalkDownRight {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* Jump_Right {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* Jump_Left {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* Fall_Left {
		nullptr
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperFlipbook* Fall_Right {
		nullptr
	};
};

/*
 *A Paper Character using the 2d animation sprites
 */
UCLASS()
class GACHA1_API AMain2 : public APaperCharacter
{
	GENERATED_BODY()

public:
	AMain2();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Landed(const FHitResult& Hit) override;
	UFUNCTION()
		void DoubleJump();
	UPROPERTY()
		int DoubleJumpCounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float JumpHeight;
	EAnimationDirection Last;

private:
	float zPosition;
	FVector TempPos = FVector();
	bool CanMove;
protected:

	virtual void BeginPlay() override;
	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce) override;

	void MoveRight(float Value);
	void MoveForward(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UCameraComponent* CameraComponent;

	UFUNCTION(BlueprintCallable, Category = "AnimationCharacter|Animation")
		void Animate(float DeltaTime, FVector OldLocation, FVector const OldVelocity);

	UFUNCTION(BlueprintCallable, Category = "Animation Character| Animation")
		void SetCurrentAnimationDirection(FVector const& Velocity);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationCharacter|Config")
		EAnimationDirection CurrentAnimationDirection {
	};


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimationCharacter|Config")
		FAnimationFlipbooks Flipbooks;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationCharacter|Config")
		uint8 bIsMoving : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Health = 100.0f;
public:
	void DealDamage(float DamageAmount);

};


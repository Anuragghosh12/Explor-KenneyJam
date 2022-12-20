// Fill out your copyright notice in the Description page of Project Settings.


#include "Gacha1/Public/Main2.h"

#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PaperZD/Public/AnimSequences/PaperZDAnimSequence_Flipbook.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
AMain2::AMain2()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeRotation(FRotator(-30.f, -90.f, 0.f));
	SpringArmComponent->TargetArmLength = 500.f;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bEnableCameraRotationLag = true;
	SpringArmComponent->CameraLagSpeed = 4.f;
	SpringArmComponent->CameraRotationLagSpeed = 4.f;
	SpringArmComponent->CameraLagMaxDistance = 600.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true; //this rotates the character model towards the direction it is moving
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); //self explanatory.....we only wants it to rotate in y-axis as its limited to that axis

	GetCharacterMovement()->GravityScale = 2.0f; //gravity value, 2=2 times the value of normal gravity
	GetCharacterMovement()->AirControl = 0.8f; //how much the character can move while mid air after a jump or fall
	GetCharacterMovement()->JumpZVelocity = 1000.0f;//initial jump velocity;
	GetCharacterMovement()->GroundFriction = 3.0f;//self explanatory
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;//self explanatory
	GetCharacterMovement()->MaxFlySpeed = 600.0f;// idk what this means

	TempPos = GetActorLocation();//gets the actor location and assigns it to variable
	zPosition = TempPos.Z + 300.0f;//assigns the z-axis value of current position vector

	JumpHeight = 600.f;

	OnCharacterMovementUpdated.AddDynamic(this, &AMain2::Animate);

	bIsMoving = false;
}

void AMain2::BeginPlay()
{
	Super::BeginPlay();
	CanMove = true;
}

void AMain2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TempPos = GetActorLocation();
	TempPos.X -= 850.0f;
	TempPos.Z = zPosition;
}

void AMain2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMain2::DoubleJump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveRight", this, &AMain2::MoveRight);
}
void AMain2::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	DoubleJumpCounter = 0;
}

void AMain2::DoubleJump()
{
	if (DoubleJumpCounter <= 1)
	{
		ACharacter::LaunchCharacter(FVector(0, 0, JumpHeight), false, true); //#1 asks for the launch parameters, #2 checks for x,y launch #3 checks for z launch
		DoubleJumpCounter++;
	}
}

void AMain2::MoveRight(float Value)
{
	if (CanMove)
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value, true);
}
void AMain2::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	auto MovementComponent = GetMovementComponent();

	if(MovementComponent)
	{
		MovementComponent->AddInputVector(WorldDirection * ScaleValue, bForce);
	}
	else
	{
		Internal_AddMovementInput(WorldDirection * ScaleValue, bForce);
	}

}

void AMain2::Animate(float DeltaTime, FVector OldLocation, FVector const OldVelocity)
{
	SetCurrentAnimationDirection(OldVelocity);

	if(OldVelocity.Size()>0.0f)
	{
		switch(CurrentAnimationDirection)
		{
		case EAnimationDirection::Up:
			GetSprite()->SetFlipbook(Flipbooks.WalkUp);
			break;
		case EAnimationDirection::Down:
			GetSprite()->SetFlipbook(Flipbooks.WalkDown);
			break;
		case EAnimationDirection::Left:
			GetSprite()->SetFlipbook(Flipbooks.WalkLeft);
			break;
		case EAnimationDirection::Right:
			GetSprite()->SetFlipbook(Flipbooks.WalkRight);
			break;
		case EAnimationDirection::UpperLeft:
			GetSprite()->SetFlipbook(Flipbooks.WalkUpperLeft);
			break;
		case EAnimationDirection::UpperRight:
			GetSprite()->SetFlipbook(Flipbooks.WalkUpperRight);
			break;
		case EAnimationDirection::DownLeft:
			GetSprite()->SetFlipbook(Flipbooks.WalkDownLeft);
			break;
		case EAnimationDirection::DownRight:
			GetSprite()->SetFlipbook(Flipbooks.WalkDownRight);
			break;
		default: 
			break;
		}
	}
	else
	{
		switch(CurrentAnimationDirection)
		{
		case EAnimationDirection::Up:
			GetSprite()->SetFlipbook(Flipbooks.IdleUp);
			break;
		case EAnimationDirection::Down:
			GetSprite()->SetFlipbook(Flipbooks.IdleDown);
			break;
		case EAnimationDirection::Left:
			GetSprite()->SetFlipbook(Flipbooks.IdleLeft);
			break;
		case EAnimationDirection::Right:
			GetSprite()->SetFlipbook(Flipbooks.IdleRight);
			break;
		case EAnimationDirection::UpperLeft:
			GetSprite()->SetFlipbook(Flipbooks.IdleUpperLeft);
			break;
		case EAnimationDirection::UpperRight:
			GetSprite()->SetFlipbook(Flipbooks.IdleUpperRight);
			break;
		case EAnimationDirection::DownLeft:
			GetSprite()->SetFlipbook(Flipbooks.IdleDownLeft);
			break;
		case EAnimationDirection::DownRight:
			GetSprite()->SetFlipbook(Flipbooks.IdleDownRight);
			break;
		default: 
			break;
		}
	}
}

void AMain2::SetCurrentAnimationDirection(FVector const& Velocity)
{
	const float x = Velocity.GetSafeNormal().X;
	const float y = Velocity.GetSafeNormal().Y;

	bIsMoving = x != 0.0f || y != 0.0f;
	if(bIsMoving)
	{
		if(y>0.0f && (abs(x)<0.5))
		{
			CurrentAnimationDirection = EAnimationDirection::Down;
		}
		else if(y>0.5f && x>0.5f)
		{
			CurrentAnimationDirection = EAnimationDirection::DownRight;
		}
		else if(y > 0.5f && x < -0.5f)
		{
			CurrentAnimationDirection = EAnimationDirection::DownLeft;
		}
		else if(y<0.5f && abs(x)<0.5)
		{
			CurrentAnimationDirection = EAnimationDirection::Up;
		}
		else if(y<-0.5f && x> 0.5f)
		{
			CurrentAnimationDirection = EAnimationDirection::UpperRight;
		}
		else if(y<-0.5f && x-0.5f)
		{
			CurrentAnimationDirection = EAnimationDirection::UpperLeft;
		}
		else if(abs(y)<0.5f && x>0.0f)
		{
			CurrentAnimationDirection = EAnimationDirection::Right;
		}
		else
		{
			CurrentAnimationDirection = EAnimationDirection::Left;
		}
	}

}


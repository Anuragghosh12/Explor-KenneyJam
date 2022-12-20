// Fill out your copyright notice in the Description page of Project Settings.


#include "Main1.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMain1::AMain1(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> PlaneAsset;
		FConstructorStatics()
			:PlaneAsset(TEXT(""))
		{
			
		}
	};

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	
	SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Side View Camera")); //creating the default sub object of ucamera component and assigning it to sideviewcamera
	SideViewCamera->bUsePawnControlRotation = false; //prevents the camera from rotating with change in direction of movement

	GetCharacterMovement()->bOrientRotationToMovement = true; //this rotates the character model towards the direction it is moving
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f,0.0f); //self explanatory.....we only wants it to rotate in y-axis as its limited to that axis

	GetCharacterMovement()->GravityScale = 2.0f; //gravity value, 2=2 times the value of normal gravity
	GetCharacterMovement()->AirControl = 0.8f; //how much the character can move while mid air after a jump or fall
	GetCharacterMovement()->JumpZVelocity = 1000.0f;//initial jump velocity;
	GetCharacterMovement()->GroundFriction = 3.0f;//self explanatory
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;//self explanatory
	GetCharacterMovement()->MaxFlySpeed = 600.0f;// idk what this means

	TempPos = GetActorLocation();//gets the actor location and assigns it to variable
	zPosition = TempPos.Z + 300.0f;//assigns the z-axis value of current position vector
	
	JumpHeight = 600.f;
}

// Called when the game starts or when spawned
void AMain1::BeginPlay()
{
	Super::BeginPlay();
	CanMove = true;
	
}

// Called every frame
void AMain1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TempPos = GetActorLocation();
	TempPos.X -= 850.0f;
	TempPos.Z = zPosition;
	SideViewCamera->SetWorldLocation(TempPos);
}

// Called to bind functionality to input
void AMain1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &AMain1::DoubleJump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveRight", this, &AMain1::MoveRight);
}

void AMain1::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	DoubleJumpCounter = 0;
}


void AMain1::DoubleJump()
{
	if(DoubleJumpCounter<=1)
	{
		ACharacter::LaunchCharacter(FVector(0,0,JumpHeight), false, true); //#1 asks for the launch parameters, #2 checks for x,y launch #3 checks for z launch
		DoubleJumpCounter++;
	}
}

void AMain1::MoveRight(float Value)
{
	if (CanMove)
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
}

void AMain1::RestartLevel()
{
}

void AMain1::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}


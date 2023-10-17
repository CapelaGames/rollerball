// Fill out your copyright notice in the Description page of Project Settings.


#include "RollerBallPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARollerBallPlayer::ARollerBallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create components
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	
	RootComponent = Mesh;
	// Attach springarm to the mesh
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);

	Mesh->SetSimulatePhysics(true);
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll= false;
	SpringArm->bInheritYaw = false;

}

// Called when the game starts or when spawned
void ARollerBallPlayer::BeginPlay()
{
	
	Mesh->OnComponentHit.AddDynamic(this, &ARollerBallPlayer::OnHit);
	Super::BeginPlay();
	// Account for mass in MoveForce
	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();
}

// Called to bind functionality to input
void ARollerBallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Custom Input Axis Bingings.
	InputComponent->BindAxis("MoveForward", this, &ARollerBallPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARollerBallPlayer::MoveRight);
	//Custom Action Binding.
	InputComponent->BindAction("Jump", IE_Pressed, this, &ARollerBallPlayer::Jump);
}

void ARollerBallPlayer::MoveRight(float Value)
{
	//Get right vectot, move based on input and speed
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void ARollerBallPlayer::MoveForward(float Value)
{
	const FVector Forward = Camera->GetForwardVector() * MoveForce * Value;
	Mesh->AddForce(Forward);
}

void ARollerBallPlayer::Jump()
{
	if (JumpCount >= MaxJumpCount){return;}
	Mesh->AddImpulse(FVector(0,0,JumpImpulse));
	JumpCount++;
}

void ARollerBallPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	float HitDirection = Hit.Normal.Z;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Z Normal: %f"), HitDirection));
	//UE_LOG();	

	if(HitDirection > 0)
	{
		JumpCount = 0;
	}
}


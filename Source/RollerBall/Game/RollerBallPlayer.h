// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
//#include "GameFramework/SpringArmComponent.h"
#include "RollerBallPlayer.generated.h"

//Forward Declarations
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ROLLERBALL_API ARollerBallPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARollerBallPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//define Components
	//metaspecifiers
	//pointers should be blueprint read only
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UCameraComponent* Camera;

	//Variables
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MoveForce = 500.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float JumpImpulse = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxJumpCount =1;


public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Functions
	void MoveRight(float Value);
	void MoveForward(float Value);
	void Jump();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	int32 JumpCount = 0;


};

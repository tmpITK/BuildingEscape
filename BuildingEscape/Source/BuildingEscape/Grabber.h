// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float Reach=100.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Ray-cast and grab what's in reach on key press
	void Grab();
	// Called when grab is released
	void Release();
	// Find assumed attached physics component
	void FindPhysicsHandleComponent();
	//Setup assumed attached input component
	void SetupInputComponent();
	// Return hit for firs physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	// returns start of reach line
	FVector GetReachLineStart();
	// returns end of reach line
	FVector GetReachLineEnd();

};

// Fill out your copyright notice in the Description page of Project Settings.
#include "Grabber.h"
#include "Engine/World.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "DrawDebugHelpers.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	GEngine->AddOnScreenDebugMessage(-1, 0.001f, FColor::Red, 
		FString::Printf(TEXT("Player is at %s \nwith rotation %s"), 
			*PlayerViewPointLocation.ToString(),
			*PlayerViewPointRotation.ToString()
		));

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach;
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor::Green,
		false,
		0.f,
		0.f,
		10.f
	);
	/*UE_LOG(LogTemp, Warning, TEXT("Player is at %s \nwith rotation %s"),
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString()
	);*/

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	if (Hit.bBlockingHit) {
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *(Hit.GetActor()->GetName()));
	}
	
}


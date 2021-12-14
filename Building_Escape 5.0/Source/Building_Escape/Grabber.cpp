// Copyright Bhanu Prasad M 2021

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
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

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty for %s"), *(GetOwner()->GetActorLabel()))
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get Players viewpoint
	FVector ViewPointLocation;
	FRotator ViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT ViewPointLocation,
		OUT ViewPointRotation);

	// UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"),
	// 	*ViewPointLocation.ToString(),
	// 	*ViewPointRotation.ToString()
	// );

	// Draw a line from player showing the reach
	FVector LineTraceEndLocation = ViewPointLocation + ViewPointRotation.Vector() * Reach;
	DrawDebugLine(
		GetWorld(),
		ViewPointLocation,
		LineTraceEndLocation,
		FColor(0, 255, 0),
		true,
		0.f,
		0,
		5.0f);

	// Ray-cast out to certain distance (Reach)

	// See what it hitsS
}

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

	// Check for physics handle component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Physics Handle for %s"),
		*(GetOwner()->GetActorLabel()))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to Find Physics Handle for %s"),
		*(GetOwner()->GetActorLabel()))
	}

	// Check for input component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Input component for %s"),
		*(GetOwner()->GetActorLabel()))
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	// else
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Unable to Find Input component for %s"),
	// 	*(GetOwner()->GetActorLabel()))
	// }
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber press"));
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

	// Draw a line from player showing the reach
	FVector LineTraceEndLocation = ViewPointLocation + ViewPointRotation.Vector() * Reach;
	DrawDebugLine(
		GetWorld(),
		ViewPointLocation,
		LineTraceEndLocation,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.0f);

	// Ray-cast out to certain distance (Reach)
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		ViewPointLocation,
		LineTraceEndLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	// Logging out to test
	if(Hit.GetActor() != nullptr)
	{
		UE_LOG(
			LogTemp, 
			Warning, 
			TEXT("Trace hit on %s at a distance of %f"), 
			*(Hit.GetActor()->GetActorLabel()),
			GetOwner()->GetDistanceTo(Hit.GetActor())
		);
	}

	// See what it hitsS
}

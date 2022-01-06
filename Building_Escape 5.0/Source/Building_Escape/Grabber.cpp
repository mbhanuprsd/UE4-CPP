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
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

// Check for physics handle component
void UGrabber::FindPhysicsHandle()
{
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
}

// Check for input component
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber pressed"));

	// Get Players viewpoint
	FVector ViewPointLocation;
	FRotator ViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT ViewPointLocation,
		OUT ViewPointRotation);

	// Draw a line from player showing the reach
	FVector LineTraceEndLocation = ViewPointLocation + ViewPointRotation.Vector() * Reach;

	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent *ComponentToGrab = HitResult.GetComponent();

	// If we hit something then attach physics handdle
	if (HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			LineTraceEndLocation);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber released"));
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// Move the object we are holding
		// Get Players viewpoint
		FVector ViewPointLocation;
		FRotator ViewPointRotation;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			OUT ViewPointLocation,
			OUT ViewPointRotation);

		// Draw a line from player showing the reach
		FVector LineTraceEndLocation = ViewPointLocation + ViewPointRotation.Vector() * Reach;
		PhysicsHandle->SetTargetLocation(LineTraceEndLocation);
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	// Get Players viewpoint
	FVector ViewPointLocation;
	FRotator ViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT ViewPointLocation,
		OUT ViewPointRotation);

	// Draw a line from player showing the reach
	FVector LineTraceEndLocation = ViewPointLocation + ViewPointRotation.Vector() * Reach;

	// Ray-cast out to certain distance (Reach)
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		ViewPointLocation,
		LineTraceEndLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams);

	// Logging out to test
	if (Hit.GetActor() != nullptr)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Trace hit on %s at a distance of %f"),
			*(Hit.GetActor()->GetActorLabel()),
			GetOwner()->GetDistanceTo(Hit.GetActor()));
	}

	return Hit;
}
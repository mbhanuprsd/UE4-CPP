// Copyright Bhanu Prasad M 2021


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	// OpenAngle = InitialYaw + OpenAngle;
	OpenAngle += InitialYaw;
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has open door component but no Pressure Plate!"), *(GetOwner()->GetActorLabel()));
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (TotalMassOfActors() > MassToOpenDoors)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
	{
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("Yaw of %s is %f"), *(GetOwner()->GetActorLabel()), GetOwner()->GetActorRotation().Yaw);

	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * OpenDoorSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("Yaw of %s is %f"), *(GetOwner()->GetActorLabel()), GetOwner()->GetActorRotation().Yaw);

	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * CloseDoorSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	// Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Add up their masses
	for (AActor* OverlapActor : OverlappingActors)
	{
		TotalMass += OverlapActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	
	return TotalMass;
}
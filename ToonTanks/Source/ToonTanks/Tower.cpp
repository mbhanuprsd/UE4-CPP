// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank)
	{
		// Find the distance to the tank
		float Distance = FVector::Distance(GetActorLocation(), Tank->GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("Distance from %s : %f"), *GetActorLabel(), Distance);
		// CHeck to see if tank is in range
		if (Distance <= FireRange)
		{
			// if tank is in range, rotate turret towards tank
			RotateTurret(Tank->GetActorLocation());
		}
	}
}

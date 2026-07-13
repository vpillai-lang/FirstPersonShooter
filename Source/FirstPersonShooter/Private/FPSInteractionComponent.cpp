// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSInteractionComponent.h"
#include "FPSGameplayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UFPSInteractionComponent::UFPSInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFPSInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFPSInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFPSInteractionComponent::PrimaryInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("PrimaryInteract called"));
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	UE_LOG(LogTemp, Warning, TEXT("EyeLocation: %s"), *EyeLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("EyeRotation: %s"), *EyeRotation.ToString());

	// FHitResult Hit;
	// bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	TArray<FHitResult> Hits;

	float Radius = 30.f;

	FCollisionShape Shape;
	Shape.SetSphere(30.0f);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();

		if (HitActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitActor->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Nothing hit"));
		}

		if (HitActor)
		{
			if (HitActor->Implements<UFPSGameplayInterface>())
			{

				APawn* MyPawn = Cast<APawn>(MyOwner);

				if (HitActor->Implements<UFPSGameplayInterface>())
				{
					UE_LOG(LogTemp, Warning, TEXT("Implements interface"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Does NOT implement interface"));
				}


				IFPSGameplayInterface::Execute_Interact(HitActor, MyPawn);

				DrawDebugSphere(
					GetWorld(),
					Hit.Location,
					Radius,
					32,
					LineColor,
					false,
					2.0f
				);

				break;
			}
		}

		DrawDebugSphere(
			GetWorld(),
			Hit.Location,
			Radius,
			32,
			LineColor,
			false,
			2.0f
		);
	}



	DrawDebugLine(
		GetWorld(),
		EyeLocation,
		End,
		LineColor,
		false,
		2.0f,
		0,
		2.0f
	);


}
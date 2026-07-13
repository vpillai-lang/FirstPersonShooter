// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSItemChest.h"
#include "Components\StaticMeshComponent.h"

// Sets default values
AFPSItemChest::AFPSItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110;
}

void AFPSItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Chest interacted!"));
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

// Called when the game starts or when spawned
void AFPSItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


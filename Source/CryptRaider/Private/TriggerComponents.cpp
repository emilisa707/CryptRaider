// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponents.h"

UTriggerComponents::UTriggerComponents()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponents::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if(Actor != nullptr)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if(Component != nullptr)
		{
			Component->SetSimulatePhysics(false);
		}
		Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
	}
	else
	{
		Mover->SetShouldMove(false);
	}
	
}

void UTriggerComponents::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

void UTriggerComponents::BeginPlay()
{
	Super::BeginPlay();
}

AActor* UTriggerComponents::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	for(AActor* Actor : Actors)
	{
		bool HasAccptableTag = Actor->ActorHasTag(AcceptableActorTag);
		bool isGrabbed = Actor->ActorHasTag("Grabbed");
		if(HasAccptableTag && !isGrabbed)
		{
			return  Actor;
		}
	}

	return nullptr;
}

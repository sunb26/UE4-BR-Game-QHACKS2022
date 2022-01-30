// Copyright Epic Games, Inc. All Rights Reserved.

#include "BRProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "BRCharacter.h"
#include "BRGameMode.h"

ABRProjectile::ABRProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ABRProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 6000.f;
	ProjectileMovement->MaxSpeed = 6000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	// Allows other players to see bullets from your gun
	SetReplicates(true);
	SetReplicateMovement(true);

}



void ABRProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//// Only add impulse and destroy projectile if we hit a physics
	//if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	//{
	//	OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

	//	Destroy();
	//}

	if (HasAuthority())
	{
		if (ABRCharacter* HitPlayer = Cast<ABRCharacter>(OtherActor)) // Checks to see if anyone has been hit
		{
			if (ABRGameMode* GM = Cast<ABRGameMode>(GetWorld()->GetAuthGameMode()))
			{
				/** Lets game know that a player has been killed */
				ABRCharacter* Killer = Cast<ABRCharacter>(GetOwner());
				GM->PlayerDied(HitPlayer, Killer);

				HitPlayer->Killer = Killer; // Set dead players killer to the killer
				HitPlayer->OnRep_Killer(); // Trigger Ragdoll

			}
		}
	}




}
// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
ATank::ATank(){

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
    

}
void ATank::HandleDestruction(){
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}
void ATank::BeginPlay(){
    Super::BeginPlay();
    TankPlayerController = Cast<APlayerController>(GetController());
    
}
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
    
    
}
// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(TankPlayerController){
        FHitResult hitResult;
        TankPlayerController->
            GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, 
            false,
            hitResult );

        // DrawDebugSphere(
        // GetWorld(), 
        // hitResult.ImpactPoint,
        // 25.f,
        // 12,
        // FColor::Red,
        // false,
        // -1.f
        // );
        RotateTurret(hitResult.ImpactPoint);
    }


}
void ATank::Move(float Value){
    // UE_LOG(LogTemp, Warning, TEXT("value %f"), Value);
    FVector DeltaLoc (0.f);
    DeltaLoc.X = Value *Speed *UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(DeltaLoc, true);

}

void ATank::Turn(float Value){
    // UE_LOG(LogTemp, Warning, TEXT("value %f"), Value);
    FRotator DeltaRotation (0.f);
    DeltaRotation.Yaw = Value *TurnRate *UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);

}

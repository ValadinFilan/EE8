// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/Star.h"

AStar::AStar()
{
	LBComponent = CreateDefaultSubobject<ULineBatchComponent>(TEXT("LineBatcher"));
	//RStream = FRandomStream(Parameters.Seed);// specify seed
}

void AStar::Initialize(int32 Seed, TArray<FVector> NearestNeighbours)
{
	Super::Initialize();

	RStream = FRandomStream(Seed);// specify seed
	Neighbours = NearestNeighbours;
	DrawL();
}

void AStar::DrawL()
{
	TArray<FBatchedLine> lines;
	for (auto i = 0; i < Neighbours.Num() - 1; i++)
	{
		FVector start = FVector(Neighbours[i].X, Neighbours[i].Y, Neighbours[i].Z);

		FBatchedLine line = FBatchedLine(start,
			this->GetActorLocation(),
			FLinearColor(1, 1, 1, 0.5),
			100000, // for long period draw
			10.0,
			4
		);
		lines.Add(line);
	}
	LBComponent->DrawLines(lines);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f = FloatVariable / %f = FloatVariable / %f = FloatVariable"), Neighbours.Num(), 0, 0));
}
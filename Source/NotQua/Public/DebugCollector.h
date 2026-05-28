// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DebugCollector.generated.h"


USTRUCT(BlueprintType)
struct FCSVRow : public FTableRowBase
{
    GENERATED_BODY()
    //Custom Struct for player locational data 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    FVector WorldLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    FVector ForwardVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    FColor PlayerColor;

    //Set the layout
    FCSVRow()
        : WorldLocation(FVector::ZeroVector)
        , ForwardVector(FVector::ZeroVector)
        , PlayerColor(FColor::Black)
    {
    }
};

UCLASS()
class NOTQUA_API UDebugCollector : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable)
    static void ExampleFunction(FString InExample, FString& OutExample);

    UFUNCTION(BlueprintCallable)
    static void DataCollector(FVector WorldLocation, FVector ForwardVector, FColor PlayerColor);

    UFUNCTION(BlueprintCallable)
    static bool LoadCSV(TArray<FCSVRow>& OutRows);

    UFUNCTION(BlueprintCallable)
    static void ClearData();
};

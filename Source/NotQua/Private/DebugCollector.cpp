// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugCollector.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"

void UDebugCollector::ExampleFunction(FString InExample, FString& outExample) {

	UE_LOG(LogTemp, Warning, TEXT("This is a log message!"));

}



void UDebugCollector::DataCollector(FVector WorldLocation, FVector ForwardVector, FColor PlayerColor) {
	FString FilePath = FPaths::ProjectSavedDir() + TEXT("PlayerHistory.csv");

    FString CSVLine = FString::Printf(TEXT("%f,%f,%f,%f,%f,%f,%d,%d,%d\n"),

        WorldLocation.X,
        WorldLocation.Y,
        WorldLocation.Z,

        ForwardVector.X,
        ForwardVector.Y,
        ForwardVector.Z,

        PlayerColor.R,
        PlayerColor.G,
        PlayerColor.B
    );

    FFileHelper::SaveStringToFile(
        CSVLine,
        *FilePath,
        FFileHelper::EEncodingOptions::AutoDetect,
        &IFileManager::Get(),
        FILEWRITE_Append
    );
		
}


bool UDebugCollector::LoadCSV(TArray<FCSVRow>& OutRowArray) {
    FString path = FPaths::ProjectSavedDir() + TEXT("PlayerHistory.csv");
    TArray<FString> Lines;
    FFileHelper::LoadFileToStringArray(Lines, * path);

    for (const FString& Line : Lines)
    {

        //just for debug
        UE_LOG(LogTemp, Warning, TEXT("%s"), *Line);


        TArray<FString> rowPieces;
        //Grab the values from the CSV, cut out the commas and cull any empty chars just to be sure.
        Line.ParseIntoArray(rowPieces, TEXT(","), true);

        //Check if the row has exactly 9 values (3 vector3s). If it doesn't skip to the next entry.
        //This shouldn't ever actually happen but put it here just in case.
        if (rowPieces.Num() != 9)
            continue;


        //create the custom struct inheriting from FCSVRow
        FCSVRow Row;
        Row.WorldLocation = FVector(
            FCString::Atof(*rowPieces[0]), 
            FCString::Atof(*rowPieces[1]), 
            FCString::Atof(*rowPieces[2]));
        Row.ForwardVector = FVector(
            FCString::Atof(*rowPieces[3]),
            FCString::Atof(*rowPieces[4]),
            FCString::Atof(*rowPieces[5]));
        Row.PlayerColor = FColor(
            FCString::Atof(*rowPieces[6]),
            FCString::Atof(*rowPieces[7]),
            FCString::Atof(*rowPieces[8]));
        OutRowArray.Add(Row);
    }
    return true;
}

void UDebugCollector::ClearData() {
    FString path = FPaths::ProjectSavedDir() + TEXT("PlayerHistory.csv");
    FString emptyString = TEXT("");
    FFileHelper::SaveStringToFile(emptyString, * path);
}
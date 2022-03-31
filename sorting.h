#pragma once
#include "types.h"

//Cele de jos sunt implementate deja;
void bubbleSort(Array* array,void(*callBack)(Context*),Context* context);
void selectionSort(Array* array,void(*callBack)(Context*),Context* context);
void insertionSort(Array* array, void(*callBack)(Context*),Context* context);
void quickSort(Array* array, void(*callBack)(Context*),Context* context);
void mergeSort(Array* array, void(*callBack)(Context*),Context* context);

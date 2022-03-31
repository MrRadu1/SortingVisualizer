#include "sorting.h"
#include <stdlib.h>
#include "SDL_timer.h"
static void push(Array *arr, unsigned val)
{
    unsigned i = 0;
    while(arr->data[i] != 0 && i < arr->size)
        i++;
    if(i < arr->size)
        arr->data[i] = val;
}
static void del(Array *arr, unsigned val)
{
    unsigned i = 0;
    while(arr->data[i] != val && i < arr->size)
        i++;
    for(unsigned j = i; j < arr->size - 1; j++)
        arr->data[j] = arr->data[j+1];

}
//Merge Sort Algorithm
static void merge(Array* array, unsigned middle, unsigned left, unsigned right,void(*callBack)(Context*),Context* context)
{
    unsigned n1 = middle - left + 1;
    unsigned n2 = right - middle ;
    unsigned *v1 = malloc(n1 * sizeof (unsigned ));
    unsigned *v2 = malloc(n2 * sizeof (unsigned ));

    for(unsigned i = 0; i < n1; i++)
        v1[i] = array->data[left+i];
    for(unsigned i =0; i< n2; i++)
        v2[i] = array->data[middle+1+i];
    unsigned i = 0, j = 0, k = left;
    while(i < n1 && j < n2)
    {
        if(v1[i]< v2[j])
        {
            array->data[k] = v1[i];
            push(context->selected,i);
            push(context->selected,k);
            callBack(context);//aici se modifica ceva si trebuie printat pe ecran;
            del(context->selected,i);
            del(context->selected,k);
            i++;
        }
        else
        {
            array->data[k] = v2[j];
            push(context->selected,j);
            push(context->selected,k);
            callBack(context);//aici se modifica ceva si trebuie printat pe ecran;
            del(context->selected,j);
            del(context->selected,k);

            j++;
        }
        k++;
    }
    //daca cumva au mai ramas elemente ori in subvectorul stang ori in subvectorul drept le adaugam la final.
    while(i < n1)
    {
        array->data[k] = v1[i];
        context->array = array;
        push(context->selected,i);
        push(context->selected,k);
        callBack(context);
        del(context->selected,i);
        del(context->selected,k);
        i++;
        k++;
    }
    while(j < n2)
    {
        array->data[k] = v2[j];
        context->array = array;
        push(context->selected,j);
        push(context->selected,k);
        callBack(context);
        del(context->selected,j);
        del(context->selected,k);
        j++;
        k++;
    }

}
static void mergeSorting(Array* array, unsigned left, unsigned right,void(*callBack)(Context*),Context* context )
{
    if(left<right) {
        unsigned middle = (left + right) / 2; //cautam mijlocul vectorului pe care vrem sa il aranjam
        mergeSorting(array, left, middle,callBack,context);
        mergeSorting(array, middle + 1,right,callBack,context); //apelam metoda divide et impera pt a sorta pe rand toti subvectorii array-ului
        merge(array, middle, left, right,callBack,context);//apelam functia pentru a lipi cei doi subvectori ordonati
    }
}
void mergeSort(Array* array, void(*callBack)(Context*),Context* context)
{
    mergeSorting(array,0,array->size-1,callBack,context);
    //done
    context->done = 1;
    callBack(context);
}

//Quick Sort Algorithm

static unsigned pivot(Array* array,unsigned left, unsigned right,void(*callBack)(Context*),Context* context)
{
    unsigned piv = array->data[right];
    unsigned index = left-1;
    unsigned aux;
    for(unsigned i = left; i < right; i++)
    {
        if(array->data[i] < piv)
        {
            index++;
            aux = array->data[index];
            array->data[index] = array->data[i];
            // aici nu apelam callback deoarece ne dorim sa ne arate pe ecran direct liniile inversate
            array->data[i] = aux;
            context->array = array;
            callBack(context); // se face o modificare deci reapelam modificarea ecranului

        }
    }
    aux = array->data[index + 1];
    array->data[index + 1] = array->data[right];
    array->data[right] = aux;
    context->array = array;
    callBack(context); // se face o modificare deci reapelam modificarea ecranului
    return index + 1;
}

static void quickSorting(Array* array,unsigned left,unsigned right,void(*callBack)(Context*),Context* context)
{
    if(left < right)
    {
        unsigned piv = pivot(array, left, right,callBack,context);
        if(piv > left)
        quickSorting(array, left, piv - 1,callBack,context);
        if(piv < right)
        quickSorting(array, piv + 1, right,callBack,context);
    }
}

void quickSort(Array* array, void(*callBack)(Context*),Context* context)
{
    quickSorting(array,0,array->size-1,callBack,context);
    //done
    context->done = 1;
    callBack(context);
}

//Selection Sort Algorithm

static void swap(unsigned *a, unsigned *b)
{
    unsigned aux = *a;
    *a = *b;
    *b = aux;
}
static unsigned minim(Context *context,Array* array, unsigned begin)
{
   unsigned min = array->data[begin], indexMin = begin;
   for(unsigned i = begin + 1; i < array->size; i++)
   {
       if(array->data[i] < min) {
           min = array->data[i];
           indexMin = i;
       }

   }
   return indexMin;
}
void selectionSort(Array* array,void(*callBack)(Context*),Context* context){
       for(unsigned i = 0; i < array->size; i++)
       {
           unsigned min = minim(context,array,i);
           push(context->selected,min);
           push(context->selected,i);
           swap(&array->data[min],&array->data[i]);
           callBack(context);// dupa ce am modificat ceva trimitem la ecran pentru a modifica grafica
           del(context->selected,min);
           del(context->selected,i);
          // callBack(context);
       }
    
    context->done = 1;
    callBack(context);
}

// Insertion Sort Algorithm

void insertionSort(Array* array, void(*callBack)(Context*),Context* context)
{
    unsigned elem;
    for(unsigned i = 1; i < array->size; i++)
    {
        elem = array->data[i];
        push(context->selected,i);
        int j = i - 1;
        while(j >= 0 && elem < array->data[j])
        {
            array->data[j+1] = array->data[j];
            push(context->selected,j);
            callBack(context); //aici se modifica un element care trebuie transmis la ecran
            del(context->selected,j);
            j--;
        }
        array->data[j + 1] = elem;
        callBack(context);
        del(context->selected,i);

    }
    //done
    context->done = 1;
    callBack(context);


}
//Bubble sort
void bubbleSort(Array* array, void(*callBack)(Context*),Context* context)
{
    unsigned aux;
    for(unsigned i = 0; i < array->size-1; i++)
        for(unsigned  j = i + 1; j < array->size; j++)
        {
            if(array->data[i] > array->data[j])
            {
                aux = array->data[i];

                push(context->selected,i);// adaug elementele ce trebuie colorate in rosu
                push(context->selected,j);

                array->data[i] = array->data[j];
                array->data[j] = aux;
                callBack(context);

                del(context->selected,i);// sterg elementele;
                del(context->selected,j);

            }
        }

        context->done = 1;
        callBack(context);
}
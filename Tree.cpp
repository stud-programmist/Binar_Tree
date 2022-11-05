#include <iostream>
#include <omp.h>
#include <cstdio>
#include <windows.h>

using namespace std;

struct bTree //структура дерева
{
    int Key; // значаение элемента дерева
    bTree *Left; // указатель на левую ветвь дерева
    bTree *Right; // указатель на правую ветвь дерева
};
 
class TREE //Класс бинарного дерева
{ 
private:
    bTree *Tree; //Указатель на корень дерева.
    void Search (int,bTree**); //модуль, который распределяет элементы дерева 
			      //по правило растановки эелементов в бинарном дерева
			     // (в левом поддереве содержатся значения, меньшие, чем значение данного узла. В правом поддереве содержатся значения, большие, чем значение данного узла.)
public:
    //Конструктор
    TREE() 
    {
        Tree=NULL;
    }

    bTree** GetTree () 
    {
        return &Tree;
    } //Получение вершины дерева. 

    void BuildTree ();// Создание дерева
    void CleanTree (bTree **); //Очистка дерева  
    void Obhod ();
    void Obhod (bTree **); //Обход дерева с конца и увеличение значений эелемента дерева на 1
    void Print (bTree**,int);  // Вывод дерева
    //глобальные переменные
    int el, i;
    int *a = new int [i];
   
};
TREE A;
int main ()
{ 
    //TREE A;
    A.BuildTree ();
    A.Print (A.GetTree (),0);
    A.Obhod();
    //A.Obhod(A.GetTree ());
    printf("--------------------\n");
    printf("\n");
    A.Print (A.GetTree (),0);
    A.CleanTree (A.GetTree ());
    printf("Well done! \n");
    return 0;
}
void TREE::BuildTree ()
{
    srand(time(0));
    printf("Количество элементов дерева: \n");
    scanf("%d", &i);
    printf("\n");
    //int *a = new int [i];
    for(int j=0; j<i; j++)
	a[j]=rand() % 100 +1;

    for(int j=0; j<i; j++) 
    {
	el=a[j];
        Search (el,&Tree);
    }
    //delete [] a;
}
void TREE::Search (int x, bTree **p)
{
    if (*p==NULL)
    {
        *p = new(bTree);
        (**p).Key = x;
        (**p).Left = NULL; (**p).Right = NULL; 
    }
    else
        if (x<(**p).Key) Search (x,&((**p).Left));
        else
            if (x>(**p).Key) Search (x,&((**p).Right));
}

void TREE::Obhod()
{
	#pragma omp parallel
	{
		#pragma omp single nowait
		{
			Obhod (A.GetTree ());
		}
	}
		
}

void TREE::Obhod (bTree **w)
{
	#pragma omp task firstprivate(w)
	{
		if (*w)
    		{ 
		    (**w).Key++;

		    if ((**w).Left)
		    {
			#pragma omp task firstprivate(w)
			{
				Obhod (&((**w).Left));
			}			
		    }

		    if ((**w).Right)
		    {
			#pragma omp task firstprivate(w)
			{
				Obhod (&((**w).Right));
			}			
		    }
    		}		
	}
}

void TREE::CleanTree (bTree **w)
    //Очистка дерева.
    //*w - указатель на корень дерева.
{ 
    if (*w!=NULL)
    { 
        CleanTree (&((**w).Left));
        CleanTree (&((**w).Right));
        delete *w;
    }
    // Освобождение памяти динамического массива
     //   delete [] a;
}

void TREE::Print (bTree **w,int l)
    //Изображение дерева *w на экране дисплея (рекурсивный алгоритм).
    // *w - указатель на корень дерева.
{ 
    int i;
    if (*w!=NULL)
    { 
        Print (&((**w).Right),l+1);
        for (i=1; i<=l; i++) cout << "    ";
        cout<<(**w).Key<<"\t"<<endl;
        Print (&((**w).Left),l+1); 
    }
}
#include <iostream>
#include <ctime>
#include <clocale>
#include "math.h"
#include "MyForm.h"
#include <string>

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GenAlgForm::MyForm form;
	Application::Run(% form);
}

std::string *out=new std::string("");

// фенотип хромосомы а, то есть расшифровка решения, представляемого хромосомой а
int GenAlgForm::MyForm::ft(bool* a) {
    return (8 * (int)a[0] + 4 * (int)a[1] + 2 * (int)a[2] + 1 * (int)a[3] +5);//сдвиг на 5 необходим, чтобы хромосомы из области решения лежали в интервале [0000;1010]
}

// Вычисляем целевую функцию 
int GenAlgForm::MyForm::tf(int x) {
    return 5 * x * x + 2 * x - 10;
}

// Быстрая сортировка массива генов
void GenAlgForm::MyForm::quickSort(bool** a, int low, int high)
{
    int* i=new int();
    *i = low;
    int* j = new int();
    *j = high;
    int* pivot = new int();
    * pivot= tf(ft(a[(*i + *j) / 2]));
    bool* temp=new bool [4];

    while (*i <= *j)
    {
        while (tf(ft(a[*i])) < *pivot) ++(*i);
        while (tf(ft(a[*j])) > *pivot) --(*j);
        if (*i <= *j)
        {
            if (*i < *j) {
                for (int n = 0; n < 4; ++n) {
                    temp[n] = a[*i][n];
                    a[*i][n] = a[*j][n];
                    a[*j][n] = temp[n];
                }
            }
            (*i)++;
            (*j)--;
        }
    }
    if (*j > low)
        quickSort(a, low, *j);
    if (*i < high)
        quickSort(a, *i, high);
    delete i;
    delete j;
    delete pivot;
    delete[] temp;
}

//Элитная селекция. В качестве функции приспособленности я использую целевую функцию.
//Так как я ищу минимум, чем меньше значение целевой функции, тем больше приспособленность.
void GenAlgForm::MyForm::eliteSelection(bool** a, int *popNum, int *maxCros, int* exTrueCros) {
    //сортируем популяцию по значению целевой функции, от меньшего к большему, так как ищем минимум
    quickSort(a, 0, *popNum-1);
    //ищем среднюю преспособленность
    double* avrFit = new double(0);
    int* numFit = new int(0);
    for (int i = 0; i < *popNum; ++i) {
        if (!(ft(a[i]) < 5 || ft(a[i]) > 15)) {
            *avrFit += tf(ft(a[i]));
            ++(*numFit);
        }
    }
    if (*numFit) *avrFit /= *numFit;
    else return;
    *out += "Элитная селекция. Средняя преспособленность текущей популяции: " + std::to_string(*avrFit) + "\r\n";
    //определяем число "лучших" хромосом, преспособленность которых будет выше средней.
    //так как я ищу минимум это означает, что значение целевой функции хромосомы должно быть меньше либо равно среднему значению
    int* trueCros = new int(0);
    while (*trueCros < *maxCros && tf(ft(a[*trueCros])) <= (int)(*avrFit)) ++(*trueCros);
    if (*trueCros % 2 == 1) --(*trueCros);
    if (*trueCros < 2) *trueCros = 2;
    //заполняем родительский пул лучшими хромосомами. пары формируются согласно инбридингу
    //одновременно выводим отобранные хромомсомы
    *out += "Отобранные хромосомы:\r\n\r\n";
    for (int i = 0; i < *trueCros; ++i) {
        for (int j = 0; j < 4; ++j) {
            a[*popNum + i][j] = a[i][j];
            if (a[*popNum + i][j]) *out += "1 "; else *out += "0 ";
        }
        *out += "\r\n";
        if (i % 2 == 1) *out+="\r\n";
    }
    *exTrueCros = *trueCros;
    delete avrFit;
    delete numFit;
    delete trueCros;
    return;
}
//Селекция инбридингом. Формируем случайные близкородственные родительские пары.
void GenAlgForm::MyForm::inbreedingSelection(bool** a, int *popNum, int *maxCros) {
    //сортируем популяцию по значению целевой функции, соседние хромосомы получаются близкородственными
    quickSort(a,0, *popNum-1);
    //формируем в популяции случайные близкородственные пары, причем одна и та же хромосома может входить в несколько пар
    int* k=new int();//случайная позиция первой хромосомы в паре
    for (int i = *popNum; i < *popNum + *maxCros; i += 2) {
        *k = rand() % (*popNum - 1);
        for (int j = 0; j < 4; ++j) {
            a[i][j] = a[*k][j]; //записываем геном первой хромосомы в паре
            a[i + 1][j] = a[*k + 1][j]; //и второй
        }
    }
    //выводим полученные пары
    *out += "Селекция инбридингом. Отобранные хромосомы:\r\n\r\n";
    for (int i = 0; i < *maxCros; ++i) {
        for (int j = 0; j < 4; ++j) {
            a[*popNum + i][j] = a[i][j];
            if (a[*popNum + i][j])  *out += "1 "; else *out += "0 ";
        }
        *out += "\r\n";
        if (i % 2 == 1) *out +="\r\n";
    }
    delete k;
}
//Стандартный двухточечный оператор кроссинговера 
void GenAlgForm::MyForm::STPcros(bool** a, int *popNum, int *trueCros) {
    *out += "Стандартный двухточечный оператор кроссинговера\r\n";
    bool* tmp = new bool[4];//временная хромосома для хранения генов во время обмена
    int* l1 = new int();
    int* l2 = new int();
    int* tmpl=new int();//точки скрещивания и переменная для их перестановки
    for (int i = *popNum; i < *popNum + *trueCros; i += 2) {
        //генерация двух точек скрещивания
        *l1 = rand() % 3;
        *l2 = rand() % 3;
        while (*l1 == *l2) *l2 = rand() % 3;
        if (*l2 < *l1) {
            *tmpl = *l1;
            *l1 = *l2;
            *l2 = *tmpl;
        }
        *out += "Хромосомы " + std::to_string(i + 1 - *popNum) + " и " + std::to_string(i + 2 - *popNum) + ": выбраны точки после генов под номерами " + std::to_string(*l1 + 1) + " и " + std::to_string(*l2 + 1) + "\r\n";
        //обмен генов
        for (int j = *l1 + 1; j <= *l2; ++j) {
            tmp[j] = a[i][j];
            a[i][j] = a[i + 1][j];
            a[i + 1][j] = tmp[j];
        }
    }
    *out+="\r\nПул потомков:\r\n\r\n";
    for (int i = *popNum; i < *popNum + *trueCros; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (a[i][j]) *out += "1 "; else *out += "0 ";
        }
        *out += "\r\n";
        if (i % 2 == 1) *out += "\r\n";
    }
    delete [] tmp;
    delete l1, l2, tmpl;
}
//оператор кроссинговера на основе чисел Фибоначчи
void GenAlgForm::MyForm::FIBcros(bool** a, int* popNum, int* trueCros) {
    *out += "Оператор кроссинговера на основе чисел Фибоначчи\r\n";
    bool* tmp=new bool [4];//временная хромосома для хранения генов во время обмена
    for (int i = *popNum; i < *popNum + *trueCros; i += 2) {
        //точки разрыва выбраны в соответствии с числами Фибоначчи, то есть после 1, 2 и 3 генов.
        //обмен генов
        for (int j = 1; j < 4; j += 2) {
            tmp[j] = a[i][j];
            a[i][j] = a[i + 1][j];
            a[i + 1][j] = tmp[j];
        }
    }
    *out +="\r\nПул потомков:\r\n\r\n";
    for (int i = *popNum; i < *popNum + *trueCros; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (a[i][j])  *out += "1 "; else *out += "0 ";
        }
        *out +="\r\n";
        if (i % 2 == 1) *out += "\r\n";
    }
    delete [] tmp;
}
//Упорядоченный двухточечный оператор кроссинговера 
void GenAlgForm::MyForm::OTPcros(bool** a, int* popNum, int* trueCros) {
    *out += "Упорядоченный двухточечный оператор кроссинговера\r\n";
    int* l1, * l2;
    int* tmpl=new int();//точки скрещивания и переменная для их перестановки
    bool* b1, * b2, * b11, * b22;//для проверки логики оператора
    for (int i = *popNum; i < *popNum + *trueCros; i += 2) {
        //генерация двух точек скрещивания
        l1 = new int(rand() % 3);
        l2 = new int(rand() % 3);
        while (*l1 == *l2) *l2 = rand() % 3;
        if (*l2 < *l1) {
            *tmpl = *l1;
            *l1 = *l2;
            *l2 = *tmpl;
        }
        *out += "Хромосомы " + std::to_string(i + 1 - *popNum) + " и " + std::to_string(i + 2 - *popNum) + ": выбраны точки после генов под номерами " + std::to_string(*l1 + 1) + " и " + std::to_string(*l2 + 1) + "\r\n";
        //для i-го потомка заполняем 1-цами между l1 и l2 <=> когда 1) a[i] не имеет 1 до l1; 2) и после l2; 3) a[i+1] имеет 1. иначе заполняем 0
        //для i+1-го потомка заполняем 1-цами между l1 и l2 <=> когда 1) a[i+1] не имеет 1 до l1; 2) и после l2; 3) a[i] имеет 1. иначе заполняем 0
        b1 = new bool(true);
        b2 = new bool(true);
        //1)
        for (int j = 0; j <= *l1; ++j) {
            *b1 = *b1 && (!a[i][j]);
            *b2 = *b2 && (!a[i + 1][j]);
        }
        //2)
        for (int j = *l2 + 1; j < 4; ++j) {
            *b1 = *b1 && (!a[i][j]);
            *b2 = *b2 && (!a[i + 1][j]);
        }
        //3)
        b11 =new bool(false);
        b22 =new bool(false);
        for (int j = 0; j < 4; ++j) {
            *b11 = *b11 || a[i + 1][j];
            *b22 = *b22 || a[i][j];
        }
        for (int j = *l1 + 1; j <= *l2; ++j) {
            if (*b1 && *b11) a[i][j] = 1; else a[i][j] = 0;
            if (*b2 && *b22) a[i + 1][j] = 1; else a[i + 1][j] = 0;
        }
    }
    *out += "\r\nПул потомков:\r\n\r\n";
    for (int i = *popNum; i < *popNum + *trueCros; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (a[i][j])*out += "1 "; else *out += "0 ";
        }
        *out += "\r\n";
        if (i % 2 == 1) *out += "\r\n";
    }
    delete l1, l2, tmpl, b1, b2, b11, b22;
}
//Частично-соответствующий двухточечный оператор кроссинговера 
void GenAlgForm::MyForm::PRTPcros(bool** a, int* popNum, int* trueCros) {
    *out += "Частично-соответствующий двухточечный оператор кроссинговера\r\n";
    bool* tmp = new bool [4];//временная хромосома для хранения генов во время обмена
    int* l1,* l2;
    int* tmpl=new int();//точки скрещивания и переменная для их перестановки
    int* b=new int();//логика оператора
    for (int i = *popNum; i < *popNum + *trueCros; i += 2) {
        //генерация двух точек скрещивания
        l1 = new int(rand() % 3);
        l2 = new int(rand() % 3);
        while (*l1 == *l2) *l2 = rand() % 3;
        if (*l2 < *l1) {
            *tmpl = *l1;
            *l1 = *l2;
            *l2 = *tmpl;
        }
        *out += "Хромосомы " + std::to_string(i) + " и " + std::to_string(i + 1) + ": выбраны точки после генов под номерами " + std::to_string(*l1) + " и " + std::to_string(*l2) + "\r\n";
        //обмен генов аналогично стандартному двуточечному между l1 и l2
        for (int j = *l1 + 1; j <= *l2; ++j) {
            tmp[j] = a[i][j];
            a[i][j] = a[i + 1][j];
            a[i + 1][j] = tmp[j];
        }
        //далее проверяем оставшиеся элементы на повторения и заменяем повторяющиеся на первый частично соответствующий
        //для элементов до l1
        for (int j = 0; j <= *l1; ++j) {
            //для i-го элемента
            *b = *l1 + 1;
            //сравниваем текущий элемент с элементами которые мы обменяли пока не найдем повтор или не выйдем за границу
            while (*b <= *l2 && a[i][j] != a[i][*b]) ++(*b);
            //если не вышли за границу, то нашли повтор
            if (*b != *l2 + 1) a[i][j] = a[i + 1][*b];
            //аналогично для i+1 элемента
            *b = *l1 + 1;
            while (*b <= *l2 && a[i + 1][j] != a[i + 1][*b]) ++(*b);
            if (*b != *l2 + 1) a[i + 1][j] = a[i][*b];
        }
        //для элементов после l2
        for (int j = *l2 + 1; j < 4; ++j) {
            *b = *l1 + 1;
            while (*b <= *l2 && a[i][j] != a[i][*b]) ++(*b);
            if (*b != *l2 + 1) a[i][j] = a[i + 1][*b];
            *b = *l1 + 1;
            while (*b <= *l2 && a[i + 1][j] != a[i + 1][*b]) ++(*b);
            if (*b != *l2 + 1) a[i + 1][j] = a[i][*b];
        }
    }
    *out += "\r\nПул потомков:\r\n\r\n";
    for (int i = *popNum; i < *popNum + *trueCros; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (a[i][j]) *out += "1 "; else *out += "0 ";
        }
        *out += "\r\n";
        if (i % 2 == 1) *out += "\r\n";
    }
    delete [] tmp;
    delete l1, l2, tmpl, b;
}
// точечная мутация
void GenAlgForm::MyForm::Pmut(bool** a, int* popNum, int* trueCros, int* maxCros, int* mutNum) {
    int* c, * g;//номер хромосомы и гена выбранных для мутации
    *out += "Точечная мутация. Количество мутаций: " + std::to_string(*mutNum) + "\r\n";
    for (int i = 0; i < *mutNum; ++i) {
        c = new int(rand() % *trueCros);
        g = new int(rand() % 4);
        *out += "Выбрана хромосома номер " + std::to_string(*c + 1) + ". Выбран ген номер" + std::to_string(*g + 1) + "\r\n";
        //переписываем выбранную хромосому в пул мутаций
        for (int j = 0; j < 4; ++j) {
            a[*popNum + *maxCros + i][j] = a[*popNum + *c][j];
        }
        //мутируем выбраный ген 
        if (a[*popNum + *maxCros + i][*g]) a[*popNum + *maxCros + i][*g] = 0; else a[*popNum + *maxCros + i][*g] = 1;
    }
    delete c, g;
}
//транспозиция
void GenAlgForm::MyForm::Tmut(bool** a, int* popNum, int* trueCros, int* maxCros, int* mutNum) {
    int* c;//номер хромосомы выбранной для мутации
    int* l1, * l2;
    int* tmpl=new int();//номера генов начала и конца блока
    int* l3;//позиция вставки инвертированного блока
    int* k; //позиция вставки гена не из блока и последняя такая заполненная позиция
    *out += "Транспозиция. Количество: " + std::to_string(*mutNum) + "\r\n";
    for (int i = 0; i < *mutNum; ++i) {
        //выбираем хромосому
        c = new int (rand() % (*trueCros));
        //выбираем блок из 2-3 генов  
        l1 = new int(rand() % 4);
        l2 = new int(rand() % 4);
        while (*l1 == *l2 || abs(*l1 - *l2) > 2) *l2 = rand() % 4;
        if (*l2 < *l1) {
            *tmpl = *l1;
            *l1 = *l2;
            *l2 = *tmpl;
        }
        //выбираем позицию, на которой станет этот блок
        l3 = new int(rand() % 3);
        while (*l3 == *l1 || *l3 + abs(*l2 - *l1) > 3) *l3 = rand() % 3;
        *out += "Выбрана хромосома номер " + std::to_string(*c + 1) + ". В блок входят гены от " + std::to_string(*l1 + 1) + " до " + std::to_string(*l2 + 1) + ". Блок встанет с позиции " + std::to_string(*l3 + 1) + "\r\n";
        //записываем строительный блок в инвертированном виде на выбранную позицию
        for (int j = 0; j <= abs(*l2 - *l1); ++j) {
            a[*popNum + *maxCros + i][*l3 + j] = a[*popNum + *c][*l2 - j];
        }
        //дописываем оставшиеся гены
        k = new int(0);
        for (int j = 0; j < *l1; ++j) {//выбрали позицию гена слева от блока в исходной хромосоме
            while (!(*k<*l3 || *k>*l3 + abs(*l2 - *l1))) ++(*k);//выбрали позиию гена в мутировавшей хромосоме
            a[*popNum + *maxCros + i][*k] = a[*popNum + *c][j];
            ++(*k);
        }
        for (int j = *l2 + 1; j < 4; ++j) {//выбрали позицию гена справа от блока в исходной хромосоме
            while (!(*k<*l3 || *k> * l3 + abs(*l2 - *l1))) ++(*k);//выбрали позиию гена в мутировавшей хромосоме
            a[*popNum + *maxCros + i][*k] = a[*popNum + *c][j];
            ++(*k);
        }
    }
    delete c, l1, l2, tmpl, l3, k;
}
    
int popNum, genNum, crosProb, mutProb, range, focus, maxCros, mutNum, trueCros, numFit;
short strat, rangeB, rangeE, sel, oper, mut;
float avrFit;


System::Void GenAlgForm::MyForm::StartGeneticAlgorithm_Click(System::Object^ sender, System::EventArgs^ e)
{  
    srand((unsigned int)time(0)); // генерация случайных чисел
    setlocale(LC_ALL, "Russian");
    popNum=-1; // Численность популяции
    popNum = (int)FORMpopNum->Value;
    genNum=-1; // Число генераций
    genNum = (int)FORMgenNum->Value;
    crosProb=-1; // Вероятность кроссинговера
    crosProb=(int)FORMcrosProb->Value;
    mutProb=-1; // Вероятность мутации
    mutProb=(int)FORMmutProb->Value;
    strat=-1; // Стратегия создания популяции
    if (strat1->Checked == true) strat = 1;
    else if (strat2->Checked == true) strat = 2;
    rangeB = 5;
    rangeE = 15;
    //случай фокусировки
    if (strat == 2) {
        range = (int)FORMrange->Value;//велечина максимального смещения от фокуса
        focus = 5 + rand()%11;//фокус, находится в области решения задачи
        while (!(focus + range <= 15 && focus - range >= 5)) focus = 5 + rand() % 11;//весь интервал генерации должен лежать в области решения
        rangeB = focus - range;
        rangeE = focus + range;
    }
    sel=-1;//вид селекции
    if (sel1->Checked == true) sel = 1;
    else if (sel2->Checked == true) sel = 2;
    oper=-1;//оператор кроссинговера
    if (oper1->Checked == true) oper = 1;
    else if (oper2->Checked == true) oper = 2;
    else if (oper3->Checked == true) oper = 3;
    else if (oper4->Checked == true) oper = 4;
    mut=-1;//оператор мутации/инверсии
    if (mut1->Checked == true) mut = 1;
    else if (mut2->Checked == true) mut = 2;

    //определение размера родительского пула. Если размер популяции не меньше двух, то кроссинговер возможен
    maxCros = 0;
    if (popNum >= 2) {
        maxCros = popNum * crosProb / 100;
        if (maxCros % 2 == 1) --maxCros;
        if (maxCros < 2 && crosProb != 0) maxCros = 2;
    }

    //определение размера пула мутаций. Если кроссинговер невозможен, мутации не происходят
    mutNum = 0;
    if (maxCros)  mutNum = maxCros * mutProb / 100;

    // Генерация начальной популяции 
    //создаем массив
    bool** pop = new bool* [popNum + maxCros + mutNum];
    for (int i = 0; i < popNum + maxCros + mutNum; ++i) {
        pop[i] = new bool[4];
        for (int j = 0; j < 4; ++j) {
            pop[i][j] = true;
        }
    }
    //генерация начальной популяции
    for (int i = 0; i < popNum; ++i) {
        // генерация хромосомы
        do {
            for (int j = 0; j < 4; ++j) {
                pop[i][j] = rand() % 2;
            }
        } while (ft(pop[i]) < rangeB || ft(pop[i]) > rangeE);
    }
    // Вывод начальной популяции    
    if (strat == 1) *out+="Выбрана стратегия Дробовика.\r\n\r\n";
    else *out += "Выбрана стратегия Фокусироваки(Фокус: "+ std::to_string(focus)+ ").\r\n\r\n";
    *out += "Начальная популяция (в скобках указаны фенотип и значение целевой функции):\r\n\r\n";

    for (int i = 0; i < popNum; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (pop[i][j]) *out += "1 ";
            else *out += "0 ";
        }
        *out += "("+ std::to_string(ft(pop[i])) + " " + std::to_string(tf(ft(pop[i]))) + ")" + "\r\n";
    }
    // начало итераций.
    trueCros = 0;
    for (int k = 1; k <= genNum; ++k) { 
        *out += "---------------------------------------\r\n";
        *out += "Генерация " + std::to_string(k) + "\r\n\r\n";
        //селекция   
        if (sel == 1) eliteSelection(pop, &popNum, &maxCros, &trueCros);
        else {
            trueCros = maxCros;
            inbreedingSelection(pop, &popNum, &maxCros);
        }
        //кроссинговер
        if (oper == 1) STPcros(pop, &popNum, &trueCros);
        if (oper == 2) OTPcros(pop, &popNum, &trueCros);
        if (oper == 3) PRTPcros(pop, &popNum, &trueCros);
        if (oper == 4) FIBcros(pop, &popNum, &trueCros);
        //мутация
        if (mut == 1) Pmut(pop, &popNum, &trueCros, &maxCros, &mutNum);
        if (mut == 2) Tmut(pop, &popNum, &trueCros, &maxCros, &mutNum);
        //показываем популяцию до отбора
        *out += "\r\n Популяция после кроссинговера и мутации (в скобках указано значение целевой функции): \r\n\r\n";
        for (int i = 0; i < popNum + trueCros; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (pop[i][j]) *out += "1 "; else *out += "0 ";
            }
            *out += "(" + std::to_string(tf(ft(pop[i]))) + ")" + "\r\n";
        }
        for (int i = popNum + maxCros; i < popNum + maxCros + mutNum; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (pop[i][j]) *out += "1 "; else *out += "0 ";
            }
            *out += "(" + std::to_string(tf(ft(pop[i]))) + ")" + "\r\n";
        }
        //отсев
        quickSort(pop,0, popNum + maxCros + mutNum-1);
        //выводим популяцию и считаем приспособленность
        avrFit = 0;
        numFit = 0;
        *out += "\r\n Популяция после отбора (в скобках указаны фенотип и значение целевой функции): \r\n\r\n";
        for (int i = 0; i < popNum; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (pop[i][j]) *out += "1 "; else *out += "0 ";
            }
            *out += "(" + std::to_string(ft(pop[i])) + " " + std::to_string(tf(ft(pop[i]))) + ")" + "\r\n";
            if (!(ft(pop[i]) < 5 || ft(pop[i]) > 15)) {
                avrFit += tf(ft(pop[i]));
                ++numFit;
            }
        }
        if (numFit) {
            avrFit /= numFit;
            *out += "\r\n Средняя приспособленность популяции: ";
            *out += std::to_string(avrFit) + "\r\n";
        } 
        else {
            *out += "\r\n В популяции не осталось приспособленных особей. ";
            break; 
        }
    }
    //вывод ответа:
    if (numFit) *out += "\r\n Ответ: " + std::to_string(ft(pop[0]));
    else *out += "\r\n Популяция вымерла, ответ не найден.";
    //чистка
    for (int i = 0; i < popNum + maxCros + mutNum; ++i) {
        delete[] pop[i];
    }
    delete[] pop;
    delete FORMcout->Text;
    FORMcout->Text = gcnew String(out->c_str());
    *out = "";
}
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

// ������� ��������� �, �� ���� ����������� �������, ��������������� ���������� �
int GenAlgForm::MyForm::ft(bool* a) {
    return (8 * (int)a[0] + 4 * (int)a[1] + 2 * (int)a[2] + 1 * (int)a[3] +5);//����� �� 5 ���������, ����� ��������� �� ������� ������� ������ � ��������� [0000;1010]
}

// ��������� ������� ������� 
int GenAlgForm::MyForm::tf(int x) {
    return 5 * x * x + 2 * x - 10;
}

// ������� ���������� ������� �����
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

//������� ��������. � �������� ������� ����������������� � ��������� ������� �������.
//��� ��� � ��� �������, ��� ������ �������� ������� �������, ��� ������ �����������������.
void GenAlgForm::MyForm::eliteSelection(bool** a, int *popNum, int *maxCros, int* exTrueCros) {
    //��������� ��������� �� �������� ������� �������, �� �������� � ��������, ��� ��� ���� �������
    quickSort(a, 0, *popNum-1);
    //���� ������� �����������������
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
    *out += "������� ��������. ������� ����������������� ������� ���������: " + std::to_string(*avrFit) + "\r\n";
    //���������� ����� "������" ��������, ����������������� ������� ����� ���� �������.
    //��� ��� � ��� ������� ��� ��������, ��� �������� ������� ������� ��������� ������ ���� ������ ���� ����� �������� ��������
    int* trueCros = new int(0);
    while (*trueCros < *maxCros && tf(ft(a[*trueCros])) <= (int)(*avrFit)) ++(*trueCros);
    if (*trueCros % 2 == 1) --(*trueCros);
    if (*trueCros < 2) *trueCros = 2;
    //��������� ������������ ��� ������� �����������. ���� ����������� �������� ����������
    //������������ ������� ���������� ����������
    *out += "���������� ���������:\r\n\r\n";
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
//�������� �����������. ��������� ��������� ����������������� ������������ ����.
void GenAlgForm::MyForm::inbreedingSelection(bool** a, int *popNum, int *maxCros) {
    //��������� ��������� �� �������� ������� �������, �������� ��������� ���������� ������������������
    quickSort(a,0, *popNum-1);
    //��������� � ��������� ��������� ����������������� ����, ������ ���� � �� �� ��������� ����� ������� � ��������� ���
    int* k=new int();//��������� ������� ������ ��������� � ����
    for (int i = *popNum; i < *popNum + *maxCros; i += 2) {
        *k = rand() % (*popNum - 1);
        for (int j = 0; j < 4; ++j) {
            a[i][j] = a[*k][j]; //���������� ����� ������ ��������� � ����
            a[i + 1][j] = a[*k + 1][j]; //� ������
        }
    }
    //������� ���������� ����
    *out += "�������� �����������. ���������� ���������:\r\n\r\n";
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
//����������� ������������ �������� ������������� 
void GenAlgForm::MyForm::STPcros(bool** a, int *popNum, int *trueCros) {
    *out += "����������� ������������ �������� �������������\r\n";
    bool* tmp = new bool[4];//��������� ��������� ��� �������� ����� �� ����� ������
    int* l1 = new int();
    int* l2 = new int();
    int* tmpl=new int();//����� ����������� � ���������� ��� �� ������������
    for (int i = *popNum; i < *popNum + *trueCros; i += 2) {
        //��������� ���� ����� �����������
        *l1 = rand() % 3;
        *l2 = rand() % 3;
        while (*l1 == *l2) *l2 = rand() % 3;
        if (*l2 < *l1) {
            *tmpl = *l1;
            *l1 = *l2;
            *l2 = *tmpl;
        }
        *out += "��������� " + std::to_string(i + 1 - *popNum) + " � " + std::to_string(i + 2 - *popNum) + ": ������� ����� ����� ����� ��� �������� " + std::to_string(*l1 + 1) + " � " + std::to_string(*l2 + 1) + "\r\n";
        //����� �����
        for (int j = *l1 + 1; j <= *l2; ++j) {
            tmp[j] = a[i][j];
            a[i][j] = a[i + 1][j];
            a[i + 1][j] = tmp[j];
        }
    }
    *out+="\r\n��� ��������:\r\n\r\n";
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
//�������� ������������� �� ������ ����� ���������
void GenAlgForm::MyForm::FIBcros(bool** a, int* popNum, int* trueCros) {
    *out += "�������� ������������� �� ������ ����� ���������\r\n";
    bool* tmp=new bool [4];//��������� ��������� ��� �������� ����� �� ����� ������
    for (int i = *popNum; i < *popNum + *trueCros; i += 2) {
        //����� ������� ������� � ������������ � ������� ���������, �� ���� ����� 1, 2 � 3 �����.
        //����� �����
        for (int j = 1; j < 4; j += 2) {
            tmp[j] = a[i][j];
            a[i][j] = a[i + 1][j];
            a[i + 1][j] = tmp[j];
        }
    }
    *out +="\r\n��� ��������:\r\n\r\n";
    for (int i = *popNum; i < *popNum + *trueCros; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (a[i][j])  *out += "1 "; else *out += "0 ";
        }
        *out +="\r\n";
        if (i % 2 == 1) *out += "\r\n";
    }
    delete [] tmp;
}
//������������� ������������ �������� ������������� 
void GenAlgForm::MyForm::OTPcros(bool** a, int* popNum, int* trueCros) {
    *out += "������������� ������������ �������� �������������\r\n";
    int* l1, * l2;
    int* tmpl=new int();//����� ����������� � ���������� ��� �� ������������
    bool* b1, * b2, * b11, * b22;//��� �������� ������ ���������
    for (int i = *popNum; i < *popNum + *trueCros; i += 2) {
        //��������� ���� ����� �����������
        l1 = new int(rand() % 3);
        l2 = new int(rand() % 3);
        while (*l1 == *l2) *l2 = rand() % 3;
        if (*l2 < *l1) {
            *tmpl = *l1;
            *l1 = *l2;
            *l2 = *tmpl;
        }
        *out += "��������� " + std::to_string(i + 1 - *popNum) + " � " + std::to_string(i + 2 - *popNum) + ": ������� ����� ����� ����� ��� �������� " + std::to_string(*l1 + 1) + " � " + std::to_string(*l2 + 1) + "\r\n";
        //��� i-�� ������� ��������� 1-���� ����� l1 � l2 <=> ����� 1) a[i] �� ����� 1 �� l1; 2) � ����� l2; 3) a[i+1] ����� 1. ����� ��������� 0
        //��� i+1-�� ������� ��������� 1-���� ����� l1 � l2 <=> ����� 1) a[i+1] �� ����� 1 �� l1; 2) � ����� l2; 3) a[i] ����� 1. ����� ��������� 0
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
    *out += "\r\n��� ��������:\r\n\r\n";
    for (int i = *popNum; i < *popNum + *trueCros; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (a[i][j])*out += "1 "; else *out += "0 ";
        }
        *out += "\r\n";
        if (i % 2 == 1) *out += "\r\n";
    }
    delete l1, l2, tmpl, b1, b2, b11, b22;
}
//��������-��������������� ������������ �������� ������������� 
void GenAlgForm::MyForm::PRTPcros(bool** a, int* popNum, int* trueCros) {
    *out += "��������-��������������� ������������ �������� �������������\r\n";
    bool* tmp = new bool [4];//��������� ��������� ��� �������� ����� �� ����� ������
    int* l1,* l2;
    int* tmpl=new int();//����� ����������� � ���������� ��� �� ������������
    int* b=new int();//������ ���������
    for (int i = *popNum; i < *popNum + *trueCros; i += 2) {
        //��������� ���� ����� �����������
        l1 = new int(rand() % 3);
        l2 = new int(rand() % 3);
        while (*l1 == *l2) *l2 = rand() % 3;
        if (*l2 < *l1) {
            *tmpl = *l1;
            *l1 = *l2;
            *l2 = *tmpl;
        }
        *out += "��������� " + std::to_string(i) + " � " + std::to_string(i + 1) + ": ������� ����� ����� ����� ��� �������� " + std::to_string(*l1) + " � " + std::to_string(*l2) + "\r\n";
        //����� ����� ���������� ������������ ������������ ����� l1 � l2
        for (int j = *l1 + 1; j <= *l2; ++j) {
            tmp[j] = a[i][j];
            a[i][j] = a[i + 1][j];
            a[i + 1][j] = tmp[j];
        }
        //����� ��������� ���������� �������� �� ���������� � �������� ������������� �� ������ �������� ���������������
        //��� ��������� �� l1
        for (int j = 0; j <= *l1; ++j) {
            //��� i-�� ��������
            *b = *l1 + 1;
            //���������� ������� ������� � ���������� ������� �� �������� ���� �� ������ ������ ��� �� ������ �� �������
            while (*b <= *l2 && a[i][j] != a[i][*b]) ++(*b);
            //���� �� ����� �� �������, �� ����� ������
            if (*b != *l2 + 1) a[i][j] = a[i + 1][*b];
            //���������� ��� i+1 ��������
            *b = *l1 + 1;
            while (*b <= *l2 && a[i + 1][j] != a[i + 1][*b]) ++(*b);
            if (*b != *l2 + 1) a[i + 1][j] = a[i][*b];
        }
        //��� ��������� ����� l2
        for (int j = *l2 + 1; j < 4; ++j) {
            *b = *l1 + 1;
            while (*b <= *l2 && a[i][j] != a[i][*b]) ++(*b);
            if (*b != *l2 + 1) a[i][j] = a[i + 1][*b];
            *b = *l1 + 1;
            while (*b <= *l2 && a[i + 1][j] != a[i + 1][*b]) ++(*b);
            if (*b != *l2 + 1) a[i + 1][j] = a[i][*b];
        }
    }
    *out += "\r\n��� ��������:\r\n\r\n";
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
// �������� �������
void GenAlgForm::MyForm::Pmut(bool** a, int* popNum, int* trueCros, int* maxCros, int* mutNum) {
    int* c, * g;//����� ��������� � ���� ��������� ��� �������
    *out += "�������� �������. ���������� �������: " + std::to_string(*mutNum) + "\r\n";
    for (int i = 0; i < *mutNum; ++i) {
        c = new int(rand() % *trueCros);
        g = new int(rand() % 4);
        *out += "������� ��������� ����� " + std::to_string(*c + 1) + ". ������ ��� �����" + std::to_string(*g + 1) + "\r\n";
        //������������ ��������� ��������� � ��� �������
        for (int j = 0; j < 4; ++j) {
            a[*popNum + *maxCros + i][j] = a[*popNum + *c][j];
        }
        //�������� �������� ��� 
        if (a[*popNum + *maxCros + i][*g]) a[*popNum + *maxCros + i][*g] = 0; else a[*popNum + *maxCros + i][*g] = 1;
    }
    delete c, g;
}
//������������
void GenAlgForm::MyForm::Tmut(bool** a, int* popNum, int* trueCros, int* maxCros, int* mutNum) {
    int* c;//����� ��������� ��������� ��� �������
    int* l1, * l2;
    int* tmpl=new int();//������ ����� ������ � ����� �����
    int* l3;//������� ������� ���������������� �����
    int* k; //������� ������� ���� �� �� ����� � ��������� ����� ����������� �������
    *out += "������������. ����������: " + std::to_string(*mutNum) + "\r\n";
    for (int i = 0; i < *mutNum; ++i) {
        //�������� ���������
        c = new int (rand() % (*trueCros));
        //�������� ���� �� 2-3 �����  
        l1 = new int(rand() % 4);
        l2 = new int(rand() % 4);
        while (*l1 == *l2 || abs(*l1 - *l2) > 2) *l2 = rand() % 4;
        if (*l2 < *l1) {
            *tmpl = *l1;
            *l1 = *l2;
            *l2 = *tmpl;
        }
        //�������� �������, �� ������� ������ ���� ����
        l3 = new int(rand() % 3);
        while (*l3 == *l1 || *l3 + abs(*l2 - *l1) > 3) *l3 = rand() % 3;
        *out += "������� ��������� ����� " + std::to_string(*c + 1) + ". � ���� ������ ���� �� " + std::to_string(*l1 + 1) + " �� " + std::to_string(*l2 + 1) + ". ���� ������� � ������� " + std::to_string(*l3 + 1) + "\r\n";
        //���������� ������������ ���� � ��������������� ���� �� ��������� �������
        for (int j = 0; j <= abs(*l2 - *l1); ++j) {
            a[*popNum + *maxCros + i][*l3 + j] = a[*popNum + *c][*l2 - j];
        }
        //���������� ���������� ����
        k = new int(0);
        for (int j = 0; j < *l1; ++j) {//������� ������� ���� ����� �� ����� � �������� ���������
            while (!(*k<*l3 || *k>*l3 + abs(*l2 - *l1))) ++(*k);//������� ������ ���� � ������������ ���������
            a[*popNum + *maxCros + i][*k] = a[*popNum + *c][j];
            ++(*k);
        }
        for (int j = *l2 + 1; j < 4; ++j) {//������� ������� ���� ������ �� ����� � �������� ���������
            while (!(*k<*l3 || *k> * l3 + abs(*l2 - *l1))) ++(*k);//������� ������ ���� � ������������ ���������
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
    srand((unsigned int)time(0)); // ��������� ��������� �����
    setlocale(LC_ALL, "Russian");
    popNum=-1; // ����������� ���������
    popNum = (int)FORMpopNum->Value;
    genNum=-1; // ����� ���������
    genNum = (int)FORMgenNum->Value;
    crosProb=-1; // ����������� �������������
    crosProb=(int)FORMcrosProb->Value;
    mutProb=-1; // ����������� �������
    mutProb=(int)FORMmutProb->Value;
    strat=-1; // ��������� �������� ���������
    if (strat1->Checked == true) strat = 1;
    else if (strat2->Checked == true) strat = 2;
    rangeB = 5;
    rangeE = 15;
    //������ �����������
    if (strat == 2) {
        range = (int)FORMrange->Value;//�������� ������������� �������� �� ������
        focus = 5 + rand()%11;//�����, ��������� � ������� ������� ������
        while (!(focus + range <= 15 && focus - range >= 5)) focus = 5 + rand() % 11;//���� �������� ��������� ������ ������ � ������� �������
        rangeB = focus - range;
        rangeE = focus + range;
    }
    sel=-1;//��� ��������
    if (sel1->Checked == true) sel = 1;
    else if (sel2->Checked == true) sel = 2;
    oper=-1;//�������� �������������
    if (oper1->Checked == true) oper = 1;
    else if (oper2->Checked == true) oper = 2;
    else if (oper3->Checked == true) oper = 3;
    else if (oper4->Checked == true) oper = 4;
    mut=-1;//�������� �������/��������
    if (mut1->Checked == true) mut = 1;
    else if (mut2->Checked == true) mut = 2;

    //����������� ������� ������������� ����. ���� ������ ��������� �� ������ ����, �� ������������ ��������
    maxCros = 0;
    if (popNum >= 2) {
        maxCros = popNum * crosProb / 100;
        if (maxCros % 2 == 1) --maxCros;
        if (maxCros < 2 && crosProb != 0) maxCros = 2;
    }

    //����������� ������� ���� �������. ���� ������������ ����������, ������� �� ����������
    mutNum = 0;
    if (maxCros)  mutNum = maxCros * mutProb / 100;

    // ��������� ��������� ��������� 
    //������� ������
    bool** pop = new bool* [popNum + maxCros + mutNum];
    for (int i = 0; i < popNum + maxCros + mutNum; ++i) {
        pop[i] = new bool[4];
        for (int j = 0; j < 4; ++j) {
            pop[i][j] = true;
        }
    }
    //��������� ��������� ���������
    for (int i = 0; i < popNum; ++i) {
        // ��������� ���������
        do {
            for (int j = 0; j < 4; ++j) {
                pop[i][j] = rand() % 2;
            }
        } while (ft(pop[i]) < rangeB || ft(pop[i]) > rangeE);
    }
    // ����� ��������� ���������    
    if (strat == 1) *out+="������� ��������� ���������.\r\n\r\n";
    else *out += "������� ��������� ������������(�����: "+ std::to_string(focus)+ ").\r\n\r\n";
    *out += "��������� ��������� (� ������� ������� ������� � �������� ������� �������):\r\n\r\n";

    for (int i = 0; i < popNum; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (pop[i][j]) *out += "1 ";
            else *out += "0 ";
        }
        *out += "("+ std::to_string(ft(pop[i])) + " " + std::to_string(tf(ft(pop[i]))) + ")" + "\r\n";
    }
    // ������ ��������.
    trueCros = 0;
    for (int k = 1; k <= genNum; ++k) { 
        *out += "---------------------------------------\r\n";
        *out += "��������� " + std::to_string(k) + "\r\n\r\n";
        //��������   
        if (sel == 1) eliteSelection(pop, &popNum, &maxCros, &trueCros);
        else {
            trueCros = maxCros;
            inbreedingSelection(pop, &popNum, &maxCros);
        }
        //������������
        if (oper == 1) STPcros(pop, &popNum, &trueCros);
        if (oper == 2) OTPcros(pop, &popNum, &trueCros);
        if (oper == 3) PRTPcros(pop, &popNum, &trueCros);
        if (oper == 4) FIBcros(pop, &popNum, &trueCros);
        //�������
        if (mut == 1) Pmut(pop, &popNum, &trueCros, &maxCros, &mutNum);
        if (mut == 2) Tmut(pop, &popNum, &trueCros, &maxCros, &mutNum);
        //���������� ��������� �� ������
        *out += "\r\n ��������� ����� ������������� � ������� (� ������� ������� �������� ������� �������): \r\n\r\n";
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
        //�����
        quickSort(pop,0, popNum + maxCros + mutNum-1);
        //������� ��������� � ������� �����������������
        avrFit = 0;
        numFit = 0;
        *out += "\r\n ��������� ����� ������ (� ������� ������� ������� � �������� ������� �������): \r\n\r\n";
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
            *out += "\r\n ������� ����������������� ���������: ";
            *out += std::to_string(avrFit) + "\r\n";
        } 
        else {
            *out += "\r\n � ��������� �� �������� ��������������� ������. ";
            break; 
        }
    }
    //����� ������:
    if (numFit) *out += "\r\n �����: " + std::to_string(ft(pop[0]));
    else *out += "\r\n ��������� �������, ����� �� ������.";
    //������
    for (int i = 0; i < popNum + maxCros + mutNum; ++i) {
        delete[] pop[i];
    }
    delete[] pop;
    delete FORMcout->Text;
    FORMcout->Text = gcnew String(out->c_str());
    *out = "";
}
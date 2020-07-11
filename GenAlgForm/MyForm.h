#pragma once

namespace GenAlgForm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::NumericUpDown^ FORMpopNum;


	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::NumericUpDown^ FORMgenNum;



	private: System::Windows::Forms::Label^ label3;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::RadioButton^ strat1;
	private: System::Windows::Forms::RadioButton^ strat2;
	private: System::Windows::Forms::NumericUpDown^ FORMrange;







	private: System::Windows::Forms::Label^ label6;



	private: System::Windows::Forms::GroupBox^ FORMstrat;
	private: System::Windows::Forms::GroupBox^ FORMsel;



	private: System::Windows::Forms::RadioButton^ sel2;



	private: System::Windows::Forms::RadioButton^ sel1;
	private: System::Windows::Forms::GroupBox^ FORMoper;

	private: System::Windows::Forms::RadioButton^ oper4;



	private: System::Windows::Forms::RadioButton^ oper3;

	private: System::Windows::Forms::RadioButton^ oper2;

	private: System::Windows::Forms::RadioButton^ oper1;
	private: System::Windows::Forms::GroupBox^ FORMmut;

	private: System::Windows::Forms::RadioButton^ mut2;



	private: System::Windows::Forms::RadioButton^ mut1;
	private: System::Windows::Forms::NumericUpDown^ FORMcrosProb;
	private: System::Windows::Forms::NumericUpDown^ FORMmutProb;
	public: System::Windows::Forms::TextBox^ FORMcout;
	private:



	private:

	private: System::Windows::Forms::Button^ StartGeneticAlgorithm;








	private: System::ComponentModel::IContainer^ components;

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->FORMpopNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->FORMgenNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->strat1 = (gcnew System::Windows::Forms::RadioButton());
			this->strat2 = (gcnew System::Windows::Forms::RadioButton());
			this->FORMrange = (gcnew System::Windows::Forms::NumericUpDown());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->FORMstrat = (gcnew System::Windows::Forms::GroupBox());
			this->FORMsel = (gcnew System::Windows::Forms::GroupBox());
			this->sel2 = (gcnew System::Windows::Forms::RadioButton());
			this->sel1 = (gcnew System::Windows::Forms::RadioButton());
			this->FORMoper = (gcnew System::Windows::Forms::GroupBox());
			this->oper4 = (gcnew System::Windows::Forms::RadioButton());
			this->oper3 = (gcnew System::Windows::Forms::RadioButton());
			this->oper2 = (gcnew System::Windows::Forms::RadioButton());
			this->oper1 = (gcnew System::Windows::Forms::RadioButton());
			this->FORMmut = (gcnew System::Windows::Forms::GroupBox());
			this->mut2 = (gcnew System::Windows::Forms::RadioButton());
			this->mut1 = (gcnew System::Windows::Forms::RadioButton());
			this->FORMcrosProb = (gcnew System::Windows::Forms::NumericUpDown());
			this->FORMmutProb = (gcnew System::Windows::Forms::NumericUpDown());
			this->FORMcout = (gcnew System::Windows::Forms::TextBox());
			this->StartGeneticAlgorithm = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FORMpopNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FORMgenNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FORMrange))->BeginInit();
			this->FORMstrat->SuspendLayout();
			this->FORMsel->SuspendLayout();
			this->FORMoper->SuspendLayout();
			this->FORMmut->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FORMcrosProb))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FORMmutProb))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(23, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(105, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Размер популяции:";
			// 
			// FORMpopNum
			// 
			this->FORMpopNum->Location = System::Drawing::Point(26, 25);
			this->FORMpopNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->FORMpopNum->Name = L"FORMpopNum";
			this->FORMpopNum->Size = System::Drawing::Size(120, 20);
			this->FORMpopNum->TabIndex = 1;
			this->FORMpopNum->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(23, 60);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(125, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Количество генераций:";
			// 
			// FORMgenNum
			// 
			this->FORMgenNum->Location = System::Drawing::Point(26, 76);
			this->FORMgenNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->FORMgenNum->Name = L"FORMgenNum";
			this->FORMgenNum->Size = System::Drawing::Size(120, 20);
			this->FORMgenNum->TabIndex = 3;
			this->FORMgenNum->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 50, 0, 0, 0 });
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(23, 110);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(155, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Вероятность кроссинговера:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(23, 159);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(120, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Вероятность мутации:";
			// 
			// strat1
			// 
			this->strat1->AutoSize = true;
			this->strat1->Checked = true;
			this->strat1->Location = System::Drawing::Point(12, 15);
			this->strat1->Name = L"strat1";
			this->strat1->Size = System::Drawing::Size(76, 17);
			this->strat1->TabIndex = 9;
			this->strat1->TabStop = true;
			this->strat1->Text = L"Дробовик";
			this->strat1->UseVisualStyleBackColor = true;
			// 
			// strat2
			// 
			this->strat2->AutoSize = true;
			this->strat2->Location = System::Drawing::Point(12, 38);
			this->strat2->Name = L"strat2";
			this->strat2->Size = System::Drawing::Size(95, 17);
			this->strat2->TabIndex = 10;
			this->strat2->Text = L"Фокусировка";
			this->strat2->UseVisualStyleBackColor = true;
			// 
			// FORMrange
			// 
			this->FORMrange->Location = System::Drawing::Point(231, 281);
			this->FORMrange->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->FORMrange->Name = L"FORMrange";
			this->FORMrange->Size = System::Drawing::Size(46, 20);
			this->FORMrange->TabIndex = 12;
			this->FORMrange->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(12, 283);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(208, 13);
			this->label6->TabIndex = 14;
			this->label6->Text = L"Велечина смещения при фокусировке: ";
			// 
			// FORMstrat
			// 
			this->FORMstrat->Controls->Add(this->strat2);
			this->FORMstrat->Controls->Add(this->strat1);
			this->FORMstrat->Location = System::Drawing::Point(26, 213);
			this->FORMstrat->Name = L"FORMstrat";
			this->FORMstrat->Size = System::Drawing::Size(251, 60);
			this->FORMstrat->TabIndex = 17;
			this->FORMstrat->TabStop = false;
			this->FORMstrat->Text = L"Стратегия создания популяции:";
			// 
			// FORMsel
			// 
			this->FORMsel->Controls->Add(this->sel2);
			this->FORMsel->Controls->Add(this->sel1);
			this->FORMsel->Location = System::Drawing::Point(26, 307);
			this->FORMsel->Name = L"FORMsel";
			this->FORMsel->Size = System::Drawing::Size(251, 60);
			this->FORMsel->TabIndex = 18;
			this->FORMsel->TabStop = false;
			this->FORMsel->Text = L"Вид селекции:";
			// 
			// sel2
			// 
			this->sel2->AutoSize = true;
			this->sel2->Location = System::Drawing::Point(12, 38);
			this->sel2->Name = L"sel2";
			this->sel2->Size = System::Drawing::Size(80, 17);
			this->sel2->TabIndex = 10;
			this->sel2->Text = L"Инбридинг";
			this->sel2->UseVisualStyleBackColor = true;
			// 
			// sel1
			// 
			this->sel1->AutoSize = true;
			this->sel1->Checked = true;
			this->sel1->Location = System::Drawing::Point(12, 15);
			this->sel1->Name = L"sel1";
			this->sel1->Size = System::Drawing::Size(67, 17);
			this->sel1->TabIndex = 9;
			this->sel1->TabStop = true;
			this->sel1->Text = L"Элитная";
			this->sel1->UseVisualStyleBackColor = true;
			// 
			// FORMoper
			// 
			this->FORMoper->Controls->Add(this->oper4);
			this->FORMoper->Controls->Add(this->oper3);
			this->FORMoper->Controls->Add(this->oper2);
			this->FORMoper->Controls->Add(this->oper1);
			this->FORMoper->Location = System::Drawing::Point(26, 373);
			this->FORMoper->Name = L"FORMoper";
			this->FORMoper->Size = System::Drawing::Size(254, 109);
			this->FORMoper->TabIndex = 19;
			this->FORMoper->TabStop = false;
			this->FORMoper->Text = L"Оператор кроссинговера:";
			// 
			// oper4
			// 
			this->oper4->AutoSize = true;
			this->oper4->Location = System::Drawing::Point(12, 84);
			this->oper4->Name = L"oper4";
			this->oper4->Size = System::Drawing::Size(170, 17);
			this->oper4->TabIndex = 12;
			this->oper4->Text = L"На основе чисел Фибоначчи";
			this->oper4->UseVisualStyleBackColor = true;
			// 
			// oper3
			// 
			this->oper3->AutoSize = true;
			this->oper3->Location = System::Drawing::Point(12, 61);
			this->oper3->Name = L"oper3";
			this->oper3->Size = System::Drawing::Size(239, 17);
			this->oper3->TabIndex = 11;
			this->oper3->Text = L"Частично соответствующий двухточечный";
			this->oper3->UseVisualStyleBackColor = true;
			// 
			// oper2
			// 
			this->oper2->AutoSize = true;
			this->oper2->Location = System::Drawing::Point(12, 38);
			this->oper2->Name = L"oper2";
			this->oper2->Size = System::Drawing::Size(178, 17);
			this->oper2->TabIndex = 10;
			this->oper2->Text = L"Упорядоченный двухточечный";
			this->oper2->UseVisualStyleBackColor = true;
			// 
			// oper1
			// 
			this->oper1->AutoSize = true;
			this->oper1->Checked = true;
			this->oper1->Location = System::Drawing::Point(12, 15);
			this->oper1->Name = L"oper1";
			this->oper1->Size = System::Drawing::Size(164, 17);
			this->oper1->TabIndex = 9;
			this->oper1->TabStop = true;
			this->oper1->Text = L"Стандартный двухточечный";
			this->oper1->UseVisualStyleBackColor = true;
			// 
			// FORMmut
			// 
			this->FORMmut->Controls->Add(this->mut2);
			this->FORMmut->Controls->Add(this->mut1);
			this->FORMmut->Location = System::Drawing::Point(29, 488);
			this->FORMmut->Name = L"FORMmut";
			this->FORMmut->Size = System::Drawing::Size(251, 60);
			this->FORMmut->TabIndex = 20;
			this->FORMmut->TabStop = false;
			this->FORMmut->Text = L"Мутация/инверсия:";
			// 
			// mut2
			// 
			this->mut2->AutoSize = true;
			this->mut2->Location = System::Drawing::Point(12, 38);
			this->mut2->Name = L"mut2";
			this->mut2->Size = System::Drawing::Size(98, 17);
			this->mut2->TabIndex = 10;
			this->mut2->Text = L"Транспозиция";
			this->mut2->UseVisualStyleBackColor = true;
			// 
			// mut1
			// 
			this->mut1->AutoSize = true;
			this->mut1->Checked = true;
			this->mut1->Location = System::Drawing::Point(12, 15);
			this->mut1->Name = L"mut1";
			this->mut1->Size = System::Drawing::Size(72, 17);
			this->mut1->TabIndex = 9;
			this->mut1->TabStop = true;
			this->mut1->Text = L"Точечная";
			this->mut1->UseVisualStyleBackColor = true;
			// 
			// FORMcrosProb
			// 
			this->FORMcrosProb->Location = System::Drawing::Point(26, 126);
			this->FORMcrosProb->Name = L"FORMcrosProb";
			this->FORMcrosProb->Size = System::Drawing::Size(120, 20);
			this->FORMcrosProb->TabIndex = 21;
			this->FORMcrosProb->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 70, 0, 0, 0 });
			// 
			// FORMmutProb
			// 
			this->FORMmutProb->Location = System::Drawing::Point(26, 175);
			this->FORMmutProb->Name = L"FORMmutProb";
			this->FORMmutProb->Size = System::Drawing::Size(120, 20);
			this->FORMmutProb->TabIndex = 22;
			this->FORMmutProb->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
			// 
			// FORMcout
			// 
			this->FORMcout->Location = System::Drawing::Point(300, 25);
			this->FORMcout->Multiline = true;
			this->FORMcout->Name = L"FORMcout";
			this->FORMcout->ReadOnly = true;
			this->FORMcout->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->FORMcout->Size = System::Drawing::Size(688, 504);
			this->FORMcout->TabIndex = 23;
			// 
			// StartGeneticAlgorithm
			// 
			this->StartGeneticAlgorithm->Location = System::Drawing::Point(447, 545);
			this->StartGeneticAlgorithm->Name = L"StartGeneticAlgorithm";
			this->StartGeneticAlgorithm->Size = System::Drawing::Size(401, 30);
			this->StartGeneticAlgorithm->TabIndex = 24;
			this->StartGeneticAlgorithm->Text = L"Начать выполнение генетического алгоритма";
			this->StartGeneticAlgorithm->UseVisualStyleBackColor = true;
			this->StartGeneticAlgorithm->Click += gcnew System::EventHandler(this, &MyForm::StartGeneticAlgorithm_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1010, 600);
			this->Controls->Add(this->StartGeneticAlgorithm);
			this->Controls->Add(this->FORMcout);
			this->Controls->Add(this->FORMmutProb);
			this->Controls->Add(this->FORMcrosProb);
			this->Controls->Add(this->FORMmut);
			this->Controls->Add(this->FORMoper);
			this->Controls->Add(this->FORMsel);
			this->Controls->Add(this->FORMstrat);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->FORMrange);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->FORMgenNum);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->FORMpopNum);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"Генетический алгоритм";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FORMpopNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FORMgenNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FORMrange))->EndInit();
			this->FORMstrat->ResumeLayout(false);
			this->FORMstrat->PerformLayout();
			this->FORMsel->ResumeLayout(false);
			this->FORMsel->PerformLayout();
			this->FORMoper->ResumeLayout(false);
			this->FORMoper->PerformLayout();
			this->FORMmut->ResumeLayout(false);
			this->FORMmut->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FORMcrosProb))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FORMmutProb))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

	private: System::Void StartGeneticAlgorithm_Click(System::Object^ sender, System::EventArgs^ e);
	int ft(bool* a);
	int tf(int x);
	void quickSort(bool** a, int low, int high);
	void eliteSelection(bool** a, int* popNum, int* maxCros, int* exTrueCros);
	void inbreedingSelection(bool** a, int* popNum, int* maxCros);
	void STPcros(bool** a, int* popNum, int* trueCros);
	void FIBcros(bool** a, int* popNum, int* trueCros);
	void OTPcros(bool** a, int* popNum, int* trueCros);
	void PRTPcros(bool** a, int* popNum, int* trueCros);
	void Pmut(bool** a, int* popNum, int* trueCros, int* maxCros, int* mutNum);
	void Tmut(bool** a, int* popNum, int* trueCros, int* maxCros, int* mutNum);
};
}
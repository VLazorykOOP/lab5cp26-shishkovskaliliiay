#pragma once
#include "Task2.h"
#include <cmath>

namespace Project2 {
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class Task1 : public System::Windows::Forms::Form
	{
	public:
		Task1(void)
		{
			InitializeComponent();
			this->DoubleBuffered = true;
			CreateNumericInputs();
		}

	protected:
		~Task1() { if (components) delete components; }

	private:
		System::Windows::Forms::MenuStrip^ menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^ завдання1ToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ завдання2ToolStripMenuItem;
		System::ComponentModel::IContainer^ components;

		array<NumericUpDown^>^ numX;
		array<NumericUpDown^>^ numY;

		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->завдання1ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->завдання2ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();

			this->menuStrip1->Items->AddRange(gcnew cli::array<ToolStripItem^>(2) {
				this->завдання1ToolStripMenuItem, this->завдання2ToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Size = System::Drawing::Size(800, 28);

			this->завдання1ToolStripMenuItem->Text = L"Завдання №1";
			this->завдання2ToolStripMenuItem->Text = L"Завдання №2";
			this->завдання2ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Task1::завдання2ToolStripMenuItem_Click);

			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(800, 650); // Встановлено розмір
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Task1";
			this->Text = L"Крива Без'є - Задача 1";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Task1::Task1_Paint);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
		}

		void CreateNumericInputs() {
			numX = gcnew array<NumericUpDown^>(4);
			numY = gcnew array<NumericUpDown^>(4);
			array<int>^ startX = { 150, 250, 500, 600 };
			array<int>^ startY = { 500, 200, 200, 500 };

			for (int i = 0; i < 4; i++) {
				numX[i] = gcnew NumericUpDown();
				numX[i]->Location = System::Drawing::Point(15 + (i * 140), 40);
				numX[i]->Size = System::Drawing::Size(60, 22);
				numX[i]->Maximum = 2000;
				numX[i]->Value = (Decimal)startX[i];
				numX[i]->ValueChanged += gcnew EventHandler(this, &Task1::OnUpdate);
				this->Controls->Add(numX[i]);

				numY[i] = gcnew NumericUpDown();
				numY[i]->Location = System::Drawing::Point(80 + (i * 140), 40);
				numY[i]->Size = System::Drawing::Size(60, 22);
				numY[i]->Maximum = 2000;
				numY[i]->Value = (Decimal)startY[i];
				numY[i]->ValueChanged += gcnew EventHandler(this, &Task1::OnUpdate);
				this->Controls->Add(numY[i]);
			}
		}

		void OnUpdate(Object^ sender, EventArgs^ e) { this->Invalidate(); }

		void Task1_Paint(Object^ sender, PaintEventArgs^ e) {
			Graphics^ g = e->Graphics;
			g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

			array<PointF>^ p = gcnew array<PointF>(4);
			for (int i = 0; i < 4; i++) p[i] = PointF((float)numX[i]->Value, (float)numY[i]->Value);

			Pen^ dashPen = gcnew Pen(Color::LightGray, 1.0f);
			dashPen->DashStyle = System::Drawing::Drawing2D::DashStyle::Dash;
			g->DrawLine(dashPen, p[0], p[1]);
			g->DrawLine(dashPen, p[1], p[2]);
			g->DrawLine(dashPen, p[2], p[3]);

			Pen^ bezierPen = gcnew Pen(Color::Red, 2.5f);
			PointF prev = p[0];
			for (double t = 0.0; t <= 1.001; t += 0.01) {
				double mt = 1.0 - t;
				float x = (float)(mt * mt * mt * p[0].X + 3 * t * mt * mt * p[1].X + 3 * t * t * mt * p[2].X + t * t * t * p[3].X);
				float y = (float)(mt * mt * mt * p[0].Y + 3 * t * mt * mt * p[1].Y + 3 * t * t * mt * p[2].Y + t * t * t * p[3].Y);
				g->DrawLine(bezierPen, prev, PointF(x, y));
				prev = PointF(x, y);
			}

			for (int i = 0; i < 4; i++) {
				g->FillEllipse(Brushes::Blue, p[i].X - 4.0f, p[i].Y - 4.0f, 8.0f, 8.0f);
				g->DrawString("P" + i, this->Font, Brushes::Black, p[i].X + 5.0f, p[i].Y + 5.0f);
			}
		}

		System::Void завдання2ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			Task2^ secondForm = gcnew Task2();
			secondForm->Show();
		}
	};
}

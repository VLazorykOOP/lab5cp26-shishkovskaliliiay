#pragma once
#include <cmath>

namespace Project2 {
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class Task2 : public System::Windows::Forms::Form
	{
	private:
		NumericUpDown^ numK;
		NumericUpDown^ numA;
		NumericUpDown^ numB;
		Label^ lblK;
		Label^ lblAB;

	public:
		Task2(void)
		{
			InitializeComponent();
			this->DoubleBuffered = true;
			this->ClientSize = System::Drawing::Size(800, 650); // Однаковий розмір
			this->Text = L"Фрактал: Дерево Архімеда";

			// Налаштування елементів як на скріншоті
			lblK = gcnew Label(); lblK->Text = "K:"; lblK->Location = Point(10, 15); lblK->Width = 20;
			numK = gcnew NumericUpDown(); numK->Location = Point(35, 12); numK->Size = System::Drawing::Size(50, 22);
			numK->Value = 14; numK->ValueChanged += gcnew EventHandler(this, &Task2::OnUpdate);

			lblAB = gcnew Label(); lblAB->Text = "A/B:"; lblAB->Location = Point(100, 15); lblAB->Width = 35;
			numA = gcnew NumericUpDown(); numA->Location = Point(140, 12); numA->Size = System::Drawing::Size(60, 22);
			numA->Value = 67; numA->ValueChanged += gcnew EventHandler(this, &Task2::OnUpdate);

			numB = gcnew NumericUpDown(); numB->Location = Point(210, 12); numB->Size = System::Drawing::Size(60, 22);
			numB->Value = 57; numB->ValueChanged += gcnew EventHandler(this, &Task2::OnUpdate);

			this->Controls->Add(lblK); this->Controls->Add(numK);
			this->Controls->Add(lblAB); this->Controls->Add(numA); this->Controls->Add(numB);
		}

	private:
		void OnUpdate(Object^ sender, EventArgs^ e) { this->Invalidate(); }

		void DrawTree(Graphics^ g, float x, float y, float a, float b, double angle, int k) {
			if (k <= 0) return;
			double rad = angle * Math::PI / 180.0;

			float x2 = x + a * (float)Math::Cos(rad);
			float y2 = y - a * (float)Math::Sin(rad);
			float x3 = x2 - b * (float)Math::Sin(rad);
			float y3 = y2 - b * (float)Math::Cos(rad);
			float x4 = x - b * (float)Math::Sin(rad);
			float y4 = y - b * (float)Math::Cos(rad);

			g->DrawPolygon(Pens::Black, gcnew array<PointF>{PointF(x, y), PointF(x2, y2), PointF(x3, y3), PointF(x4, y4)});

			DrawTree(g, x4, y4, a * 0.7f, b * 0.7f, angle + 30, k - 1);
			DrawTree(g, x3, y3, a * 0.7f, b * 0.7f, angle - 30, k - 1);
		}

	protected:
		virtual void OnPaint(PaintEventArgs^ e) override {
			Graphics^ g = e->Graphics;
			g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
			DrawTree(g, 400, 580, (float)numA->Value, (float)numB->Value, 0, (int)numK->Value);
		}

		void InitializeComponent(void) {
			this->SuspendLayout();
			this->Name = L"Task2";
			this->ResumeLayout(false);
		}
	};
}

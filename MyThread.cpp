//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MyThread.h"
#include "Unit1.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall MyThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
 void Mutation(std::vector < std::vector <int> >  &vec)
{
	for(int z=0; z<vec.size(); z++)
	{
		for(int i =0; i<vec[z].size(); i++)
		{
			int s = rand()%100;
			if(s<StrToInt(Form1->Edit2->Text))
			{
				if(vec[z][i]==0)vec[z][i]=1;
				else vec[z][i]=0;
			}
		}
	}
}

void Crossing(std::vector < std::vector <int> >  &vec)
{
	for(int i = 0; i<vec.size(); i+=2)
	{
		std::vector <int> first = vec[i];
		std::vector <int> second = vec[i+1];

		for(int j = second.size()/2; j< second.size(); j++)
		{
			second[j] =  vec[i][j];

		}

		for(int j = first.size()/2; j<first.size(); j++)
		{
			first[j] = vec[i+1][j];
		}
		vec[i] = first;
		vec[i+1] = second;
	}
}
int FitnessFunc(std::vector<int > mas, std::vector<int > etalon)
{
	 int count = 0;
	 for(int i=0; i<mas.size(); i++)
	 {
		if(mas[i]== etalon[i]) count++;
	 }
	 return count;
}

std::vector<int> GetBestOsob(std::vector < std::vector <int> >  &vec, std::vector<int > etalon)
{
	int max =0;
	for(int i=0; i<vec.size(); i++)
	{
		if(FitnessFunc(vec[i],etalon)>max) max = FitnessFunc(vec[i],etalon);
	}
	for(int i=0; i<vec.size(); i++)
	{
		if(FitnessFunc(vec[i],etalon)==max)
		{
			//ShowMessage((UnicodeString)vec.size() + " in getBEstOsob");
			return vec[i];
		}
	}
	ShowMessage("Error");
}

void Selection(std::vector < std::vector <int> >  &vec, std::vector<int > &etalon)
{
	//сначала узнаем сумму фитнесс функций
	int sum = 0;
	int *intervals = new int[vec.size()];
	int *mas = new int[vec.size()];
	for(int i = 0; i<vec.size(); i++)
	{
		int r = FitnessFunc(vec[i], etalon);
		sum+=r;
		intervals[i]=sum;

	}
	//теперь делаем выборку))))
	std::vector < std::vector <int> >  out;
	for(int i=0; i< vec.size(); i++)
	{
		int s = rand()%sum;
		int j = 0;
		while(s>intervals[j])
		{
			j++;
		}
		if(j<0)ShowMessage("Ошибка в скрещивании");
		out.push_back(vec[j]);

	}
	//ShowMessage((UnicodeString)out[0].size() + " Размер out");
	vec = out;

	//теперь отсортируем по убыванию фитнесс ф-и

	for(int i =0; i< vec.size(); i++)
	{
		mas[i]=FitnessFunc(vec[i], etalon);
	}

	for(int i = 0; i< vec.size(); i++)
	{
		for(int j=0; j<vec.size()-1; j++)
		{
			if(mas[j]<mas[j+1])
			{
				int k = mas[j];
				mas[j] = mas[j+1];
				mas[j+1]=k;

				std::vector<int> temp = vec[j];
				vec[j]=vec[j+1];
				vec[j+1] = temp;
				temp.clear();
			}
		}
	}

	delete mas;
    delete intervals;
}



std::vector<TColor> IntToPixels(std::vector<int > &mas)
{

	std::vector<TColor> vec;

	for(int i =0; i< mas.size(); i++)
	{
		if(mas[i]==0)vec.push_back(clWhite);
		else vec.push_back(clBlack);
	}
	return vec;
}

void FillBitmap(std::vector<int > &mas, TBitmap* output)
{
	output->Canvas->Lock();
	//ShowMessage(mas.size());
	std::vector <TColor> color = IntToPixels(mas);
	for(int i=0; i<output->Width; i++)
	{
		for(int j=0; j< output->Height; j++)
		{
			output->Canvas->Pixels[i][j] = color[output->Height * i + j];
		}

	}
	color.clear();
	output->Canvas->Unlock();
}




TBitmap* ResizeB(TBitmap* in, int koef)
{
	in->Canvas->Lock();
	TBitmap* out = new TBitmap();
	out->Canvas->Lock();
	out->Height = in->Height * koef;
	out->Width = in->Width * koef;

	for(int i = 0 ; i<in->Width; i++)
	{
		for(int z=0; z<koef; z++)
		{
			for(int j=0; j< in->Height; j++)
			{
				for(int k=0; k<koef; k++)
				{
					out->Canvas->Pixels[i*koef+z][j*koef+k] = in->Canvas->Pixels[i][j];
				}
			}
		}
	}
	in->Canvas->Unlock();
	out->Canvas->Unlock();



	return out;
}
using std::vector;
__fastcall MyThread::MyThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall MyThread::Execute()
{
	//---- Place thread code here ----

    Form1->Timer1->Interval = StrToInt(Form1->Edit3->Text);


	Form1->bitmap = new TBitmap();
	Form1->bitmap->LoadFromFile("fcsm.bmp");
	Form1->input = ResizeB(Form1->bitmap, 10);
	//ShowMessage(Form1->input->Width);
	Form1->CanDrawBitmap = true;
	Form1->CanDrawInput = true;

	Form1->output = new TBitmap();
	Form1->bitmap->Canvas->Lock();
	Form1->output->Canvas->Lock();

	Form1->output->SetSize(Form1->bitmap->Width, Form1->bitmap->Height);
	std::vector<int> etalon;

	//bitmap->Canvas->Lock();
	for(int i = 0; i<Form1->bitmap->Width; i++)
	{
		for(int j = 0; j<Form1->bitmap->Height; j++)
		{

			if(Form1->bitmap->Canvas->Pixels[i][j]==clBlack)
			etalon.push_back(1);
			else etalon.push_back(0);

		}
	}
	//bitmap->Canvas->Unlock();

	//начнем делать генетический алгоритм
	int PoulationSize = StrToInt(Form1->Edit1->Text);

	vector<          vector<int>           > population;
	for(int i =0; i<PoulationSize; i++)
	{
		vector<int> temp;
		for(int j=0; j<etalon.size(); j++)
		{
			int a = rand()%2;
			temp.push_back(a);
		}
		population.push_back(temp);
	}

	//создали первую популяцию, пока без проблем
	vector<int> temp = GetBestOsob(population, etalon);
	int BestFunc = FitnessFunc(etalon, etalon);
	Form1->Label8->Caption = BestFunc;
	//ShowMessage((UnicodeString)BestFunc);
	Form1->bitmap->Canvas->Unlock();
	Form1->output->Canvas->Unlock();
    //ShowMessage((UnicodeString)population[0].size() + " Размер нервого элемента популяции до цикла");

	int iteration = 0;
	while(FitnessFunc(temp, etalon) < BestFunc && iteration<100000)
	{
		Form1->bitmap->Canvas->Lock();
		//ShowMessage((UnicodeString)population[0].size() + " Размер первого элемента популяции до отбора");
		Form1->output->Canvas->Lock();
		Form1->output->SetSize(Form1->bitmap->Width, Form1->bitmap->Height);
		Form1->bitmap->Canvas->Unlock();
		Form1->output->Canvas->Unlock();
		Form1->bitmap->Canvas->Lock();
		Form1->output->Canvas->Lock();
		Selection(population, etalon);
		//ShowMessage((UnicodeString)population[0].size() + " Размер первого элемента популяции до скрещивания");
		Crossing(population);
		//ShowMessage((UnicodeString)population[0].size() + " Размер первого элемента популяции до мутации");
		Mutation(population);
		temp =  GetBestOsob(population, etalon);

		Form1->bitmap->Canvas->Unlock();
		Form1->output->Canvas->Unlock();

		//ShowMessage((UnicodeString)population[0].size() + " Размер первого элемента популяции после всего");

		FillBitmap(temp, Form1->output);
		//output = ResizeB(output, 10);
		Form1->output = ResizeB(Form1->output, 10);
		Form1->CanDrawOutput = true;
		iteration ++;
		int y = FitnessFunc(temp, etalon);
		Form1->Label2->Caption = iteration;
		Form1->Label4->Caption = y;
		if(y> StrToInt(Form1->Label6->Caption)) Form1->Label6->Caption = y;
		//if(population.size()>10)ShowMessage(population.size());
		//ShowMessage((UnicodeString)temp.size() + " Размер temp") ;
	}
	//ShowMessage("Вышли из цикла");



	//output->Canvas->Unlock();

	//delete Form1->bitmap;
	//delete Form1->input;
	//delete Form1->output;




}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "MyThread.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
    Form1->DoubleBuffered = true;
//	Form1->Canvas->Lock();
//	bitmap->Canvas->Lock();

	//Form1->Canvas->Ellipse(100,100,200,200);
//  	bitmap->Canvas[i][j]
//	Form1->Canvas->Unlock();
//	bitmap->Canvas->Unlock();

}





//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
	Form1->BitBtn1->Enabled = false;
	MyThread *thread = new MyThread(false);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	if(CanDrawBitmap)
	{
		//Form1->bitmap->Canvas->Lock();
		//Form1->Canvas->Lock();
		//Form1->Canvas->Draw(230,0,Form1->bitmap);
		//Form1->Canvas->Unlock();
		//Form1->bitmap->Canvas->Unlock();
		//ShowMessage(bitmap->Width);
		//ShowMessage(bitmap->Height);
		//CanDrawBitmap = false;
	}

	if(CanDrawInput)
	{
		Form1->input->Canvas->Lock();
		Form1->Canvas->Lock();
		Form1->Canvas->Draw(0,0,Form1->input);
		Form1->Canvas->Unlock();
		Form1->input->Canvas->Unlock();
	}

	if(CanDrawOutput)
	{
		Form1->Canvas->Lock();
		Form1->output->Canvas->Lock();
		Form1->Canvas->Draw(0,150,Form1->output);
		Form1->Canvas->Unlock();
		Form1->output->Canvas->Unlock();
		CanDrawOutput = false;
	}

	//Form1->Canvas->Draw(0,0, Form1->input);
	//Form1->Canvas->Draw(230,0,Form1->bitmap);
	//if(BitBtn1->Enabled == false)BitBtn1->Enabled = true;
	//else BitBtn1->Enabled = false;
}
//---------------------------------------------------------------------------


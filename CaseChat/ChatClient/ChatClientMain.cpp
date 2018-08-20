//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ChatClientMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IrisCSocket"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::sckConnected(TObject *Sender)
{
	try {
		memo->Lines->Add("Conectado...");
		pnConn->Visible = false;
		pnLogin->Visible = true;

	} catch (...) {
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::sckDisconnected(TObject *Sender)
{
	try {
		memo->Lines->Add("Desconectado...");
		pnConn->Visible = true;
		pnLogin->Visible = false;
		edUser->Enabled = true;
		edUser->Text = "";
		btLogin->Caption = "Login";
		memo->Lines->Clear();

	} catch (...) {
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::sckReadBuff(TObject *Sender, UnicodeString Buff)
{
	try {
		String msg = Buff, de;

		if (msg.Trim().UpperCase().Pos("LOGIN_OK") > 0) {
			btSend->Enabled = true;
			edUser->Enabled = false;
			btLogin->Caption = "Desconectar";
			memo->Lines->Add("Você está OnLine...");

		} else if(msg.Trim().UpperCase().Pos("|MESSAGE|") > 0) {
			de = msg.SubString(0,msg.Trim().UpperCase().Pos("|MESSAGE|")-1);
			memo->Lines->Add(Time().FormatString("HH:MM:SS") + " : De: "+ de +" : " + msg.SubString(msg.Trim().UpperCase().Pos("|MESSAGE|")+9,msg.Length()));

		}


	} catch (...) {
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::btConnectClick(TObject *Sender)
{
	try {
		sck->Host = edIP->Text;
		sck->Port = StrToInt(edPort->Text);
		sck->Initialize();
		sck->Connect();

	} catch (...) {
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::btSendClick(TObject *Sender)
{
	try {
		if (sck->Connected()) {
			sck->SendBuff(edUser->Text+"|MESSAGE|"+edMsg->Text);
		} else {
			sck->Disconnect();
			ShowMessage("Você foi desconectado...");
			sckDisconnected(this);
        }
	} catch (...) {
	}
	edMsg->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btLoginClick(TObject *Sender)
{
	try {
		if (!edUser->Text.Trim().IsEmpty()) {
			if (btLogin->Caption.Trim().UpperCase() == "LOGIN") {
				sck->SendBuff(edUser->Text+"|LOGIN|"+edUser->Text);

			} else {
				sck->Disconnect();

			}
		}

	} catch (...) {
	}

}
//---------------------------------------------------------------------------


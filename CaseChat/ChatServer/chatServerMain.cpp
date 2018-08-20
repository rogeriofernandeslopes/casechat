//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "chatServerMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SSocket"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void TForm1::CloseLog()
{
	try
	{
		fclose(fp);
	}
	catch(Exception &exc)
	{
	}
}
//---------------------------------------------------------------------------

void TForm1::InitLog()
{
	LogReady = true;
	char lname[80];

	try
	{
		lname[0] = 0;
		wsprintf(lname, "SERVER_%s.log", Date().FormatString("YYYYMMDD"));
		fp = fopen(lname, "a");
		if(!fp)
			return;
		nLog = lname;
		nLogAnt = nLog;
		WriteLog("\n\n********************************[ Log Iniciado ]*********************************\n");
	}
	catch(Exception &exc)
	{
	}
}
//---------------------------------------------------------------------------

void TForm1::WriteLog(char fmt[800], ...)
{
	TDate d = Date();
	String dt = d.FormatString("YYYYMMDD");
	va_list ap;

	try
	{
		nLog = "SERVER_" + dt + ".log";
		if(nLog != nLogAnt)
		{
			if(LogReady)
				fclose(fp);
			LogReady = false;
		}
		if(!LogReady)
			InitLog();

		va_start(ap,fmt);
		vfprintf(fp, fmt, ap);
		fflush(fp);
		va_end(ap);

	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------

void TForm1::WriteToLog(AnsiString msg, AnsiString nickName)
{
	try
	{
		logLock->Acquire();
		WriteLog("[%s] : user[ %s ] : %s\n", DateTimeToStr(Now()).c_str(), nickName.c_str(), msg.c_str());
		logLock->Release();
	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btStartClick(TObject *Sender)
{
	try {
		ss->Port = StrToInt(edPort->Text);
		ss->Active = true;
	} catch (...) {
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ssAccept(TObject *Sender, TCustomWinSocket *Socket)
{
	try {
		WriteToLog("Novo Cliente Conectando...","SERVER");

	} catch (...) {
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ssClientDisconnect(TObject *Sender,
	  TCustomWinSocket *Socket)
{
	try {
		WriteToLog("Cliente Desconectado...","SERVER");
		removeClient(Socket);

	} catch (...) {
	}

}
//---------------------------------------------------------------------------

bool TForm1::removeClient(TCustomWinSocket *sck)
{
	ClientChat *c = NULL;
	String name;
	bool founded=false;

	try {
		std::list<ClientChat *>::iterator it;
		for(it = Clients.begin();it != Clients.end();it++)
		{
			c = *it;
			if (c->getSocket() == sck) {
				name = c->getNickName();
				Clients.remove(c);
				sendAllMSG(name+"|MESSAGE|Participante Saiu : " + name,name);
				WriteToLog("Participante Saiu : " + name,name);
				founded = true;
				break;
			}
		}
		refreshList();

	} catch (Exception &exc) {
		//log->WriteToLog("Exception em findCase1: " + exc.ToString());
	}
	return founded;

}

void TForm1::refreshList()
{
	ClientChat *c = NULL;
	try {
		participantes->Lines->Clear();

		std::list<ClientChat *>::iterator it;
		for(it = Clients.begin();it != Clients.end();it++)
		{
			c = *it;
			participantes->Lines->Add(c->getNickName());
		}

	} catch (Exception &exc) {
		//log->WriteToLog("Exception em findCase1: " + exc.ToString());
	}

}

void __fastcall TForm1::ssClientRead(TObject *Sender, TCustomWinSocket *Socket)
{
	try {
		String msg, name;

		msg = Socket->ReceiveText();
		ClientChat *cl;
		//memo->Lines->Add("Recebeu Mensagem: " + msg);

		if (msg.Pos("|LOGIN|") > 0)
		{
			name = msg.SubString(msg.Pos("|LOGIN|")+7,msg.Length());
			cl = findClient(name);
			if (!cl) {
				cl = new ClientChat();
				cl->setNickName(name);
				cl->setLastMessage("LOGIN");
				cl->setSocket(Socket);
				Clients.insert(Clients.end(),cl);
				participantes->Lines->Add(name);
				sendLoginMSG(name + "|MESSAGE|Novo Participante: " + name,name);
				Socket->SendText("LOGIN_OK");
				WriteToLog("Novo Participante : " + name,name);

			} else {
				Socket->SendText(name + "|MESSAGE|Nome Em Uso. Escolha Outro.");
			}
		} else if (msg.Pos("|MESSAGE|") > 0){

			name = msg.SubString(0,msg.Pos("|MESSAGE|")-1);
			//msg = msg.SubString(msg.Pos("|MESSAGE|")+9,msg.Length());
			sendAllMSG(msg,name);
			WriteToLog("Nova Mensagem : " + msg.SubString(msg.Pos("|MESSAGE|")+9,msg.Length()),name);


		}

	} catch (...) {
	}

}
//---------------------------------------------------------------------------

ClientChat *TForm1::findClient(String name)
{
	bool found=false;
	ClientChat *c = NULL;
	try {
		std::list<ClientChat *>::iterator it;
		for(it = Clients.begin();it != Clients.end();it++)
		{
			c = *it;
			if(c->getNickName().Trim() == name.Trim())
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			c = NULL;
		}

	} catch (Exception &exc) {
		//log->WriteToLog("Exception em findCase1: " + exc.ToString());
	}
	return c;

}
//---------------------------------------------------------------------------

void TForm1::sendAllMSG(String msg, String name)
{
	ClientChat *c = NULL;
	try {
		std::list<ClientChat *>::iterator it;
		for(it = Clients.begin();it != Clients.end();it++)
		{
			c = *it;
			c->getSocket()->SendText(msg);
		}

	} catch (Exception &exc) {
		//log->WriteToLog("Exception em findCase1: " + exc.ToString());
	}


}
//---------------------------------------------------------------------------

void TForm1::sendLoginMSG(String msg, String name)
{
	ClientChat *c = NULL;
	try {
		std::list<ClientChat *>::iterator it;
		for(it = Clients.begin();it != Clients.end();it++)
		{
			c = *it;
			if(c->getNickName().Trim() != name.Trim())
			{
				c->getSocket()->SendText(msg);
			}
		}

	} catch (Exception &exc) {
		//log->WriteToLog("Exception em findCase1: " + exc.ToString());
	}


}
//---------------------------------------------------------------------------

void __fastcall TForm1::ssClientError(TObject *Sender, TCustomWinSocket *Socket,
	  TErrorEvent ErrorEvent, int &ErrorCode)
{
	ErrorCode =0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btEndClick(TObject *Sender)
{
	try {
		ss->Active = false;
		Close();

	} catch (...) {
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	try {
		WriteToLog("Finalizando Servidor","SERVER");
		CloseLog();

	} catch (...) {
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ssListen(TObject *Sender, TCustomWinSocket *Socket)
{
	try {
		WriteToLog("Server Iniciado...","SERVER");
		btStart->Enabled = false;
		edPort->Enabled = false;
		btEnd->Enabled = true;

	} catch (...) {
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
	try {
		logLock = new TCriticalSection();
	} catch (...) {
	}

}
//---------------------------------------------------------------------------


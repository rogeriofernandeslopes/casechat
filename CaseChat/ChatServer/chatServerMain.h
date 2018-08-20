//---------------------------------------------------------------------------

#ifndef chatServerMainH
#define chatServerMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SSocket.h"
#include <ExtCtrls.hpp>
#include <ScktComp.hpp>
#include <list>
#include <ExtCtrls.hpp>
#include <stdio.h>

//---------------------------------------------------------------------------

class ClientChat {
	protected:
	String nickName, lastMessage;
	TCustomWinSocket *sck;

	public:
		ClientChat(){}; 

		void setNickName(String nk) { nickName = nk; }
		String getNickName() { return nickName; }

		void setLastMessage(String lm) { lastMessage = lm; }
		String getLastMessage() { return lastMessage; }

		void setSocket(TCustomWinSocket *s) { sck = s; }
		TCustomWinSocket * getSocket() { return sck; }

};


class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel2;
	TEdit *edPort;
	TButton *btStart;
	TSSocket *ss;
	TMemo *participantes;
	TButton *btEnd;
	void __fastcall btStartClick(TObject *Sender);
	void __fastcall ssAccept(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ssClientDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ssClientRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ssClientError(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode);
	void __fastcall btEndClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ssListen(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

	FILE *fp;
	bool LogReady;
	String nLog,nLogAnt;
	TCriticalSection *logLock;

	std::list<ClientChat *> Clients;

	ClientChat *findClient(String name);
	void sendAllMSG(String msg, String name);
	void sendLoginMSG(String msg, String name);
	bool removeClient(TCustomWinSocket *sck);
	void refreshList();

	void CloseLog();
	void InitLog();
	void WriteLog(char fmt[800], ...);
	void WriteToLog(AnsiString msg, AnsiString nickName);

};


//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

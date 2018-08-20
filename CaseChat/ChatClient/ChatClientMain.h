//---------------------------------------------------------------------------

#ifndef ChatClientMainH
#define ChatClientMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "IrisCSocket.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TEdit *edIP;
	TButton *btConnect;
	TMemo *memo;
	TPanel *pnConn;
	TStatusBar *StatusBar1;
	IrisCSocket *sck;
	TPanel *Panel2;
	TButton *btSend;
	TEdit *edPort;
	TEdit *edMsg;
	TPanel *pnLogin;
	TButton *btLogin;
	TEdit *edUser;
	void __fastcall sckConnected(TObject *Sender);
	void __fastcall sckDisconnected(TObject *Sender);
	void __fastcall sckReadBuff(TObject *Sender, UnicodeString Buff);
	void __fastcall btConnectClick(TObject *Sender);
	void __fastcall btSendClick(TObject *Sender);
	void __fastcall btLoginClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Chat Server'
  ClientHeight = 300
  ClientWidth = 635
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 635
    Height = 25
    Align = alTop
    TabOrder = 0
    object edPort: TEdit
      Left = 1
      Top = 1
      Width = 121
      Height = 23
      Align = alLeft
      TabOrder = 0
      Text = '9000'
      ExplicitLeft = 48
      ExplicitTop = 14
      ExplicitHeight = 21
    end
    object btStart: TButton
      Left = 122
      Top = 1
      Width = 100
      Height = 23
      Align = alLeft
      Caption = 'Iniciar Servidor'
      TabOrder = 1
      OnClick = btStartClick
      ExplicitLeft = 128
      ExplicitTop = 0
    end
    object btEnd: TButton
      Left = 534
      Top = 1
      Width = 100
      Height = 23
      Align = alRight
      Caption = 'Finalizar Servidor'
      Enabled = False
      TabOrder = 2
      OnClick = btEndClick
      ExplicitLeft = 535
      ExplicitTop = -4
    end
  end
  object participantes: TMemo
    Left = 0
    Top = 25
    Width = 635
    Height = 275
    Align = alClient
    ReadOnly = True
    TabOrder = 1
    ExplicitLeft = 8
    ExplicitTop = 41
    ExplicitWidth = 169
    ExplicitHeight = 259
  end
  object ss: TSSocket
    Active = False
    Port = 9000
    ServerType = stNonBlocking
    OnListen = ssListen
    OnAccept = ssAccept
    OnClientDisconnect = ssClientDisconnect
    OnClientRead = ssClientRead
    OnClientError = ssClientError
    Left = 552
    Top = 32
  end
end

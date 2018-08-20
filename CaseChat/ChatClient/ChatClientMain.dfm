object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Chat Client'
  ClientHeight = 231
  ClientWidth = 505
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object pnConn: TPanel
    Left = 0
    Top = 0
    Width = 505
    Height = 22
    Align = alTop
    BevelOuter = bvLowered
    TabOrder = 0
    object btConnect: TButton
      Left = 171
      Top = 1
      Width = 80
      Height = 20
      Align = alLeft
      Caption = 'Conectar'
      TabOrder = 0
      OnClick = btConnectClick
    end
    object edIP: TEdit
      Left = 1
      Top = 1
      Width = 121
      Height = 20
      Align = alLeft
      TabOrder = 1
      Text = 'localhost'
      ExplicitHeight = 21
    end
    object edPort: TEdit
      Left = 122
      Top = 1
      Width = 49
      Height = 20
      Align = alLeft
      Alignment = taCenter
      TabOrder = 2
      Text = '9000'
      ExplicitHeight = 21
    end
  end
  object memo: TMemo
    Left = 0
    Top = 44
    Width = 505
    Height = 146
    Align = alClient
    TabOrder = 1
    ExplicitTop = 22
    ExplicitHeight = 168
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 212
    Width = 505
    Height = 19
    Panels = <>
  end
  object Panel2: TPanel
    Left = 0
    Top = 190
    Width = 505
    Height = 22
    Align = alBottom
    BevelOuter = bvLowered
    TabOrder = 3
    object btSend: TButton
      Left = 429
      Top = 1
      Width = 75
      Height = 20
      Align = alRight
      Caption = 'Enviar'
      Enabled = False
      TabOrder = 0
      OnClick = btSendClick
      ExplicitLeft = 435
      ExplicitTop = -4
    end
    object edMsg: TEdit
      Left = 1
      Top = 1
      Width = 428
      Height = 20
      Align = alClient
      TabOrder = 1
      ExplicitHeight = 21
    end
  end
  object pnLogin: TPanel
    Left = 0
    Top = 22
    Width = 505
    Height = 22
    Align = alTop
    BevelOuter = bvLowered
    TabOrder = 4
    Visible = False
    ExplicitTop = 8
    object btLogin: TButton
      Left = 122
      Top = 1
      Width = 129
      Height = 20
      Align = alLeft
      Caption = 'Login'
      TabOrder = 0
      OnClick = btLoginClick
    end
    object edUser: TEdit
      Left = 1
      Top = 1
      Width = 121
      Height = 20
      Align = alLeft
      TabOrder = 1
      ExplicitHeight = 21
    end
  end
  object sck: IrisCSocket
    OnConnected = sckConnected
    OnDisconnected = sckDisconnected
    OnReadBuff = sckReadBuff
    Left = 288
    Top = 96
  end
end

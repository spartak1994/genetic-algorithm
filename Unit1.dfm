object Form1: TForm1
  Left = 0
  Top = 0
  Caption = #1043#1077#1085#1077#1090#1080#1095#1077#1089#1082#1080#1081' '#1072#1083#1075#1086#1088#1080#1090#1084
  ClientHeight = 282
  ClientWidth = 439
  Color = clGradientActiveCaption
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 304
    Top = 112
    Width = 56
    Height = 13
    Caption = #1048#1090#1077#1088#1072#1094#1080#1103': '
  end
  object Label2: TLabel
    Left = 366
    Top = 112
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label3: TLabel
    Left = 236
    Top = 131
    Width = 124
    Height = 13
    Caption = #1052#1072#1082#1089'. '#1074#1099#1078'. '#1074' '#1087#1086#1087#1091#1083#1103#1094#1080#1080
  end
  object Label4: TLabel
    Left = 366
    Top = 131
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label5: TLabel
    Left = 234
    Top = 150
    Width = 126
    Height = 13
    Caption = #1040#1073#1089'. '#1084#1072#1082#1089' '#1074#1099#1078#1080#1074#1072#1077#1084#1086#1089#1090#1080
  end
  object Label6: TLabel
    Left = 366
    Top = 150
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label7: TLabel
    Left = 304
    Top = 169
    Width = 57
    Height = 13
    Caption = #1069#1090#1072#1083#1086#1085#1085#1099#1081
  end
  object Label8: TLabel
    Left = 366
    Top = 169
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label9: TLabel
    Left = 280
    Top = 24
    Width = 92
    Height = 13
    Caption = #1056#1072#1079#1084#1077#1088' '#1087#1086#1087#1091#1083#1103#1094#1080#1080
  end
  object Label10: TLabel
    Left = 280
    Top = 51
    Width = 90
    Height = 13
    Caption = #1042#1077#1088'. '#1084#1091#1090#1072#1094#1080#1080' '#1074' %'
  end
  object Label11: TLabel
    Left = 280
    Top = 80
    Width = 94
    Height = 13
    Caption = #1048#1085#1090#1077#1088#1074#1072#1083' '#1090#1072#1081#1084#1077#1088#1072
  end
  object BitBtn1: TBitBtn
    Left = 328
    Top = 232
    Width = 75
    Height = 25
    Caption = 'Go'
    TabOrder = 0
    OnClick = BitBtn1Click
  end
  object Edit1: TEdit
    Left = 378
    Top = 21
    Width = 41
    Height = 21
    NumbersOnly = True
    TabOrder = 1
    Text = '1000'
  end
  object Edit2: TEdit
    Left = 378
    Top = 48
    Width = 41
    Height = 21
    NumbersOnly = True
    TabOrder = 2
    Text = '1'
  end
  object Edit3: TEdit
    Left = 378
    Top = 75
    Width = 41
    Height = 21
    NumbersOnly = True
    TabOrder = 3
    Text = '1000'
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 200
    Top = 216
  end
end

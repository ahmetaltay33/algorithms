object frmMain: TfrmMain
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Date Time Converter'
  ClientHeight = 288
  ClientWidth = 523
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object txtInput: TEdit
    Left = 47
    Top = 226
    Width = 210
    Height = 21
    TabOrder = 0
  end
  object btnConvert: TButton
    Left = 47
    Top = 253
    Width = 170
    Height = 25
    Caption = 'Convert >>'
    TabOrder = 1
    OnClick = btnConvertClick
  end
  object btnReverse: TButton
    Left = 302
    Top = 253
    Width = 170
    Height = 25
    Caption = '<< Reverse'
    TabOrder = 2
    OnClick = btnReverseClick
  end
  object txtOutput: TEdit
    Left = 302
    Top = 226
    Width = 210
    Height = 21
    TabOrder = 3
  end
  object grpInputFormat: TGroupBox
    Left = 8
    Top = 8
    Width = 249
    Height = 212
    Caption = 'Input Format'
    TabOrder = 4
    object Label1: TLabel
      Left = 9
      Top = 47
      Width = 74
      Height = 13
      Caption = 'Date Separator'
    end
    object Label2: TLabel
      Left = 10
      Top = 74
      Width = 73
      Height = 13
      Alignment = taRightJustify
      Caption = 'Time Separator'
    end
    object Label3: TLabel
      Left = 34
      Top = 101
      Width = 49
      Height = 13
      Alignment = taRightJustify
      Caption = 'Long Date'
    end
    object Label4: TLabel
      Left = 31
      Top = 128
      Width = 52
      Height = 13
      Alignment = taRightJustify
      Caption = 'Short Date'
    end
    object Label5: TLabel
      Left = 35
      Top = 155
      Width = 48
      Height = 13
      Alignment = taRightJustify
      Caption = 'Long Time'
    end
    object Label6: TLabel
      Left = 32
      Top = 182
      Width = 51
      Height = 13
      Alignment = taRightJustify
      Caption = 'Short Time'
    end
    object Label7: TLabel
      Left = 53
      Top = 23
      Width = 30
      Height = 13
      Alignment = taRightJustify
      Caption = 'Locale'
    end
    object txtInputDateSeparator: TEdit
      Left = 89
      Top = 44
      Width = 150
      Height = 21
      TabOrder = 0
      Text = '-'
    end
    object txtInputTimeSeparator: TEdit
      Left = 89
      Top = 71
      Width = 150
      Height = 21
      TabOrder = 1
      Text = ':'
    end
    object txtInputLongDate: TEdit
      Left = 89
      Top = 98
      Width = 150
      Height = 21
      TabOrder = 2
      Text = 'yyyy-MM-dd hh:mm:ss'
    end
    object txtInputShortDate: TEdit
      Left = 89
      Top = 125
      Width = 150
      Height = 21
      TabOrder = 3
      Text = 'yyyy-MM-dd'
    end
    object txtInputLongTime: TEdit
      Left = 89
      Top = 152
      Width = 150
      Height = 21
      TabOrder = 4
      Text = 'hh:mm:ss'
    end
    object txtInputShortTime: TEdit
      Left = 89
      Top = 179
      Width = 150
      Height = 21
      TabOrder = 5
      Text = 'hh:mm'
    end
    object txtInputLocale: TEdit
      Left = 89
      Top = 20
      Width = 150
      Height = 21
      TabOrder = 6
      Text = 'en-US'
      OnKeyUp = txtInputLocaleKeyUp
    end
  end
  object grpOutputFormat: TGroupBox
    Left = 263
    Top = 8
    Width = 249
    Height = 212
    Caption = 'Output Format'
    TabOrder = 5
    object Label8: TLabel
      Left = 9
      Top = 47
      Width = 74
      Height = 13
      Caption = 'Date Separator'
    end
    object Label9: TLabel
      Left = 10
      Top = 74
      Width = 73
      Height = 13
      Alignment = taRightJustify
      Caption = 'Time Separator'
    end
    object Label10: TLabel
      Left = 34
      Top = 101
      Width = 49
      Height = 13
      Alignment = taRightJustify
      Caption = 'Long Date'
    end
    object Label11: TLabel
      Left = 31
      Top = 128
      Width = 52
      Height = 13
      Alignment = taRightJustify
      Caption = 'Short Date'
    end
    object Label12: TLabel
      Left = 35
      Top = 155
      Width = 48
      Height = 13
      Alignment = taRightJustify
      Caption = 'Long Time'
    end
    object Label13: TLabel
      Left = 32
      Top = 182
      Width = 51
      Height = 13
      Alignment = taRightJustify
      Caption = 'Short Time'
    end
    object Label14: TLabel
      Left = 53
      Top = 23
      Width = 30
      Height = 13
      Alignment = taRightJustify
      Caption = 'Locale'
    end
    object txtOutputDateSeparator: TEdit
      Left = 89
      Top = 44
      Width = 150
      Height = 21
      TabOrder = 0
      Text = '-'
    end
    object txtOutputTimeSeparator: TEdit
      Left = 89
      Top = 71
      Width = 150
      Height = 21
      TabOrder = 1
      Text = ':'
    end
    object txtOutputLongDate: TEdit
      Left = 89
      Top = 98
      Width = 150
      Height = 21
      TabOrder = 2
      Text = 'yyyy-MM-dd hh:mm:ss'
    end
    object txtOutputShortDate: TEdit
      Left = 89
      Top = 125
      Width = 150
      Height = 21
      TabOrder = 3
      Text = 'yyyy-MM-dd'
    end
    object txtOutputLongTime: TEdit
      Left = 89
      Top = 152
      Width = 150
      Height = 21
      TabOrder = 4
      Text = 'hh:mm:ss'
    end
    object txtOutputShortTime: TEdit
      Left = 89
      Top = 179
      Width = 150
      Height = 21
      TabOrder = 5
      Text = 'hh:mm'
    end
    object txtOutputLocale: TEdit
      Left = 89
      Top = 20
      Width = 150
      Height = 21
      TabOrder = 6
      Text = 'tr-TR'
      OnKeyUp = txtOutputLocaleKeyUp
    end
  end
  object btnInputNow: TButton
    Left = 8
    Top = 224
    Width = 33
    Height = 25
    Caption = 'Now'
    TabOrder = 6
    OnClick = btnInputNowClick
  end
  object btnOutputNow: TButton
    Left = 263
    Top = 224
    Width = 33
    Height = 25
    Caption = 'Now'
    TabOrder = 7
    OnClick = btnOutputNowClick
  end
end

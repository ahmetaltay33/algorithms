unit uFrmMain;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.ComCtrls, Vcl.StdCtrls;

type
  TfrmMain = class(TForm)
    txtInput: TEdit;
    btnConvert: TButton;
    btnReverse: TButton;
    txtOutput: TEdit;
    grpInputFormat: TGroupBox;
    txtInputDateSeparator: TEdit;
    txtInputTimeSeparator: TEdit;
    txtInputLongDate: TEdit;
    txtInputShortDate: TEdit;
    txtInputLongTime: TEdit;
    txtInputShortTime: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    txtInputLocale: TEdit;
    Label7: TLabel;
    grpOutputFormat: TGroupBox;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    txtOutputDateSeparator: TEdit;
    txtOutputTimeSeparator: TEdit;
    txtOutputLongDate: TEdit;
    txtOutputShortDate: TEdit;
    txtOutputLongTime: TEdit;
    txtOutputShortTime: TEdit;
    txtOutputLocale: TEdit;
    btnInputNow: TButton;
    btnOutputNow: TButton;
    procedure btnConvertClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure btnReverseClick(Sender: TObject);
    procedure txtInputLocaleKeyUp(Sender: TObject; var Key: Word; Shift: TShiftState);
    procedure txtOutputLocaleKeyUp(Sender: TObject; var Key: Word; Shift: TShiftState);
    procedure btnInputNowClick(Sender: TObject);
    procedure btnOutputNowClick(Sender: TObject);
  private
    { Private declarations }
    function CreateInputFormatSettings(): TFormatSettings;
    function CreateOutputFormatSettings(): TFormatSettings;
  public
    { Public declarations }
  end;

var
  frmMain: TfrmMain;

implementation

{$R *.dfm}

procedure TfrmMain.btnInputNowClick(Sender: TObject);
begin
  txtInput.Text := DateTimeToStr(Now, CreateInputFormatSettings);
end;

procedure TfrmMain.btnOutputNowClick(Sender: TObject);
begin
  txtOutput.Text := DateTimeToStr(Now, CreateOutputFormatSettings);
end;

procedure TfrmMain.btnReverseClick(Sender: TObject);
var
  lOutput: TDateTime;
begin
  lOutput := StrToDateTime(txtOutput.Text, CreateOutputFormatSettings);
  txtInput.Text := DateTimeToStr(lOutput, CreateInputFormatSettings);
end;

procedure TfrmMain.btnConvertClick(Sender: TObject);
var
  lInput: TDateTime;
begin
  lInput := StrToDateTime(txtInput.Text, CreateInputFormatSettings);
  txtOutput.Text := DateTimeToStr(lInput, CreateOutputFormatSettings);
end;

function TfrmMain.CreateInputFormatSettings: TFormatSettings;
begin
  Result := TFormatSettings.Create(txtInputLocale.Text);
  if txtInputDateSeparator.Text <> '' then
    Result.DateSeparator := txtInputDateSeparator.Text[1];
  if txtInputTimeSeparator.Text <> '' then
    Result.TimeSeparator := txtInputTimeSeparator.Text[1];
  Result.LongDateFormat := txtInputLongDate.Text;
  Result.ShortDateFormat := txtInputShortDate.Text;
  Result.LongTimeFormat := txtInputLongTime.Text;
  Result.ShortTimeFormat := txtInputShortTime.Text;
end;

function TfrmMain.CreateOutputFormatSettings: TFormatSettings;
begin
  Result := TFormatSettings.Create(txtOutputLocale.Text);
  if txtOutputDateSeparator.Text <> '' then
    Result.DateSeparator := txtOutputDateSeparator.Text[1];
  if txtOutputTimeSeparator.Text <> '' then
    Result.TimeSeparator := txtOutputTimeSeparator.Text[1];
  Result.LongDateFormat := txtOutputLongDate.Text;
  Result.ShortDateFormat := txtOutputShortDate.Text;
  Result.LongTimeFormat := txtOutputLongTime.Text;
  Result.ShortTimeFormat := txtOutputShortTime.Text;
end;

procedure TfrmMain.FormCreate(Sender: TObject);
var
  lKey: Word;
begin
  lKey := VK_RETURN;
  txtInputLocaleKeyUp(txtInput, lKey, []);
  txtOutputLocaleKeyUp(txtOutput, lKey, []);
  btnInputNow.Click();
end;

procedure TfrmMain.txtInputLocaleKeyUp(Sender: TObject; var Key: Word; Shift: TShiftState);
begin
  if Key = VK_RETURN then
  begin
    with TFormatSettings.Create(txtInputLocale.Text) do
    begin
      txtInputDateSeparator.Text := DateSeparator;
      txtInputTimeSeparator.Text := TimeSeparator;
      txtInputLongDate.Text := LongDateFormat;
      txtInputShortDate.Text := ShortDateFormat;
      txtInputLongTime.Text := LongTimeFormat;
      txtInputShortTime.Text := ShortTimeFormat;
    end;
  end;
end;

procedure TfrmMain.txtOutputLocaleKeyUp(Sender: TObject; var Key: Word; Shift: TShiftState);
begin
  if Key = VK_RETURN then
  begin
    with TFormatSettings.Create(txtOutputLocale.Text) do
    begin
      txtOutputDateSeparator.Text := DateSeparator;
      txtOutputTimeSeparator.Text := TimeSeparator;
      txtOutputLongDate.Text := LongDateFormat;
      txtOutputShortDate.Text := ShortDateFormat;
      txtOutputLongTime.Text := LongTimeFormat;
      txtOutputShortTime.Text := ShortTimeFormat;
    end;
  end;
end;

end.

//---------------------------------------------------------------------------
#include <iostream>
#include <vcl.h>
#pragma hdrstop
#include <string>
#include <stdio.h>
#include <cstdio.h>
#define str(x) # x
 #define xstr(x) str(x)

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
String path;

struct TAGdata
{
	char tag[3];
	char title[30];
 	char artist[30];
	char album[30];
	char year[4];
	char comment[30];
	char genre;
};

String genre[]={"Blues", "Classic Rock","Country","Dance","Disco","Funk","Grunge",
 "Hip-Hop","Jazz","Metal","New Age","Oldies","Other","Pop","R&B",
 "Rap","Reggae","Rock","Techno","Industrial","Alternative","Ska",
 "Death Metal","Pranks","Soundtrack","Euro-Techno","Ambient",
 "Trip-Hop","Vocal","Jazz+Funk","Fusion","Trance","Classical",
 "Instrumental","Acid","House","Game","Sound Clip","Gospel",
 "Noise","AlternRock","Bass","Soul","Punk","Space","Meditative",
 "Instrumental Pop","Instrumental Rock","Ethnic","Gothic",
 "Darkwave","Techno-Industrial","Electronic","Pop-Folk",
 "Eurodance","Dream","Southern Rock","Comedy","Cult","Gangsta",
 "Top 40","Christian Rap","Pop/Funk","Jungle","Native American",
 "Cabaret","New Wave","Psychadelic","Rave","Showtunes","Trailer",
 "Lo-Fi","Tribal","Acid Punk","Acid Jazz","Polka","Retro",
 "Musical","Rock n Roll","Hard Rock","Folk","Folk-Rock",
 "National Folk","Swing","Fast Fusion","Bebob","Latin","Revival",
 "Celtic","Bluegrass","Avantgarde","Gothic Rock","Progressive Rock",
 "Psychedelic Rock","Symphonic Rock","Slow Rock","Big Band",
 "Chorus","Easy Listening","Acoustic","Humour","Speech","Chanson",
 "Opera","Chamber Music","Sonata","Symphony","Booty Bass","Primus",
 "Porn Groove","Satire","Slow Jam","Club","Tango","Samba",
 "Folklore","Ballad","Power Ballad","Rhythmic Soul","Freestyle",
 "Duet","Punk Rock","Drum Solo","Acapella","Euro-House","Dance Hall"};


struct TAGdata tags;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{


if(OpenDialog1->Execute())
{
  importGrid();
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
StringGrid1->Cells[0][0]="title";
StringGrid1->Cells[1][0]="artist";
StringGrid1->Cells[2][0]="album";
StringGrid1->Cells[3][0]="year";
StringGrid1->Cells[4][0]="comment";
StringGrid1->Cells[5][0]="genre";

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
  int a,i,bitcount;
  long b;
  FILE * pFile;
  String temp;


  pFile = fopen ( OpenDialog1->FileName.c_str() , "r+" );
  fseek (pFile, 0, SEEK_END);
    bitcount=ftell (pFile);
  b=bitcount-128;
    fseek ( pFile , b , SEEK_SET );
  fscanf ( pFile , "%3s", &tags.tag);
  strcpy(&tags.tag[3],"\0");
  if (!strcmp(tags.tag,"TAG") )
  {
   b=bitcount-125;
  if(Edit1->Text!="")
  {
        a=30-Edit1->Text.Length();
        for(i=0;i<a;i++)
        {
        Edit1->Text=Edit1->Text+" ";
        }
        rewind(pFile);
        fsetpos (pFile, &b);
        fputs(Edit1->Text.c_str(), pFile);
        }
  b=bitcount-95;
  if(Edit2->Text!="")
  {
        a=30-Edit2->Text.Length();
        for(i=0;i<a;i++)
        {
        Edit2->Text=Edit2->Text+" ";
        }
        fsetpos (pFile, &b);
        fputs(Edit2->Text.c_str(), pFile);
        }
  b=bitcount-65;
  if(Edit3->Text!="")
  {
        a=30-Edit3->Text.Length();
        for(i=0;i<a;i++)
        {
        Edit3->Text=Edit3->Text+" ";
        }
        fsetpos (pFile, &b);
        fputs(Edit3->Text.c_str(), pFile);
        }
  b=bitcount-35;
  if(Edit4->Text!="")
  {
        if(checkyear(Edit4->Text))
        {
        fsetpos (pFile, &b);
        fputs(Edit1->Text.c_str(), pFile);
        }
        }
    b=bitcount-31;
  if(Edit5->Text!="")
  {
        a=30-Edit5->Text.Length();
        for(i=0;i<a+1;i++)
        {
        Edit5->Text=Edit5->Text+" ";
        }
        fsetpos (pFile, &b);
        fputs(Edit5->Text.c_str(), pFile);
        }
    b=bitcount-1;
    if(ComboBox1->ItemIndex>0)
  {
     fsetpos (pFile, &b);
     a=ComboBox1->ItemIndex;
     sprintf(temp.c_str(),"%x",a);
     a=a-1;
        fputc( a , pFile);
        }
     else
     {
     a=12;
     fsetpos (pFile, &b);
        fputc( a , pFile);
     }

  fclose(pFile);



 }
 importGrid();
}
//---------------------------------------------------------------------------

void TForm1::importGrid()
{
int a,i;
long b;
bool genre_found=false;
String temp;
  //char temp[4];
  FILE * pFile;

  pFile = fopen ( OpenDialog1->FileName.c_str() , "r+" );
  fseek (pFile, 0, SEEK_END);
    a=ftell (pFile);
  b=a-128;
  fseek ( pFile , b , SEEK_SET );
  fscanf ( pFile , "%3s", &tags.tag);
  strcpy(&tags.tag[3],"\0");
  if (!strcmp(tags.tag,"TAG") )
  {
        b=b+3;
        fsetpos (pFile, &b);
         fscanf ( pFile , "%30" xstr(30) "[^\n]%*[^\n]", &tags.title );
         b=b+30;
         fsetpos (pFile, &b);
         fscanf ( pFile , "%30" xstr(30) "[^\n]%*[^\n]", &tags.artist );
         b=b+30;
         fsetpos (pFile, &b);
         fscanf (pFile , "%30" xstr(30) "[^\n]%*[^\n]", &tags.album );
         b=b+30;
         fsetpos (pFile, &b);
         fscanf (pFile , "%4" xstr(4) "[^\n]%*[^\n]", &tags.year );


         b=b+4;
         fsetpos (pFile, &b);
         fscanf (pFile , "%30" xstr(30) "[^\n]%*[^\n]", &tags.comment );
         b=b+30;
         fsetpos (pFile, &b);
         fscanf (pFile , "%d", &tags.genre );

  fclose ( pFile );
temp=tags.title;
temp.SetLength(30);
StringGrid1->Cells[0][1]=temp.c_str();
temp=tags.artist;
temp.SetLength(30);
StringGrid1->Cells[1][1]=temp.c_str();
temp=tags.album;
temp.SetLength(30);
StringGrid1->Cells[2][1]=temp.c_str();
temp=tags.year;
temp.SetLength(4);
StringGrid1->Cells[3][1]=temp.c_str();
temp=tags.comment;
temp.SetLength(30);
StringGrid1->Cells[4][1]=temp.c_str();
genre_found=false;
for(i=0;i<80;i++)
{
        if(tags.genre==i)
        {

          StringGrid1->Cells[5][1]=genre[i];
          ComboBox1->ItemIndex=i+1;
          genre_found=true;
         }
}
if(!genre_found)
{

           StringGrid1->Cells[5][1]="other";
          ComboBox1->ItemIndex=13;
          
}

}
}


bool TForm1::checkyear(AnsiString s)
{
int i;
bool itis=true;
if(s.Length()==4)
{
for(i=1; i<=s.Length();i++)
        if(!isdigit(s[i]) && s[i]!=',' && s[i]!='.' && s[i]!='-')
        itis=false;
}
else
itis=false;
        return itis;
}






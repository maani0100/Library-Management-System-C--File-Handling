#include<iostream>
#include<fstream>
using namespace std;

class Student
{
 int isbn;
 char name[20];
 char auther[20];
 string edition;
 string publication;
 
 public:
  void getData();
  void showData();
  int getisbn(){return isbn;}
}s;

void Student::getData()
{
 cout<<"\n\nEnter Student Details......\n";
 cout<<"Enter ISBN No.          : "; cin>>isbn;
 cout<<"Enter Book Name         : "; cin.ignore(); cin.getline(name,20);
 cout<<"Enter Book Auther       : "; cin>>auther;
 cout<<"Enter Book Edition      : "; cin>>edition;
 cout<<"Enter Book Publication  : "; cin>>publication;
 cout<<endl;
}

void Student::showData()
{
 cout<<"\n\n.......Available Books......\n\n";
 cout<<"ISBN No.          : "<<isbn<<endl;
 cout<<"Book Name         : "<<name<<endl;
 cout<<"Book Auther       : "<<auther<<endl;
 cout<<"Book Edition      : "<<edition<<endl;
 cout<<"Book Publication  : "<<publication<<endl;
 cout<<endl;
}

void addData()
{
 ofstream fout;
 fout.open("Students.dat",ios::binary|ios::out|ios::app);
 s.getData();
 fout.write((char*)&s,sizeof(s));
 fout.close();
 cout<<"\n\nBook Successfully Added to File....\n";
}

void displayData()
{
 ifstream fin;
 fin.open("Students.dat",ios::in|ios::binary);
 while(fin.read((char*)&s,sizeof(s)))
 {
  s.showData();
 }
 fin.close();
 cout<<"\n\nBooks Reading from File Successfully Done....\n";
}

void searchData()
{
 int n, flag=0;
 ifstream fin;
 fin.open("Students.dat",ios::in|ios::binary);
 cout<<"Enter ISBN No you want to search : ";
 cin>>n;
 
 while(fin.read((char*)&s,sizeof(s)))
 {
  if(n==s.getisbn())
  {
   cout<<"The Details of ISBN No. "<<n<<" shown here with:\n";
   s.showData();
   flag++;
  }
 }
 fin.close();
 if(flag==0)
  cout<<"The ISBN No. "<<n<<" not found....\n\n";
 cout<<"\n\nData Reading from File Successfully Done....\n";
}

void deleteData()
{
 int n, flag=0;
 ifstream fin;
 ofstream fout,tout;

 fin.open("Students.dat",ios::in|ios::binary);
 fout.open("TempStud.dat",ios::out|ios::app|ios::binary);

 cout<<"Enter ISBN No of a Book you want to Delete : ";
 cin>>n;
 
 while(fin.read((char*)&s,sizeof(s)))
 {
  if(n==s.getisbn())
  {
   cout<<"The Following ISBN No. "<<n<<" has been Deleted:\n";
   s.showData();
   flag++;
  }
  else
  {
   fout.write((char*)&s,sizeof(s));
  }
 }
 fout.close();
 fin.close();
 if(flag==0)
  cout<<"The ISBN No. "<<n<<" not found....\n\n";
 remove("Students.dat");
 rename("tempStud.dat","Students.dat");
}



void editData()
{
 int n, flag=0, pos;
 fstream fio;

 fio.open("Students.dat",ios::in|ios::out|ios::binary);
 
 cout<<"Enter ISBN No of a Book you want to Edit : ";
 cin>>n;
 
 while(fio.read((char*)&s,sizeof(s)))
 {
  pos=fio.tellg();
  if(n==s.getisbn())
  {
   cout<<"The Following ISBN No. "<<n<<" will be Edited with new data:\n";
   s.showData();
   cout<<"\n\nNow Enter the New Details....\n";
   s.getData();
   fio.seekg(pos-sizeof(s));
   fio.write((char*)&s,sizeof(s));
   flag++;
  }
 }
 fio.close();
 
 if(flag==0)
  cout<<"The ISBN No. "<<n<<" not found....\n\n";
}

void project()
{
 int ch;
 do
 {
  system("cls");
  cout<<"\n==================================================================================\n\n";
  cout<<"              L I B R A R Y    M A N A G E M E N T    S Y S T E M \n\n";
  cout<<"==================================================================================\n\n";
  cout<<"1. Add New Book\n";
  cout<<"2. Display The Books\n";
  cout<<"3. Search Book From The List\n";
  cout<<"4. Edit The Existing Book Details\n";
  cout<<"5. Delete Existing Book From The List\n";
  cout<<"0. Exit from Program\n\n";
  cout<<"Enter your choice  : ";
  cin>>ch;
  system("cls");
  switch(ch)
  {
   case 1: addData(); break;
   case 2: displayData(); break;
   case 3: searchData();  break;
   case 4: editData();  break;
   case 5: deleteData();  break;
  }
  system("pause");
 }while(ch);
}

int main()
{
 project();
}

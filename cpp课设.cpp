#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;
class Absence 
{
public:
    string date;
    int    whatclass;//�ڼ��ڿ�
    string couse;
    string name;
    string type;//���ٵ������ˡ���ټ����Σ�
    void Absrecord();
    void Read(ifstream& in);
    void Save(ofstream& out);
};

static int FLAG = 0;
void Absence::Read(ifstream& in)
{
    in >> date >> whatclass>>couse>>name>>type;
}
void  Absence::Save(ofstream& out)
{
    if (FLAG == 0)
    {

        out << right << setw(20) << "ȱ������" << setw(20) << "�ڼ��ڿ�" << setw(20) << "�γ�����" << setw(20) << "ѧ������" << setw(25) << "ȱ������" << endl;
        FLAG = 1;

    }
    out << right << setw(20) << date << setw(20) << whatclass << setw(21) << couse << setw(27) << name << setw(25) << type << endl;
    out.close();
}
static int top=-1;
class CLASS
{public:Absence abs[100];
        int Modifyrecord(string Name);
        void Search(string Name);
        void Sort1();//ͳ��ĳ��ʱ���ڣ�����ѧ�����������δ����������δ����ɶൽ������
        void Sort2();//ͳ��ĳ��ʱ���ڣ���ѧ�����εĿγ̼������˴Σ��������˴��ɶൽ������
       
};

class Statistics1:public Absence
{public:
    int num;
    int flag;//1����ǰ���ѳ��ָ�ѧ����0��ʾǰ��δ���ָ�ѧ��
    Statistics1()
    {
        flag = 0;
        num = 1;
    }
};
string file = "statistics.txt";
//¼��ѧ����ȱ�μ�¼
void Absence::Absrecord()
{
    
    cout << "��ֱ�����ѧ����ȱ���������������ȱ�����ڡ��ڼ��ڿΡ��γ����ơ�ѧ��������ȱ�����ͣ��ٵ������ˡ���ټ����Σ�" << endl;
    cin >> date >> whatclass >> couse >> name >> type;
    ofstream out(file,ios::app);
    if(out)
    {
        if (FLAG == 0)
        {
            
        out << right<<setw(20) << "ȱ������" << setw(20) << "�ڼ��ڿ�" << setw(20) << "�γ�����"  << setw(20) << "ѧ������" << setw(25) << "ȱ������" << endl;
        FLAG = 1;
           
        }
        out <<right<< setw(20) << date << setw(20) << whatclass << setw(21) << couse << setw(27) << name << setw(25) << type << endl;
        out.close();
    }
    cout << "¼��ɹ�" << endl;
};
//�޸�ĳ��ѧ����ȱ�μ�¼
int CLASS::Modifyrecord(string Name)
{
    Absence abs2[100],abs3;
    bool Flag = true;
    int i,j,k,l,y;
    string n;
    ifstream in(file);
    if (in)
    {
        abs3.Read(in);
        for (i = 0; i <= top; i++)
        {
            abs2[i].Read(in);
        }
        in.close();
    }
    for( i = 0; i <= top;i++)
    {
        if (abs2[i].name == Name) { cout << "���ڸ�ѧ����¼" << endl; y = i; break; }
    }
    if (i > top ) { cout << "�޸�ѧ����¼" << endl; return -1; }
    else
    {
        cout << "1.ȱ������ 2.�ڼ��ڿ� 3.�γ����� 4.ѧ������ 5.ȱ�����ͣ��ٵ������ˡ���ټ����Σ�6.�˳��޸�" << endl;
        
        while (Flag)
        {
            cout << "�����������޸����ݵ����" << endl;
            cin >> j;
            switch (j)
            {
            case 1: {
                cout << "��������Ҫ�޸ĳɵ�ȱ������" << endl;
                cin >> n;
                abs[i].date = n;
                abs2[y].date = n;
                ofstream out(file);
                if (out)
                {
                    abs3.Save(out);
                    for (i = 0; i <= top; i++)
                    {
                        abs2[i].Save(out);
                    }
                }
                out.close();
                break; }
            
            case 2:cout << "��������Ҫ�޸ĳɵڼ��ڿ�" << endl;
                cin >> k;
                abs[i].whatclass = k; break;
            case 3:cout << "��������Ҫ�޸ĳɵĿγ�����" << endl;
                cin >> n;
                abs[i].couse = n; break;
            case 4:cout << "��������Ҫ�޸ĳɵ�ѧ������" << endl;
                cin >> n;
                abs[i].name = n; break;
            case 5:cout << "��������Ҫ�޸ĳɵ�ȱ�����ͣ��ٵ������ˡ���ټ����Σ�" << endl;
                cin >> n;
                abs[i].date = n; break;
            case 6:Flag = false;
             }
        }
        cout << "�޸�ѧ��ȱ�μ�¼�ɹ�" << endl; return 0;
    }
}
void CLASS::Search(string Name)
{
   bool Flag = true;
   int i;
   string n;
   for (i = 0; i <= top; i++)
     {
       if (abs[i].name == Name) 
       { cout << "ȱ�����ڣ�\t" <<abs[i].date<< endl; 
       cout << "�ڼ��ڿΣ�\t" << abs[i].whatclass << endl;
       cout << "�γ����ƣ�\t" << abs[i].couse<< endl;
       cout << "ѧ��������\t" << abs[i].name << endl;
       cout << "ȱ�����ͣ�\t" << abs[i].type<< endl;
       break; 
       }
      }
    if (i > top) cout << "�޸�ѧ����¼" << endl;
 }
void Swap(Statistics1& s, Statistics1& t)
{
    Statistics1 a;
    a = s;
    s = t;
    t = a;

}
void CLASS::Sort1()
{
    int i,m=0,j,s=0,d=0,b;
    string n, k;
    Statistics1 sta1[100],sta[50];
    cout << "���������Ķ�ʱ���ڣ����磺2002.2.2  2002.4.2��" << endl;
    cin >> n >> k;
    for(i=0;i<=top;i++)
    {
        if (strcmp(abs[i].date.c_str(), n.c_str()) >=0 && strcmp(abs[i].date.c_str(), k.c_str()) <= 0)
        {if(strcmp(abs[i].type.c_str(),"����")==0)
            sta1[m++].name = abs[i].name;
                       
        }
    }
    for (j = 0; j < m; j++)
    {
        if (sta1[j].flag == 0)
        {
            sta[s++].name = sta1[j].name;
            sta1[j].flag = 1;
            b = s - 1;
            for (d = s; d < m; d++)
            {
                if (sta1[d].flag ==0)
                    if (sta[b].name == sta1[d].name)
                    {
                        sta1[d].flag = 1; sta[b].num++;
                    }
            }
        }
    }
    for (i = 0; i < s - 1; i++)
        for (j = 0; j < s - i - 1; j++)
        {
            if (sta[j].num < sta[j + 1].num)
                Swap(sta[j], sta[j + 1]);

        }
    for (i = 0; i < s; i++)
        cout << "ѧ������:" <<setw(6)<< sta[i].name <<setw(16)<< "���δ����� " << sta[i].num << endl;
}
class SC
{public:
    string couse;
    int num;
    int flag;
    SC()
    {
        num = 1; flag = 0;
    }
};
void Swap(SC& s, SC& t)
{
    SC a;
    a = s;
    s = t;
    t = a;

}
void CLASS::Sort2()
{
    SC Couse[10],Couse1[50];
    int i, m = 0, j, s = 0, d = 0, b;
    string n, k;
    cout << "���������Ķ�ʱ���ڣ����磺2002.2.2  2002.4.2��" << endl;
    cin >> n >> k;
    for (i = 0; i <= top; i++)
    {
        if (strcmp(abs[i].date.c_str(), n.c_str()) >= 0 && strcmp(abs[i].date.c_str(), k.c_str()) <= 0)
        {
            if (strcmp(abs[i].type.c_str(), "����") == 0)
            Couse1[m++].couse = abs[i].couse;

        }
    }
    for (j = 0; j < m; j++)
    {
        if (Couse1[j].flag == 0)
        {
            Couse[s++].couse = Couse1[j].couse;
            Couse1[j].flag = 1;
            b = s - 1;
            for (d = s; d < m; d++)
            {
                if (Couse1[d].flag == 0)
                    if (Couse[b].couse == Couse1[d].couse)
                    {
                        Couse1[d].flag = 1; Couse[b].num++;
                    }
            }
        }
    }
    for (i = 0; i < s - 1; i++)
        for (j = 0; j < s - i - 1; j++)
        {
            if (Couse[j].num < Couse[j + 1].num)
                Swap(Couse[j], Couse[j + 1]);

        }
    for (i = 0; i < s; i++)
        cout << "ѧ�����εĿγ̣� " <<setw(13)<< Couse[i].couse<< "���������� " << Couse[i].num << endl;
}
void menu()
{   cout << "************************���ڹ���ϵͳ************************" << endl;
    cout << "1.¼��ѧ����ȱ�μ�¼" << endl;
    cout << "2.�޸�ĳ��ѧ����ȱ�μ�¼" << endl;
    cout << "3.��ѯĳ��ѧ����ȱ�����" << endl;
    cout << "4.ͳ��ĳ��ʱ���ڣ�����ѧ�����������δ����������δ����ɶൽ������" << endl;
    cout << "5.ͳ��ĳ��ʱ���ڣ���ѧ�����εĿγ̼������˴Σ��������˴��ɶൽ������" << endl;
    cout <<"6.�˳�ϵͳ" << endl;
}
int main()
    {
        string Name;
        CLASS Class;
        int n;
        bool flag = true;
        while (flag)
        {
            menu();
            cout << "��������Ҫѡ��Ĺ���" << endl;
            cin >> n;
            switch (n)
            {
            case 1:Class.abs[++top].Absrecord(); break;
            case 2:cout << "�������ѧ������" << endl;
                cin >> Name;
                Class.Modifyrecord(Name); break;
            case 3:cout << "�������ѧ������" << endl;
                cin >> Name;
                Class.Search(Name); break;
            case 4:Class.Sort1();
                break;
            case 5:Class.Sort2(); break;
            case 6:flag = false; break;
            default:cout << "����������������������" << endl; break;
            }
        }
        return 0;
    }

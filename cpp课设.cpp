#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;
class Absence 
{
public:
    string date;
    int    whatclass;//第几节课
    string couse;
    string name;
    string type;//（迟到、早退、请假及旷课）
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

        out << right << setw(20) << "缺课日期" << setw(20) << "第几节课" << setw(20) << "课程名称" << setw(20) << "学生姓名" << setw(25) << "缺课类型" << endl;
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
        void Sort1();//统计某段时间内，旷课学生姓名及旷课次数，按旷课次数由多到少排序
        void Sort2();//统计某段时间内，有学生旷课的课程及旷课人次，按旷课人次由多到少排序
       
};

class Statistics1:public Absence
{public:
    int num;
    int flag;//1代表前面已出现该学生，0表示前面未出现该学生
    Statistics1()
    {
        flag = 0;
        num = 1;
    }
};
string file = "statistics.txt";
//录入学生的缺课记录
void Absence::Absrecord()
{
    
    cout << "请分别输入学生的缺课情况，它包括：缺课日期、第几节课、课程名称、学生姓名、缺课类型（迟到、早退、请假及旷课）" << endl;
    cin >> date >> whatclass >> couse >> name >> type;
    ofstream out(file,ios::app);
    if(out)
    {
        if (FLAG == 0)
        {
            
        out << right<<setw(20) << "缺课日期" << setw(20) << "第几节课" << setw(20) << "课程名称"  << setw(20) << "学生姓名" << setw(25) << "缺课类型" << endl;
        FLAG = 1;
           
        }
        out <<right<< setw(20) << date << setw(20) << whatclass << setw(21) << couse << setw(27) << name << setw(25) << type << endl;
        out.close();
    }
    cout << "录入成功" << endl;
};
//修改某个学生的缺课记录
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
        if (abs2[i].name == Name) { cout << "存在该学生记录" << endl; y = i; break; }
    }
    if (i > top ) { cout << "无该学生记录" << endl; return -1; }
    else
    {
        cout << "1.缺课日期 2.第几节课 3.课程名称 4.学生姓名 5.缺课类型（迟到、早退、请假及旷课）6.退出修改" << endl;
        
        while (Flag)
        {
            cout << "请输入你想修改内容的序号" << endl;
            cin >> j;
            switch (j)
            {
            case 1: {
                cout << "请输入你要修改成的缺课日期" << endl;
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
            
            case 2:cout << "请输入你要修改成第几节课" << endl;
                cin >> k;
                abs[i].whatclass = k; break;
            case 3:cout << "请输入你要修改成的课程名称" << endl;
                cin >> n;
                abs[i].couse = n; break;
            case 4:cout << "请输入你要修改成的学生姓名" << endl;
                cin >> n;
                abs[i].name = n; break;
            case 5:cout << "请输入你要修改成的缺课类型（迟到、早退、请假及旷课）" << endl;
                cin >> n;
                abs[i].date = n; break;
            case 6:Flag = false;
             }
        }
        cout << "修改学生缺课记录成功" << endl; return 0;
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
       { cout << "缺课日期：\t" <<abs[i].date<< endl; 
       cout << "第几节课：\t" << abs[i].whatclass << endl;
       cout << "课程名称：\t" << abs[i].couse<< endl;
       cout << "学生姓名：\t" << abs[i].name << endl;
       cout << "缺课类型：\t" << abs[i].type<< endl;
       break; 
       }
      }
    if (i > top) cout << "无该学生记录" << endl;
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
    cout << "请输入在哪段时间内（例如：2002.2.2  2002.4.2）" << endl;
    cin >> n >> k;
    for(i=0;i<=top;i++)
    {
        if (strcmp(abs[i].date.c_str(), n.c_str()) >=0 && strcmp(abs[i].date.c_str(), k.c_str()) <= 0)
        {if(strcmp(abs[i].type.c_str(),"旷课")==0)
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
        cout << "学生姓名:" <<setw(6)<< sta[i].name <<setw(16)<< "旷课次数： " << sta[i].num << endl;
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
    cout << "请输入在哪段时间内（例如：2002.2.2  2002.4.2）" << endl;
    cin >> n >> k;
    for (i = 0; i <= top; i++)
    {
        if (strcmp(abs[i].date.c_str(), n.c_str()) >= 0 && strcmp(abs[i].date.c_str(), k.c_str()) <= 0)
        {
            if (strcmp(abs[i].type.c_str(), "旷课") == 0)
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
        cout << "学生旷课的课程： " <<setw(13)<< Couse[i].couse<< "旷课人数： " << Couse[i].num << endl;
}
void menu()
{   cout << "************************考勤管理系统************************" << endl;
    cout << "1.录入学生的缺课记录" << endl;
    cout << "2.修改某个学生的缺课记录" << endl;
    cout << "3.查询某个学生的缺课情况" << endl;
    cout << "4.统计某段时间内，旷课学生姓名及旷课次数，按旷课次数由多到少排序" << endl;
    cout << "5.统计某段时间内，有学生旷课的课程及旷课人次，按旷课人次由多到少排序" << endl;
    cout <<"6.退出系统" << endl;
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
            cout << "请输入您要选择的功能" << endl;
            cin >> n;
            switch (n)
            {
            case 1:Class.abs[++top].Absrecord(); break;
            case 2:cout << "请输入该学生姓名" << endl;
                cin >> Name;
                Class.Modifyrecord(Name); break;
            case 3:cout << "请输入该学生姓名" << endl;
                cin >> Name;
                Class.Search(Name); break;
            case 4:Class.Sort1();
                break;
            case 5:Class.Sort2(); break;
            case 6:flag = false; break;
            default:cout << "您的输入有误，请重新输入" << endl; break;
            }
        }
        return 0;
    }

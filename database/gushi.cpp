#include<bits/stdc++.h>
#include"lib/cJSON.c"
#include"lib/CJsonObject.cpp"
#include"lib/something.cpp"
using namespace std;
using namespace neb;

CJsonObject poems;

//#define debug

int help() {
    string guide = 
    "���Ĺ�ʫ�����������������\n"
    "����:\n"
    "   -h �鿴����\n"
    "   -a <����> ָ��������Ŀ��������ָ��Ĭ��Ϊ5��\n"
    "   -f <��Χ> ָ�����ⷶΧ����ʽΪ'�꼶(.����)'�������'|'��������ָ����Ϊȫ����\n"
    "ʹ����:\n"
    "   -a 10 -f 9.1 (����10����,���ⷶΧ�Ǿ��꼶�ϲ�)\n"
    "   -a 20 -f 8|9.1(����20����,���ⷶΧ�ǰ��꼶���²�����꼶�ϲ�)\n"
    "   -a 100 -f 7|8|9 (����100����,���ⷶΧ���������н׶�)\n"
    ;
    cout << guide;
    return 0;
}
int init() {
    //�����������
    srand((int) time(NULL));
    
    //����ʫ�ʿ�
    stringstream jsonstr;
    ifstream fin("database/poems.json");
    jsonstr << fin.rdbuf();
    fin.close();
    poems.Parse(jsonstr.str());

    return 0;
}
string generate(int a,string f) {
    stringstream ss,ssa;
    int arraySize = poems["poems"].GetArraySize();
    for(int i=0;i<a;i++) {
        //ѡ��ʫ��(s0)
        int ra0 = getRand(0,arraySize);
        CJsonObject poem = poems["poems"][ra0];
        string s0 = poem("context");

        //ѡ��ʫ��(s1)
        vector<string> v1;
        split(s0,v1,' ');
        int ra1 = getRand(0,v1.size());
        string s1 = v1[ra1];

        //ѡ��ʫ����Ҫ����յĵط�(s2)
        vector<string> v2;
        string s1copy = s1;
        replace_all(s1copy,"?",",");replace_all(s1copy,"!",",");replace_all(s1copy,"��",",");replace_all(s1copy,"��",",");replace_all(s1copy,"��",",");
        split(s1copy,v2,',');
        int ra2 = getRand(0,v2.size());
        string s2 = v2[ra2];
        replace_all(s2,".","");replace_all(s2,"!","");replace_all(s2,"?","");replace_all(s2,"��","");replace_all(s2,"��",",");replace_all(s2,"��",",");

        //���������
        string s = replace_all(s1,s2,"_____");
        ss << i+1 << ". " << s << ("(" + poem("author") + "<<" + poem("title") + ">>)") << endl;
        ssa << i+1 << ". "  << s2 << endl;

        #ifdef debug
            ss << s0 << "|" << s1 << "|" << s2 << endl;
        #endif
    }

    return ss.str()+"\nAnswer:\n"+ssa.str();
}
int main(int argc, char** argv) {
    init();

    int a=5; string f="";
    cin >> a >> f;
    
    cout << generate(a,f);

    return 0;
}
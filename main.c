#include "fuc.h"

int main()
{
    int quit = 1;
    mgraph g;
    Create_Map(&g);
    while (quit)
    {
        switch (menu())
        {
            case 1:                 // ������Ϣ��ѯ
                system("cls");
                All_Scenic(&g);
                Search_Scenic(&g);
                break;
            case 2:                 // ��·�����Ƽ������·����
                system("cls");
                All_Scenic(&g);
                Ai_Plan(&g);
                break;
            case 3:                 // ������������ľ���
                system("cls");
                All_Scenic(&g);
                Search_Distance(&g);
                break;
            case 4:                 // �������������·
                system("cls");
                floyd(&g);
                break;
            case 5:                 // ����˵�
                system("cls");
                Admin_System();
                break;
            case 6:                 // �˳�����ϵͳ
                system("cls");
                Exit(&quit);
                break;
            default:
                printf("\t\t�������������������룡\n\n");
        }
        system("cls");
    }
    return 0;
}
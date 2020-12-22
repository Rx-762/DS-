#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "Windows.h"

#define M 8
#define Pwd_Max 10
#define Input_Max 3
#define INF 9999

typedef struct
{
    int num;         // ������
    char name[20];   // ��������
    char intro[400]; // ������
} vertex;

typedef struct // ����ͼ�ṹ��
{
    vertex vexs[M];     // ������Ϣ����
    int edge[M][M];     // �ڽӾ���
    int vexNum, edgNum; // �������ͱ���
} mgraph;

// @Author �����
int menu();                      // ���˵�
int Login();                     // ��̨��¼У��
int Admin_Menu();                // ����Ա���˵�
int Judge_Num(int num);          // �������ж�
void Change_Pwd();               // ����Ա�����޸�
void Admin_System();             // ��̨����ϵͳ
void Exit(int *quit);            // �������˳�
void Admin_Exit(int *quit);      // ����Աϵͳ�˳�
void Create_Map(mgraph *g);      // ��ȡ�ļ����ݽ���ͼ
void All_Scenic(mgraph *g);      // ������о�����Ϣ
void Change_Info(mgraph *g);     // ������Ϣ�޸�
void Search_Scenic(mgraph *g);   // ������Ϣ��ѯ
void Search_Distance(mgraph *g); // ��ѯ������λ���������
void encrypt(char *s);           // ����
void decrypt(char *s);           // ����

// @Author �����
void Ai_Plan(mgraph *g);                                            // dijkstra�㷨�����·��
void showPath(int path[], int v0, int v1);                          // �������·��
void showResult(int v0, int v1, int dist[], int path[]);            // ������·��

// @Author ������
void showFloydPath(mgraph *g , int path[][M], int v0, int v);       //�����㵽�յ���м���
void showFloydResult(mgraph *g, int dist[][M], int path[][M]);      //���floyd�㷨�Ľ��
void floyd(mgraph *g);                                              //floyd�㷨

// ���˵�
int menu()
{
    int s;
    printf("        ������������������������������������������������������������       \n");
    printf("������������������ ��ӭʹ�þ���ɽ������ѯϵͳ �ȩ�������������\n");
    printf("��       ������������������������������������������������������������      ��\n");
    printf("��                                           ��\n");
    printf("��         1.������Ϣ��ѯ                    ��\n");
    printf("��                                           ��\n");
    printf("��         2.����·�����ܹ滮                ��\n");
    printf("��                                           ��\n");
    printf("��         3.��ѯ��������ľ���              ��\n");
    printf("��                                           ��\n");
    printf("��         4.����·�߲ο�                    ��\n");
    printf("��                                           ��\n");
    printf("��         5.����Ա��¼                      ��\n");
    printf("��                                           ��\n");
    printf("��         6.�˳�������ѯϵͳ                ��\n");
    printf("��                                           ��\n");
    printf("������������������������������������������������������������������������������������������\n\n");
    printf("[-]�밴����������ѡ�������ţ�");
    scanf("%d", &s);
    printf("\n\n");
    return s;
}

// ����Ա�˵�
int Admin_Menu()
{
    int s;
    printf("        ��������������������������������������������������       \n");
    printf("������������������  ��ӭʹ�ú�̨����ϵͳ �ȩ�������������\n");
    printf("��       ��������������������������������������������������      ��\n");
    printf("��                                      ��\n");
    printf("��         1.������Ϣ����               ��\n");
    printf("��                                      ��\n");
    printf("��         2.����Ա�˺������޸�         ��\n");
    printf("��                                      ��\n");
    printf("��         3.�˳�����ϵͳ               ��\n");
    printf("��                                      ��\n");
    printf("��������������������������������������������������������������������������������\n\n");
    printf("[-]�밴����������ѡ�������ţ�");
    scanf("%d", &s);
    printf("\n\n");
    return s;
}

// �����˳�
void Exit(int *quit)
{
    int i, j;
    *quit = 0;
    printf("\n");
    printf("\t��л����ʹ�ã�Bye!\n");
    printf("\n");
    printf("*     *     *****      *              *\n");
    printf("  * *      *     *      *     *      * \n");
    printf("   *       *   * *       *   *  *   *  \n");
    printf("   *       *     *        * *    * *   \n");
    printf("   *        *****  *       *      *    \n");
    Sleep(1500);
}

// ����Աϵͳ�˳�����
void Admin_Exit(int *quit)
{
    *quit = 0;
    printf("\n[-]�����˳�......");
    Sleep(500);
}

// �жϾ������Ƿ���ȷ
int Judge_Num(int num)
{
    if (num < 1 || num > 8)
    {
        printf("[-]����ľ������������������룡\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

// ��ȡ�ļ����ݽ���ͼ
void Create_Map(mgraph *g)
{
    int i, j, k, e;
    FILE *rf;
    rf = fopen("data.txt", "r");
    if (rf)
    {
        fscanf(rf, "%d%d", &g->vexNum, &g->edgNum); // ��ȡ��������ͱ���
        for (i = 0; i < g->vexNum; i++)             // ��ȡ���㣨���㣩��Ϣ
            fscanf(rf, "%d%s%s", &g->vexs[i].num, g->vexs[i].name, g->vexs[i].intro);
        for (i = 0; i < g->vexNum; i++) // �����ڽӾ���
            for (j = 0; j < g->vexNum; j++)
            {
                if (i == j)
                    g->edge[i][j] = 0;
                else
                    g->edge[i][j] = INF; // ��ʾ��ͨ
            }
        for (k = 0; k < g->edgNum; k++) // ����Ȩ��
        {
            fscanf(rf, "%d%d%d", &i, &j, &e);
            g->edge[i][j] = g->edge[j][i] = e;
        }
        fclose(rf);
    }
    else
        g->edgNum = 0;
}

// ���о�����Ϣ���
void All_Scenic(mgraph *g)
{
    int i, j;
    printf("\n[-]������Ϣ�б�\n\n");
    for (i = 0; i < g->vexNum; i++)
    {
        printf(" %d:%s\n", g->vexs[i].num, g->vexs[i].name); // ��������š�����
        printf("\n");
    }
}

// ������Ϣ��ѯ
void Search_Scenic(mgraph *g)
{
    int s;
    do
    {
        printf("[-]��������Ҫ���ҵľ����ţ�");
        scanf("%d", &s);
    } while (Judge_Num(s));
    printf("\n[-]�������ƣ�%s\n\n", g->vexs[s - 1].name);
    printf("[-]�����飺 %s\n\n", g->vexs[s - 1].intro);
    system("pause");
}

// ��ѯ��������ľ���
void Search_Distance(mgraph *g)
{
    int i, s, dis = 9998, res[M];
    do
    {
        printf("\n[-]����������ǰλ�õı�ţ�");
        scanf("%d", &s);
    } while (Judge_Num(s));
    s--;
    for (i = 0; i < M; i++) // ��ѯ��̾���
    {
        if ((g->edge[s][i] <= dis) && (s != i))
        {
            dis = g->edge[s][i];
        }
    }
    for (i = 0; i < M; i++) // ������
    {
        if (g->edge[s][i] == dis)
        {
            printf("\n[-]%s���������������%d��\n", g->vexs[i].name, g->edge[s][i]);
        }
    }
    printf("\n");
    system("pause");
}

// ��½У�麯��
int Login()
{
    int i = 0, j = 0;                       // �������볤�ȡ��������
    char correct_pwd[11], input_pwd[11], s; // ��ȷ���롢�������롢��ʱ�洢�ַ�
    FILE *rf;
    rf = fopen("pwd.txt", "r");
    fscanf(rf, "%s", correct_pwd); // ��ȡ����
    decrypt(correct_pwd);
    printf("\n[-]���������Ա���룺\n");
    while (j < Input_Max)
    {
        while (s = getch())
        {
            if (s == '\r') // �س��˳�����
            {
                input_pwd[i] = '\0';
                break;
            }
            if (s == '\b')
            {
                if (i != 0)
                {
                    i--;
                    printf("\b \b"); // ���ˡ��ڵ�*������
                }
            }
            else if (i < Pwd_Max)
            {
                putchar('*');
                input_pwd[i++] = s;
            }
        }
        if (strcmp(input_pwd, correct_pwd) == 0 ? 1 : 0)
        {
            printf("\n[-]��½�ɹ��������������ҳ��......\n");
            Sleep(1000);
            system("cls"); // ��¼��Ϣ����
            return strcmp(input_pwd, correct_pwd) == 0 ? 1 : 0;
        }
        else
        {
            i = 0; // �����ʼ��
            if (++j == Input_Max)
            {
                printf("\n[-]�����������������Ʒ�Χ��������ת�����˵�......\n");
                Sleep(1000);
            }
            else
            {
                printf("\n[-]��������������������룬��ʣ��%d�λ��ᣡ\n", Input_Max - j);
            }
        }
    }
    return 0;
}

// ������Ϣ�޸ĺ���
void Change_Info(mgraph *g)
{
    int i, j, s;
    FILE *rf;
    rf = fopen("data.txt", "w");
    do
    {
        printf("\n[-]��������Ҫ������Ϣ����ı�ţ�");
        scanf("%d", &s);
    } while (Judge_Num(s));
    s--;
    printf("\n[-]�������µľ������ƣ�");
    scanf("%s", g->vexs[s].name);
    printf("\n[-]�������µĵľ����飺");
    scanf("%s", g->vexs[s].intro);
    fprintf(rf, "%d %d\n", g->vexNum, g->edgNum); // д�뾰�����������
    for (i = 0; i < g->vexNum; i++)               // д�뾰����Ϣ
        fprintf(rf, "%d %s\n%s\n", g->vexs[i].num, g->vexs[i].name, g->vexs[i].intro);
    for (i = 0; i < g->vexNum; i++) // д�뾰���Ȩ��
        for (j = i; j < g->vexNum; j++)
            if (g->edge[i][j] != 0 && g->edge[i][j] != INF)
                fprintf(rf, "%d %d %d\n", i, j, g->edge[i][j]);
    fclose(rf);
    printf("\n[-]������Ϣ���ĳɹ�������������Ч��");
    Sleep(1000);
}

// ����Ա������ĺ���
void Change_Pwd()
{
    int i = 0;           // �������볤��
    char New_Pwd[11], s; // �����롢��ʱ�洢�ַ�
    FILE *rf;
    rf = fopen("pwd.txt", "w");
    printf("\n[-]�����������룺");
    while (s = getch())
    {
        if (s == '\r') // �س��˳�����
        {
            New_Pwd[i] = '\0';
            break;
        }
        if (s == '\b')
        {
            if (i != 0)
            {
                i--;
                printf("\b \b"); // ���ˡ��ڵ�*������
            }
        }
        else if (i < Pwd_Max)
        {
            putchar('*');
            New_Pwd[i++] = s;
        }
    }
    encrypt(New_Pwd);
    fprintf(rf, "%s", New_Pwd);
    printf("\n\n[-]������ĳɹ���");
    Sleep(1000);
    fclose(rf);
}

// ����ϵͳ
void Admin_System()
{
    if (Login())
    {
        int quit = 1;
        mgraph g;
        Create_Map(&g);
        while (quit)
        {
            switch (Admin_Menu())
            {
            case 1: // ������Ϣ����
                system("cls");
                Change_Info(&g);
                break;
            case 2: // ����Ա�������
                system("cls");
                Change_Pwd();
                break;
            case 3: // �˳�����ϵͳ
                system("cls");
                Admin_Exit(&quit);
                break;
            default:
                printf("[-]�������������������룡\n\n");
            }
            system("cls");
        }
    }
}

// ���ܺ���
void encrypt(char *s)
{
    int i;
    for (i = 0; i < strlen(s); i++)
        if (s[i] % 2 == 0)
            s[i] += 2;
        else
            s[i] -= 2;
}

// ���ܺ���
void decrypt(char *s)
{
    int i;
    for (i = 0; i < strlen(s); i++)
        if (s[i] % 2 == 0)
            s[i] -= 2;
        else
            s[i] += 2;
}

void showPath(int path[], int v0, int v1)
{ //���v0��v��·��
    if (v1 == v0)
    {
        switch (v0)
        {
        case 0:
            printf("�˽�¥");
            break;
        case 1:
            printf("���ҽԺ");
            break;
        case 2:
            printf("������ڿ�");
            break;
        case 3:
            printf("����԰����");
            break;
        case 4:
            printf("�����");
            break;
        case 5:
            printf("��ɽ��԰");
            break;
        case 6:
            printf("����ɽ����");
            break;
        case 7:
            printf("�ʼ�ɽ");
            break;
        default:
            printf("[-]�������������������룡\n\n");
        }
        return;
    }
    showPath(path, v0, path[v1]); //�ݹ飬ֱ����һ������
    switch (v1)
    {
    case 0:
        printf("->�˽�¥");
        break;
    case 1:
        printf("->���ҽԺ");
        break;
    case 2:
        printf("->������ڿ�");
        break;
    case 3:
        printf("->����԰����");
        break;
    case 4:
        printf("->�����");
        break;
    case 5:
        printf("->��ɽ��԰");
        break;
    case 6:
        printf("->����ɽ����");
        break;
    case 7:
        printf("->�ʼ�ɽ");
        break;
    default:
        printf("[-]�������������������룡\n\n");
    }
}

void showResult(int v0, int v1, int dist[], int path[])
{ //������
    showPath(path, v0, v1);
    printf("������Ҫ�ߵľ���Ϊ%d��\n\n", dist[v1]);
}

void Ai_Plan(mgraph *g)
{
    int dist[M];                       //����������dist[i]�洢��ǰ�ڵ�v��i����С����
    int path[M];                       //·��������path[i]=k;��ʾ��k��i
    int final[M];                      //��ʾ��ǰԪ���Ƿ�������·��
    int i, j, c, v, min, minV, v0, v1; //min��¼��С�ߵ�ֵ,minV��¼��Ӧ�ĵ�

    //1.��ȡ�����յ�
    do
    {
        printf("\n[-]�����ĸ��������(���)��");
        scanf("%d", &v0);
    } while (Judge_Num(v0));
    v0--;
    do
    {
        printf("\n[-]����ȥ�ĸ�����(���)��");
        scanf("%d", &v1);
    } while (Judge_Num(v1));
    v1--;

    //2.��ʼ������S���������dist
    for (i = 0; i < g->vexNum; i++)
    {
        dist[i] = INF;
        path[i] = -1;
        final[i] = 0;
    }
    v = v0;
    dist[v] = 0;

    //2.�����ҳ�n-1���ڵ����S��
    for (c = 1; c < g->vexNum; c++)
    { //������n-1�������̾���(����n-1��ѭ��)��ÿ�����һ�������̾���(����һ����)��c���������
        min = INF;
        final[v] = 1; //��v���뼯��s
        for (i = 0; i < g->vexNum; i++)
        { //ɨ��G��v�������ڽӵ�i����ѡȡ��Сֵ��v->minV��ֵΪmin
            //�޸�S��v-s�и��ڵ�ľ���
            if (i != v && final[i] == 0 && dist[v] + g->edge[v][i] < dist[i])
            {                                      //��������˸�С��
                dist[i] = dist[v] + g->edge[v][i]; //�޸�·������С����
                path[i] = v;                       //�޸�·��
            }
            if (final[i] == 0 && min > dist[i]) //final[i]==0���ų�����S�Ѵ��ڵĽ��
            {
                min = dist[i]; //�޸ĵ�ǰ��Сֵ
                minV = i;      //�޸���Сֵ�Ľڵ�
            }
        }
        //printf("\nѡ���ߣ�%d ->%d( %d )", v,minV,min);
        v = minV; //���µ�ǰ�ڵ㣬���½ڵ㿪ʼ����̾���
    }
    printf("\n[-]���·��Ϊ��\n\n");
    printf("[-]");
    showResult(v0, v1, dist, path);
    system("pause");
}

void showFloydPath(mgraph *g, int path[][M], int v0, int v)
{ //���v0��v�������м���
    int k = path[v0][v];
    if (k == -1)
        return;
    showFloydPath(g, path, v0, k);
    printf("%s->", g->vexs[k].name);
    showFloydPath(g, path, k, v);
}

void showFloydResult(mgraph *g, int dist[][M], int path[][M])
{ //���floyd�Ľ��
    int u, v;
    for (u = 0; u < g->vexNum; u++)
        for (v = 0; v < g->vexNum; v++)
            if (dist[u][v] == INF)
                printf("[%d->%d]:���ɴ�.\n", u, v);
            else if(g->vexs[u].num != g->vexs[v].num)
            {
                printf("[%d->%d]:%s->", g->vexs[u].num, g->vexs[v].num, g->vexs[u].name);
                showFloydPath(g, path, u, v);
                printf("%s", g->vexs[v].name);
                printf("����·��%d��\n", dist[u][v]);
            }
}

void floyd(mgraph *g)
{
    int dist[M][M];
    int path[M][M];
    int u, v, k;
    for (u = 0; u < g->vexNum; u++) //��ʼ��
        for (v = 0; v < g->vexNum; v++)
        {
            dist[u][v] = g->edge[u][v];
            path[u][v] = -1;
        }
    for (k = 0; k < g->vexNum; k++)
        for (u = 0; u < g->vexNum; u++)
            for (v = 0; v < g->vexNum; v++)
                if (dist[u][k] != INF && dist[k][v] != INF && dist[u][k] + dist[k][v] < dist[u][v])
                {
                    dist[u][v] = dist[u][k] + dist[k][v];
                    path[u][v] = k;
                }
    printf("\n���о���ľ����·�����£�\n");
    showFloydResult(g, dist, path);
    system("pause");
}
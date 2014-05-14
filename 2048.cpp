###����̨��2048�ȽϺ�ʵ�֣�����������.
####������ game.h�ļ�

// ɽկ�ڿ�� 2048

    #include <iostream>
    #include <iomanip>
    #include <ctime>
    using namespace std;
    #define rand(x) ( rand() % (x) ) 
    #define UP    1
    #define DOWN  2
    #define LEFT  3
    #define RIGHT 4
    struct POS
    {
        int x;
        int y;
    };
    class Game
    {
    public:
        Game();
        ~Game();
        int  get_random_2or4();
        bool get_null_pos(POS &pos);
        bool set_2or4_pos(int m,POS &pos);
        bool merge(int direction,bool realMerge);        
        bool isGameOver();
        bool set_userinput(char c);
        bool has2048();
        void printArray();
    private:    
        int a[4][4];
    };
    Game::Game()
    {
        // �������������
        srand((unsigned(time(0))));
        // ��ʼ������
        for(int i = 0; i < 4;i++)
            for(int j = 0;j < 4;j++)
                a[i][j] = 0;
        for(int i = 0; i < 2;i++)
        {
            // �������2��4
            int m = get_random_2or4();
            // ��������λ��
            POS pos;
            get_null_pos(pos);
            set_2or4_pos(m,pos);
        }
        printArray();
    }
    Game::~Game()
    {
        
    }
    int Game::get_random_2or4()
    {
        int m = rand(4); // ����0,1,2,3
        
        // ����2 ��4 �ı���Ϊ3 : 1
        return m < 3 ? 2 : 4; 
    }
    bool Game::get_null_pos(POS &pos)
    {
        POS available_pos[16];
        int n = 0;
        for(int i = 0;i < 4;i++)
            for(int j = 0;j < 4;j++)
                if(a[i][j] == 0)
                {
                    available_pos[n].x = i;
                    available_pos[n].y = j;
                    n++;
                }
        // û�п���λ��
        if(n == 0)
            return false;
        else
        {
            int rand_i = rand(n);
            pos = available_pos[rand_i];
            return true;
        }
    }
    bool Game::set_2or4_pos(int m,POS &pos)
    {
        a[pos.x][pos.y] = m;
        return true;
    }
    bool Game::merge(int direction,bool realMerge = false)
    {
        int nRet = false;
        // ��������a������b
        int b[4][4];
        for(int i = 0;i < 4;i++)
            for(int j = 0;j < 4;j++)
                b[i][j] = a[i][j];
        if(direction == UP)
        {
            // ���Ϻϲ�
            for(int i = 0;i < 4;i++)
            {
                int has_merge = false; // ��һ��ֻ�ϲ�һ��
                for(int j = 1;j < 4;j++)
                {
                    // ��λ��Ϊ��,����
                    if(b[j][i] == 0)
                        continue;
                    // ��λ�÷ǿ�
                    int former_index = j;
                    int current_index = j - 1;
                    int val = b[j][i];
                    // �����滻����λ��ֱ������������������
                    while(current_index >= 0 && b[current_index][i] == 0)
                    {
                        b[current_index][i] = val;
                        b[former_index][i]  = 0;
                        former_index = current_index;
                        current_index -- ;
                    }
                    // �������������ͬ����
                    if(current_index >= 0 && b[current_index][i] == val)
                    {
                        if(!has_merge)    // ������δ�ϲ�������ϲ�
                        {
                            has_merge = true;
                            b[current_index][i] *= 2;
                            b[former_index][i]   = 0;
                        }
                    }
                }
                if(has_merge == true)
                    nRet = true;
            }
            
        }
        if(direction == DOWN)
        {
            // ���Ϻϲ�
            for(int i = 0;i < 4;i++)
            {
                int has_merge = false; // ��һ��ֻ�ϲ�һ��
                for(int j = 2;j >= 0;j--)
                {
                    // ��λ��Ϊ��,����
                    if(b[j][i] == 0)
                        continue;
                    // ��λ�÷ǿ�
                    int former_index = j;
                    int current_index = j + 1 ;
                    int val = b[j][i];
                    // �����滻����λ��ֱ������������������
                    while(current_index < 4 && b[current_index][i] == 0)
                    {
                        b[current_index][i] = val;
                        b[former_index][i]  = 0;
                        former_index = current_index;
                        current_index ++ ;
                    }
                    // �������������ͬ����
                    if(current_index < 4 && b[current_index][i] == val)
                    {
                        if(!has_merge)    // ������δ�ϲ�������ϲ�
                        {
                            has_merge = true;
                            b[current_index][i] *= 2;
                            b[former_index][i]   = 0;
                        }
                    }
                }
                if(has_merge == true)
                    nRet = true;
            }
        }
        if(direction == LEFT)
        {
            // ����ϲ�
            for(int i = 0; i < 4; i++)
            {
                int has_merge = false; // ��һ��ֻ�ϲ�һ��
                for(int j = 1;j < 4 ; j ++)
                {
                    if(b[i][j] == 0)
                        continue;
                    int former_index = j;
                    int current_index = j - 1;
                    int val = b[i][j];
                    //// �����滻����λ��ֱ������������������
                    while(current_index >= 0 && b[i][current_index] == 0)
                    {
                        b[i][current_index] = val;
                        b[i][former_index]  = 0;
                        former_index = current_index;
                        current_index -- ;
                    }
                    // �������������ͬ����
                    if(current_index >= 0 && b[i][current_index] == val)
                    {
                        if(!has_merge)    // ������δ�ϲ�������ϲ�
                        {
                            has_merge = true;
                            b[i][current_index] *= 2;
                            b[i][former_index]   = 0;
                        }
                    }
                }
                if(has_merge == true)
                    nRet = true;
                }
            }
        if(direction == RIGHT)
        {
            // ���Һϲ�
            for(int i = 0; i < 4; i++)
            {
                int has_merge = false; // ��һ��ֻ�ϲ�һ��
                for(int j = 2;j >= 0 ; j --)
                {
                    if(b[i][j] == 0)
                        continue;
                    int former_index = j;
                    int current_index = j + 1;
                    int val = b[i][j];
                    //// �����滻����λ��ֱ������������������
                    while(current_index < 4 && b[i][current_index] == 0)
                    {
                        b[i][current_index] = val;
                        b[i][former_index]  = 0;
                        former_index = current_index;
                        current_index ++ ;
                    }
                    // �������������ͬ����
                    if(current_index < 4 && b[i][current_index] == val)
                    {
                        if(!has_merge)    // ������δ�ϲ�������ϲ�
                        {
                            has_merge = true;
                            b[i][current_index] *= 2;
                            b[i][former_index]   = 0;
                        }
                    }
                }
                if(has_merge == true)
                    nRet = true;
                }
            }
        if(realMerge == true)
        {
            for(int i = 0;i < 4;i++)
                for(int j = 0;j < 4;j++)
                    a[i][j] = b[i][j];
        }
        return nRet;
    }
    bool Game::isGameOver()
    {
        POS pos;
        if(get_null_pos(pos) == false)
        {
            int nRet = false;
            nRet |= merge(UP,false);
            nRet |= merge(DOWN,false);
            nRet |= merge(LEFT,false);
            nRet |= merge(RIGHT,false);
            if(nRet == false)
                return true;
        }
        return false;
    }
    bool Game::set_userinput(char c)
    {
        int direction = 0;
        switch (c)
        {
            case 'i':
                direction = UP;break;
            case 'k':
                direction = DOWN;break;
            case 'j':
                direction = LEFT;break;
            case 'l':
                direction = RIGHT;break;
            default:
                return false;
        }
        // �ϲ�
        merge(direction,true);
        
        int m = get_random_2or4();
        POS pos;
        if(get_null_pos(pos))
            set_2or4_pos(m,pos);
        printArray();
        return true;
    }
    void Game::printArray()
    {
        static long turns = 1;
                // -------------------------
             //    |     |     |     |     |
             //    -------------------------
             //    |     |     |     |     |
             //    -------------------------
             //    |     |     |     |     |
             //    -------------------------
             //    |     |     |     |     |
             //    -------------------------
        cout << "���ǵ�"<< left << setw(5) << turns++ << "��"<< endl;
        for(int i = 0;i < 25;i++)
            cout << '-';
        cout << endl;
        for(int i = 0; i < 4;i++)
        {
            
            for(int j = 0;j < 4;j++)
            {
                cout << '|';
                cout << ' ';
                if(a[i][j] != 0)
                    cout << left << setw(4) << a[i][j];
                else
                    cout << left << setw(4) << ' ';
            }
            cout << '|';
            cout << endl;
            for(int k = 0;k < 25;k++)
                cout << '-';
            cout << endl;
        }
        cout << endl;
    }
    bool Game::has2048()
    {
        for(int i = 0; i < 4 ;i++)
            for(int j = 0; j < 4;j++)
                if(a[i][j] == 2048)
                    return true;
        return false;
    }


####������ main.cpp �ļ�

    #include "Game.h"
    #include <conio.h>
    int main()
    {
        cout << "---------------------------------" <<endl;
        cout << "��Ϸ˵����" <<endl;
        cout << "���� J K L I �ֱ���� �� �� �� �� " << endl;
        cout << "���������ʼ��Ϸ" <<endl;
        cout << "---------------------------------" <<endl;
        getch();
        Game game;
        while(!game.isGameOver() && !game.has2048())
        {
            char c = getch();
            game.set_userinput(c);
        }
        if(game.isGameOver())
            cout << "ɧ�꣬��ȥ������" << endl;
            
        if(game.has2048())
            cout << "Ĥ�ݴ���" << endl;
        getch();
        return 0;
    }


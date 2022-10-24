#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>

void step_one(int);
void step_two(int);
int eat(int,int,int);
int fold_up(int,int,int);


char char_chess_color[9][9],char_chess_layer[9][9],char_chess_type[9][9];
int int_chess_color[9][9],int_chess_layer[9][9],int_chess_type[9][9];
int color;
int main(int argc,char* argv[])
{
    int i,j,step;
    FILE *chessColor,*chessLayer,*chessType,*stepLog;
    //Color = argv[1];
    //step = argv[2];
    chessColor = fopen(argv[3],"r");
    chessLayer = fopen(argv[4],"r");
    chessType = fopen(argv[5],"r");
    stepLog = fopen(argv[6],"r");
    if (strcmp(argv[1], "white") == 0)
    {
        color = 1;
    }
    else
    {
        color = 2;
    }
    if (strcmp(argv[2], "1") == 0)
    {
        step = 1;
    }
    else
    {
        step = 2;
    }
// chess_color
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            int a;
            a = fgetc(chessColor);
            while(a != '0' && a != '1' && a != '2')
            {
                a = fgetc(chessColor);
            }
            char_chess_color[i][j] = a;
        }
    }
    for(i=0;i<9;i++) // char turn to int
    {
        for(j=0;j<9;j++)
        {
            int_chess_color[i][j] = char_chess_color[i][j] - 48;
        }
    }
    for(i=0;i<4;i++) //turn to -1 of the edge
    {
        for(j=5;j<9-i;j++)
        {
            int_chess_color[i][j+i] = -1;
            int_chess_color[j+i][i] = -1;
        }
    }
    int_chess_color[4][4] = -1;

// chess_layer

    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            int a;
            a = fgetc(chessLayer);
            while(a != '0' && a != '1' && a != '2' && a != '3' && a != '4' && a != '5' && a != '6' && a != '7' && a != '8' && a != '9')
            {
                a = fgetc(chessLayer);
            }
            char_chess_layer[i][j] = a;
        }
    }
    for(i=0;i<9;i++) // char turn to int
    {
        for(j=0;j<9;j++)
        {
            int_chess_layer[i][j] = char_chess_layer[i][j] - 48;
        }
    }
    for(i=0;i<4;i++) //turn to -1 of the edge
    {
        for(j=5;j<9-i;j++)
        {
            int_chess_layer[i][j+i] = -1;
            int_chess_layer[j+i][i] = -1;
        }
    }
    int_chess_layer[4][4] = -1;

//chess_type
    for(i=0;i<9;i++)
        {
        for(j=0;j<9;j++)
        {
            int a;
            a = fgetc(chessType);
            while(a != '0' && a != '1' && a != '2' && a!='3')
            {
                a = fgetc(chessType);
            }
            char_chess_type[i][j] = a;
        }
    }
    for(i=0;i<9;i++) // char turn to int
    {
        for(j=0;j<9;j++)
        {
            int_chess_type[i][j] = char_chess_type[i][j] - 48;
        }
    }
    for(i=0;i<4;i++) //turn to -1 of the edge
    {
        for(j=5;j<9-i;j++)
        {
            int_chess_type[i][j+i] = -1;
            int_chess_type[j+i][i] = -1;
        }
    }
    int_chess_type[4][4] = -1;


    fclose(chessColor);
    fclose(chessLayer);
    fclose(chessType);
    fclose(stepLog);

/////////////////////////////////////////////////////
/*----------------start----------------------------*/
/////////////////////////////////////////////////////



if(step == 1)
{
    step_one(color);
}
else
{
    step_two(color);
}


/////////////////////////////////////////////////////
/*----------------end------------------------------*/
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
/*----------------write to file--------------------*/
chessColor = fopen(argv[3],"w");
chessLayer = fopen(argv[4],"w");
chessType = fopen(argv[5],"w");

for(i=0;i<9;i++)
{
    for(j=0;j<9;j++)
    {
        fprintf(chessColor,"%d",int_chess_color[i][j]);
        if(j!=8) fprintf(chessColor,",");
    }
    if(i!=8)
    {
        fprintf(chessColor,"\n");
    }
}
for(i=0;i<9;i++)
{
    for(j=0;j<9;j++)
    {
        fprintf(chessLayer,"%d",int_chess_layer[i][j]);
        if(j!=8) fprintf(chessLayer,",");
    }
    if(i!=8)
    {
       fprintf(chessLayer,"\n");
    }
}
for(i=0;i<9;i++)
{
    for(j=0;j<9;j++)
    {
        fprintf(chessType,"%d",int_chess_type[i][j]);
        if(j!=8) fprintf(chessType,",");
    }
    if(i!=8)
    {
        fprintf(chessType,"\n");
    }
}
fclose(chessColor);
fclose(chessLayer);
fclose(chessType);

/*----------------write to file--------------------*/
/////////////////////////////////////////////////////
    return 0;
}

/////////////////////////////////////////////////////
/*----------------rule-----------------------------*/
/////////////////////////////////////////////////////


void step_one(int color)
{
    int i,j,row,column,eat_or_not = 0,ran_row,ran_col;
    int flag = 0;
    int my_max_row,my_max_column,my_max_level;
    srand(time(NULL));
    ran_row = (rand()%9);
    ran_col = (rand()%9);

    for(i=0;i<9;i++)
    {
        ran_row = (ran_row + 1)%9;
        for(j=0;j<9;j++)
        {
            ran_col = (ran_col + 1)%9;
            if(int_chess_color[ran_row][ran_col] == color && int_chess_layer[ran_row][ran_col] >= my_max_level)
            {
                my_max_row = ran_row;
                my_max_column = ran_col;
                my_max_level = int_chess_layer[ran_row][ran_col];
            }
        }
    }
    eat_or_not = eat(color,my_max_row,my_max_column);

    for(i=0;i<9;i++)
    {
        ran_row = (ran_row + 1)%9;
        if(eat_or_not == 1)
        {
            break;
        }
        for(j=0;j<9;j++)
        {
            ran_col = (ran_col + 1)%9;
            if(int_chess_color[ran_row][ran_col] == color && eat_or_not == 0)
            {
                row = ran_row;
                column = ran_col;
                eat_or_not = eat(color,row,column);
            }
            if(eat_or_not == 1)
            {
                break;
            }
        }
    }
}


void step_two(int color)
{
    int i,j,k,l,row,column,eat_or_not = 0,fold_or_not = 0,a = 0;
    int tzaar_fold_flag = 0;
    int chess_num_me = 0,chess_num_opp = 0;
    int ran_row,ran_col,enemy_max_level=1;
    int my_tzaar_maxlayer=0,my_tzaar_maxlayer_row=0,my_tzaar_maxlayer_col=0,my_tzarra_maxlayer=0,my_tzarra_maxlayer_row=0,my_tzarra_maxlayer_col=0;
    int my_max_row,my_max_column,my_max_level;
    srand(time(NULL));
    ran_row = (rand()%9);
    ran_col = (rand()%9);


////////////////////////////////////////
/*----------------1----------------*/
////////////////////////////////////////

for(i=0;i<9;i++)
{
    for(j=0;j<9;j++)
    {
        if(int_chess_color[i][j] == color && int_chess_type[i][j] == 3 && int_chess_layer[i][j] >= my_tzaar_maxlayer)
        {
            my_tzaar_maxlayer_row = i;
            my_tzaar_maxlayer_col = j;
            my_tzaar_maxlayer = int_chess_layer[i][j];
        }
        if(int_chess_color[i][j] == color && int_chess_type[i][j] == 2 && int_chess_layer[i][j] >= my_tzarra_maxlayer)
        {
            my_tzarra_maxlayer_row = i;
            my_tzarra_maxlayer_col = j;
            my_tzarra_maxlayer = int_chess_layer[i][j];
        }
        if(int_chess_color[i][j] != color && int_chess_layer[i][j] >= enemy_max_level)
        {
            enemy_max_level = int_chess_layer[i][j];
        }
        if(int_chess_color[i][j] == color && int_chess_layer[i][j] >= my_max_level)
        {
            my_max_row = i;
            my_max_column = j;
            my_max_level = int_chess_layer[i][j];
        }
        if(int_chess_color[i][j] == color)
        {
            chess_num_me++;
        }
        if(int_chess_color[i][j] != color && int_chess_color[i][j] != 0 && int_chess_color[i][j] != -1)
        {
            chess_num_opp++;
        }
    }
}



////////////////////////////////////////
/*----------------1----------------*/
////////////////////////////////////////

    if(my_max_level != 1 && my_tzaar_maxlayer > enemy_max_level && (my_tzarra_maxlayer > enemy_max_level || chess_num_me-chess_num_opp<=2 || enemy_max_level<5) || chess_num_opp<8)//eat
    {
        eat_or_not = eat(color,my_max_row,my_max_column);
        for(i=0;i<9;i++)
        {
            ran_row = (ran_row + 1)%9;
            if(eat_or_not == 1)
            {
                break;
            }
            for(j=0;j<9;j++)
            {
                ran_col = (ran_col + 1)%9;
                if(int_chess_color[ran_row][ran_col] == color && eat_or_not == 0)
                {
                    row = ran_row;
                    column = ran_col;
                    eat_or_not = eat(color,row,column);
                }
                if(eat_or_not == 1)
                {
                    break;
                }
            }
        }
        if(eat_or_not == 1)
        {
            a = 1;
        }
        else if(eat_or_not == 0)
        {
            for(i=0;i<9;i++)
            {
                ran_row = (ran_row + 1)%9;
                if(fold_or_not == 1)
                {
                    break;
                }
                for(j=0;j<9;j++)
                {
                    ran_col = (ran_col + 1)%9;
                    if(int_chess_color[ran_row][ran_col] == color && fold_or_not == 0)
                    {
                        row = ran_row;
                        column = ran_col;
                        fold_or_not = fold_up(color,row,column);
                    }
                    if(fold_or_not == 1)
                    {
                        break;
                    }
                }
            }
        }
    }
    else//fold_up
    {
        for(i=0;i<9;i++)
            {
                if(fold_or_not == 1)
                {
                    break;
                }
                for(j=0;j<9;j++)
                {
                    if(int_chess_color[i][j] == color && int_chess_type[i][j] == 3 && int_chess_layer[i][j] >= my_tzaar_maxlayer && (my_tzaar_maxlayer <= enemy_max_level))
                    {
                        row = i;
                        column = j;
                        fold_or_not = fold_up(color,row,column);
                    }
                    if(fold_or_not == 1)
                    {
                        tzaar_fold_flag = 1;
                        break;
                    }
                }
            }
        if(tzaar_fold_flag == 0)
        {
            for(i=9;i>0;i--)
            {
                if(fold_or_not == 1)
                {
                    break;
                }
                for(j=9;j>0;j--)
                {
                    if(int_chess_color[i][j] == color && int_chess_type[i][j] == 2 && int_chess_layer[i][j] >= my_tzarra_maxlayer && (my_tzarra_maxlayer <= enemy_max_level))
                    {
                        row = i;
                        column = j;
                        fold_or_not = fold_up(color,row,column);
                    }
                    if(fold_or_not == 1)
                    {
                        break;
                    }
                }
            }
        }
        if(fold_or_not == 1)
        {
            a = 1;
        }
        else if(fold_or_not == 0)
        {
            for(i=0;i<9;i++)
            {
                ran_row = (ran_row + 1)%9;
                if(eat_or_not == 1)
                {
                    break;
                }
                for(j=0;j<9;j++)
                {
                    ran_col = (ran_col + 1)%9;
                    if(int_chess_color[ran_row][ran_col] == color && eat_or_not == 0)
                    {
                        row = ran_row;
                        column = ran_col;
                        eat_or_not = eat(color,row,column);
                    }
                    if(eat_or_not == 1)
                    {
                        break;
                    }
                }
            }
        }
    }
}

int eat(int color,int row,int column)
{
    int direction,i;
    int flag = 0,count = 0;
    srand(time(NULL));
    direction = (rand()%6);
    while(flag == 0)
    {
        switch(direction)
        {
        case 0:
            for(i=1;i<8;i++)
            {
                if(int_chess_color[row][column+i] == color || int_chess_color[row][column+i] <0 || int_chess_color[row][column+i] > 2)
                {
                    break;
                }
                else if(int_chess_layer[row][column+i] > int_chess_layer[row][column])
                {
                    break;
                }
                else if(int_chess_color[row][column+i] != color && int_chess_color[row][column+i] != 0)
                {
                    if(int_chess_layer[row][column] >= int_chess_layer[row][column+i])
                    {
                        int_chess_color[row][column] = 0;
                        int_chess_color[row][column+i] = color;
                        int_chess_layer[row][column+i] = int_chess_layer[row][column];
                        int_chess_layer[row][column] = 0;
                        int_chess_type[row][column+i] = int_chess_type[row][column];
                        int_chess_type[row][column] = 0;
                        flag = 1;
                        break;
                    }
                }
            }
            break;
        case 1:
        for(i=1;i<8;i++)
        {
            if(int_chess_color[row-i][column] == color || int_chess_color[row-i][column] < 0 || int_chess_color[row-i][column] > 2)
            {
                break;
            }
            else if(int_chess_layer[row-i][column] > int_chess_layer[row][column])
            {
                    break;
            }
            else if(int_chess_color[row-i][column] != color && int_chess_color[row-i][column] != 0)
            {
                if(int_chess_layer[row][column] >= int_chess_layer[row-i][column])
                {
                    int_chess_color[row][column] = 0;
                    int_chess_color[row-i][column] = color;
                    int_chess_layer[row-i][column] = int_chess_layer[row][column];
                    int_chess_layer[row][column] = 0;
                    int_chess_type[row-i][column] = int_chess_type[row][column];
                    int_chess_type[row][column] = 0;
                    flag = 1;
                    break;
                }
            }
        }
        break;
        case 2:
        for(i=1;i<8;i++)
        {
            if(int_chess_color[row-i][column-i] == color || int_chess_color[row-i][column-i] < 0 || int_chess_color[row-i][column-i] > 2)
            {
                break;
            }
            else if(int_chess_layer[row-i][column-i] > int_chess_layer[row][column])
            {
                    break;
            }
            else if(int_chess_color[row-i][column-i] != color && int_chess_color[row-i][column-i] != 0)
            {
                if(int_chess_layer[row][column] >= int_chess_layer[row-i][column-i])
                {
                    int_chess_color[row][column] = 0;
                    int_chess_color[row-i][column-i] = color;
                    int_chess_layer[row-i][column-i] = int_chess_layer[row][column];
                    int_chess_layer[row][column] = 0;
                    int_chess_type[row-i][column-i] = int_chess_type[row][column];
                    int_chess_type[row][column] = 0;
                    flag = 1;
                    break;
                }
            }
        }
        break;
        case 3:
        for(i=1;i<8;i++)
        {
            if(int_chess_color[row][column-i] == color || int_chess_color[row][column-i] < 0 || int_chess_color[row][column-i] > 2)
            {
                break;
            }
            else if(int_chess_layer[row][column-i] > int_chess_layer[row][column])
            {
                    break;
            }
            else if(int_chess_color[row][column-i] != color && int_chess_color[row][column-i] != 0)
            {
                if(int_chess_layer[row][column] >= int_chess_layer[row][column-i])
                {
                    int_chess_color[row][column] = 0;
                    int_chess_color[row][column-i] = color;
                    int_chess_layer[row][column-i] = int_chess_layer[row][column];
                    int_chess_layer[row][column] = 0;
                    int_chess_type[row][column-i] = int_chess_type[row][column];
                    int_chess_type[row][column] = 0;
                    flag = 1;
                    break;
                }
            }
        }
        break;
        case 4:
        for(i=1;i<8;i++)
        {
            if(int_chess_color[row+i][column] == color || int_chess_color[row+i][column] < 0 || int_chess_color[row+i][column] > 2)
            {
                break;
            }
            else if(int_chess_layer[row+i][column] > int_chess_layer[row][column])
            {
                    break;
            }
            else if(int_chess_color[row+i][column] != color && int_chess_color[row+i][column] != 0)
            {
                if(int_chess_layer[row][column] >= int_chess_layer[row+i][column])
                {
                    int_chess_color[row][column] = 0;
                    int_chess_color[row+i][column] = color;
                    int_chess_layer[row+i][column] = int_chess_layer[row][column];
                    int_chess_layer[row][column] = 0;
                    int_chess_type[row+i][column] = int_chess_type[row][column];
                    int_chess_type[row][column] = 0;
                    flag = 1;
                    break;
                }
            }
        }
        break;
        case 5:
        for(i=1;i<8;i++)
        {
            if(int_chess_color[row+i][column+i] == color || int_chess_color[row+i][column+i] < 0 || int_chess_color[row+i][column+i] > 2)
            {
                break;
            }
            else if(int_chess_layer[row+i][column+i] > int_chess_layer[row][column])
            {
                break;
            }
            else if(int_chess_color[row+i][column+i] != color && int_chess_color[row+i][column+i] != 0)
            {
                if(int_chess_layer[row][column] >= int_chess_layer[row+i][column+i])
                {
                    int_chess_color[row][column] = 0;
                    int_chess_color[row+i][column+i] = color;
                    int_chess_layer[row+i][column+i] = int_chess_layer[row][column];
                    int_chess_layer[row][column] = 0;
                    int_chess_type[row+i][column+i] = int_chess_type[row][column];
                    int_chess_type[row][column] = 0;
                    flag = 1;
                    break;
                }
            }
        }
        break;
        }//end of switch
        direction = ((direction + 1) % 6) ;
        //printf("direction = %d\n",direction);
        count++;
        if(count == 7)
        {
            return 0;
        }
    }//end of while
    if(flag ==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int fold_up(int color,int row,int column)
{
    int direction,i,count = 0;
    int flag = 0;
    srand(time(NULL));
    direction = (rand()%6);

    while(flag == 0)
    {
        switch(direction)
        {
        case 0:
            for(i=1;i<8;i++)
            {
                if((int_chess_color[row][column+i] != color && int_chess_color[row][column+i] != 0) || int_chess_color[row][column+i] < 0 || int_chess_color[row][column+i] > 2)
                {
                    break;
                }
                else if(int_chess_color[row][column+i] == color && int_chess_layer[row][column+i]>0 && int_chess_layer[row][column+i]<10 && int_chess_layer[row][column+i] ==1)
                {
                    int_chess_color[row][column] = 0;
                    int_chess_color[row][column+i] = color;
                    int_chess_layer[row][column+i] = int_chess_layer[row][column+i] + int_chess_layer[row][column];
                    int_chess_layer[row][column] = 0;
                    int_chess_type[row][column+i] = int_chess_type[row][column];
                    int_chess_type[row][column] = 0;
                    flag = 1;
                    return 1;
                }
            }
            break;
        case 1:
            for(i=1;i<8;i++)
            {
                if((int_chess_color[row-i][column] != color && int_chess_color[row-i][column] != 0) || int_chess_color[row-i][column] < 0 || int_chess_color[row-i][column] > 2 && int_chess_layer[row-i][column] != 1)
                {
                    break;
                }
                else if(int_chess_color[row-i][column] == color && int_chess_layer[row-i][column]>0 && int_chess_layer[row-i][column]<10)
                {
                    int_chess_color[row][column] = 0;
                    int_chess_color[row-i][column] = color;
                    int_chess_layer[row-i][column] = int_chess_layer[row-i][column] + int_chess_layer[row][column];
                    int_chess_layer[row][column] = 0;
                    int_chess_type[row-i][column] = int_chess_type[row][column];
                    int_chess_type[row][column] = 0;
                    flag = 1;
                    return 1;
                }
            }
            break;
        case 2:
            for(i=1;i<8;i++)
            {
                if((int_chess_color[row-i][column-i] != color && int_chess_color[row-i][column-i] != 0) || int_chess_color[row-i][column-i] < 0 || int_chess_color[row-i][column-i] > 2 && int_chess_layer[row-i][column-i] != 1)
                {
                    break;
                }
                else if(int_chess_color[row-i][column-i] == color && int_chess_layer[row-i][column-i]>0 && int_chess_layer[row-i][column-i]<10 && int_chess_layer[row-i][column-i] == 1)
                {
                    int_chess_color[row][column] = 0;
                    int_chess_color[row-i][column-i] = color;
                    int_chess_layer[row-i][column-i] = int_chess_layer[row-i][column-i] + int_chess_layer[row][column];
                    int_chess_layer[row][column] = 0;
                    int_chess_type[row-i][column-i] = int_chess_type[row][column];
                    int_chess_type[row][column] = 0;
                    flag = 1;
                    return 1;
                }
            }
            break;
        case 3:
            for(i=1;i<8;i++)
            {
                if((int_chess_color[row][column-i] != color && int_chess_color[row][column-i] != 0) || int_chess_color[row][column-i] < 0 || int_chess_color[row][column-i] > 2 && int_chess_layer[row][column-i] != 1)
                {
                    break;
                }
                else if(int_chess_color[row][column-i] == color && int_chess_layer[row][column-i]>0 && int_chess_layer[row][column-i]<10 && int_chess_layer[row][column-i] == 1)
                {
                    int_chess_color[row][column] = 0;
                    int_chess_color[row][column-i] = color;
                    int_chess_layer[row][column-i] = int_chess_layer[row][column-i] + int_chess_layer[row][column];
                    int_chess_layer[row][column] = 0;
                    int_chess_type[row][column-i] = int_chess_type[row][column];
                    int_chess_type[row][column] = 0;
                    flag = 1;
                    return 1;
                }
            }
            break;
        case 4:
            for(i=1;i<8;i++)
            {
                if((int_chess_color[row+i][column] != color && int_chess_color[row+i][column] != 0) || int_chess_color[row+i][column] < 0 || int_chess_color[row+i][column] > 2 && int_chess_layer[row+i][column] != 1)
                {
                    break;
                }
                else if(int_chess_color[row+i][column] == color && int_chess_layer[row+i][column]>0 && int_chess_layer[row+i][column]<10 && int_chess_layer[row+i][column] == 1)
                {
                    int_chess_color[row][column] = 0;
                    int_chess_color[row+i][column] = color;
                    int_chess_layer[row+i][column] = int_chess_layer[row+i][column] + int_chess_layer[row][column];
                    int_chess_layer[row][column] = 0;
                    int_chess_type[row+i][column] = int_chess_type[row][column];
                    int_chess_type[row][column] = 0;
                    flag = 1;
                    return 1;
                }
            }
            break;
        case 5:
            for(i=1;i<8;i++)
            {
                if((int_chess_color[row+i][column+i] != color && int_chess_color[row+i][column+i] != 0) || int_chess_color[row+i][column+i] < 0 || int_chess_color[row+i][column+i] > 2 && int_chess_layer[row+i][column+i] != 1)
                {
                    break;
                }
                else if(int_chess_color[row+i][column+i] == color && int_chess_layer[row+i][column+i]>0 && int_chess_layer[row+i][column+i]<10 && int_chess_layer[row+i][column+i] == 1)
                {
                    int_chess_color[row][column] = 0;
                    int_chess_color[row+i][column+i] = color;
                    int_chess_layer[row+i][column+i] = int_chess_layer[row+i][column+i] + int_chess_layer[row][column];
                    int_chess_layer[row][column] = 0;
                    int_chess_type[row+i][column+i] = int_chess_type[row][column];
                    int_chess_type[row][column] = 0;
                    flag = 1;
                    return 1;
                }
            }
            break;
        }//end of switch
        direction = ((direction + 1) % 6) ;
        count++;
        if(count == 6)
        {
            return 0;
        }
    }//end of while
    if(flag ==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

////////////////////////////////////////
/*----------------rule----------------*/
////////////////////////////////////////

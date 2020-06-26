#include <iostream>
#include <cstring>

using namespace std;
void set_maps(int x, int y, int digit);
void print_map();
int box_judge(int x, int y);
void print_digit_map(int digit);
int same_box_judge(int saved_index[], int num);

//存储地图
int maps[9][9];
int digit_maps[10][9][9] = {0};
int start_point_x[9] = {0, 0, 0, 3, 3, 3, 6, 6, 6};
int start_point_y[9] = {0, 3, 6, 0, 3, 6, 0, 3, 6};

int main()
{
    int i, j;
    bool finished = false;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            cin >> maps[i][j];
        }
    }
    memset(digit_maps, 0, sizeof(digit_maps));
    //分析读入的数据
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            int digit = maps[i][j];
            if(digit!=0){
                //将对应数字的行列以及九宫格内设置为不可选
//                if(digit==2){
//                    cout << "before set: " << i << " "<< j << endl;
//                    print_digit_map(2);
//                    cout << endl;
//                }
                set_maps(i, j, digit);
//                if(digit==2){
//                    cout << "after set" << endl;
//                    print_digit_map(2);
//                    cout << endl;
//                }
            }
        }
    }
    cout << endl;

    //开始九宫格按数字搜索，digit表示搜索的数字，k表示搜索的九宫格id
    while(finished!=true){
        finished = true;
        for(int digit=1; digit<10; digit++){
            //九宫格判断
            for(int k=0; k<9; k++){
                int x = start_point_x[k];
                int y = start_point_y[k];
                int num = 0;
                int saved_i = 0, saved_j = 0;
                for(i=x; i<x+3; i++){
                    for(j=y; j<y+3; j++){
                        if(digit_maps[digit][i][j]==0){
                            num+=1;
                            saved_i = i;
                            saved_j = j;
                        }
                    }
                }
//                if(digit==2){
//                    print_digit_map(2);
//                }
    //            cout << num << endl;
                //填入数字
                if(num==1){
//                    cout << "find" << endl;
                    finished = false;
                    maps[saved_i][saved_j] = digit;
                    set_maps(saved_i, saved_j, digit);
                    cout << "(" << saved_i << ", " << saved_j <<")" << " " << digit << endl;
//                    for(i=x; i<x+3; i++){
//                        for(j=y; j<y+3; j++){
//                            if(digit_maps[digit][i][j]==0){
////                                if(digit==2){
////                                    print_digit_map(2);
////                                }
//                                maps[i][j] = digit;
//                                set_maps(i, j, digit);
//                                cout << "(" << i << ", " << j <<")" << " " << digit << endl;
//                            }
//                        }
//                    }
                }
            }

            //行列判断, i表示, j表示列
            //按行判断
            for(i=0; i<9; i++){
                int num = 0;
                int saved_j[9] = {0};
                for(j=0; j<9; j++){
                    if(digit_maps[digit][i][j]==0){
                        saved_j[num] = j;
                        num += 1;
                    }
                }
                //表示找到
                if(num==1){
                    finished = false;
                    maps[i][saved_j[0]] = digit;
                    set_maps(i, saved_j[0], digit);
                    cout << "(" << i << ", " << saved_j[0] <<")" << " " << digit << endl;
                }
                if(num>1 && num < 4){
                    int box_num = same_box_judge(saved_j, num);
                    if(box_num!=-1){
                        box_num = (i / 3) * 3 + box_num;
//                        cout << "digit: " << digit << " row: " << i << " box_num: "<< box_num << endl;
//                        print_digit_map(digit);
//                        cout << endl;
//                        print_map();
//                        cout << endl;
                        //表示这个box的不是这一行的地方不可以填该digit
                        for(int row=start_point_x[box_num]; row<start_point_x[box_num]+3; row++){
                            if(row == i){
                                continue;
                            }
                            for(int col=start_point_y[box_num]; col<start_point_y[box_num]+3; col++){
//                                cout << box_num << ": " << digit << " :: " << row << " " << col << endl;
                                if(digit_maps[digit][row][col]==0){
                                    //有发生改变
                                    finished = false;
                                    digit_maps[digit][row][col] = 1;
                                }
                            }
                        }
//                        cout << "after set ---" << endl;
//                        print_digit_map(digit);
//                        cout << endl;
                    }
                }
            }

            //按列判断
            for(j=0; j<9; j++){
                int num = 0;
                int saved_i[9] = {0};
                for(i=0; i<9; i++){
                    if(digit_maps[digit][i][j]==0){
                        saved_i[num] = i;
                        num += 1;
                    }
                }
                //表示找到
                if(num==1){
                    finished = false;
                    maps[saved_i[0]][j] = digit;
                    set_maps(saved_i[0], j, digit);
                    cout << "(" << saved_i[0] << ", " << j <<")" << " " << digit << endl;
                }
                if(num>1 && num < 4){
                    int box_num = same_box_judge(saved_i, num);
                    if(box_num!=-1){
                        //表示这个box的不是这一列的地方不可以填该digit
                        box_num = box_num * 3 + j / 3;
//                        cout << "digit: " << digit << " col: " << j << " box_num: "<< box_num << endl;
//                        print_digit_map(digit);
//                        cout << endl;
//                        print_map();
//                        cout << endl;
                        for(int row=start_point_x[box_num]; row<start_point_x[box_num]+3; row++){
                            for(int col=start_point_y[box_num]; col<start_point_y[box_num]+3; col++){
//                                cout << box_num << ": " << digit << " :: " << row << " " << col << endl;
                                if(col == j){
                                    continue;
                                }
                                if(digit_maps[digit][row][col]==0){
                                    //表示发生改变
                                    finished = false;
                                    digit_maps[digit][row][col] = 1;
                                }
                            }
                        }
//                        cout << "after set ---" << endl;
//                        print_digit_map(digit);
//                        cout << endl;
                    }
                }
            }

            //单个格子判断
            for(i=0; i<9; i++){
                for(j=0; j<9; j++){
                    if(digit_maps[digit][i][j]==0){
                        //判断这个位置的其他digit map是否为1
                        bool find_one = true;
                        for(int d=1; d<10; d++){
                            if(d!=digit && digit_maps[d][i][j]==0){
                                find_one = false;
                                break;
                            }
                        }
                        if(find_one==true){
                            finished = false;
                            maps[i][j] = digit;
                            set_maps(i, j, digit);
                        }
                    }
                }
            }
        }
    }
//    for(int digit=1; digit<10; digit++){
//        print_digit_map(digit);
//        cout << endl;
//    }
    print_map();
    cout << "Hello world!" << endl;
    return 0;
}

void set_maps(int x, int y, int digit)
{
    //所有数字的map相应的位置设置为不可选
    int i, j;
    for(i=1; i<10; i++){
        digit_maps[i][x][y] = 1;
//        if(i==2 && digit!=2){
//            cout << "set 2 : " << digit << endl;
//            print_digit_map(2);
//            cout << "check up" << endl;
//        }
    }
    //第x行
    for(i=0; i<9; i++){
        digit_maps[digit][x][i] = 1;
    }
//    if(digit==1){
//        cout << "after set x row: " << endl;
//        print_digit_map(2);
//        cout << endl;
//    }
    //第y列
    for(i=0; i<9; i++){
        digit_maps[digit][i][y] = 1;
//        if(digit==1){
//            cout << "digit: " << digit << ", i: " << i << ", y: " << y << endl;
//            print_digit_map(2);
//            cout << endl;
//        }

    }
//    if(digit==1){
//        cout << "after set y col: " << endl;
//        print_digit_map(2);
//        cout << endl;
//    }
    //九宫格内
    int box_num = box_judge(x, y);

    int start_x = start_point_x[box_num-1];
    int start_y = start_point_y[box_num-1];
//    if(digit==2){
//        cout << "box: " << box_num << endl;
//        cout << "startx: " << start_x << endl;
//        cout << "starty: " << start_y << endl;
//    }
    for(i=start_x; i<start_x+3; i++){
        for(j=start_y; j<start_y+3; j++){
            digit_maps[digit][i][j] = 1;
        }
    }

}

void print_map()
{
    int i, j;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            cout << maps[i][j] << " ";
        }
        cout << endl;
    }
}

void print_digit_map(int digit)
{
    int i, j;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            cout << digit_maps[digit][i][j] << " ";
        }
        cout << endl;
    }
}

int box_judge(int x, int y)
{
    if(x<3){
        if(y<3) return 1;
        else if(y<6) return 2;
        else return 3;
    }
    else if(x<6){
        if(y<3) return 4;
        else if(y<6) return 5;
        else return 6;
    }
    else{
        if(y<3) return 7;
        else if(y<6) return 8;
        else return 9;
    }
}

int same_box_judge(int saved_index[], int num)
{
    int i;
    int box_num = saved_index[0] / 3;
    for(i=0; i<num; i++){
        if((saved_index[i] / 3) != box_num){
            return -1;
        }
    }
    return box_num;

}

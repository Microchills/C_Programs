#include <fstream>
#include <iostream>
#include <string>
using namespace std;

//定义Sentence类，包含日语jap，罗马音romaji，中文chs三个成员变量
//和learn，exercise，test三个成员函数
class Sentence {
    string jap;
    string romaji;
    string chs;

   public:
    Sentence() { ; };
    Sentence(string jap, string romaji, string chs);
    string getJap() { return jap; }
    string getRomaji() { return romaji; }
    string getChs() { return chs; }
    int learn();
    int exercise(int mode);
    int test(int i, int* score);
};

// Sentence::Sentence() {}

Sentence::Sentence(string Jap, string Romaji, string Chs) {
    jap = Jap;
    romaji = Romaji;
    chs = Chs;
}

int Sentence::learn() {
    int exitOrNot = 0;
    cout << jap << " " << romaji << " " << endl
         << chs << endl;
    cout << "--------------------------------";
    char Exitag = getchar();
    if (Exitag == 'q') {
        exitOrNot = 1;
    }
    return exitOrNot;
}

//返回值的目的是判断是否需要在练习过程中退出
int Sentence::exercise(int mode) {
    string c_answer, answer;  //正确答案，输入答案
    switch (mode - 4) {
        case 1:
            c_answer = chs;
            cout << jap << "(" << romaji << ")"
                 << "：";
            break;
        case 2:
            c_answer = romaji;
            cout << jap << " " << chs << "：";
            break;
    }
    getline(cin, answer);
    int exitOrNot = 0;
    while (answer != "") {
        if (answer == "a") {
            cout << c_answer << endl;
            break;
        } else if (answer == "q") {
            cout << "是否退出练习？(y：是；n：否)：";
            char Exitag;
            cin >> Exitag;
            cin.ignore();
            if (Exitag == 'y') {
                exitOrNot = 1;
                break;
            } else {
                cout << "请重新输入答案：";
                getline(cin, answer);
            }
        } else if (answer == c_answer) {
            cout << "<太棒了!>" << endl;
            break;
        } else {
            cout << "<再想想：";
            getline(cin, answer);
        }
    }
    cout << "-------------------------------" << endl;
    return exitOrNot;
}

//返回值的目的是判断是否需要在考试过程中退出
int Sentence::test(int i, int* score) {
    cout << jap << " " << chs << "：";
    string answer;
    int Exitag = 0;
    getline(cin, answer);
    if (answer == romaji) {
        score[i] = 1;
    } else if (answer == "q") {
        cout << "是否退出考试？(y：是；n：否)：";
        char exit;
        cin >> exit;
        if (exit == 'y') {
            Exitag = 1;
        }
        cin.ignore();
    } else {
        score[i] = 0;
    }
    cout << "-------------------------------" << endl;
    return Exitag;
}

int ChoseMode() {
    cout << "+-----------------------------+" << endl;
    cout << "|    欢迎来到<轻松学日语>     |" << endl;
    cout << "|-----------------------------|" << endl;
    cout << "|         1.学习模式          |" << endl;
    cout << "|         2.练习模式          |" << endl;
    cout << "|         3.考试模式          |" << endl;
    cout << "|         4.退出              |" << endl;
    cout << "+-----------------------------+" << endl;
    cout << "请选择模式：";
    int tag;
    cin >> tag;
    cout << "-------------------------------" << endl;
    if (tag == 2) {
        int ex_tag;
        cout << "请选择练习模式：1.日译中；2.中译日：";
        cin >> ex_tag;
        tag = tag + ex_tag + 2;  //练习模式有两种情况，统一转换为mode值5，6
        cout << "-------------------------------" << endl;
    }
    cin.ignore();
    return tag;
}

//将从文件中读取的每一行分割，转换为Sentence类
Sentence SplitFileLine(string line) {
    string jap, romaji, chs;
    int index = 0;
    int length = line.length();
    for (int i = 0; i < length; i++) {
        if (line[i] == '~') {
            index = 1;
        } else if (line[i] == '-') {
            index = 2;
        }
        switch (index) {
            case 0:
                jap += line[i];
                break;
            case 1:
                romaji += line[i];
                break;
            case 2:
                chs += line[i];
                break;
        }
    }
    romaji.erase(0, 1);
    chs.erase(0, 1);
    Sentence sentence(jap, romaji, chs);
    return sentence;
}

//读取文件内容并存入Sentence类数组中
Sentence* ReadFile() {
    ifstream file;
    string line;
    Sentence* sentences = new Sentence[50];
    file.open("DailyJapanese.txt", ios::in);
    int i = 0;
    while (getline(file, line)) {
        Sentence sentence = SplitFileLine(line);
        *(sentences + i) = sentence;
        i++;
    }
    file.close();
    return sentences;
}

//在学习、练习或考试结束后输出结果并判断是否退出
char EndofMode(int mode, int Exitag, Sentence* sentences, int* score) {
    char tag;
    int total_score = 0;
    switch (mode) {
        case 1:
            cout << "重新开始请按“r”，否则返回上一级：";
            cin >> tag;
            break;
        case 5:
        case 6:
            if (Exitag == 0) {
                cout << "练习结束，太棒了！" << endl;
            }
            cout << "重新开始请按“r”，否则返回上一级：";
            cin >> tag;
            break;
        case 3:
            if (Exitag == 0) {
                Sentence errorSen[50];
                int j = 0;
                for (int i = 0; i < 50; i++) {
                    total_score += score[i];
                    if (score[i] == 0) {
                        errorSen[j] = sentences[i];
                        j++;
                    }
                }
                cout << "<考试结束，你的分数为："
                     << total_score * 2 << " 分>" << endl;
                if (total_score == 100) {
                    cout << "全部答对，太棒啦！";
                } else {
                    cout << "本次答错的题目有：" << endl;
                    cout << "--------------------------------" << endl;
                    for (int i = 0; i < 50 - total_score; i++) {
                        string jap = errorSen[i].getJap();
                        string romaji = errorSen[i].getRomaji();
                        string chs = errorSen[i].getChs();
                        cout << jap << " " << romaji << " " << endl
                             << chs << endl;
                        cout << "--------------------------------" << endl;
                    }
                }
            }
            cout << "重新开始请按“r”，否则返回上一级：";
            cin >> tag;
            break;
    }
    cin.ignore();
    return tag;
}

//根据选择的模式对读取出的Sentence类进行操作
char ExeMode(int mode, Sentence* sentences) {
    int score[50];
    int Exitag = 0;
    switch (mode) {
        case 1:
            for (int i = 0; i < 50; i++) {
                cout << i + 1 << "、";
                Exitag = sentences[i].learn();
                if (Exitag == 1) {
                    cout << "退出练习。";
                    break;
                }
            }
            break;
        case 3:
            for (int i = 0; i < 50; i++) {
                cout << i + 1 << "、";
                Exitag = sentences[i].test(i, score);
                if (Exitag == 1) {
                    cout << "退出考试。";
                    break;
                }
            }
            break;
        case 5:
        case 6:
            for (int i = 0; i < 50; i++) {
                cout << i + 1 << "、";
                Exitag = sentences[i].exercise(mode);
                if (Exitag == 1) {
                    cout << "退出练习。";
                    break;
                }
            }
            break;
        default:
            break;
    }
    char tag = EndofMode(mode, Exitag, sentences, score);
    return tag;
}

int main() {
    //读取文件并存入数组
    Sentence* sentences = ReadFile();
    //主界面选择模式循环
    while (true) {
        char tag = 'r';
        int mode = ChoseMode();
        //退出程序
        if (mode == 4) {
            cout << "------> 期待下次相见哦~ <------";
            break;
        }
        //重复模式循环
        while (tag == 'r') {
            tag = ExeMode(mode, sentences);
        }
    }
    return 0;
}

#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

//等额本金还款
void equal_principal();

//等额本息还款
void equal_loan();

//判断还款方式并计算
void calculate();

float mortgage, rate;
int year, means;

int main(){
    cout << "---这是一个房贷计算器(输入后按“Enter”继续)---\n";
    char quitOrretry = 'r';
    //判断是否退出
    while (quitOrretry == 'r'){
        cout << "请输入您的贷款金额（万元）：";
        cin >> mortgage;
        while (mortgage <= 0) {
            cout << "您的输入有误，请重新输入贷款金额（万元）：";
            cin >> mortgage;
        }
        cout << "请输入贷款期限（年）：";
        cin >> year;
        cout << "请输入年利率（%）：";
        cin >> rate;
        cout << "请选择还款方式（1.等额本金；2.等额本息）：";
        cin >> means;
        calculate();
        cout << "--------------------------------------\n";
        cout << "输入“q”退出，输入“r”继续计算：";
        cin >> quitOrretry;
    }
}

void calculate(){
    cout << "--------------------------------------\n";
    if ( means == 1){
        equal_principal();
    }
    else if ( means == 2){
        equal_loan();
    }
    else{
        cout << "您的输入有误，请重新输入还款方式（1.等额本金；2.等额本息）：";
        cin >> means;
        calculate();
    }
}

void equal_principal(){
    //计算每月需还的本金额
    float pri_pay = mortgage / (year * 12);
    cout << "接下来的6个月你需要偿还贷款的金额为(万元)：\n";
    //输出未来6个月的还款额
    for (int i = 0; i<6; i++){
        float pri_left = mortgage - pri_pay * i;
        float interest = pri_left * rate * 0.01 / 12;
        cout << fixed << setprecision(2) << (interest+pri_pay) << " ";
    }
    cout << "\n";
    //计算还款总额
    float total_pay = mortgage + (mortgage + pri_pay) * year * 12 * rate * 0.01 / 24;
    cout << "你需要偿还的贷款总金额为（万元）：" << fixed << setprecision(2) << total_pay <<"\n";
}

void equal_loan(){
    float muti_rate = pow (1 + rate * 0.01 / 12, year * 12);
    //计算每月还款额
    float pay_month = mortgage * muti_rate * (rate * 0.01 / 12) /
                     (muti_rate - 1);
    //计算还款总额
    float total_pay = pay_month * year * 12;
    cout << "你每月需偿还的贷款金额为（万元）：" << fixed << setprecision(2) << pay_month << "\n";
    cout << "你需要偿还的贷款总额为（万元）：" << fixed << setprecision(2) << total_pay << "\n";
}
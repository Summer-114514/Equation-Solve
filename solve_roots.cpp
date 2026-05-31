#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include <iomanip>

double eval_poly(const std::vector<double>& coef, double x){
    double r = 0;
    for (double c : coef) r = r * x + c;
    return r;
}

int main(){
    std::cout << "选择方程类型：1) 线性 ax+b=0  2) 二次 ax^2+bx+c=0  3) 多项式+二分法\n选择(1/2/3): ";
    int choice;
    if(!(std::cin >> choice)) return 0;
    std::cout << std::fixed << std::setprecision(12);

    if (choice == 1) {
        double a,b; std::cout << "输入 a b: "; std::cin >> a >> b;
        if (std::abs(a) < 1e-15) {
            if (std::abs(b) < 1e-15) std::cout << "所有实数都是解\n";
            else std::cout << "无解\n";
        } else {
            std::cout << "根 x = " << -b / a << "\n";
        }
    }
    else if (choice == 2) {
        double a,b,c; std::cout << "输入 a b c: "; std::cin >> a >> b >> c;
        if (std::abs(a) < 1e-15) {
            if (std::abs(b) < 1e-15) {
                if (std::abs(c) < 1e-15) std::cout << "所有实数都是解\n";
                else std::cout << "无解\n";
            } else {
                std::cout << "退化为线性方程，根 x = " << -c / b << "\n";
            }
        } else {
            double D = b*b - 4*a*c;
            if (D > 0) {
                double r1 = (-b + std::sqrt(D)) / (2*a);
                double r2 = (-b - std::sqrt(D)) / (2*a);
                std::cout << "两实根: " << r1 << " 和 " << r2 << "\n";
            } else if (std::abs(D) < 1e-15) {
                double r = -b / (2*a);
                std::cout << "重根: " << r << "\n";
            } else {
                std::complex<double> r1((-b) / (2*a), std::sqrt(-D) / (2*a));
                std::complex<double> r2 = std::conj(r1);
                std::cout << "复根: " << r1 << " 和 " << r2 << "\n";
            }
        }
    }
    else if (choice == 3) {
        int deg; std::cout << "请输入多项式次数 n (>=1): "; std::cin >> deg;
        if (deg < 1) { std::cout << "次数应 >=1\n"; return 0; }
        std::vector<double> coef(deg+1);
        std::cout << "按降幂输入系数 a_n ... a_0: ";
        for (int i = 0; i <= deg; ++i) std::cin >> coef[i];
        double L,R; std::cout << "输入区间 L R: "; std::cin >> L >> R;
        double tol = 1e-12; int maxit = 200;
        double fa = eval_poly(coef, L), fb = eval_poly(coef, R);
        if (std::abs(fa) < tol) { std::cout << "根 x = " << L << "\n"; return 0; }
        if (std::abs(fb) < tol) { std::cout << "根 x = " << R << "\n"; return 0; }
        if (fa * fb > 0) { std::cout << "f(L) 与 f(R) 同号，二分法无法保证有根，请换区间\n"; return 0; }
        double a = L, b = R, m = a;
        for (int it = 0; it < maxit; ++it) {
            m = 0.5 * (a + b);
            double fm = eval_poly(coef, m);
            if (std::abs(fm) < tol || (b - a) / 2 < tol) break;
            if (fa * fm <= 0) { b = m; fb = fm; }
            else { a = m; fa = fm; }
        }
        std::cout << "找到近似根 x = " << m << "\n";
    }
    else {
        std::cout << "无效选择\n";
    }
    return 0;
}

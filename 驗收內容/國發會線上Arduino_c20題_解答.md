# Arduino 

```
1 ( A )在Arduino的程式中，若想加入註解，應以何符號標示?

(A) /*...*/
(B) \\
(C) "
(D) '
```

```
2 ( A )在C語言中，若變數宣告int x=27; int y=5; 試問 x % y的運算結果為何?

(A) 2
(B) 3
(C) 4
(D) 5
```

```
3 ( B )執行下列程式後，變數k = ? 

		int k=0;
		for(byte a=5; a<=10; a++)
			k+=a;

(A) 55
(B) 45
(C) 40
(D) 35		
```

```
4 (B)下面程式碼執行後,area的資料型別是:
float area;
float PI = 3.14159;
int radius = 10;
PI * radius * radius
area = PI * radius * radius

(A) int
(B) float
(C) double
(D) String

```

```
5 (A)下面程式碼執行後,area的資料型別是:
int area;
float PI = 3.14159;
int radius = 10;
PI * radius * radius
area = PI * radius * radius

(A) int
(B) float
(C) double
(D) String
```

```
6(B)下面程式碼,如果變數average要有小數點,那一個描述是不正確的?
float average;
int chinese = 78;
int english = 98;
int math = 67;
int sum = chinese + english + math

(A) average = (float)sum/3;
(B) average = sum/3;
(C) average = sum/3.0;
(D) average = (double)sum/3;

```

```
7(A)下列程式碼,定義常數語法是有正確的

(A) #define PI 3.14
(B) typedef PI 3.14
(C) #incldue PI 3.14
(D) int PI = 3.14
```

```
8(B)下列是輸入半徑,計算出圓面積的程式碼,下列空白的區域程式碼,何者正確?

#include <iostream>
#define PI 3.14159
using namespace std;

int main() {
	double radius;
	cout << "請輸入圓半徑:";
	cin >> radius;
	cout << "半徑" << radius << "的圓面積是" << _________;
}

(A) radius * PI
(B) radius * radius * PI
(C) radius / raduis * PI
(D) 2 * radius * PI
```

```
9(C)下列讓使用者輸入被除數(整數)及除數(整數，不可以是零)，程式會顯示兩數相除的商及餘數。何者為正確的

#include <iostream>
using namespace std;

int main() {
	int n=0,m=0;
	cout << "請輸入被除數(整數):";
	cin >> n;
	cout << "請輸入除數(整數,不可以為0):";
	cin >> m;

	___________________________________
	return 0;
}

(A) cout << "商:" << n//m << "餘數:" << n/m << "\n";
(B) cout << "商:" << n%m << "餘數:" << n/m << "\n";
(C) cout << "商:" << n/m << "餘數:" << n%m << "\n";
(D) cout << "商:" << n//m << "餘數:" << n%m << "\n";
```

```
10(D)下列使用的為前置遞增,何種描素為正確?
int x = 1;
int y = ++x;

(A) 程式執行完,x值為1,y值為2
(B) 程式執行完,x值為2,y值為1
(C) 程式執行完,x值為1,y值為1
(D) 程式執行完,x值為2,y值為2
```

```
10(B)下列使用的為後置遞增,何種描素為正確?
int x = 1;
int y = x++;

(A) 程式執行完,x值為1,y值為2
(B) 程式執行完,x值為2,y值為1
(C) 程式執行完,x值為1,y值為1
(D) 程式執行完,x值為2,y值為2
```

```
11(D)下列何者描素為錯誤的?

(A) == 代表內容相等
(B) != 內容不相等
(C) > 大於
(D) >= 小於等於
```

```
12(D)運算子+=下列何者描素為正確?

(A) 關係運算子
(B) 比較運算子
(C) 數學運算子
(D) 複合指定運算子
```

```
13(A)if的單向選擇是那一個?
(A)
if(條件式){
  程式區塊
  ......
}

(B)
if (條件式){
    程式區塊一
}else{
    程式區塊二
}

(C)
if (條件式一){
    程式區塊一
}else if(條件式二){
    程式區塊二
}else if(條件式三){
     程式區塊三
}else{
    程式區塊else
}
```

```
14(B)if的雙向選擇是那一個?
(A)
if(條件式){
  程式區塊
  ......
}

(B)
if (條件式){
    程式區塊一
}else{
    程式區塊二
}

(C)
if (條件式一){
    程式區塊一
}else if(條件式二){
    程式區塊二
}else if(條件式三){
     程式區塊三
}else{
    程式區塊else
}
```

```
15(C)if的多向選擇是那一個?
(A)
if(條件式){
  程式區塊
  ......
}

(B)
if (條件式){
    程式區塊一
}else{
    程式區塊二
}

(C)
if (條件式一){
    程式區塊一
}else if(條件式二){
    程式區塊二
}else if(條件式三){
     程式區塊三
}else{
    程式區塊else
}

```

```
16(D)以下的語法描述，何者正確?

if...
    if...  
    else...
else...
    if...
    else...

(A)單向選擇
(B)雙向選擇
(C)多向選擇
(D)巢狀選擇
```

```
17(C)下列程式碼空白區必需填入何者?
#include <iostream>
using namespace std;

int main() {
	char op;
	int num1 = 20, num2 = 4;
	cout << "num1=20,num2=4\n";
	cout << "請輸入要執行的運算(+-*/):";
	cin >> op;
	switch(op){
	case '+':
		cout << "num1+num2=" << num1+num2 << "\n";
		break;
	case '-':
		cout << "num1-num2=" << num1-num2 << "\n";
		break;
	case '*':
		cout << "num1*num2=" << num1*num2 << "\n";
		break;
	case '/':
		cout << "num1/num2=" << num1/num2 << "\n";
		break;
	_________
		cout << "無法執行運算!\n";
		break;
	}
	return 0;
}

(A) break;
(B) continue;
(C) default:
(D) another:
```

```
18(C)請問以下迴圈執行幾次?
for(int i=2; i<=10; i+=2){

}

(A) 3次
(B) 4次
(C) 5次
(D) 6次
```

```
19(C)以下列空白區塊要填入?

#include <iostream>
using namespace std;

int main() {
	int sum=0, n;
	for(int i=1; i<=_________; i++){
		if(i==7){
			cout << "請輸入星期日的支出:";
		}else{
			cout << "請輸入星期" << i << " 的支出:";
		}

		cin >> n;
		sum += n;
	}

	cout << "本星期的支出為:" << sum << "元\n";
	return 0;
}

(A) "5"
(B) 6
(C) 7
(D) "7"
```

```
20(D)以下內部迴圈的程式區塊總共會被執行幾次?
#include <iostream>
using namespace std;

int main() {
	for(int i=1; i<=9; i++){
		for(int j=1; j<=9; j++){
			cout << i << "*" << j << "=" << i*j << "\t";
		}
		cout << "\n";
	}
	return 0;
}

(A) 64
(B) 100
(C) 72
(D) 81
```
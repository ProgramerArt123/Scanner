int func1(){
	return 99;
}

int func2(){
	return 1234;
}

void func3(){
	printf("I am func3!\n");
}

void func4(){
	return;
}

enum PATTERN_TYPE { 
	PATTERN_TYPE_NONE,
	PATTERN_TYPE_AND = 1,
	PATTERN_TYPE_OR,
	PATTERN_TYPE_STRING,
	PATTERN_TYPE_CHAR
};

struct RECTANGLE{
	double length;
	double width; 
	union TIME{
		int play;
		int study;
	};
	enum PATTERN_TYPE { 
		PATTERN_TYPE_NONE,
		PATTERN_TYPE_AND = 1,
		PATTERN_TYPE_OR,
		PATTERN_TYPE_STRING,
		PATTERN_TYPE_CHAR
	};
};

union TIME{
	int play;
	int study;
	struct RECTANGLE{
		double length;
		double width; 
	};
	enum PATTERN_TYPE { 
		PATTERN_TYPE_NONE,
		PATTERN_TYPE_AND = 1,
		PATTERN_TYPE_OR,
		PATTERN_TYPE_STRING,
		PATTERN_TYPE_CHAR
	};
};

int main(){
		int x = 1 % 2 + 5 * 6 + 9 / 3;
		int y = 1 % 2 + 5 * (6 + 9) / 3;
		int z = x + y;
        printf("x=%d, y=%d, z=%d\n", x, y, z);
		z = 999;
		printf("z=%d\n", z);
		int w = func1();
		printf("w=%d\n", w);
		printf("w2=%d,w=%d\n", func1() + func2() * 3, w);
		int a = w += 99;
		printf("a=%d, w3=%d\n", a, w);
		int c = a = 100;
		printf("a=%d, c=%d\n", a, c);
		c ++;
		printf("c=%d\n", c);
		int d = 123;
		int e = d ++;
		int f = ++ d;
		printf("e=%d,f=%d\n", e, f);
		const int i = 0;
		int const j = 0;
		printf("i=%d,j=%d\n", i, j);
		int k=0,l=123;
		func3();
		int * * * *p;
		int *p2 = &k;
		int*p3;
		return 0;
}

#define B(x)void main(){puts("#define B(x)"x"\n#define X(s)S(s)\n#define S(s)#s\nB(X(B(x)))");}
#define X(s)S(s)
#define S(s)#s
B(X(B(x)))

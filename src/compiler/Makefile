all: voltzc

voltz.yy.cc: voltz.l
	flex -o voltz.yy.cc voltz.l

voltzc: voltz.yy.cc
	clang -o voltzc voltz.yy.cc -ll

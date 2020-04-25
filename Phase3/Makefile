# GNU make手册：http://www.gnu.org/software/make/manual/make.html
# ************ 遇到不明白的地方请google以及阅读手册 *************

# 编译器设定和编译选项
CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -std=c99

# 编译目标：src目录下的所有.c文件
CFILES = $(shell find ./ -name "*.c")
OBJS = $(CFILES:.c=.o)
LFILE = $(shell find ./ -name "*.l")
YFILE = $(shell find ./ -name "*.y")
LFC = $(shell find ./ -name "*.l" | sed s/[^/]*\\.l/lex.yy.c/)
YFC = $(shell find ./ -name "*.y" | sed s/[^/]*\\.y/syntax.tab.c/)
LFO = $(LFC:.c=.o)
YFO = $(YFC:.c=.o)

parser: syntax $(filter-out $(LFO),$(OBJS))
	$(CC) -o parser $(filter-out $(LFO),$(OBJS)) -lfl -ly

syntax: lexical syntax-c
	$(CC) -c $(YFC) -o $(YFO)

lexical: $(LFILE)
	$(FLEX) -o $(LFC) $(LFILE)

syntax-c: $(YFILE)
	$(BISON) -o $(YFC) -d -v $(YFILE)

-include $(patsubst %.o, %.d, $(OBJS))

# 定义的一些伪目标
.PHONY: clean test
test2017a:
	./parser ../Test/Tests_2-2017/A-1.c
	./parser ../Test/Tests_2-2017/A-2.c
	./parser ../Test/Tests_2-2017/A-3.c
	./parser ../Test/Tests_2-2017/A-4.c
	./parser ../Test/Tests_2-2017/A-5.c
	./parser ../Test/Tests_2-2017/A-6.c
	./parser ../Test/Tests_2-2017/A-7.c
	./parser ../Test/Tests_2-2017/A-8.c
	./parser ../Test/Tests_2-2017/A-9.c
	./parser ../Test/Tests_2-2017/A-10.c
	./parser ../Test/Tests_2-2017/A-11.c
	./parser ../Test/Tests_2-2017/A-12.c
	./parser ../Test/Tests_2-2017/A-13.c
	./parser ../Test/Tests_2-2017/A-14.c
	./parser ../Test/Tests_2-2017/A-15.c
	./parser ../Test/Tests_2-2017/A-16.c
	./parser ../Test/Tests_2-2017/A-17.c
	./parser ../Test/Tests_2-2017/A-18.c
	./parser ../Test/Tests_2-2017/A-19.c
	./parser ../Test/Tests_2-2017/A-20.c
test2017b:
	./parser ../Test/Tests_2-2017/B-1.c
	./parser ../Test/Tests_2-2017/B-2.c
test2017c:
	./parser ../Test/Tests_2-2017/C-1.c
	./parser ../Test/Tests_2-2017/C-2.c
test2017d:
	./parser ../Test/Tests_2-2017/D-1.c
	./parser ../Test/Tests_2-2017/D-2.c
	./parser ../Test/Tests_2-2017/D-3.c
test2017e:
	./parser ../Test/Tests_2-2017/E-3.c
test2019a:
	./parser ../Test/Tests_2-2019/A-1.c
	./parser ../Test/Tests_2-2019/A-2.c
	./parser ../Test/Tests_2-2019/A-3.c
	./parser ../Test/Tests_2-2019/A-4.c
	./parser ../Test/Tests_2-2019/A-5.c
	./parser ../Test/Tests_2-2019/A-6.c
	./parser ../Test/Tests_2-2019/A-7.c
	./parser ../Test/Tests_2-2019/A-8.c
	./parser ../Test/Tests_2-2019/A-9.c
	./parser ../Test/Tests_2-2019/A-10.c
	./parser ../Test/Tests_2-2019/A-11.c
	./parser ../Test/Tests_2-2019/A-12.c
	./parser ../Test/Tests_2-2019/A-13.c
	./parser ../Test/Tests_2-2019/A-14.c
	./parser ../Test/Tests_2-2019/A-15.c
	./parser ../Test/Tests_2-2019/A-16.c
	./parser ../Test/Tests_2-2019/A-17.c
	./parser ../Test/Tests_2-2019/A-18.c
	./parser ../Test/Tests_2-2019/A-19.c
	./parser ../Test/Tests_2-2019/A-20.c
test2019b:
	./parser ../Test/Tests_2-2019/B-1.c
	./parser ../Test/Tests_2-2019/B-2.c
test2019c:
	./parser ../Test/Tests_2-2019/C-1.c
	./parser ../Test/Tests_2-2019/C-2.c	
test2019d:
	./parser ../Test/Tests_2-2019/D-1.c
	./parser ../Test/Tests_2-2019/D-2.c
	./parser ../Test/Tests_2-2019/D-3.c
test2019e:
	./parser ../Test/Tests_2-2019/E-3.c
testsimple:
	./parser ../test_simple/1/1.cmm
	./parser ../test_simple/1/2.cmm
	./parser ../test_simple/1/3.cmm
	./parser ../test_simple/1/4.cmm
	./parser ../test_simple/1/5.cmm
	./parser ../test_simple/1/6.cmm
	./parser ../test_simple/1/7.cmm
	./parser ../test_simple/1/8.cmm
	./parser ../test_simple/1/9.cmm
	./parser ../test_simple/1/10.cmm
	./parser ../test_simple/1/11.cmm
	./parser ../test_simple/1/12.cmm
	./parser ../test_simple/1/13.cmm
	./parser ../test_simple/1/14.cmm
	./parser ../test_simple/1/15.cmm
	./parser ../test_simple/1/16.cmm
	./parser ../test_simple/1/17.cmm
	./parser ../test_simple/2/b5.cmm
	./parser ../test_simple/2/b6.cmm

clean:
	rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -f *~

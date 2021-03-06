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
test:
	./parser ../Test/test1.cmm ../Test/test1.ir
test2017a:
	./parser ../Test/Tests_3-2017/official-A-1.cmm ../output/a1.ir
	./parser ../Test/Tests_3-2017/official-A-2.cmm ../output/a2.ir
	./parser ../Test/Tests_3-2017/official-A-3.cmm ../output/a3.ir
	./parser ../Test/Tests_3-2017/official-A-4.cmm ../output/a4.ir
	./parser ../Test/Tests_3-2017/official-A-5.cmm ../output/a5.ir
test2017b:
	./parser ../Test/Tests_3-2017/official-B-1.cmm ../output/b1.ir
	./parser ../Test/Tests_3-2017/official-B-2.cmm ../output/b2.ir
	./parser ../Test/Tests_3-2017/official-B-3.cmm ../output/b3.ir
test2017c:
	./parser ../Test/Tests_3-2017/official-C-1.cmm ../output/c1.ir
	./parser ../Test/Tests_3-2017/official-C-2.cmm ../output/c2.ir
test2017d:
	./parser ../Test/Tests_3-2017/official-D-1.cmm ../output/d1.ir
test2017e:
	./parser ../Test/Tests_3-2017/official-E1-1.cmm ../output/e11.ir
	./parser ../Test/Tests_3-2017/official-E1-2.cmm ../output/e12.ir
	./parser ../Test/Tests_3-2017/official-E1-3.cmm ../output/e13.ir
	./parser ../Test/Tests_3-2017/official-E2-1.cmm ../output/e21.ir
	./parser ../Test/Tests_3-2017/official-E2-2.cmm ../output/e22.ir
	./parser ../Test/Tests_3-2017/official-E2-3.cmm ../output/e23.ir
testhard:
	./parser ../Test/Tests_hard/8Lab3Hard.0.cmm ../output/8Lab3Hard.0.ir
	./parser ../Test/Tests_hard/8Lab3Hard.1.cmm ../output/8Lab3Hard.1.ir
	./parser ../Test/Tests_hard/8Lab3Hard.2.cmm ../output/8Lab3Hard.2.ir
	./parser ../Test/Tests_hard/impossible1.cmm ../output/impossible1.ir
testnormala:
	./parser ../Test/Tests_3_Normal/Tests/A_1.cmm ../output/a1_normal.ir
	./parser ../Test/Tests_3_Normal/Tests/A_2.cmm ../output/a2_normal.ir
	./parser ../Test/Tests_3_Normal/Tests/A_3.cmm ../output/a3_normal.ir
	./parser ../Test/Tests_3_Normal/Tests/A_4.cmm ../output/a4_normal.ir
	./parser ../Test/Tests_3_Normal/Tests/A_5.cmm ../output/a5_normal.ir
testnormalb:
	./parser ../Test/Tests_3_Normal/Tests/B_1.cmm ../output/b1_normal.ir
	./parser ../Test/Tests_3_Normal/Tests/B_2.cmm ../output/b2_normal.ir
	./parser ../Test/Tests_3_Normal/Tests/B_3.cmm ../output/b3_normal.ir
testnormalc:
	./parser ../Test/Tests_3_Normal/Tests/C_1.cmm ../output/c1_normal.ir
	./parser ../Test/Tests_3_Normal/Tests/C_2.cmm ../output/c2_normal.ir
testnormald:
	./parser ../Test/Tests_3_Normal/Tests/D_1.cmm ../output/d1_normal.ir
testnormale:
	./parser ../Test/Tests_3_Normal/Tests/E1_1.cmm ../output/e1_1_normal.ir
	./parser ../Test/Tests_3_Normal/Tests/E1_2.cmm ../output/e1_2_normal.ir
	./parser ../Test/Tests_3_Normal/Tests/E1_3.cmm ../output/e1_3_normal.ir
	./parser ../Test/Tests_3_Normal/Tests/E2_1.cmm ../output/e2_1_normal.ir
	./parser ../Test/Tests_3_Normal/Tests/E2_2.cmm ../output/e2_2_normal.ir
	./parser ../Test/Tests_3_Normal/Tests/E2_3.cmm ../output/e2_3_normal.ir


clean:
	rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -f *~

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "semantic.h"
#include "intercode.h"

extern void yyrestart(FILE *);
extern int yyparse();
extern int yylineno;

int errorsum;

TreeNode *root;

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
		FILE *fp = fopen(argv[1], "r");
        if(!fp)
        {
            perror(argv[1]);
            return 1;
        }

        errorsum = 0;
        root = NULL;

		yyrestart(fp);
        yylineno = 1;
		yyparse();

        // if(errorsum == 0)
        //     printParsingTree(root, 0);

        semantic_analysis(root);

        generate_intercode(root);

        fclose(fp);
    }
    return 0;
}

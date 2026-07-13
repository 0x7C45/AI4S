%{
int yylex(void);
void yyerror(const char *message);
%}

%%
source:
    /* empty */
    ;
%%

void yyerror(const char *message) {
    (void)message;
}

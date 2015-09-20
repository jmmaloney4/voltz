%{
#include <iostream>
#include "voltzc.h"
using namespace voltzc;
using namespace std;
%}

%%

\n          { return token(token::NEWLINE); }
\t          { return token(TAB); }
' '         { return token(SPACE); }

"//".*\n    { return token(LINE_COMMENT); }
"/*".*"*/"  { return token(BLOCK_COMMENT); }


%%

SECTION     TEXT ;; lalalallala
INPUT OLD_DATA
LOAD OLD_DATA ;; lalalalallala
L1: DIV DOIS
STORE  NEW_DATA
MUL DOIS
STORE TMP_DATA
LOAD OLD_DATA
SUB TMP_DATA
STORE TMP_DATA
OUTPUT TMP_DATA
COPY NEW_DATA,    OLD_DATA
LOAD OLD_DATA
JMPP L1
STOP
SECTION DATA ;; lalalallala
DOIS: CONST 2
OLD_DATA: SPACE+3
TMP_DATA: SPACE
NEW_DATA: SPACE
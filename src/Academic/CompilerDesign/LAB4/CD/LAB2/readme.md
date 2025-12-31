TASK : To generate First Follow Trailing and Leading of a grammar given in a file.

1.Computing First
    -if X is a terminal then FIRST(X) is {X}
    -if X is a non terminal and X->aå is a production then add a to FIRST(X) where å is a string of terminals and non terminals
    -if X is a non terminal and X->e is a production then include e in FIRST(X)
    
    -for a non-terminal starting production if X->Y1Y2..Yk if Y1 is non-terminal then add all symbols from FIRST(Y1) to FIRST(X) (except e)
    -in the above scenario if FIRST(Y1) contains e then add all symbols(except e) from FIRST(Y2) to FIRST(X)
    -in the above scenario if all if FIRST(Yi) contain e then add e to FIRST(X)

2.Computing Follow
    -if S is a start symbol then $ is included in FOLLOW(S)
    -if there is a production A->aBb where a and b are any strings of terminals and non-terminals then
    FIRST(b)(except e) is added to FOLLOW(B)
    -END OF PEODUCTION : if there is a produciton of the form A->aB or A->aBb where FIRST(B) contains e
    then FOLLOW(A) is added to FOLLOW(B)

3.computing leading
    -if there is a production of form A->bad where b is e or a single non terminal then a is in LEADING(A)
    -if there is a production of form A->Ba if a is in LEADING(B) a is in LEADING(A)
:- op(1150, xfx, -:).
:- assert((then(0,0,0))).

p.
r.

r, s, t -: p.
x, y -: z.
s, t -: r.
r, t -: r.

compileRules() :- findall([[X],[Y]], (X-:Y), L),
                    addRules(L).
            
addRules([]).
addRules([[[X],[Y]]|T]):- getNextRule(C),
                            len(X, L),
                            addThen(C, L, Y),
                            addIf(X, C),
                            addRules(T).

addIf((H,T), C) :- !,
                    assert((if(H, C))),
                    addIf(T, C).
addIf((H), C) :- !,
                    assert((if(H, C))).
                            
addThen(C, L, Y):- assert((then(C, L, Y))).

len((_,T), C) :- !,
                    len((T), M),
                    C is M + 1.
len((_), 1) :- !.
            
getNextRule(C) :- findall(X, (then(X,_,_)), L),
                    !,
                    max(L, M),
                    C is M + 1.
getNextRule(0).

max([], 0):- !.
max([H|T], C) :- max(T, C),
                    H < C,
                    !.
max([H|_], H) :- !.

printThen():- findall([X, Y, Z], (then(X,Y,Z)), L),
                writeln(L).
                
printIf():- findall([X, Y], (if(X,Y)), L),
                writeln(L).


:- op(1150, xfx, -:).
:- assert((then(0,0,0))).

%p.
%r.

p -: r.
q -: r.
r, p -: s.

% if P is already a clause, there is nothing left to do
add(P) :- clause(P, true),
            !.
/*
 * if P is not a clause
    then assert it
    for each if clause containing P, decrement its consequence and check if the consequence can be added
 */
add(P) :- assert(P),
            (
                if(P, R),
                then(R, N, C),
                (
                    (
                        0 is N - 1,
                        retract(then(R, N, C)),
                        assert(then(R, 0, C)),
                        add(C)
                    );
                    (
                        M is N - 1,
                        retract(then(R, N, C)),
                        assert(then(R, M, C))
                    )
                ),
                fail
            );
            true.
            
% if P is not a clause, there is nothing left to do
remove(P) :- not(clause(P, true)),
                !.
/*
 * if P is a clause
    then remove it it
    for each if clause containing P, decrement its consequence and check if the consequence can be removed
 */
remove(P) :- retract(P),
            (
                if(P, R),
                then(R, N, C),
                (
                    (
                        1 is N + 1,
                        retract(then(R, N, C)),
                        assert(then(R, 1, C)),
                        (
                            (
                                getSatisfied(C, 0),
                                remove(C)
                            );
                            true
                        )
                    );
                    (
                        M is N + 1,
                        retract(then(R, N, C)),
                        assert(then(R, M, C))
                    )
                ),
                fail
            );
            true.

% compile all the rules
compileRules() :- findall([[X],[Y]], (X-:Y), L),
                    addRules(L).

% if there are no rules to add, finish            
addRules([]).
/* if there are rules to add
 * get the next rule number
 * get the number of antecedents
 * add the then clause
 * add the if clauses
 * add the rest of the rules
 */
addRules([[[X],[Y]]|T]):- getNextRule(C),
                            len(X, L),
                            addThen(C, L, Y),
                            addIf(X, C),
                            addRules(T).

% add the first if rule in the format if(atom, ruleID)
addIf((H,T), C) :- !,
                    assert((if(H, C))),
                    addIf(T, C).
% add the only remaining if rule in the format if(atom, ruleID)
addIf((H), C) :- !,
                    assert((if(H, C))).
                            
% add the then rule as then(ruleID, number of satisfiable atoms, consequence)                            
addThen(C, L, Y):- assert((then(C, L, Y))).

% get the number of clauses that are satisfied, and in which P is the consequence
getSatisfied(P, C) :- findall(R, then(R, 0, P), L),
                        getLength(L, C).
                        
% the length of an empty list is 0
getLength([], 0).
% the length of a list is 1 + the length of the Tail
getLength([_|T], C) :- getLength(T, M),
                        C is 1 + M.

% if there is more than one atom in the list, the length is 1 + the length of the rest of the list
len((_,T), C) :- !,
                    len((T), M),
                    C is M + 1.
% if there is one atom in the list, the length of the list is
len((_), 1) :- !.
            
% get all the then rules and their ID, then sort them and return the next rule number
getNextRule(C) :- findall(X, (then(X,_,_)), L),
                    !,
                    max(L, M),
                    C is M + 1.
getNextRule(0).

% the maximum of an empty list is 0
max([], 0):- !.
% if the Head is less than the maximum of the rest of the string, return the maximum of the rest of the string
max([H|T], C) :- max(T, C),
                    H < C,
                    !.
% if all else fails, then the Head must be the largest number
max([H|_], H) :- !.

printThen():- findall([X, Y, Z], (then(X,Y,Z)), L),
                writeln(L).
                
printIf():- findall([X, Y], (if(X,Y)), L),
                writeln(L).

:- op(1150, xfx, -:).
:- dynamic then/3.
:- dynamic if/2.
:- assert(u(0)).
:- assert(o(0)).

p -: q.
q -: r.
p, q -: s.
r, s -: t.
t -: u.

(a,+) -: (a,+).
(b,+) -: (c,+).
(a,+), (b,+) -: (d,+).
(c,+), (d,+) -: (e,+).
(e,+) -: (f,+).

add(P, Q) :- uadd((P,+)),
                oadd(Q),
                write("Unoptimized: "),
                u(U),
                writeln(U),
                write("Optimized: "),
                o(O),
                writeln(O),
                clear().
            
clear() :- retract(u(_)),
            assert(u(0)),
            retract(o(_)),
            assert(o(0)).
            
incrementUnoptimized() :- retract(u(S)),
                            M is S + 1,
                            assert(u(M)).
            
incrementOptimized() :- retract(o(S)),
                        M is S + 1,
                        assert(o(M)).

/*
 *
 * Unoptimized Rule Format
 *
 */

% if the clause already exists, there is nothing to uadd, so you're done
uadd((X,+)) :- %writeln("-2"),
                clause(X, true),
                !.
% if the clause does not exist, there is nothing to uremove, so you're done
uadd((X,-)) :- %writeln("-1"),
                not(clause(X, true)),
                !.
                        
/*
if the clause doesn't already exist,
    uadd the clause specified
    for every clause in which X exists as positive (i.e., same sign):
        if there are no false predicates (if either Y is not a member of the If, or Y is a clause), uadd the RHS
    for every clause in which X exists as negative (i.e., different sign):
        uremove the RHS
 */
uadd((X,+)) :- !,
                assert(X),
                (
                    (If -: Then),
                    incrementUnoptimized(),
                    (
                        (
                            uamember((X,+), If),
                            not(
                                (
                                    (uamember((Y,+), If),
                                    not(clause(Y, true)))
                                );
                                (
                                    (uamember((Y,-), If),
                                    clause(Y, true))
                                )
                            ),
                            uadd(Then),
                            fail
                        );
                        (
                            uamember((X,-), If),
                            uremove(Then)
                        )
                    ); 
                    true
                ).

/*
if the clause exists,
    uremove the clause specified
    for every clause in which X exists as negative (i.e., same sign):
        if there are no false predicates (if either Y is not a member of the If, or Y is a clause), uadd the RHS
    for every clause in which X exists as positive (i.e., different sign):
        uremove the RHS
 */                
uadd((X,-)) :- !,
                retract(X),
                (
                    (If -: Then),
                    (
                        (
                            uamember((X,-), If),
                            not(
                                (
                                    (uamember((Y,+), If),
                                    not(clause(Y, true)))
                                ) ;
                                (
                                    (uamember((Y,-), If),
                                    clause(Y, true))
                                )
                            ),
                            uadd(Then),
                            fail
                        );
                        (
                            uamember((X,+), If),
                            uremove(Then)
                        )
                    ); 
                    true
                ).

uremove((X,-)) :- assert(X).                        
uremove((X,+)) :- retract(X).
                        
/*
Case 1: the member is not known, and is assigned the elements in the list
 */
% if there is more than one element remaining, X is the head, or part of the tail
/*uamember((X,S), ((P,S), T)) :- var(X),
                                !,
                                (X = P;
                                uamember((X,S), T)).*/
uamember((X,S), ((P,S), T)) :- var(X),
                            !,
                            (
                                uamember((X,S), T);
                                (X=P)
                            ).
% if there is only one element remaining, then it is the member
uamember((X,S), ((X,S))) :- var(X),
                        !.
                   
/*
Case 2: the member is known, and is tested within the list
 */
% if X is the only element remaining, then it is a member
uamember((X,S), ((X,S))):- %writeln("1"),
                            not(var(X)),
                            !.
% if X is at the head of the list, then it is a member
uamember((X,S), ((X,S),_)) :- %writeln("2"),
                                not(var(X)),
                                !.
% if X is not at the head, then check if it's in T, the tail
uamember(X, ((_,_), T)) :- %writeln("3"),
                            not(var(X)),
                            !,
                            uamember(X, T).

/*
 *
 * Optimized Rule Format
 *
 */

% if P is already a clause, there is nothing left to do
oadd(P) :- clause(P, true),
            !.
/*
 * if P is not a clause
    then assert it
    for each if clause containing P, decrement its consequence and check if the consequence can be added
 */
oadd(P) :- assert(P),
            (
                if(P, R),
                then(R, N, C),
                incrementOptimized(),
                (
                    (
                        0 is N - 1,
                        retract(then(R, N, C)),
                        assert(then(R, 0, C)),
                        oadd(C)
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
oremove(P) :- not(clause(P, true)),
                !.
/*
 * if P is a clause
    then oremove it it
    for each if clause containing P, decrement its consequence and check if the consequence can be removed
 */
oremove(P) :- retract(P),
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
                                oremove(C)
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

% if there are no rules to oadd, finish            
addRules([]).
/* if there are rules to oadd
 * get the next rule number
 * get the number of antecedents
 * oadd the then clause
 * oadd the if clauses
 * oadd the rest of the rules
 */
addRules([[[X],[Y]]|T]):- getNextRule(C),
                            len(X, L),
                            addThen(C, L, Y),
                            addIf(X, C),
                            addRules(T).

% oadd the first if rule in the format if(atom, ruleID)
addIf((H,T), C) :- !,
                    assert((if(H, C))),
                    addIf(T, C).
% oadd the only remaining if rule in the format if(atom, ruleID)
addIf((H), C) :- !,
                    assert((if(H, C))).
                            
% oadd the then rule as then(ruleID, number of satisfiable atoms, consequence)                            
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

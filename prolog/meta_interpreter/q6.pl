:- op(1150, xfx, -:).

p(X,Y), p(Y,Z) -: gp(X,Z).
s(X, Y), s(Y, Z) -: s(X, Z).
gp(X, _) -: old(X).
                    
% if the clause already exists, there is nothing to add, so you're done
cadd(X) :- clause(X, true),
            !.
/*
if the clause doesn't already exist,
    add the clause specified
    for every clause in which X exists, if there are no false predicates (if either Y is not a member of the If, or Y is a clause),
    add the RHS
    !(A n !B) = !A v B
 */
cadd(X) :- assert(X),
            (
                (If -: Then),
                amember(X, If),
                If,
                cadd(Then),
                fail
            );
            true.
                 
% if the clause already exists, there is nothing to remove, so you're done       
cremove(X) :- not(clause(X, true)),
                !.
                
/*
if the clause exists,
    count the number of Then clauses that are satisfied and successfully implies the given caluse
    if there is just one (the one being deleted), remove the clause specified
 */
cremove(X) :- retract(X),
                (
                    (If -: Then),
                    amember(X, If),
                    retract(Then),
                    fail
                );
                true.

/*
Case 1: the member is not known, and is assigned the elements in the list
 */
% if there is more than one element remaining, X is the head, or part of the tail
amember(X, (H, T)) :- var(X),
                        !,
                        (
                            (H,
                            X = H);
                            amember(X, T)
                        ).
% if there is only one element remaining, then it is the member
amember(X, (A)) :- var(X),
                    A,
                    X = A,
                    !.
                   
/*
Case 2: the member is known, and is tested within the list
 */ 
% if the functor of element at the head of the list is the same as that the test element, then the test element is a member
amember(X, (P, _)) :- not(var(X)),
                        functor(P, H, A),
                        functor(X, H, A),
                        !.
% if X is not at the head, then check if it's in T, the tail
amember(X, (_, T)) :- not(var(X)),
                        !,
                        amember(X, T).
% if there is only one element remaining, and the functor of that element is the same as that the test element, then the test element is a member
amember(X, (P)):- not(var(X)),
                    !,
                    functor(P, H, A),
                    functor(X, H, A).
                    
%satisfiable(X, C) :- findall(If, ((If -: X), If), L),
%                        writeln(L).
                    
printIfThen() :- (
                        (If -: Then),
                        writeln(If -: Then),
                        fail
                    );
                    true.
                
valued([]).    
valued([H|T]) :- not(var(H)),
                    valued(T).
                    
printSiblings() :- (
                        s(X,Y),
                        writeln(s(X,Y)),
                        fail
                    );
                    true.

printParents() :- (
                        p(X,Y),
                        writeln(p(X,Y)),
                        fail
                    );
                    true.
                    
printGrandParents() :- (
                        gp(X,Y),
                        writeln(gp(X,Y)),
                        fail
                    );
                    true.

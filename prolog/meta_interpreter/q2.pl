:- op(1150, xfx, -:).

% placeholder rules
(f,+) -: (h,+).
(f,-) -: (i,+).
(e,+), (f,-) -: (g,+).

% if the clause already exists, there is nothing to add, so you're done
add((X,+)) :- clause(X, true),
                !.
% if the clause does not exist, there is nothing to remove, so you're done
add((X,-)) :- not(clause(X, true)),
                !.
                        
/*
 * if the clause doesn't already exist, add the clause specified
 * for every clause in which X exists as positive (i.e., same sign),
 * if there are no false predicates (if either Y is not a member of the If, or Y is a clause), add the RHS
 * for every clause in which X exists as negative (i.e., different sign),
 * remove the RHS
 */
add((X,+)) :- !,
                assert(X),
                (
                    (If -: Then),
                    (
                        (
                            amember((X,+), If),
                            not(
                                (
                                    (amember((Y,+), If),
                                    not(clause(Y, true)))
                                );
                                (
                                    (amember((Y,-), If),
                                    clause(Y, true))
                                )
                            ),
                            add(Then),
                            fail
                        );
                        (
                            amember((X,-), If),
                            remove(Then)
                        )
                    ); 
                    true
                ).

/*
 * if the clause exists, remove the clause specified
 * for every clause in which X exists as negative (i.e., same sign),
 * if there are no false predicates (if either Y is not a member of the If, or Y is a clause), add the RHS
 * for every clause in which X exists as positive (i.e., different sign),
 * remove the RHS
 */                
add((X,-)) :- !,
                retract(X),
                (
                    (If -: Then),
                    (
                        (
                            amember((X,-), If),
                            not(
                                (
                                    (amember((Y,+), If),
                                    not(clause(Y, true)))
                                ) ;
                                (
                                    (amember((Y,-), If),
                                    clause(Y, true))
                                )
                            ),
                            add(Then),
                            fail
                        );
                        (
                            amember((X,+), If),
                            remove(Then)
                        )
                    ); 
                    true
                ).

remove((X,-)) :- assert(X).                        
remove((X,+)) :- retract(X).
                        
/*
 * Case 1: the member is not known, and is assigned the elements in the list
 */
% if there is more than one element remaining, X is the head, or part of the tail
amember((X,S), ((P,S), T)) :- var(X),
                                !,
                                (
                                    amember((X,S), T);
                                    (X=P)
                                ).
% if there is only one element remaining, then it is the member
amember((X,S), ((X,S))) :- var(X),
                         !.
                   
/*
 * Case 2: the member is known, and is tested within the list
 */
% if X is the only element remaining, then it is a member
amember((X,S), ((X,S))):- not(var(X)),
                            !.
% if X is at the head of the list, then it is a member
amember((X,S), ((X,S),_)) :- not(var(X)),
                                !.
% if X is not at the head, then check if it's in T, the tail
amember(X, ((_,_), T)) :- not(var(X)),
                            !,
                            amember(X, T).

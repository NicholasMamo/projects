:- op(1150, xfx, -:).

% placeholder rules
p -: q.
r, s, t -: u.
q -: t.
p -: v.
                    
% if the clause already exists, there is nothing to add, so you're done
add_positive_slow(X) :- clause(X, true),
                        !.
/*
 * if the clause doesn't already exist,
 * add the clause specified
 * for every clause in which X exists,
 * if there are no false predicates (if either Y is not a member of the If, or Y is a clause),
 * add the RHS
 */
add_positive_slow(X) :- assert(X),
                        ((If -: Then),
                        amember(X, If),
                        not((amember(Y, If),
                                not(clause(Y, true)))),
                        add_positive_slow(Then),
                        fail) ; true.

/*
 * Case 1: the member is not known, and is assigned the elements in the list
 */
% if there is only one element remaining, then it is the member
amember(X, (X)) :- var(X), !.
% if there is more than one element remaining, X is the head, or part of the tail
amember(X, (H, T)) :- var(X),
                        !,
                        (X = H;
                            amember(X, T)).
                   
/*
 * Case 2: the member is known, and is tested within the list
 */
% if X is the only element remaining, then it is a member
amember(X, (X)):- not(var(X)),
                    !.
% if X is at the head of the list, then it is a member
amember(X, (X, _)) :- not(var(X)),
                        !.
% if X is not at the head, then check if it's in T, the tail
amember(X, (_, T)) :- not(var(X)),
                        !,
                        amember(X, T).

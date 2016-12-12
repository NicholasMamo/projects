:- op(1150, xfx, -:).
:- dynamic c/3.

:- assert(c(1, 1, x)).
:- assert(c(1, 2, x)).
:- assert(c(1, 3, o)).
:- assert(c(2, 1, o)).
:- assert(c(2, 2, o)).
:- assert(c(2, 3, x)).
:- assert(c(3, 1, x)).
:- assert(c(3, 2, x)).
:- assert(c(3, 3, o)).

% Winning Conditions
c(R1, C1, S), c(R1, C2, S), c(R1, C3, S), removeList([C1, C2, C3], [1, 2, 3], []) -: win(S).
c(R1, C1, S), c(R2, C1, S), c(R3, C1, S), removeList([R1, R2, R3], [1, 2, 3], []) -: win(S).
c(R1, C1, S), c(R2, C2, S), c(R3, C3, S), removeList([C1, C2, C3], [1, 2, 3], []), removeList([R1, R2, R3], [1, 2, 3], []), (4 is C1 + R1), (4 is C2 + R2), (4 is C3 + R3) -: win(S).
c(R1, C1, S), c(R2, C2, S), c(R3, C3, S), removeList([C1, C2, C3], [1, 2, 3], []), removeList([R1, R2, R3], [1, 2, 3], []), (C1 is R1), (C2 is R2), (C3 is R3) -: win(S).

% Horizontal
c(R1, C1, S), c(R1, C2, S), removeList([C1, C2], [1, 2, 3], [C3]) -: c(R1, C3, S).

% Vertical
c(R1, C1, S), c(R2, C1, S), removeList([R1, R2], [1, 2, 3], [R3]) -: c(R3, C1, S).

% Diagonals
c(R1, C1, S), c(R2, C2, S), removeList([R1, R2], [1, 2, 3], [R3]), removeList([C1, C2], [1, 2, 3], [C3]), (4 is C3 + R3) -: c(R3, C3, S).
c(R1, C1, S), c(R2, C2, S), removeList([R1, R2], [1, 2, 3], [R3]), removeList([C1, C2], [1, 2, 3], [C3]), (C3 is R3) -: c(R3, C3, S).

clear() :- (clause(c(R, C, S), true),
            retract(c(R, C, S)),
            false);
            true.

% If there is an established winning condition, there is nothing that can be done
play(_) :- (If -: win(S)),
            If,
            !,
            write("Player "),
            write(S),
            write(" Won!").
                
% If there is a satisfiable winning condition, then win the game!
play(S) :- (If -: c(R, C, S)),
            If,
            not(clause(c(R, C, _), true)),
            assert(c(R, C, S)),
            !,
            write("Placed "),
            write(S),
            write(" at ("),
            write(R),
            write(", "),
            write(C),
            write(")"),
            nl,
            print(),
            play(S).
            
% If there is a blocking condition, then block the other player!
play(S) :- (If -: c(R, C, T)),
            If,
            not(clause(c(R, C, _), true)),
            not(T==S),
            assert(c(R, C, S)),
            !,
            write("Placed "),
            write(S),
            write(" at ("),
            write(R),
            write(", "),
            write(C),
            write(")"),
            nl,
            print().
            
% If there is space on the board, then place the given symbol wherever there is space
play(S) :- getPlays(P),
            P < 9,
            !,
            getEmpty(L),
            getLength(L, Len),
            random_between(1, Len, Random),
            getElementAt(Random, L, (R, C)),
            assert(c(R, C, S)),
            write("Placed "),
            write(S),
            write(" at ("),
            write(R),
            write(", "),
            write(C),
            write(")"),
            nl,
            print().
            
% If the board is full, then there's nothing that can be done!
play(_) :- !,
            write("The board is full!"),
            nl,
            print().
            
getElementAt(1, [H|_], H) :- !.
getElementAt(N, [_|T], C) :- N > 1,
                                M is N - 1,
                                getElementAt(M, T, C).
            
getEmpty(L) :- getEmptyRow(1, T1),
                getEmptyRow(2, T2),
                appendList(T1, T2, Temp),
                getEmptyRow(3, T3),
                appendList(Temp, T3, L).
                
getEmptyRow(R, T) :- getEmptyRowColumn(R, 1, T1),
                        getEmptyRowColumn(R, 2, T2),
                        appendList(T1, T2, Temp),
                        getEmptyRowColumn(R, 3, T3),
                        appendList(Temp, T3, T).
                    
getEmptyRowColumn(R, C, [(R, C)]) :- not(clause(c(R, C, _), true)),
                                !.                                
getEmptyRowColumn(_, _, []) :- !.

appendList([], L, L).
appendList([H|T], L, [H|Temp]) :- appendList(T, L, Temp).
            
getPlays(C) :- findall(S, c(_, _, S), L),
                getLength(L, C).
                
getLength([], 0).
getLength([_|T], C):- getLength(T, M),
                        C is M + 1.
                    
removeElement(_, [], []) :- !.
removeElement(E, [E|T], L) :- !,
                                removeElement(E, T, L).
removeElement(E, [H|T], [H|TL]) :- !,
                                    removeElement(E, T, TL).
                    
removeList([], A, A).
removeList([H|T], A, L) :- removeElement(H, A, TL),
                            removeList(T, TL, L).
                            
print() :- printRow(1),
            nl,
            printRow(2),
            nl,
            printRow(3),
            nl.
            
printRow(R) :- printRowColumn(R, 1),
                !,
                printRowColumn(R, 2),
                !,
                printRowColumn(R, 3),
                !.
                
printRowColumn(R, C) :- clause(c(R, C, _), true),
                        !,
                        c(R, C, S),
                        write(S),
                        write("  ").
                        
printRowColumn(_, _) :- write("   "),
                        !.

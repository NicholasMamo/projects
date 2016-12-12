:- use_module(http).

process(Question, Answer) :- q(Semantic, Question, []),
								interpret(Semantic, Answer),
								!.
								
process(_, "incorrect input").
								
interpret(bool(Semantic), yes) :- removeFree(Semantic, Processed),
									call(Processed),
									!.
interpret(bool(_), no) :- !.

interpret(wh(which(Semantic)), Answer) :- extract(Semantic, 1, Variable),
											removeFree(Semantic, Processed),
											compileList(Processed, Variable, Compiled),
											removeDuplicates(Compiled, Distinct),
											stringify(Distinct, Answer),
											!.
									
interpret(wh(when(Semantic)), Answer) :- extractFromEnd(Semantic, 1, Variable),
											removeFree(Semantic, Processed),
											not(functor(Processed, belong, _)),
											compileList(Processed, Variable, Compiled),
											removeDuplicates(Compiled, Distinct),
											stringify(Distinct, Answer),
											!.
											
interpret(wh(where(Semantic)), Answer) :- extract(Semantic, 1, Variable),
											removeFree(Semantic, Processed),
											not(functor(Processed, belong, _)),
											compileList(Processed, Variable, Compiled),
											removeDuplicates(Compiled, Distinct),
											stringify(Distinct, Answer),
											!.
											
interpret(how(Semantic), Answer) :- extract(Semantic, 1, Variable),
										removeFree(Semantic, Processed),
										compileList(Processed, Variable, Compiled), % duplicates are important here
										count(Compiled, Answer),
										!.
										
interpret(_, "incorrect input"). 

% sentence types

q(bool(Semantic)) --> bool(Semantic). % yes/no questions
q(wh(Semantic)) --> wh(Semantic). % which/when/where questions
q(how(Semantic)) --> howq(Semantic). % how many questions

wh(which(Semantic)) --> whichq(Semantic).
wh(when(Semantic)) --> whenq(Semantic).
wh(where(Semantic)) --> whereq(Semantic).

% TYPE 1
bool(Semantic) --> ap(N), np(N, X), cvp(p, Verb), {descriptive(N, X), reduce(Verb, X, Semantic)}.

% TYPE 2
whichq(Semantic) --> which(), snp(N), cvp(N, Semantic). % there is no open variable because the query won't include a flight number

% TYPE 3
whenq(Semantic) --> when(), ap(N), np(N, X), cvp(p, Verb), {descriptive(N, X), reduce(Verb, X, Semantic)}.

% TYPE 4
whereq(Semantic) --> where(), ap(N), np(N, X), svp(p, Verb), pp(P), {agree(Verb, P), descriptive(N, X), reduce(Verb, X, 2, Semantic)}.

% TYPE 5
howq(Semantic) --> hp(), snp(p), cvp(p, Semantic).

% grammar

ap(N) --> a(N).

hp() --> how(), quantifier().

np(N, _) --> snp(N). % a plural noun phrase may only be made up of a simple, plural noun phrase
np(N, F) --> cnp(N, F). % a noun phrase may be made up of a compound noun phrase

snp(N) --> n(N). % a simple noun phrase is only made up of one noun
snp(F) --> [F].
cnp(s, F) --> n(s), [F]. % a compound noun phrase is made up of a singular noun and another noun describing it

pp(P) --> p(P).

cvp(N, Semantic) --> v(N, V), pp(P), snp(Noun), {agree(V, P), reduce(V, Noun, Semantic)}. % a compound verb phrase is made up of a verb and a noun
svp(N, Semantic) --> v(N, Semantic).

% lexicon

a(s) --> [does].
a(p) --> [do].

agree(_^_^_^arrive(_, _, _), from).
agree(_^_^belong(_, _), to).
agree(_^_^_^depart(_, _, _), from).
agree(_^_^_^go(_, _, _), to).
agree(_^_^_^leave(_, _, _), from).

how() --> [how].

n(s) --> [airline].
n(s) --> [flight].
n(s) --> [plane].
n(p) --> [airlines].
n(p) --> [flights].
n(p) --> [planes].

p(to) --> [to].
p(from) --> [from].

quantifier() --> [many].

v(s, Origin^Flight^Time^arrive(Flight, Origin, Time)) --> [arrives].
v(s, Airline^Flight^belong(Flight, Airline)) --> [belongs].
v(s, Origin^Flight^Time^depart(Flight, Origin, Time)) --> [departs].
v(s, Destination^Flight^Time^go(Flight, Destination, Time)) --> [goes].
v(s, Origin^Flight^Time^leave(Flight, Origin, Time)) --> [leaves].
v(p, Origin^Flight^Time^arrive(Flight, Origin, Time)) --> [arrive].
v(p, Origin^Flight^Time^depart(Flight, Origin, Time)) --> [depart].
v(p, Airline^Flight^belong(Flight, Airline)) --> [belong].
v(p, Destination^Flight^Time^go(Flight, Destination, Time)) --> [go].
v(p, Origin^Flight^Time^leave(Flight, Origin, Time)) --> [leave].

which() --> [which].
when() --> [when].
where() --> [where].

% supporting functions

addToList([], _, _).
addToList([Head|Tail], Added, [Head|New]) :- addToList(Tail, Added, New).

compileList(Predicate, Variable, Values) :- findall(Variable, Predicate, Values).

copy(A, A).

count([], 0).
count([_|T], C) :- count(T, N),
					C is N + 1.
					
countFree(_^Rest, Count) :- !,
							countFree(Rest, Temp),
							Count is Temp + 1.
countFree(_, 1).
					
descriptive(s, X) :- !, not(var(X)). % a descriptive element is only needed if the noun is singular, for example, flight X
descriptive(_, _). % if the noun is plural, then the descriptive elements may be included

extract(_, 0, _) :- fail.
extract(Variable^_, 1, Variable) :- !.
extract(_^Rest, Order, Variable) :- Temp is Order - 1,
											extract(Rest, Temp, Variable),
											!.
											
extractFromEnd(List, Order, Variable) :- !,
											countFree(List, Count),
											Index is Count - Order,
											extract(List, Index, Variable).
											
ingrain(_^F, F).

inList([], _) :- fail.
inList([Element|_], Element).
inList([_|Tail], Element) :- inList(Tail, Element).
					
reduce(X^F, X, F) :- not(var(X)).
reduce(F, _, F).

reduce(A, R, _, A) :- var(R), !.
reduce(X^F, R, 1, F) :- reduce(X^F, R, F).
reduce(X^F, R, C, Result) :- Temp is C - 1,
								reduce(F, R, Temp, Reduced),
								Result = X^Reduced.
								
removeDuplicates([], []).
removeDuplicates([Head|Tail], [Head|Temp]) :- not(inList(Tail, Head)),
												removeDuplicates(Tail, Temp),
												!.
removeDuplicates([_|Tail], Reduced) :- removeDuplicates(Tail, Reduced).

removeFree(_^F, H) :- !,
						removeFree(F, H).
removeFree(F, F).

stringify([], "none").
stringify([Head], Head).
stringify([Head, Tail], String) :- string_concat(Head, " AND ", Temp),
									string_concat(Temp, Tail, String).
stringify([Head|Tail], String) :- stringify(Tail, Temp),
									string_concat(Head, ", ", TempString),
									string_concat(TempString, Temp, String).

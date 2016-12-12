:- use_module(http).

% sentence types

q --> bool. % yes/no questions
q --> wh. % which/when/where questions
q --> howq. % how many questions

wh --> whichq.
wh --> whenq.
wh --> whereq.

% TYPE 1
bool --> ap(N), np(N, X), cvp(p), {descriptive(N, X)}.

% TYPE 2
whichq --> whp(), snp(N), cvp(N). % there is no open variable because the query won't include a flight number

% TYPE 3
whenq --> whp(N), np(N, X), cvp(p), {descriptive(N, X)}.

% TYPE 4
whereq --> whp(N), np(N, X), svp(p), {descriptive(N, X)}.

% TYPE 5
howq --> hp(), snp(p), cvp(p).

% grammar

ap(N) --> a(N).

hp() --> how(), quantifier().

np(N, _) --> snp(N). % a plural noun phrase may only be made up of a simple, plural noun phrase
np(N, F) --> cnp(N, F). % a noun phrase may be made up of a compound noun phrase

snp(N) --> n(N). % a simple noun phrase is only made up of one noun
snp(F) --> [F].
cnp(s, F) --> n(s), [F]. % a compound noun phrase is made up of a singular noun and another noun describing it

pp(P) --> p(P).

cvp(N) --> v(N, V), pp(P), snp(_), {agree(V, P)}. % a compound verb phrase is made up of a verb and a noun
svp(N) --> v(N, _).

whp() --> which().
whp(N) --> when(), ap(N).
whp(N) --> where(), ap(N).

% lexicon

a(s) --> [does].
a(p) --> [do].

agree(arrive, from).
agree(belong, to).
agree(go, to).
agree(leave, from).

how() --> [how].

n(s) --> [flight].
n(s) --> [plane].
n(p) --> [flights].
n(p) --> [planes].

p(to) --> [to].
p(from) --> [from].

quantifier() --> [many].

v(s, arrive) --> [arrives].
v(s, belong) --> [belongs].
v(s, go) --> [goes].
v(s, leave) --> [leaves].
v(p, arrive) --> [arrive].
v(p, belong) --> [belong].
v(p, go) --> [go].
v(p, leave) --> [leave].

which() --> [which].
when() --> [when].
where() --> [where].

% supporting functions

descriptive(s, X) :- !, not(var(X)). % a descriptive element is only needed if the noun is singular, for example, flight X
descriptive(_, _). % if the noun is plural, then the descriptive elements may be included

count([], 0).
count([_|T], C) :- count(T, N),
					C is N + 1.

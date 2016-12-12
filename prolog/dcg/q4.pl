% grammar
s(s(NP, OPTREL)) --> np(NP), optrel(OPTREL).

np(np(d(N, DET), ap(AP), n(N, NOUN))) --> d(d(N, DET)), ap(AP), n(n(N, NOUN)).
vp(vp(V, NP)) --> v(V), np(NP).
vp(vp(V)) --> v(V).
ap(ap(A, AP)) --> a(A), !, ap(AP).
ap(a()) --> [].
optrel(optrel()) --> [].
optrel(optrel(REL, VP)) --> rel(REL), vp(VP).

d(d(N, W)) --> [W], {lex(W, d, N)}.
n(n(N, W)) --> [W], {lex(W, n, N)}.
v(W) --> [W], {lex(W, v)}.
a(W) --> [W], {lex(W, a)}.
rel(W) --> [W], {lex(W, rel)}.

% lexicon
lex(the, d, singular).
lex(the, d, plural).
lex(a, d, singular).
lex(this, d, singular).
lex(that, d, singular).
lex(dog, n, singular).
lex(cat, n, singular).
lex(dogs, n, plural).
lex(cats, n, plural).
lex(brown, a).
lex(white, a).
lex(small, a).
lex(big, a).
lex(that, rel).
lex(which, rel).
lex(bit, v).
lex(barked, v).

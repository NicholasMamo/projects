% grammar
s --> np, optrel.

np --> d(N), ap, n(N).
vp --> v, np.
vp --> v.
ap --> a, !, ap.
ap --> [].
optrel --> [].
optrel --> rel, vp.

d(N) --> [W], {lex(W, d, N)}.
n(N) --> [W], {lex(W, n, N)}.
v --> [W], {lex(W, v)}.
a --> [W], {lex(W, a)}.
rel --> [W], {lex(W, rel)}.

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

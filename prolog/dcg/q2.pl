% grammar
s --> np, !.

np --> d(N), ap, n(N).
ap --> a, !, ap.
ap --> [].

d(N) --> [W], {lex(W, d, N)}.
n(N) --> [W], {lex(W, n, N)}.
a --> [W], {lex(W, a)}.

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

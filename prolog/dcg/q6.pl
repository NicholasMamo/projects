% grammar
s --> np(N), optrel(N), vp(N).

np --> ap, n(_).
np --> d(N), ap, n(N).
np(N) --> d(N), ap, n(N).
vp(N) --> v(N), np.
vp --> v.
ap --> a, !, ap.
ap --> [].
optrel(_) --> [].
optrel(N) --> rel, vp(N).

d(N) --> [W], {lex(W, d, N)}.
n(N) --> [W], {lex(W, n, N)}.
v(N) --> [W], {lex(W, v, N)}.
a --> [W], {lex(W, a)}.
rel --> [W], {lex(W, rel)}.

% lexicon
lex(the, d, singular).
lex(the, d, plural).
lex(a, d, singular).
lex(this, d, singular).
lex(that, d, singular).

lex(policeman, n, singular).
lex(crime, n, singular).
lex(praise, n, singular).
lex(policemen, n, plural).
lex(crimes, n, plural).

lex(solves, v, singular).
lex(receives, v, singular).
lex(solve, v, plural).
lex(receive, v, plural).

lex(that, rel).
lex(which, rel).
